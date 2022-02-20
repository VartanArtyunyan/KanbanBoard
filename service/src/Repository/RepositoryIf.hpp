#pragma once

#include "Core/Model/Board.hpp"
#include <optional>
#include <vector>
namespace Reminder {
namespace Repository {
class RepositoryIf {
  public:
    virtual ~RepositoryIf() {}

    virtual Reminder::Core::Model::Board getAllLists() = 0;
    virtual std::vector<Reminder::Core::Model::List> getAll() = 0;
    virtual std::optional<Reminder::Core::Model::List> getList(int listID) = 0;
    virtual std::optional<Reminder::Core::Model::List> postList(std::string name, int position) = 0;
    virtual std::optional<Reminder::Core::Model::List> putList(int listID, std::string name) = 0;
    virtual void deleteList(int listID) = 0;

    virtual std::optional<Reminder::Core::Model::Remind> postRemind(int listID, std::string name, int position, std::string date, bool flagged) = 0;
    virtual std::optional<Reminder::Core::Model::Remind> putRemind(int listID, int reminderID, std::string name, std::string date, bool flagged) = 0;
    virtual void deleteRemind(int listID, int reminderID) = 0;
};

} // namespace Repository
} // namespace Reminder
