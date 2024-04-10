#include "OpenSearchClient.h"

#include <string>
#include <sstream>

namespace communication {
    OpenSearchClient::OpenSearchClient(std::shared_ptr<HTTPClientInterface> f_httpClient, std::string f_domain): httpClient(f_httpClient), domain(f_domain) {}
    
    void OpenSearchClient::searchIndexUsingTermQuery(std::string& indexName, TermQueryParameters& params, AWLEStatus& status){
        std::ostringstream urlStream;
        urlStream << domain << "/" << indexName << "/_search?from=" << params.from << "&" << "size=" << params.size;
        
        std::ostringstream paramsStream;
        paramsStream << "{\"query\": {\"term\": {\"" << params.termName << "\": \""<< params.value <<"\"}}}";
        
        httpClient->get(urlStream.str(), paramsStream.str(), status);
    }

    void OpenSearchClient::pushDocumentInIndex(std::string& indexName, std::string& serializedData, AWLEStatus& status) {
        std::ostringstream urlStream;
        urlStream << domain << "/" << indexName << "/_doc";
        
        httpClient->post(urlStream.str(), serializedData, status);
    }
}