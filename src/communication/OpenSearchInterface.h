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

#ifndef _SILKROAD_COMMUNICATION_OPENSEARCHINTERFACE_H_
#define _SILKROAD_COMMUNICATION_OPENSEARCHINTERFACE_H_

#include <functional>
#include <memory>
#include <string>

#include "../asdk/generic/ErrorCodes.h"
#include "./http/HTTPClientInterface.h"
#include "../../build/src/ProtoMessages.pb.h"

namespace communication {

struct TermQueryParameters {
    std::string termName;
    std::string value;
    uint16_t from;
    uint16_t size;
};

using asdk::generic::AWLEStatus;

/**
 * Interface générique d'un engin de recherche.
 */
class OpenSearchInterface  {

public:
  
    explicit OpenSearchInterface();
    virtual ~OpenSearchInterface() = default;

    virtual void searchIndexUsingTermQuery(std::string& indexName, TermQueryParameters& params, AWLEStatus& status) = 0;
    virtual std::string bulkRequestHeaderFromIndexName(std::string& indexName) = 0;
    virtual void storeBulkRequest(std::string& requestHeader, std::string& requestData, AWLEStatus& status) = 0;
    virtual void sendBulkRequests(AWLEStatus& status) = 0;

};

} // namespace communication

#endif // _SILKROAD_COMMUNICATION_OPENSEARCHINTERFACE_H_