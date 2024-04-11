#include <gtest/gtest.h>

#include <memory>

#include "../../src/communication/OpenSearchClient.h"
#include "../helpers/FakeHTTPClient.h"
#include "../helpers/FakeBodyParser.h"


using namespace std;
using namespace communication;
using namespace asdk::generic;

TEST(TestOpenSearchClient, searchFromTermQuerySuccess) {

    std::function<std::string()> uuidCallback = []() { return "1234"; };
    auto bodyParser = std::make_shared<test::FakeBodyParser>();
    auto httpClient = std::make_shared<test::FakeHTTPClient>(bodyParser);
    std::string domain = "localhost:9001";
    std::string expectedUrlResult = "localhost:9001/myIndex/_search?from=0&size=200";
    std::string expectedParams = "{\"query\": {\"term\": {\"deviceId\": \"deviceId123\"}}}";

    OpenSearchClient client(httpClient, domain, uuidCallback);

    AWLEStatus status;
    std::string indexName = "myIndex";
    TermQueryParameters params;
    params.termName = "deviceId";
    params.value = "deviceId123";
    params.from = 0;
    params.size = 200;

    client.searchIndexUsingTermQuery(indexName, params, status);

    EXPECT_TRUE(status);
    EXPECT_EQ(httpClient->lastUrl, expectedUrlResult);
    EXPECT_EQ(httpClient->lastParams, expectedParams);
}

TEST(TestOpenSearchClient, bulkRequestHeaderFromIndexName) {
    std::function<std::string()> uuidCallback = []() { return "1234"; };

    auto bodyParser = std::make_shared<test::FakeBodyParser>();
    auto httpClient = std::make_shared<test::FakeHTTPClient>(bodyParser);
    std::string domain = "localhost:9001";
    OpenSearchClient client(httpClient, domain, uuidCallback);

    std::string index = "Index1";
    std::string result = client.bulkRequestHeaderFromIndexName(index);
    std:: string expectedResult = "{\n \"_index\": \"Index1\",\n \"_id\": \"1234\"\n}\n";

    EXPECT_EQ(result.length(), expectedResult.length());
    EXPECT_EQ(result, expectedResult);
}
