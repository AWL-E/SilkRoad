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

TEST(TestMessageHandler, EncodeToJSON) {
  myproto::MyMessage msgToEncode;
  msgToEncode.set_id(1);
  msgToEncode.set_name("to encode");

  std::string encoded;

  ASSERT_TRUE(msgToEncode.SerializeToString(&encoded));
  
}

TEST(TestMessageHandler, DecodeFromJSON) {
  
}


/**
TEST_F(BasicProtoGtest, SerializeToJsonAndBackAgain) {
  // Movie PBUF message
  Movie startMovie;

  struct timeval tv;
  gettimeofday(&tv, NULL);

  ::google::protobuf::Timestamp* timestamp = new
  ::google::protobuf::Timestamp();
  timestamp->set_seconds(tv.tv_sec);
  timestamp->set_nanos(tv.tv_usec * 1000);

  startMovie.set_allocated_start_time(timestamp);
  startMovie.set_movie_name("my happy movie");

  std::string serialized = startMovie.SerializeAsString();
  std::string json_string;

  // Create a TypeResolver used to resolve protobuf message types
  google::protobuf::util::JsonOptions options;
  options.always_print_primitive_fields = true;
  std::unique_ptr<google::protobuf::util::TypeResolver>
  resolver(google::protobuf::util::NewTypeResolverForDescriptorPool(
  "type.googleapis.com",
  google::protobuf::DescriptorPool::generated_pool()));

  // Assert we can find the Movie type in the resolver
  Type type;
  ASSERT_TRUE(resolver->ResolveMessageType(
  "type.googleapis.com/movie.pbuf.Movie", &type).ok());

  auto status = google::protobuf::util::BinaryToJsonString(resolver.get(),
  "type.googleapis.com/movie.pbuf.Movie", serialized, &json_string, options);
  // std::cout << "~~~~~~~ bin str\n" << serialized << std::endl;
  std::cout << "*******\n" << json_string << std::endl;

  // Turn JSON into serialized protobuf message
  std::string movieBin;
  google::protobuf::util::JsonToBinaryString(resolver.get(),
  "type.googleapis.com/movie.pbuf.Movie", json_string, &movieBin);

  Movie startMovie2;
  startMovie2.ParseFromString(movieBin);

  EXPECT_EQ(startMovie.movie_name(), startMovie2.movie_name());
  EXPECT_EQ(startMovie.start_time(), startMovie2.start_time());
}*/