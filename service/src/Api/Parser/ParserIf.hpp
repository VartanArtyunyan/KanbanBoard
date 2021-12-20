#pragma once

#include <string>

namespace Reminder {
namespace Api {
namespace Parser {

class ParserIf {
  public:
    virtual ~ParserIf() {}

    virtual std::string getEmptyResponseString() = 0;
};

} // namespace Parser
} // namespace Api
} // namespace Reminder