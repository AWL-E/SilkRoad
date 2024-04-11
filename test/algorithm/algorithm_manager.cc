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
#include <gtest/gtest.h>

#include <memory>
#include <list>
#include "../../src/algorithm/AlgorithmManager.h"
#include "../../src/algorithm/AlgorithmInterface.h"
#include "../helpers/FakeOpenSearchClient.h"

using namespace std;
using namespace algorithm;
using namespace asdk::generic;

class FakeAlgorithm: public AlgorithmInterface {
public:
    explicit FakeAlgorithm(std::shared_ptr<test::FakeOpenSearch> f_searchEngine): AlgorithmInterface(f_searchEngine) {}
    ~FakeAlgorithm() = default;

    void prepare(AWLEStatus &status) override {};
    void execute(AWLEStatus &status) override {};
    void complete(AWLEStatus &status) override {};
};

TEST(AlgorithmManager, Instanciate) {  
//algos = std::make_shared<std::map<std::string, std::list<std::shared_ptr<AlgorithmInterface>>>>();  // algorithm::AlgorithmManager manager();
}
