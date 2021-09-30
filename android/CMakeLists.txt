cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "react-native-jsi-contacts")
set (BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

file (GLOB LIBFBJNI_INCLUDE_DIR "${BUILD_DIR}/fbjni-*-headers.jar/")

include_directories(
        "${LIBFBJNI_INCLUDE_DIR}"
        "${NODE_MODULES_DIR}/react-native/React"
        "${NODE_MODULES_DIR}/react-native/React/Base"
        "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
        "${NODE_MODULES_DIR}/react-native/ReactCommon/callinvoker"
        "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni"
)

add_library(jsicontacts  # <-- Library name
        SHARED
        src/main/cpp/JSIContacts.cpp
        src/main/cpp/ThreadPool.cpp
        src/main/cpp/nativeInstall.cpp
)

set_target_properties(
        jsicontacts PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)

file (GLOB LIBRN_DIR "${BUILD_DIR}/react-native-0*/jni/${ANDROID_ABI}")

find_library(
        log-lib
        log
)
find_library(
        FBJNI_LIB
        fbjni
        PATHS ${LIBRN_DIR}
        NO_CMAKE_FIND_ROOT_PATH
)
find_library(
        REACT_NATIVE_JNI_LIB
        reactnativejni
        PATHS ${LIBRN_DIR}
        NO_CMAKE_FIND_ROOT_PATH
)

target_link_libraries(
        jsicontacts
        ${log-lib}
        ${REACT_NATIVE_JNI_LIB}
        ${FBJNI_LIB}
        android
)
