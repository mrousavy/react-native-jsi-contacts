#include <jni.h>
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include <ReactCommon/CallInvokerHolder.h>
#include <thread>

using namespace facebook;
using TCallInvoker = jni::alias_ref<react::CallInvokerHolder::javaobject>;

inline jsi::Value getContactsAsync(jsi::Runtime& runtime,
                                   std::shared_ptr<react::CallInvoker> jsCallInvoker) {
    auto promiseCtor = runtime.global().getPropertyAsFunction(runtime, "Promise");
    auto promiseCallback = [jsCallInvoker](jsi::Runtime& runtime,
                                           const jsi::Value&,
                                           const jsi::Value* arguments,
                                           size_t count) -> jsi::Value {
        if (count != 2) {
            throw std::runtime_error("Promise Callback called with an unexpected amount of arguments!");
        }
        auto resolver = arguments[0].asObject(runtime).asFunction(runtime);
        auto rejecter = arguments[0].asObject(runtime).asFunction(runtime);

        // TODO: Use ThreadPool
        std::thread([jsCallInvoker]() {
            // ASYNC
            jsCallInvoker->invokeAsync([]() {
                // JS

            });
        });

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

void install(jsi::Runtime& jsiRuntime,
             std::shared_ptr<react::CallInvoker> jsCallInvoker) {
    // Contacts.getContactsAsync()
    auto func_getContactsAsync = jsi::Function::createFromHostFunction(jsiRuntime,
                                                                  jsi::PropNameID::forAscii(jsiRuntime, "__JSIContacts_getContactsAsync"),
                                                                  1,
                                                                  [jsCallInvoker](jsi::Runtime& runtime,
                                                                                  const jsi::Value&,
                                                                                  const jsi::Value* arguments,
                                                                                  size_t count) -> jsi::Value {
        return getContactsAsync(runtime, jsCallInvoker);
    });
    jsiRuntime.global().setProperty(jsiRuntime, "__JSIContacts_getContactsAsync", std::move(func_getContactsAsync));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mrousavy_jsi_contacts_JsiContactsModule_nativeInstall(JNIEnv *env,
                                                               jclass type,
                                                               jlong jsiRuntimePointer,
                                                               TCallInvoker jsCallInvokerHolder) {
    auto runtime = reinterpret_cast<jsi::Runtime*>(jsiRuntimePointer);
    auto jsCallInvoker = jsCallInvokerHolder->cthis()->getCallInvoker();
    if (runtime) {
        install(*runtime, jsCallInvoker);
    }
    // if runtime was nullptr, RNContacts will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}
