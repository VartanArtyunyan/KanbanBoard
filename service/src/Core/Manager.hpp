#pragma once

#include "Api/Parser/ParserIf.hpp"
#include "Repository/RepositoryIf.hpp"

namespace Reminder {
namespace Core {
class Manager {
  private:
    Reminder::Repository::RepositoryIf &repository;
    Reminder::Api::Parser::ParserIf &parser;

  public:
    Manager(Reminder::Api::Parser::ParserIf &givenParser, Reminder::Repository::RepositoryIf &givenRepository);
    ~Manager();

    std::string getAll();
    std::string getList(int listID);
    std::string postList(std::string request);
    std::string postReminder(int listID, std::string request);
    std::string putList(int listID, std::string request);
    std::string putReminder(int listID, int reminderID, std::string request);
    void deleteList(int listID);
    void deleteReminder(int listID, int reminderID);
};

} // namespace Core
} // namespace Reminder
