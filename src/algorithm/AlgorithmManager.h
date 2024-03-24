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

#ifndef _SILKROAD_ALGORITHM_ALGORITHMMANAGER_H_
#define _SILKROAD_ALGORITHM_ALGORITHMMANAGER_H_

#include <memory>
#include <string>
#include <list>

#include "../asdk/generic/ErrorCodes.h"
#include "./AlgorithmInterface.h"
namespace algorithm {

using asdk::generic::AWLEStatus;

using AlgorithmMap = std::map<std::string, std::list<std::shared_ptr<AlgorithmInterface>>>;

class AlgorithmManager  {
public:
    explicit AlgorithmManager();
    virtual ~AlgorithmManager() = default;

    void dispatch(std::string topic, std::string payload, AWLEStatus &status);
    void addAlgorithm(const std::string& topic, std::shared_ptr<AlgorithmInterface> algorithm);

private: 
    std::shared_ptr<AlgorithmMap> algos;
};

} // namespace algorithm

#endif // _ALGORITHM_ALGORITHMMANAGER_H_
