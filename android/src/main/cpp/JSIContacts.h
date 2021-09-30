#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include "ThreadPool.h"

namespace mrousavy {

using namespace facebook;

class JSIContacts : public jsi::HostObject {
public:
    explicit JSIContacts(std::shared_ptr<react::CallInvoker> callInvoker): _callInvoker(callInvoker), _threadPool(2) {}

    jsi::Value get(jsi::Runtime &, const jsi::PropNameID &name) override;
    std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;

private:
    std::shared_ptr<react::CallInvoker> _callInvoker;
    multithreading::ThreadPool _threadPool;
    jsi::Value getContactsAsync(jsi::Runtime& runtime);
};

}
