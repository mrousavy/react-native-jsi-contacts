//
// Created by Marc Rousavy on 30.09.21.
//

#pragma once

#include <jni.h>
#include <fbjni/fbjni.h>
#include <string>
#include "JArrayList.h"

namespace mrousavy {

using namespace facebook;
using namespace jni;
using namespace vision;

struct JContact : public JavaClass<JContact> {
    static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact;";

    struct JItem : public JavaClass<JItem> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$Item;";

        local_ref<jstring> getLabel();
        local_ref<jstring> getValue();
        local_ref<jstring> getId();
    };
    struct JBirthday : public JavaClass<JBirthday> {
        static constexpr auto kJavaDescriptor = "Lcom/mrousavy/jsi/contacts/Contact$Birthday;";

        jint getYear();
        jint getMonth();
        jint getDay();
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
    local_ref<JArrayList<JItem::javaobject>> getUrls();
    local_ref<JArrayList<JItem::javaobject>> getInstantMessengers();
    jboolean getHasPhoto();
    local_ref<jstring> getPhotoUri();
    local_ref<JArrayList<JItem::javaobject>> getEmails();
    local_ref<JArrayList<JItem::javaobject>> getPhones();
    local_ref<JArrayList<JPostalAddressItem::javaobject>> getPostalAddresses();
    local_ref<JBirthday::javaobject> getBirthday();
};

} // namespace mrousavy
