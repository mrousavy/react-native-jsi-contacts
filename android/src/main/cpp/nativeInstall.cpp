#include <jni.h>
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include <ReactCommon/CallInvokerHolder.h>
#include "JSIContacts.h"
#include "JContactsProvider.h"

using namespace facebook;
using TCallInvoker = jni::alias_ref<react::CallInvokerHolder::javaobject>;

void install(jsi::Runtime& jsiRuntime,
             std::shared_ptr<react::CallInvoker> jsCallInvoker,
             jni::global_ref<mrousavy::JContactsProvider::javaobject> contactsProvider) {
    auto contacts = std::make_shared<mrousavy::JSIContacts>(jsCallInvoker, contactsProvider);
    auto hostObject = jsi::Object::createFromHostObject(jsiRuntime, contacts);
    jsiRuntime.global().setProperty(jsiRuntime, "JSIContacts", hostObject);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mrousavy_jsi_contacts_JsiContactsModule_nativeInstall(JNIEnv *env,
                                                               jclass type,
                                                               jobject boxedContactsProvider,
                                                               jlong jsiRuntimePointer,
                                                               jobject boxedCallInvokerHolder) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiRuntimePointer);

    auto boxedCallInvokerRef = jni::make_local(boxedCallInvokerHolder);
    auto callInvokerHolder = jni::dynamic_ref_cast<react::CallInvokerHolder::javaobject>(boxedCallInvokerRef);
    auto callInvoker = callInvokerHolder->cthis()->getCallInvoker();

    auto boxedContactsProviderRef = jni::make_global(boxedContactsProvider);
    auto contactsProvider = jni::dynamic_ref_cast<mrousavy::JContactsProvider::javaobject>(boxedContactsProviderRef);

    if (runtime) {
        install(*runtime, callInvoker, contactsProvider);
    }
    // if runtime was nullptr, RNContacts will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    return facebook::jni::initialize(vm, [] {
        //mrousavy::JContactsProvider::registerNatives();
    });
}
