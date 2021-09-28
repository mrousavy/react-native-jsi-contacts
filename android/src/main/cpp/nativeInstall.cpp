#include <jni.h>
#include <jsi/jsi.h>

using namespace facebook;

inline jsi::Value getContactsAsync(jsi::Runtime& runtime) {
    auto promiseCtor = runtime.global().getPropertyAsFunction(runtime, "Promise");
    auto promiseCallback = [](
            jsi::Runtime& runtime,
            const jsi::Value&,
            const jsi::Value* arguments,
            size_t count) -> jsi::Value {
        if (count != 2) {
            throw std::runtime_error("Promise Callback called with an unexpected amount of arguments!");
        }
        auto resolver = arguments[0].asObject(runtime).asFunction(runtime);
        auto rejecter = arguments[0].asObject(runtime).asFunction(runtime);

        resolver.call(runtime, jsi::Array(runtime, 0));
        return jsi::Value::undefined();
    };
    auto promise = promiseCtor.callAsConstructor(runtime,
                                                 jsi::Function::createFromHostFunction(runtime,
                                                                                       jsi::PropNameID::forAscii(runtime, "PromiseCallback"),
                                                                                       2,
                                                                                       std::move(promiseCallback)));
    return promise;
}

void install(jsi::Runtime& jsiRuntime) {
    // Contacts.getContactsAsync()
    auto func_getContactsAsync = jsi::Function::createFromHostFunction(jsiRuntime,
                                                                  jsi::PropNameID::forAscii(jsiRuntime, "__JSIContacts_getContactsAsync"),
                                                                  1,
                                                                  [](jsi::Runtime& runtime,
                                                                     const jsi::Value&,
                                                                     const jsi::Value* arguments,
                                                                     size_t count) -> jsi::Value {
        return getContactsAsync(runtime);
    });
    jsiRuntime.global().setProperty(jsiRuntime, "__JSIContacts_getContactsAsync", std::move(func_getContactsAsync));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mrousavy_jsi_contacts_JsiContactsModule_nativeInstall(JNIEnv *env, jclass type, jlong jsiRuntimePointer) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiRuntimePointer);
    if (runtime) {
        install(*runtime);
    }
    // if runtime was nullptr, RNContacts will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}
