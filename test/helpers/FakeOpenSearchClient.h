#include "../../src/communication/OpenSearchInterface.h"

namespace test {

using asdk::generic::AWLEStatus;

class FakeOpenSearch : public communication::OpenSearchInterface {

public:
    FakeOpenSearch() = default;
    ~FakeOpenSearch() override = default;

    void searchIndexUsingTermQuery(std::string& indexName, communication::TermQueryParameters& params, AWLEStatus& status) {

    };

    std::string bulkRequestHeaderFromIndexName(std::string& indexName) {
        return "";
    };

    void storeBulkRequest(std::string& requestHeader, std::string& requestData, AWLEStatus& status) {

    };

    void sendBulkRequests(AWLEStatus& status) {
        
    };
};

} // namespace test