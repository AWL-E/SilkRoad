#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../../build/src/ProtoMessages.pb.h"

#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/message_differencer.h>

using namespace std;

TEST(TestMessageHandler, DecodeFromBinary) {
  ProtoMessages::TestMessage msgToEncode;
  msgToEncode.set_id(1);
  msgToEncode.set_name("to encode");

  std::string encoded;

  msgToEncode.SerializeToString(&encoded);

  ProtoMessages::TestMessage msgToDecode;
  ASSERT_TRUE(msgToDecode.ParseFromString(encoded));
  ASSERT_EQ(msgToDecode.id(), 1);
  ASSERT_EQ(msgToDecode.name(), "to encode");
  
}

TEST(TestMessageHandler, DecodeFromJSON) {
  ProtoMessages::TestMessage decodedMessage;

  std::string json = "{\"id\":1,\"name\":\"test\"}";

  google::protobuf::util::JsonParseOptions options;
  options.ignore_unknown_fields = true;
  
  google::protobuf::util::JsonStringToMessage(json, &decodedMessage, options);

  EXPECT_EQ(decodedMessage.id(), 1);
  EXPECT_EQ(decodedMessage.name(), "test");
}

TEST(TestMessageHandler, EncodeToJSON) {
  std::string encodingResult;

  ProtoMessages::TestMessage msgToEncode;
  msgToEncode.set_id(1);
  msgToEncode.set_name("to encode");
  google::protobuf::util::JsonPrintOptions encodingOptions;
  encodingOptions.add_whitespace = true;
  encodingOptions.always_print_primitive_fields = true;
  encodingOptions.preserve_proto_field_names = true;
  google::protobuf::util::MessageToJsonString(msgToEncode, &encodingResult, encodingOptions);


  google::protobuf::util::JsonParseOptions decodingOptions;
  decodingOptions.ignore_unknown_fields = true;
  ProtoMessages::TestMessage decodedMessage;

  google::protobuf::util::JsonStringToMessage(encodingResult, &decodedMessage, decodingOptions);

  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(decodedMessage, msgToEncode));
}