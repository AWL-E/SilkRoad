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
#include "ErrorCodes.h"

namespace asdk::generic {
AWLEStatus::AWLEStatus() = default;

void AWLEStatus::set(const ErrorCodes &f_errorCode) { errorCode = f_errorCode; }
const ErrorCodes &AWLEStatus::get() const { return errorCode; }
const std::string &AWLEStatus::getErrorCodeAsString() const {
  return enumToStringMap.at(errorCode);
}

void AWLEStatus::setDescription(const std::string &description) { errorDescription = description; }
const std::string &AWLEStatus::getDescription() const { return errorDescription; }

AWLEStatus::operator bool() const { return errorCode == OK; }

bool AWLEStatus::operator==(const AWLEStatus &other) const { return errorCode == other.get(); }

bool AWLEStatus::operator!=(const AWLEStatus &other) const { return errorCode != other.get(); }

bool AWLEStatus::operator==(const ErrorCodes &other) const { return errorCode == other; }

bool AWLEStatus::operator!=(const ErrorCodes &other) const { return errorCode != other; }
} // namespace asdk::generic
