#include "OpenSearchClient.h"

#include <string>
#include <sstream>
#include "../util/uuid.h"

#include "../../build/src/ProtoMessages.pb.h"
#include <google/protobuf/util/json_util.h>

namespace communication {
    OpenSearchClient::OpenSearchClient(std::shared_ptr<HTTPClientInterface> f_httpClient, std::string f_domain, UUIDCallback f_uuidCreationCallback): httpClient(f_httpClient), domain(f_domain),  uuidCreationCallback(f_uuidCreationCallback) {}
    
    void OpenSearchClient::searchIndexUsingTermQuery(std::string& indexName, TermQueryParameters& params, AWLEStatus& status){
        std::ostringstream urlStream;
        urlStream << domain << "/" << indexName << "/_search?from=" << params.from << "&" << "size=" << params.size;
        
        std::ostringstream paramsStream;
        paramsStream << "{\"query\": {\"term\": {\"" << params.termName << "\": \""<< params.value <<"\"}}}";
        
        httpClient->get(urlStream.str(), paramsStream.str(), status);
    }

    std::string OpenSearchClient::bulkRequestHeaderFromIndexName(std::string& indexName) {
        std::string uuid = uuidCreationCallback();

        ProtoMessages::IndexBulkRequest request;

        request.set__id(uuid);
        request.set__index(indexName);


        std::string encodingResult;
        google::protobuf::util::JsonPrintOptions encodingOptions;
        encodingOptions.add_whitespace = true;
        encodingOptions.always_print_primitive_fields = true;
        encodingOptions.preserve_proto_field_names = true;

        google::protobuf::util::MessageToJsonString(request, &encodingResult, encodingOptions);

        return encodingResult;
    }

    void OpenSearchClient::storeBulkRequest(std::string& requestHeader, std::string& requestData, AWLEStatus& status) {
        bulkRequests.push_back(requestHeader);
        bulkRequests.push_back(requestData);
    }

    void OpenSearchClient::sendBulkRequests(AWLEStatus& status) {
        std::string result;

        for (const std::string str : bulkRequests) {
            result += str + "\n";
        }

        std::string url = domain + "/_bulk";
        httpClient->post(url, result, status);
    }
}