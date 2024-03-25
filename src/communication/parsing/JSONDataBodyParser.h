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

#ifndef _SILKROAD_COMMUNICATION_BODYPARSER_H_
#define _SILKROAD_COMMUNICATION_BODYPARSER_H_

#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "../../asdk/generic/ErrorCodes.h"
#include "./BodyParserInterface.h"

namespace communication::parsing {

using asdk::generic::AWLEStatus;

class JSONDataBodyParser: public BodyParserInterface {
public:
  explicit JSONDataBodyParser();
  ~JSONDataBodyParser() = default;

  void parse(const std::string &payload, std::string& output, AWLEStatus &status) override;

};

} // namespace communication

#endif // _SILKROAD_COMMUNICATION_BODYPARSER_H_
