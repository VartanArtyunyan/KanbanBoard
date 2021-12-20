#pragma once

#include "ParserIf.hpp"
#include "rapidjson/document.h"

namespace Reminder {
namespace Api {
namespace Parser {

class JsonParser : public ParserIf {
  private:
    static inline std::string const EMPTY_JSON = "{}";

  public:
    JsonParser(){};
    virtual ~JsonParser(){};

    virtual std::string getEmptyResponseString() {
        return JsonParser::EMPTY_JSON;
    }
};

} // namespace Parser
} // namespace Api
} // namespace Reminder
