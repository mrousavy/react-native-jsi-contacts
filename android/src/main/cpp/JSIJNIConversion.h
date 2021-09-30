//
// Created by Marc Rousavy on 22.06.21.
//
// Copied from https://github.com/mrousavy/react-native-vision-camera/blob/main/android/src/main/cpp/JSIJNIConversion.h

#pragma once

#include <jsi/jsi.h>
#include <jni.h>
#include <fbjni/fbjni.h>

namespace vision {

namespace JSIJNIConversion {

using namespace facebook;

jsi::Value convertJNIObjectToJSIValue(jsi::Runtime& runtime, const jni::local_ref<jobject>& object);

} // namespace JSIJNIConversion

} // namespace vision
