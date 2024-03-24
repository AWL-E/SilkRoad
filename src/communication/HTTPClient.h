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

#ifndef _SILKROAD_COMMUNICATION_HTTPCLIENT_H_
#define _SILKROAD_COMMUNICATION_HTTPCLIENT_H_

#include <functional>
#include <memory>
#include <string>

#include "../asdk/generic/ErrorCodes.h"

#include <iostream>
#include <curl/curl.h>

namespace communication {

struct HTTPResponse {
    long code; // HTTP status code
    std::string body; // Response body
};

using asdk::generic::AWLEStatus;

class HTTPClient  {
public:
    HTTPClient();
    ~HTTPClient();

    HTTPResponse get(const std::string& url, AWLEStatus& status);
    HTTPResponse post(const std::string& url, const std::string& data, AWLEStatus& status);

private:
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output);
  CURL *curl;
};

} // namespace communication

#endif // _SILKROAD_COMMUNICATION_HTTPCLIENT_H_
