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

#ifndef _SILKROAD_COMMUNICATION_HTTPCLIENTINTERFACE_H_
#define _SILKROAD_COMMUNICATION_HTTPCLIENTINTERFACE_H_

#include <functional>
#include <memory>
#include <string>
#include <iostream>
#include <curl/curl.h>

#include "../../asdk/generic/ErrorCodes.h"
#include "./../parsing/BodyParserInterface.h"

namespace communication {

struct HTTPResponse {
    uint16_t code;
    std::string body;
};

using asdk::generic::AWLEStatus;

class HTTPClientInterface  {
public:
    HTTPClientInterface(std::shared_ptr<communication::parsing::BodyParserInterface> f_bodyParser);
    virtual ~HTTPClientInterface() = default;

    virtual HTTPResponse get(const std::string& url, AWLEStatus& status) = 0;
    virtual HTTPResponse get(const std::string& url, const std::string& data, AWLEStatus& status) = 0;
    
    virtual HTTPResponse post(const std::string& url, const std::string& data, AWLEStatus& status) = 0;

protected:
  std::shared_ptr<communication::parsing::BodyParserInterface> bodyParser;
};

} // namespace communication

#endif // _SILKROAD_COMMUNICATION_HTTPCLIENTINTERFACE_H_
