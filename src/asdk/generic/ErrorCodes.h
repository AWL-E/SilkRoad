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

/**
 * Cette classe est une classe appartenant à AWL-E
 * Auteur: Félix Champagne-Lapointe
*/

#ifndef _ASDK_GENERIC_ERRORCODES_H_
#define _ASDK_GENERIC_ERRORCODES_H_

#include <map>
#include <string>

namespace asdk::generic {

enum ErrorCodes {
  OK = 0,
  NOT_PERMITTED = 1,
  NO_FILE_OR_MEMORY = 2,
  IO_ERROR = 5,
  TRY_AGAIN = 11,
  OUT_OF_MEMORY = 12,
  PERMISSION_DENIED = 13,
  RESOURCE_BUSY = 16,
  INVALID_ARGUMENT = 22,
  FILE_TOO_LARGE = 27,
  TIMEOUT = 62,
  ADDRESS_IN_USE = 98,
  NOT_CONNECTED = 107,
  HOST_UNREACHABLE = 113,
  IN_PROGRESS = 115,
  NOT_RECOVERABLE = 131,
  // AWLENumbers
  UNKNOWN = 133,
  WOULD_BLOCK = 211, // Should be 11, historically overlaps with EAGAIN
  GENERIC = 212,     // com_socket error -1 is described as: General / Low level error
  UNSUPPORTED = 213, // Unsupported functionality
  INVALID_STATE = 214
};

static const std::map<ErrorCodes, const std::string> enumToStringMap = {
    {ErrorCodes::OK, "OK"},
    {ErrorCodes::NOT_PERMITTED, "NOT_PERMITTED"},
    {ErrorCodes::NO_FILE_OR_MEMORY, "NO_FILE_OR_MEMORY"},
    {ErrorCodes::IO_ERROR, "IO_ERROR"},
    {ErrorCodes::TRY_AGAIN, "TRY_AGAIN"},
    {ErrorCodes::OUT_OF_MEMORY, "OUT_OF_MEMORY"},
    {ErrorCodes::PERMISSION_DENIED, "PERMISSION_DENIED"},
    {ErrorCodes::RESOURCE_BUSY, "RESOURCE_BUSY"},
    {ErrorCodes::INVALID_ARGUMENT, "INVALID_ARGUMENT"},
    {ErrorCodes::FILE_TOO_LARGE, "FILE_TOO_LARGE"},
    {ErrorCodes::TIMEOUT, "TIMEOUT"},
    {ErrorCodes::ADDRESS_IN_USE, "ADDRESS_IN_USE"},
    {ErrorCodes::NOT_CONNECTED, "NOT_CONNECTED"},
    {ErrorCodes::HOST_UNREACHABLE, "HOST_UNREACHABLE"},
    {ErrorCodes::IN_PROGRESS, "IN_PROGRESS"},
    {ErrorCodes::NOT_RECOVERABLE, "NOT_RECOVERABLE"},
    {ErrorCodes::UNKNOWN, "UNKNOWN"},
    {ErrorCodes::WOULD_BLOCK, "WOULD_BLOCK"},
    {ErrorCodes::GENERIC, "GENERIC"},
    {ErrorCodes::UNSUPPORTED, "UNSUPPORTED"},
    {ErrorCodes::INVALID_STATE, "INVALID_STATE"}};

class AWLEStatus {
public:
  AWLEStatus();

  void set(const ErrorCodes &f_errorCode);
  const ErrorCodes &get() const;
  const std::string &getErrorCodeAsString() const;

  void setDescription(const std::string &description);
  const std::string &getDescription() const;

  operator bool() const;

  bool operator==(const AWLEStatus &other) const;

  bool operator!=(const AWLEStatus &other) const;

  bool operator==(const ErrorCodes &other) const;

  bool operator!=(const ErrorCodes &other) const;

private:
  ErrorCodes errorCode = ErrorCodes::OK;
  std::string errorDescription;
};

} // namespace asdk::generic

#endif // _ASDK_COMMUNICATION_TRANSCODER_H_
