#include <gtest/gtest.h>

#include "../../src/algorithm/ChargeEstimation.h"
#include "../helpers/FakeOpenSearchClient.h"

TEST(ChargeEstimation, Prepare) {
  asdk::generic::AWLEStatus status;
  auto searchEngine = std::make_shared<test::FakeOpenSearch>();
  algorithm::ChargeEstimation chargeEstimation(searchEngine);

  chargeEstimation.prepare(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}
TEST(ChargeEstimation, Execute) {
  asdk::generic::AWLEStatus status;
  auto searchEngine = std::make_shared<test::FakeOpenSearch>();
  algorithm::ChargeEstimation chargeEstimation(searchEngine);

  chargeEstimation.prepare(status);
  chargeEstimation.execute(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}

TEST(ChargeEstimation, Complete) {
  asdk::generic::AWLEStatus status;
  auto searchEngine = std::make_shared<test::FakeOpenSearch>();
  algorithm::ChargeEstimation chargeEstimation(searchEngine);

  chargeEstimation.prepare(status);
  chargeEstimation.execute(status);
  chargeEstimation.complete(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}