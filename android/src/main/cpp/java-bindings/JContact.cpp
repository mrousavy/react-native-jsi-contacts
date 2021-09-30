//
// Created by Marc Rousavy on 30.09.21.
//

#include "JContact.h"
#include <jni.h>
#include <fbjni/fbjni.h>


namespace mrousavy {

using namespace facebook;
using namespace jni;

using TSelf = local_ref<JContact::jhybriddata>;


TSelf JContact::initHybrid(jni::alias_ref<jhybridobject> jThis) {
    return makeCxxInstance(jThis);
}

void JContact::registerNatives() {
    registerHybrid({
        // TODO: Any Native Methods?
    });
}

local_ref<jobject> JContact::getValueByName(const std::string &name) {
    auto field = javaPart_->getClass()->getField<jobject>(name.c_str());
    auto value = javaPart_->getFieldValue(field);
    return value;
}

}
