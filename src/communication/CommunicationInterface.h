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

#ifndef _SILKROAD_COMMUNICATION_COMMUNICATIONINTERFACE_H_
#define _SILKROAD_COMMUNICATION_COMMUNICATIONINTERFACE_H_

#include <functional>
#include <memory>
#include <string>

#include "../asdk/generic/ErrorCodes.h"
#include "../communication/OpenSearchInterface.h"
#include "../algorithm/AlgorithmManager.h"
namespace communication {

using asdk::generic::AWLEStatus;

/**
 * Interface qui reçoit des messages entrant dans le cadriciel 
 */
class CommunicationInterface  {
public:
  explicit CommunicationInterface(std::shared_ptr<communication::OpenSearchInterface> f_searchEngine, std::shared_ptr<algorithm::AlgorithmManager> f_algoManager);
  ~CommunicationInterface() = default;

  bool handleIncomingMessage(const std::string &payload, AWLEStatus &status);

private:
  std::shared_ptr<communication::OpenSearchInterface> searchEngine;
  std::shared_ptr<algorithm::AlgorithmManager> algoManager;
};

} // namespace communication

#endif // _SILKROAD_COMMUNICATION_COMMUNICATIONINTERFACE_H_
