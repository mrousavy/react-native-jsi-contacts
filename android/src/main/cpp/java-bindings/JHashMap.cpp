//
// Created by Marc Rousavy on 25.06.21.
//
// Copied from https://github.com/mrousavy/react-native-vision-camera/blob/main/android/src/main/cpp/java-bindings/JHashMap.cpp

#include "JHashMap.h"

#include <jni.h>
#include <fbjni/fbjni.h>


namespace facebook {
namespace jni {

template <typename K, typename V>
local_ref<JHashMap<K, V>> JHashMap<K, V>::create() {
  return JHashMap<K, V>::newInstance();
}

} // namespace jni
} // namespace facebook
