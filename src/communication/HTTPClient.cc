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

#include "HTTPClient.h"

namespace communication { 
    HTTPClient::HTTPClient(std::shared_ptr<BodyParser> f_bodyParser) : bodyParser(f_bodyParser){
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
    }

    HTTPClient::~HTTPClient() {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    HTTPResponse HTTPClient::get(const std::string& url, AWLEStatus& status) {
        HTTPResponse response;
        long httpCode;

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPClient::WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA,  &response.body);

            CURLcode res = curl_easy_perform(curl);

            if (res == CURLE_OK) {
              curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.code);

              if(response.code >= 400) {
                  status.set(asdk::generic::ErrorCodes::UNKNOWN);
                  status.setDescription(std::to_string(httpCode));
              }
            } else {
                status.set(asdk::generic::ErrorCodes::UNKNOWN);
                status.setDescription(curl_easy_strerror(res));
            }
        }

        return response;
    }

    HTTPResponse HTTPClient::post(const std::string& url, const std::string& data, AWLEStatus& status) {
    HTTPResponse response;

    if (curl) {
        // URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        
        // Header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPClient::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.code);

            if (response.code >= 400) {
                status.set(asdk::generic::ErrorCodes::UNKNOWN);
                status.setDescription(std::to_string(response.code));
            }
        } else {
            status.set(asdk::generic::ErrorCodes::UNKNOWN);
            status.setDescription(curl_easy_strerror(res));
        }

        fprintf(stderr, "POST: %s", response.body.c_str());
    }

    return response;
}

    size_t HTTPClient::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
      size_t total_size = size * nmemb;
      output->append((char*)contents, total_size);
      return total_size;
    }
} // namespace asdk::initializer
