#pragma once

#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"
#include <string>

namespace Reminder {
namespace Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

    void initialize();
    void createDummyData();
    void handleSQLError(int statementResult, char *errorMessage);

    static bool isValid(int id) {
        return id != INVALID_ID;
    }

    static Reminder::Core::Model::Remind getRemindFromCallback(char **fieldValues, int startIndex);
    static Reminder::Core::Model::List getListFromCallback(char **fieldValues, int startIndex);

    static int queryListCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames);
    static int queryRemindCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames);

  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();
    static std::string const databaseFile;
    static inline int const INVALID_ID = -1;
    static inline std::string const Title = "Reminder";

    virtual std::vector<Reminder::Core::Model::List> getAll();
    virtual std::optional<Reminder::Core::Model::List> getList(int listID);
    virtual std::optional<Reminder::Core::Model::List> postList(std::string name, int position);
    virtual std::optional<Reminder::Core::Model::List> putList(int listID, std::string name);
    virtual void deleteList(int listID);

    virtual std::optional<Reminder::Core::Model::Remind> getRemind(int listID, int reminderID);
    virtual std::optional<Reminder::Core::Model::Remind> postRemind(int listID, std::string name, int position, std::string date, bool flagged);
    virtual std::optional<Reminder::Core::Model::Remind> putRemind(int listID, int reminderID, std::string name, std::string date, bool flagged);
    virtual void deleteRemind(int listID, int reminderID);
};

} // namespace Repository
} // namespace Reminder
