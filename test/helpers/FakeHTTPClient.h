#include "../../src/communication/http/HTTPClientInterface.h"

namespace test {

using asdk::generic::AWLEStatus;
using communication::HTTPResponse;

class FakeHTTPClient : public communication::HTTPClientInterface {
public:
    FakeHTTPClient(std::shared_ptr<communication::parsing::BodyParserInterface> f_bodyParser) 
        : communication::HTTPClientInterface(f_bodyParser){}

    HTTPResponse get(const std::string& url, AWLEStatus& status) override {
        lastUrl = url;
        status = statusToSet;
        return {returnedHttpCode, returnedPayload};
    };

    
    HTTPResponse get(const std::string& url, const std::string& data, AWLEStatus& status) override {
        lastUrl = url;
        lastParams = data;
        status = statusToSet;
        return {returnedHttpCode, returnedPayload};
    };
    

    HTTPResponse post(const std::string& url, const std::string& data, AWLEStatus& status) override {
        lastUrl = url;
        lastParams = data;
        status = statusToSet;
        return {returnedHttpCode, returnedPayload};
    };

    std::string lastUrl;
    std::string lastParams;
    AWLEStatus statusToSet;

private:
    uint16_t returnedHttpCode;
    std::string returnedPayload;
};

} // namespace test