#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../../src/communication/database/DatabaseInterface.h"

using namespace std;
using namespace communication::database;
using namespace asdk::generic;

TEST(TestDatabaseInterface, basic) {
    DatabaseInterface db;
    std::vector<std::uint32_t> vector{};
    AWLEStatus status;

    std::vector<std::string> searchFields = {"title", "content"};
    QueryParams queryParams("my_index", searchFields, "Elasticsearch", 20, 10);

    db.query<std::uint32_t>(queryParams, vector, status);
}

TEST(TestDatabaseInterface, encode) {

  
}

TEST(TestDatabaseInterface, decode) {
  
}
