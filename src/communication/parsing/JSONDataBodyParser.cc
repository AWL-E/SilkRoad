/*
 * Copyright (c) 2023-2024 AWL-E. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "JSONDataBodyParser.h"

#include <json/json.h>

namespace communication::parsing {
  
    JSONDataBodyParser::JSONDataBodyParser() {}

      void JSONDataBodyParser::parse(const std::string &payload, std::string& output, AWLEStatus &status) { 
            Json::Value root;
            Json::Reader reader;
            
            if (reader.parse(payload, root)) {
                output = root["data"].asString();
            } else {
                status.set(asdk::generic::ErrorCodes::UNKNOWN);
                status.setDescription("Failed to parse JSON");
            }
      }
} // namespace asdk::initializer
