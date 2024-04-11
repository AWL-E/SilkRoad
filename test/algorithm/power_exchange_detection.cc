#include <gtest/gtest.h>

#include "../../src/algorithm/PowerExchangeDetection.h"
#include "../helpers/FakeOpenSearchClient.h"

TEST(PowerExchangeDetection, Prepare) {
  asdk::generic::AWLEStatus status;
  auto searchEngine = std::make_shared<test::FakeOpenSearch>();
  algorithm::PowerExchangeDetection powerExchangeDetection(searchEngine);

  powerExchangeDetection.prepare(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}

TEST(PowerExchangeDetection, Execute) {
  asdk::generic::AWLEStatus status;
  auto searchEngine = std::make_shared<test::FakeOpenSearch>();
  algorithm::PowerExchangeDetection powerExchangeDetection(searchEngine);

  powerExchangeDetection.prepare(status);
  powerExchangeDetection.execute(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}
TEST(PowerExchangeDetection, Complete) {
  asdk::generic::AWLEStatus status;
  auto searchEngine = std::make_shared<test::FakeOpenSearch>();
  algorithm::PowerExchangeDetection powerExchangeDetection(searchEngine);

  powerExchangeDetection.prepare(status);
  powerExchangeDetection.execute(status);
  powerExchangeDetection.complete(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}