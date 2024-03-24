#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../../src/communication/BodyParser.h"

using namespace std;
using namespace communication;

TEST(TestBodyParser, ParseJSONEmptyBody) {
    std::string response = "";
    std::string result;
    AWLEStatus status;

    BodyParser parser;

    parser.parse(response, result, status);

    EXPECT_FALSE(status);
}

TEST(TestBodyParser, ParseJSONDataFromHTTPResponseWithData) {
    std::string response = "{\"args\": {}, \"data\": \"{\\\"key1\\\":\\\"value1\\\", \\\"key2\\\":\\\"value2\\\"}\", \"files\": {}, \"form\": {}, \"headers\": { \"Accept\": \"application/json\", \"Charset\": \"utf-8\", \"Content-Length\": \"34\", \"Content-Type\": \"application/json\", \"Host\": \"httpbin.org\", \"X-Amzn-Trace-Id\": \"Root=1-660082c5-16393878419dd54727217172\" }, \"json\": { \"key1\": \"value1\", \"key2\": \"value2\" }, \"origin\": \"142.122.55.4\", \"url\": \"http://httpbin.org/put\"}";
    std::string result;
    AWLEStatus status;

    BodyParser parser;

    parser.parse(response, result, status);

    EXPECT_TRUE(status);
    EXPECT_EQ(result, "{\"key1\":\"value1\", \"key2\":\"value2\"}");
}

TEST(TestBodyParser, ParseJSONDataFromHTTPResponseNoData) {
    std::string response = "{\"args\": {}, \"data\": \"\", \"files\": {}, \"form\": {}, \"headers\": { \"Accept\": \"application/json\", \"Charset\": \"utf-8\", \"Content-Length\": \"34\", \"Content-Type\": \"application/json\", \"Host\": \"httpbin.org\", \"X-Amzn-Trace-Id\": \"Root=1-660082c5-16393878419dd54727217172\" }, \"json\": { \"key1\": \"value1\", \"key2\": \"value2\" }, \"origin\": \"142.122.55.4\", \"url\": \"http://httpbin.org/put\"}";
    std::string result;
    AWLEStatus status;

    BodyParser parser;

    parser.parse(response, result, status);

    EXPECT_TRUE(status);
    EXPECT_EQ(result, "");
}