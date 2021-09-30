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

struct JContact : public JavaClass<JContact> {
    static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact;";

    local_ref<jobject> getValueByName(const std::string& name);

    struct JItem : public JavaClass<JItem> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$Item;";
    };
    struct JBirthday : public JavaClass<JBirthday> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$Birthday;";
    };
    struct JPostalAddressItem : public JavaClass<JPostalAddressItem> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$PostalAddressItem;";
    };
};

} // namespace mrousavy
