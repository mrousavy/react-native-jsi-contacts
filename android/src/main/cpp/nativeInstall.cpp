#include <jni.h>
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include <ReactCommon/CallInvokerHolder.h>
#include "JSIContacts.h"

using namespace facebook;
using TCallInvoker = jni::alias_ref<react::CallInvokerHolder::javaobject>;

void install(jsi::Runtime& jsiRuntime,
             std::shared_ptr<react::CallInvoker> jsCallInvoker) {
    auto contacts = std::make_shared<mrousavy::JSIContacts>(jsCallInvoker);
    auto hostObject = jsi::Object::createFromHostObject(jsiRuntime, contacts);
    jsiRuntime.global().setProperty(jsiRuntime, "JSIContacts", hostObject);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mrousavy_jsi_contacts_JsiContactsModule_nativeInstall(JNIEnv *env, jclass type, jlong jsiRuntimePointer, jobject jsCallInvokerHolder) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiRuntimePointer);

    auto callInvokerRef = jni::make_local(jsCallInvokerHolder);
    auto callInvoker = jni::dynamic_ref_cast<react::CallInvokerHolder::javaobject>(callInvokerRef);
    auto jsCallInvoker = callInvoker->cthis()->getCallInvoker();

    if (runtime) {
        install(*runtime, jsCallInvoker);
    }
    // if runtime was nullptr, RNContacts will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}
