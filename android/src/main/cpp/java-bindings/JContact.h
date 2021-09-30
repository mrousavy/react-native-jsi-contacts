//
// Created by Marc Rousavy on 30.09.21.
//

#pragma once

#include <jni.h>
#include <fbjni/fbjni.h>
#include <string>

namespace mrousavy {

using namespace facebook;
using namespace jni;

struct JContact : public HybridClass<JContact> {
    static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact;";
    static jni::local_ref<jhybriddata> initHybrid(jni::alias_ref<jhybridobject> jThis);
    static void registerNatives();

    local_ref<jobject> getValueByName(const std::string& name);
private:
    friend HybridBase;
    jni::global_ref<JContact::javaobject> javaPart_;

    explicit JContact(jni::alias_ref<JContact::jhybridobject> jThis) :
    javaPart_(jni::make_global(jThis))
    {}
};

} // namespace vision
