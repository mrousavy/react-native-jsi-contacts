//
// Created by Marc Rousavy on 30.09.21.
//

#include "ContactHostObject.h"

#include <jsi/jsi.h>
#include <fbjni/fbjni.h>

namespace mrousavy {

using namespace facebook;

ContactHostObject::~ContactHostObject() {
    // Hermes' Garbage Collector (Hades GC) calls destructors on a separate Thread
    // which might not be attached to JNI. Ensure that we use the JNI class loader when
    // deallocating the `frame` HybridClass, because otherwise JNI cannot call the Java
    // destroy() function.
    jni::ThreadScope::WithClassLoader([=] { _contact.reset(); });
}

std::vector<jsi::PropNameID> ContactHostObject::getPropertyNames(jsi::Runtime &rt) {
    std::vector<jsi::PropNameID> result;
    result.push_back(jsi::PropNameID::forUtf8(rt, std::string("// TODO")));
    return result;

}

jsi::Value ContactHostObject::get(jsi::Runtime &, const jsi::PropNameID &name) {
    return jsi::Value::undefined();
}

}
