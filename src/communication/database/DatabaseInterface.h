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

#ifndef _SILKROAD_COMMUNICATION_DATABASEINTERFACE_H_
#define _SILKROAD_COMMUNICATION_DATABASEINTERFACE_H_

#include <functional>
#include <memory>
#include <string>

#include "../../asdk/generic/ErrorCodes.h"

namespace communication::database {

using asdk::generic::AWLEStatus;

struct QueryParams {

    std::string index;                  // Elasticsearch index to search
    std::vector<std::string> fields;    // Fields to search within
    std::string query;                  // Query string
    int size;                           // Number of results to return
    int from;                           // Offset for pagination

    QueryParams(const std::string& _index, const std::vector<std::string>& _fields,
                const std::string& _query, int _size = 10, int _from = 0)
        : index(_index), fields(_fields), query(_query), size(_size), from(_from) {}
};

class DatabaseInterface  {
public:
    explicit DatabaseInterface();
    ~DatabaseInterface() = default;

    template <class T>
    void query(const QueryParams& params, std::vector<T>& output, AWLEStatus &status);
};

} // namespace communication

#include "DatabaseInterface.tpp"

#endif // _SILKROAD_COMMUNICATION_DATABASEINTERFACE_H_
