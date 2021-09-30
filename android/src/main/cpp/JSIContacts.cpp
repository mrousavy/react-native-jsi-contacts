#include "JSIContacts.h"
#include <thread>

namespace mrousavy {

jsi::Value JSIContacts::get(jsi::Runtime& runtime, const jsi::PropNameID& propName) {
    auto name = propName.utf8(runtime);

    if (name == "getContactsAsync") {
        return this->getContactsAsync(runtime);
    }

    return jsi::Value::undefined();
}

std::vector<jsi::PropNameID> JSIContacts::getPropertyNames(jsi::Runtime &rt) {
    std::vector<jsi::PropNameID> result;
    result.push_back(jsi::PropNameID::forUtf8(rt, std::string("getContactsAsync")));
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
        auto resolver = arguments[0].asObject(runtime).asFunction(runtime);
        auto rejecter = arguments[0].asObject(runtime).asFunction(runtime);

        _threadPool.enqueue([this]() {
            // ASYNC
            this->_callInvoker->invokeAsync([]() {
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

}
