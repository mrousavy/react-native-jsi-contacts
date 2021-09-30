//
// Created by Marc Rousavy on 30.09.21.
//

#include "JContact.h"
#include <jni.h>
#include <fbjni/fbjni.h>

namespace mrousavy {

using namespace facebook;
using namespace jni;

local_ref<jobject> JContact::getValueByName(const std::string &name) {
    auto field = getClass()->getField<jobject>(name.c_str());
    auto value = getFieldValue(field);
    return value;
}

}
