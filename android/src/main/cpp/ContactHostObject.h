//
// Created by Marc Rousavy on 30.09.21.
//

#pragma once

#include <jsi/jsi.h>
#include <fbjni/fbjni.h>
#include "java-bindings/JContact.h"

namespace mrousavy {
using namespace facebook;

class ContactHostObject : public jsi::HostObject {
public:
    ContactHostObject(jni::alias_ref<JContact::javaobject> contact): _contact(jni::make_global(contact)) {}
    ~ContactHostObject();

    jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;

    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;

private:
    jni::global_ref<JContact::javaobject> _contact;
};

}
