//
// Created by Marc Rousavy on 30.09.21.
//

#include "ContactHostObject.h"

#include <jsi/jsi.h>
#include <fbjni/fbjni.h>
#include "JSIJNIConversion.h"

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
    result.push_back(jsi::PropNameID::forUtf8(rt, std::string("contactId")));
    // TODO: Add others.
    return result;
}

jsi::Value ContactHostObject::get(jsi::Runtime& runtime, const jsi::PropNameID& propName) {
    auto name = propName.utf8(runtime);

    if (name == "contactId") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getContactId());
    }
    if (name == "displayName") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getDisplayName());
    }
    if (name == "givenName") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getGivenName());
    }
    if (name == "middleName") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getMiddleName());
    }
    if (name == "familyName") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getFamilyName());
    }
    if (name == "prefix") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getPrefix());
    }
    if (name == "suffix") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getSuffix());
    }
    if (name == "company") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getCompany());
    }
    if (name == "jobTitle") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getJobTitle());
    }
    if (name == "department") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getDepartment());
    }
    if (name == "note") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getNote());
    }
    if (name == "urls") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getUrls());
    }
    if (name == "instantMessengers") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getInstantMessengers());
    }
    if (name == "hasPhoto") {
        bool hasPhoto = _contact->getHasPhoto() == true;
        return jsi::Value(hasPhoto);
    }
    if (name == "photoUri") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getPhotoUri());
    }
    if (name == "emails") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getEmails());
    }
    if (name == "phones") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getPhones());
    }
    if (name == "postalAddresses") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getPostalAddresses());
    }
    if (name == "birthday") {
        return vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime,
                                                                    _contact->getBirthday());
    }

    return jsi::Value::undefined();
}

}
