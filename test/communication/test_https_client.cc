#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../../src/communication/HTTPClient.h"

using namespace std;
using namespace communication;

TEST(TestHTTPClient, GETWithCode200StatusIsTrue) {
    AWLEStatus status;
    HTTPClient client;
    HTTPResponse response = client.get("httpstat.us/200", status);
    EXPECT_TRUE(status);
    EXPECT_EQ(response.code, 200);
}

TEST(TestHTTPClient, GETWithCode404StatusIsFalse) {
    AWLEStatus status;
    HTTPClient client;
    HTTPResponse response = client.get("httpstat.us/404", status);
    EXPECT_FALSE(status);
    EXPECT_EQ(response.code, 404);
}


TEST(TestHTTPClient, POSTWithoutDataCode200StatusIsTrue) {
    AWLEStatus status;
    HTTPClient client;
    HTTPResponse response = client.post("http://httpbin.org/post", "", status);
    EXPECT_TRUE(status);
    EXPECT_EQ(response.code, 200);
}

TEST(TestHTTPClient, POSTWithDataCode200StatusIsTrue) {
    AWLEStatus status;
    HTTPClient client;
    HTTPResponse response = client.post("http://httpbin.org/post", "data=example", status);
    EXPECT_TRUE(status);
    EXPECT_EQ(response.code, 200);
}

TEST(TestHTTPClient, POSTWithCode404StatusIsFalse) {
    AWLEStatus status;
    HTTPClient client;
    HTTPResponse response = client.post("http://httpbin.org/status/404", "data=example", status);
    EXPECT_FALSE(status);
    EXPECT_EQ(response.code, 404);
}