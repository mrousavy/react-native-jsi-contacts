//
// Created by Marc Rousavy on 22.06.21.
//
// Copied from https://github.com/mrousavy/react-native-vision-camera/blob/main/android/src/main/cpp/JSIJNIConversion.cpp

#include "JSIJNIConversion.h"

#include <jsi/jsi.h>
#include <jni.h>
#include <fbjni/fbjni.h>
#include <android/log.h>

#include <string>
#include <utility>

#include <react/jni/NativeMap.h>
#include <react/jni/ReadableNativeMap.h>
#include <react/jni/WritableNativeMap.h>

#include <jsi/JSIDynamic.h>
#include <folly/dynamic.h>

#include "java-bindings/JArrayList.h"
#include "java-bindings/JHashMap.h"
#include "java-bindings/JContact.h"
#include "ContactHostObject.h"

namespace vision {

using namespace facebook;

jsi::Value JSIJNIConversion::convertJNIObjectToJSIValue(jsi::Runtime &runtime, const jni::local_ref<jobject>& object) {
  if (object->isInstanceOf(jni::JBoolean::javaClassStatic())) {
    // Boolean

    static const auto getBooleanFunc = jni::findClassLocal("java/lang/Boolean")->getMethod<jboolean()>("booleanValue");
    auto boolean = getBooleanFunc(object.get());
    return jsi::Value(boolean == true);

  } else if (object->isInstanceOf(jni::JDouble::javaClassStatic())) {
    // Double

    static const auto getDoubleFunc = jni::findClassLocal("java/lang/Double")->getMethod<jdouble()>("doubleValue");
    auto d = getDoubleFunc(object.get());
    return jsi::Value(d);

  } else if (object->isInstanceOf(jni::JInteger::javaClassStatic())) {
    // Integer

    static const auto getIntegerFunc = jni::findClassLocal("java/lang/Integer")->getMethod<jint()>("intValue");
    auto i = getIntegerFunc(object.get());
    return jsi::Value(i);

  } else if (object->isInstanceOf(jni::JString::javaClassStatic())) {
    // String

    return jsi::String::createFromUtf8(runtime, object->toString());

  } else if (object->isInstanceOf(mrousavy::JContact::javaClassStatic())) {
      // Contact

      auto contact = static_ref_cast<mrousavy::JContact>(object);
      auto hostObject = std::make_shared<mrousavy::ContactHostObject>(contact);
      return jsi::Object::createFromHostObject(runtime, hostObject);

  } else if (object->isInstanceOf(mrousavy::JContact::JItem::javaClassStatic())) {
      // Contact.Item

      auto item = static_ref_cast<mrousavy::JContact::JItem>(object);

      jsi::Object result(runtime);
      result.setProperty(runtime, "id", convertJNIObjectToJSIValue(runtime, item->getId()));
      result.setProperty(runtime, "label", convertJNIObjectToJSIValue(runtime, item->getLabel()));
      result.setProperty(runtime, "value", convertJNIObjectToJSIValue(runtime, item->getValue()));
      return result;

  } else if (object->isInstanceOf(mrousavy::JContact::JBirthday::javaClassStatic())) {
      // Contact.Birthday

      auto birthday = static_ref_cast<mrousavy::JContact::JBirthday>(object);

      jsi::Object result(runtime);
      result.setProperty(runtime, "year", jsi::Value(birthday->getYear()));
      result.setProperty(runtime, "month", jsi::Value(birthday->getMonth()));
      result.setProperty(runtime, "day", jsi::Value(birthday->getDay()));
      return result;

  } else if (object->isInstanceOf(JArrayList<jobject>::javaClassStatic())) {
      // ArrayList<E>

      auto arrayList = static_ref_cast<JArrayList<jobject>>(object);
      auto size = arrayList->size();

      auto result = jsi::Array(runtime, size);
      size_t i = 0;
      for (const auto& item : *arrayList) {
          result.setValueAtIndex(runtime, i, convertJNIObjectToJSIValue(runtime, item));
          i++;
      }
      return result;

  } else if (object->isInstanceOf(react::ReadableArray::javaClassStatic())) {
    // ReadableArray

    static const auto toArrayListFunc = react::ReadableArray::javaClassLocal()->getMethod<JArrayList<jobject>()>("toArrayList");

    // call recursive, this time ArrayList<E>
    auto array = toArrayListFunc(object.get());
    return convertJNIObjectToJSIValue(runtime, array);

  } else if (object->isInstanceOf(jni::JHashMap<jstring, jobject>::javaClassStatic())) {
    // HashMap<K, V>

    auto map = static_ref_cast<jni::JHashMap<jstring, jobject>>(object);

    auto result = jsi::Object(runtime);
    for (const auto& entry : *map) {
      auto key = entry.first->toString();
      auto value = entry.second;
      if (!value) continue;

      auto jsiValue = convertJNIObjectToJSIValue(runtime, value);
      result.setProperty(runtime, key.c_str(), jsiValue);
    }
    return result;

  } else if (object->isInstanceOf(react::ReadableMap::javaClassStatic())) {
      // ReadableMap

      static const auto toHashMapFunc = react::ReadableMap::javaClassLocal()->getMethod<jni::JHashMap<jstring, jobject>()>("toHashMap");

      // call recursive, this time HashMap<K, V>
      auto hashMap = toHashMapFunc(object.get());
      return convertJNIObjectToJSIValue(runtime, hashMap);

  }

  auto type = object->getClass()->toString();
  auto message = "Received unknown JNI type \"" + type + "\"! Cannot convert to jsi::Value.";
  __android_log_write(ANDROID_LOG_ERROR, "VisionCamera", message.c_str());
  throw std::runtime_error(message);
}

} // namespace vision
