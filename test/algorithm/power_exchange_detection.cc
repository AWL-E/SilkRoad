#include <gtest/gtest.h>

#include "../../src/algorithm/PowerExchangeDetection.h"

TEST(PowerExchangeDetection, Prepare) {
  asdk::generic::AWLEStatus status;
  algorithm::PowerExchangeDetection powerExchangeDetection;

  powerExchangeDetection.prepare(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}

TEST(PowerExchangeDetection, Execute) {
  asdk::generic::AWLEStatus status;
  algorithm::PowerExchangeDetection powerExchangeDetection;

  powerExchangeDetection.prepare(status);
  powerExchangeDetection.execute(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}
TEST(PowerExchangeDetection, Complete) {
  asdk::generic::AWLEStatus status;
  algorithm::PowerExchangeDetection powerExchangeDetection;

  powerExchangeDetection.prepare(status);
  powerExchangeDetection.execute(status);
  powerExchangeDetection.complete(status);

  EXPECT_EQ(asdk::generic::ErrorCodes::OK, status.get());
}