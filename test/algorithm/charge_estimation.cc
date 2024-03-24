#include <gtest/gtest.h>

#include "../../src/algorithm/ChargeEstimation.h"

TEST(ChargeEstimation, Prepare) {
  asdk::generic::AWLEStatus status;
  algorithm::ChargeEstimation chargeEstimation;

  chargeEstimation.prepare(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}
TEST(ChargeEstimation, Execute) {
  asdk::generic::AWLEStatus status;
  algorithm::ChargeEstimation chargeEstimation;

  chargeEstimation.prepare(status);
  chargeEstimation.execute(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}

TEST(ChargeEstimation, Complete) {
  asdk::generic::AWLEStatus status;
  algorithm::ChargeEstimation chargeEstimation;

  chargeEstimation.prepare(status);
  chargeEstimation.execute(status);
  chargeEstimation.complete(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}