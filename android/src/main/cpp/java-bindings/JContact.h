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

    struct JItem : public JavaClass<JItem> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$Item;";
    };
    struct JBirthday : public JavaClass<JBirthday> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$Birthday;";
    };
    struct JPostalAddressItem : public JavaClass<JPostalAddressItem> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$PostalAddressItem;";
    };

    local_ref<jstring> getContactId();
    local_ref<jstring> getDisplayName();
    local_ref<jstring> getGivenName();
    local_ref<jstring> getMiddleName();
    local_ref<jstring> getFamilyName();
    local_ref<jstring> getPrefix();
    local_ref<jstring> getSuffix();
    local_ref<jstring> getCompany();
    local_ref<jstring> getJobTitle();
    local_ref<jstring> getDepartment();
    local_ref<jstring> getNote();
    local_ref<JArrayClass<JItem::javaobject>> getUrls();
    local_ref<JArrayClass<JItem::javaobject>> getInstantMessengers();
    jboolean getHasPhoto();
    local_ref<jstring> getPhotoUri();
    local_ref<JArrayClass<JItem::javaobject>> getEmails();
    local_ref<JArrayClass<JItem::javaobject>> getPhones();
    local_ref<JArrayClass<JPostalAddressItem::javaobject>> getPostalAddresses();
    local_ref<JBirthday::javaobject> getBirthday();
};

} // namespace mrousavy
