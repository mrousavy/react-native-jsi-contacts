//
// Created by Marc Rousavy on 30.09.21.
//

#include "JContact.h"
#include <jni.h>
#include <fbjni/fbjni.h>

namespace mrousavy {

using namespace facebook;
using namespace jni;

    local_ref<jstring> JContact::getContactId() {
        auto field = getClass()->getField<jstring>("contactId");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getDisplayName() {
        auto field = getClass()->getField<jstring>("displayName");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getGivenName() {
        auto field = getClass()->getField<jstring>("givenName");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getMiddleName() {
        auto field = getClass()->getField<jstring>("middleName");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getFamilyName() {
        auto field = getClass()->getField<jstring>("familyName");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getPrefix() {
        auto field = getClass()->getField<jstring>("prefix");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getSuffix() {
        auto field = getClass()->getField<jstring>("suffix");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getCompany() {
        auto field = getClass()->getField<jstring>("company");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getJobTitle() {
        auto field = getClass()->getField<jstring>("jobTitle");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getDepartment() {
        auto field = getClass()->getField<jstring>("department");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getNote() {
        auto field = getClass()->getField<jstring>("note");
        return getFieldValue(field);
    }

    local_ref<JArrayClass<JContact::JItem::javaobject>> JContact::getUrls() {
        auto field = getClass()->getField<JArrayClass<JContact::JItem::javaobject>>("urls");
        return getFieldValue(field);
    }

    local_ref<JArrayClass<JContact::JItem::javaobject>> JContact::getInstantMessengers() {
        auto field = getClass()->getField<JArrayClass<JContact::JItem::javaobject>>("instantMessengers");
        return getFieldValue(field);
    }

    jboolean JContact::getHasPhoto() {
        auto field = getClass()->getField<jboolean>("hasPhoto");
        return getFieldValue(field);
    }

    local_ref<jstring> JContact::getPhotoUri() {
        auto field = getClass()->getField<jstring>("photoUri");
        return getFieldValue(field);
    }

    local_ref<JArrayClass<JContact::JItem::javaobject>> JContact::getEmails() {
        auto field = getClass()->getField<JArrayClass<JContact::JItem::javaobject>>("emails");
        return getFieldValue(field);
    }

    local_ref<JArrayClass<JContact::JItem::javaobject>> JContact::getPhones() {
        auto field = getClass()->getField<JArrayClass<JContact::JItem::javaobject>>("phones");
        return getFieldValue(field);
    }

    local_ref<JArrayClass<JContact::JPostalAddressItem::javaobject>> JContact::getPostalAddresses() {
        auto field = getClass()->getField<JArrayClass<JContact::JPostalAddressItem::javaobject>>("postalAddresses");
        return getFieldValue(field);
    }

    local_ref<JContact::JBirthday::javaobject> JContact::getBirthday() {
        auto field = getClass()->getField<JContact::JBirthday::javaobject>("birthday");
        return getFieldValue(field);
    }


    // JItem
    local_ref<jstring> JContact::JItem::getId() {
        auto field = getClass()->getField<jstring>("id");
        return getFieldValue(field);
    }
    local_ref<jstring> JContact::JItem::getLabel() {
        auto field = getClass()->getField<jstring>("label");
        return getFieldValue(field);
    }
    local_ref<jstring> JContact::JItem::getValue() {
        auto field = getClass()->getField<jstring>("value");
        return getFieldValue(field);
    }


    // JBirthday
    jint JContact::JBirthday::getYear() {
        auto field = getClass()->getField<jint>("year");
        return getFieldValue(field);
    }
    jint JContact::JBirthday::getMonth() {
        auto field = getClass()->getField<jint>("month");
        return getFieldValue(field);
    }
    jint JContact::JBirthday::getDay() {
        auto field = getClass()->getField<jint>("day");
        return getFieldValue(field);
    }

}
