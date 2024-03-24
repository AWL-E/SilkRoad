#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../../src/communication/HTTPClient.h"

using namespace std;
using namespace communication;

TEST(TestHTTPClient, basic) {
    HTTPClient client;
    client.test();
}

TEST(TestHTTPClient, encode) {

  
}
TEST(TestHTTPClient, decode) {
  
}
