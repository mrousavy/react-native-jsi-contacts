#include "JSIContacts.h"
#include <thread>
#include <fbjni/fbjni.h>
#include <react/jni/WritableNativeMap.h>
#include "JSIJNIConversion.h"

namespace mrousavy {

    jsi::Value JSIContacts::get(jsi::Runtime& runtime, const jsi::PropNameID& propName) {
        auto name = propName.utf8(runtime);

        if (name == "getContactsAsync") {
            return jsi::Function::createFromHostFunction(runtime,
                                                         jsi::PropNameID::forAscii(runtime, "getContactsAsync"),
                                                         0,
                                                         [this](jsi::Runtime& runtime,
                                                                const jsi::Value&,
                                                                const jsi::Value* arguments,
                                                                size_t count) -> jsi::Value {
                                                             return this->getContactsAsync(runtime);
                                                         });
        }
        if (name == "getHashAsync") {
            return jsi::Function::createFromHostFunction(runtime,
                                                         jsi::PropNameID::forAscii(runtime, "getContactsAsync"),
                                                         0,
                                                         [this](jsi::Runtime& runtime,
                                                                const jsi::Value&,
                                                                const jsi::Value* arguments,
                                                                size_t count) -> jsi::Value {
                                                             return this->getHashAsync(runtime);
                                                         });
        }

        return jsi::Value::undefined();
    }

    std::vector<jsi::PropNameID> JSIContacts::getPropertyNames(jsi::Runtime &rt) {
        std::vector<jsi::PropNameID> result;
        result.push_back(jsi::PropNameID::forUtf8(rt, std::string("getContactsAsync")));
        result.push_back(jsi::PropNameID::forUtf8(rt, std::string("getHashAsync")));
        return result;
    }

    jsi::Value JSIContacts::getContactsAsync(jsi::Runtime& runtime) {
        auto promiseCtor = runtime.global().getPropertyAsFunction(runtime, "Promise");
        auto promiseCallback = [this](jsi::Runtime& runtime,
                                      const jsi::Value&,
                                      const jsi::Value* arguments,
                                      size_t count) -> jsi::Value {
            if (count != 2) {
                throw std::runtime_error("Promise Callback called with an unexpected amount of arguments!");
            }
            auto resolver = std::make_shared<jsi::Function>(std::move(arguments[0].asObject(runtime).asFunction(runtime)));
            auto rejecter = std::make_shared<jsi::Function>(std::move(arguments[1].asObject(runtime).asFunction(runtime)));

            _threadPool.enqueue([this, &runtime, resolver, rejecter]() {
                try {
                    jni::ThreadScope scope;
                    auto contacts = this->_contactsProvider->getContacts();
                    // TODO: USE LOCAL REF DIRECTLY, THIS IS A WACK WORKAROUND!
                    auto globalContacts = make_global(contacts);

                    // ASYNC
                    this->_callInvoker->invokeAsync([&runtime, resolver, globalContacts]() {
                        jni::ThreadScope scope;
                        // JS
                        auto localAgain = make_local(globalContacts);
                        auto jsiValue = vision::JSIJNIConversion::convertJNIObjectToJSIValue(runtime, localAgain);
                        resolver->call(runtime, jsiValue);
                    });
                } catch (std::exception& exception) {
                    auto message = std::string("Failed to get contacts! ") + std::string(exception.what());
                    this->_callInvoker->invokeAsync([&runtime, rejecter, message]() {
                        auto error = jsi::JSError(runtime, message);
                        rejecter->call(runtime, error.value());
                    });
                }
            });

            return jsi::Value::undefined();
        };
        auto promise = promiseCtor.callAsConstructor(runtime,
                                                     jsi::Function::createFromHostFunction(runtime,
                                                                                           jsi::PropNameID::forAscii(runtime, "PromiseCallback"),
                                                                                           2,
                                                                                           std::move(promiseCallback)));
        return promise;
    }

    jsi::Value JSIContacts::getHashAsync(jsi::Runtime& runtime) {
        auto promiseCtor = runtime.global().getPropertyAsFunction(runtime, "Promise");
        auto promiseCallback = [this](jsi::Runtime& runtime,
                                      const jsi::Value&,
                                      const jsi::Value* arguments,
                                      size_t count) -> jsi::Value {
            if (count != 2) {
                throw std::runtime_error("Promise Callback called with an unexpected amount of arguments!");
            }
            auto resolver = std::make_shared<jsi::Function>(std::move(arguments[0].asObject(runtime).asFunction(runtime)));
            auto rejecter = std::make_shared<jsi::Function>(std::move(arguments[1].asObject(runtime).asFunction(runtime)));

            _threadPool.enqueue([this, &runtime, resolver, rejecter]() {
                try {
                    jni::ThreadScope scope;
                    auto hash = this->_contactsProvider->getHash();
                    std::string string = hash->toStdString();

                    // ASYNC
                    this->_callInvoker->invokeAsync([&runtime, resolver, string]() {
                        jni::ThreadScope scope;
                        // JS
                        auto jsiValue = jsi::String::createFromUtf8(runtime, string);
                        resolver->call(runtime, jsiValue);
                    });
                } catch (std::exception& exception) {
                    auto message = std::string("Failed to get contacts hash! ") + std::string(exception.what());
                    this->_callInvoker->invokeAsync([&runtime, rejecter, message]() {
                        auto error = jsi::JSError(runtime, message);
                        rejecter->call(runtime, error.value());
                    });
                }
            });

            return jsi::Value::undefined();
        };
        auto promise = promiseCtor.callAsConstructor(runtime,
                                                     jsi::Function::createFromHostFunction(runtime,
                                                                                           jsi::PropNameID::forAscii(runtime, "PromiseCallback"),
                                                                                           2,
                                                                                           std::move(promiseCallback)));
        return promise;
    }

}
