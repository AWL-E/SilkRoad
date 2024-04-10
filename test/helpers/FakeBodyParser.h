#include "../../src/communication/parsing/BodyParserInterface.h"

namespace test {

class FakeBodyParser : public communication::parsing::BodyParserInterface {

public:
    FakeBodyParser() = default;
    ~FakeBodyParser() override = default;

    void parse(const std::string &payload, std::string& output, AWLEStatus &status) override {}
};

} // namespace test