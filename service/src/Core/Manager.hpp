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
};

} // namespace Core
} // namespace Reminder
