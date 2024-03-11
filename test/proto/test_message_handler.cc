#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "proto/message_handler.h"

using namespace std;

// Next idea is to type erase the Drawer and specify which drawer we want to
// instantiate ie: Drawer drawer = std::make_unique<OPenGL>();
// drawer.drawAllShapes(shapes);
TEST(TestMessageHandler, basic) {
  proto::MyMessageHandler messageHandler;
  ASSERT_EQ(messageHandler.getName(), "test");
}

TEST(TestMessageHandler, encode) {
  myproto::MyMessage msgToEncode;
  msgToEncode.set_id(1);
  msgToEncode.set_name("to encode");

  std::string encoded;

  ASSERT_TRUE(msgToEncode.SerializeToString(&encoded));
  
}
TEST(TestMessageHandler, decode) {
  myproto::MyMessage msgToEncode;
  msgToEncode.set_id(1);
  msgToEncode.set_name("to encode");

  std::string encoded;

  msgToEncode.SerializeToString(&encoded);

  myproto::MyMessage msgToDecode;
  ASSERT_TRUE(msgToDecode.ParseFromString(encoded));
  ASSERT_EQ(msgToDecode.id(), 1);
  ASSERT_EQ(msgToDecode.name(), "to encode");
  
}
