#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "proto/message_handler.h"
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/message_differencer.h>

using namespace std;

// Next idea is to type erase the Drawer and specify which drawer we want to
// instantiate ie: Drawer drawer = std::make_unique<OPenGL>();
// drawer.drawAllShapes(shapes);
TEST(TestMessageHandler, basic) {
  proto::MyMessageHandler messageHandler;
  ASSERT_EQ(messageHandler.getName(), "test");
}

TEST(TestMessageHandler, EncodeToBinary) {
  myproto::MyMessage msgToEncode;
  msgToEncode.set_id(1);
  msgToEncode.set_name("to encode");

  std::string encoded;

  ASSERT_TRUE(msgToEncode.SerializeToString(&encoded));
  
}
TEST(TestMessageHandler, DecodeFromBinary) {
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

TEST(TestMessageHandler, DecodeFromJSON) {
  myproto::MyMessage decodedMessage;

  std::string json = "{\"id\":1,\"name\":\"test\"}";

  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  
  google::protobuf::util::JsonStringToMessage(json, &decodedMessage, options);

  EXPECT_EQ(decodedMessage.id(), 1);
  EXPECT_EQ(decodedMessage.name(), "test");
}

TEST(TestMessageHandler, EncodeToJSON) {
  std::string encodingResult;

  myproto::MyMessage msgToEncode;
  msgToEncode.set_id(1);
  msgToEncode.set_name("to encode");
  google::protobuf::util::JsonPrintOptions encodingOptions;
  encodingOptions.add_whitespace = true;
  encodingOptions.always_print_primitive_fields = true;
  encodingOptions.preserve_proto_field_names = true;
  google::protobuf::util::MessageToJsonString(msgToEncode, &encodingResult, encodingOptions);


  google::protobuf::util::JsonParseOptions decodingOptions;
  decodingOptions.ignore_unknown_fields = true;
  myproto::MyMessage decodedMessage;

  google::protobuf::util::JsonStringToMessage(encodingResult, &decodedMessage, decodingOptions);

  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(decodedMessage, msgToEncode));
}