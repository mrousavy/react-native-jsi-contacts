//
// Created by Marc Rousavy on 30.09.21.
//

#include "JContactsProvider.h"

#include <jni.h>
#include <fbjni/fbjni.h>
#include "JContact.h"

namespace mrousavy {

using namespace facebook;
using namespace jni;

local_ref<JMap<JString, JContact::javaobject>> JContactsProvider::getContacts() const {
    auto getContactsMethod = getClass()->getMethod<JMap<JString, JContact::javaobject>()>("getContacts");

    auto result = getContactsMethod(self());
    return make_local(result);
}

}
