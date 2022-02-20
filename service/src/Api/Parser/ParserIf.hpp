#pragma once

#include "Core/Model/Board.hpp"
#include <optional>
#include <string>
#include <vector>

namespace Reminder {
namespace Api {
namespace Parser {

class ParserIf {
  public:
    virtual ~ParserIf() {}

    virtual std::string getEmptyResponseString() = 0;

    virtual std::string convertToApiString(Reminder::Core::Model::Board &board) = 0;
    virtual std::string convertToApiString(std::vector<Reminder::Core::Model::List> &lists) = 0;
    virtual std::string convertToApiString(Reminder::Core::Model::List &list) = 0;
    virtual std::string convertToApiString(Reminder::Core::Model::Remind &reminder) = 0;

    virtual std::optional<Reminder::Core::Model::List> converToListModel(int listId, std::string &request) = 0;
    virtual std::optional<Reminder::Core::Model::Remind> converToRemindModel(int reminderId, std::string &request) = 0;
};

} // namespace Parser
} // namespace Api
} // namespace Reminder
