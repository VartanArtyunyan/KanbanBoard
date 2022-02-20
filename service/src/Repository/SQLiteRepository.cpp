#include "SQLiteRepository.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
using namespace Reminder::Repository;
using namespace Reminder::Core::Model;

#ifdef RELEASE_SERVICE
string const SQLiteRepository::databaseFile = "./data/reminder-app.db";
#else
string const SQLiteRepository::databaseFile = "../data/reminder-app.db";
#endif

SQLiteRepository::SQLiteRepository() : database(nullptr) {

    string databaseDirectory = filesystem::path(databaseFile).parent_path().string();

    if (filesystem::is_directory(databaseDirectory) == false) {
        filesystem::create_directory(databaseDirectory);
    }

    int result = sqlite3_open(databaseFile.c_str(), &database);

    if (SQLITE_OK != result) {
        cout << "Cannot open database: " << sqlite3_errmsg(database) << endl;
    }
    initialize();
}

SQLiteRepository::~SQLiteRepository() {
    sqlite3_close(database);
}

void SQLiteRepository::initialize() {
    int result = 0;
    char *errorMessage = nullptr;

    string sqlCreateTableLists =
        "create table if not exists list("
        "id integer not null primary key autoincrement,"
        "name text not null,"
        "position integer not null UNIQUE);";

    string sqlCreateTableReminders =
        "create table if not exists reminder("
        "id integer not null primary key autoincrement,"
        "name text not null,"
        "date text not null,"
        "position integer not null,"
        "flagged integer,"
        "list_id integer not null,"
        "unique (position, list_id),"
        "foreign key (list_id) references list (id));";

    result = sqlite3_exec(database, sqlCreateTableLists.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
    result = sqlite3_exec(database, sqlCreateTableReminders.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    // only if dummy data is needed ;)
    // createDummyData();
}

Board SQLiteRepository::getAllLists() {
    Board board = Board("ReminderApp");

    std::vector<List> lists = getAll();

    board.setLists(lists);

    return board;
}

std::vector<List> SQLiteRepository::getAll() {
    std::vector<List> output;

    string sqlQuerry =
        "SELECT list.id, list.name, list.position, reminder.id, reminder.name, reminder.position, reminder.date, reminder.flagged from list "
        "left join reminder on reminder.list_id = list.id "
        "order by list.position, reminder.position";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuerry.c_str(), queryListCallback, &output, &errorMessage);
    handleSQLError(result, errorMessage);

    return output;
}

std::optional<List> SQLiteRepository::getList(int listID) {
    std::vector<List> lists;

    string sqlQuery =
        "SELECT list.id, list.name, list.position, reminder.id, reminder.name, reminder.position, reminder.date, reminder.flagged from list "
        "left join reminder on reminder.list_id = list.id = " +
        to_string(listID) +
        " order by list.position, reminder.position";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery.c_str(), queryListCallback, &lists, &errorMessage);
    handleSQLError(result, errorMessage);

    if (lists.size() == 1) {
        return lists.front();
    } else {
        return std::nullopt;
    }
}

std::optional<List> SQLiteRepository::postList(std::string name, int position) {

    string sqlQuery =
        "INSERT INTO list('name', 'position') "
        "VALUES('" +
        name + "', '" + to_string(position) + "')";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int listID = sqlite3_last_insert_rowid(database);
        return List(listID, name, position);
    }

    return std::nullopt;
}

std::optional<Reminder::Core::Model::List> SQLiteRepository::putList(int listID, std::string name) {

    string sqlQuery =
        "UPDATE list "
        "SET name  = '" +
        name +
        "' WHERE id = " + to_string(listID);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getList(listID);
}

void SQLiteRepository::deleteList(int listID) {

    string sqlQuery1 =
        "DELETE FROM reminder "
        "WHERE reminder.list_id = " +
        to_string(listID);

    string sqlQuery2 =
        "DELETE FROM list "
        "WHERE id = " +
        to_string(listID);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery1.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    result = sqlite3_exec(database, sqlQuery2.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

std::optional<Remind> SQLiteRepository::getRemind(int listID, int reminderID) {
    std::vector<Remind> reminders;

    string sqlQuery =

        "SELECT reminder.id, reminder.name, reminder.position, reminder.date, reminder.flagged from reminder "
        "where reminder.list_id = " +
        to_string(listID) + " and reminder.id = " + to_string(reminderID) +
        " order by reminder.position";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery.c_str(), queryRemindCallback, &reminders, &errorMessage);
    handleSQLError(result, errorMessage);

    if (reminders.size() == 1) {
        return reminders.front();
    } else {
        return std::nullopt;
    }
}

std::optional<Remind> SQLiteRepository::postRemind(int listID, std::string name, int position, std::string date, bool flagged) {

    int flag = flagged ? 1 : 0;

    string sqlQuery =
        "INSERT INTO reminder ('name', 'date', 'position', 'list_id', 'flagged')"
        "VALUES('" +
        name + "', '" + date + "', " + to_string(position) + ", " + to_string(listID) + ", " + to_string(flag) + ");";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    int reminderID = INVALID_ID;
    if (SQLITE_OK == result) {
        reminderID = sqlite3_last_insert_rowid(database);
    }

    return getRemind(listID, reminderID);
}

std::optional<Remind> SQLiteRepository::putRemind(int listID, int reminderID, std::string name, std::string date, bool flagged) {

    int flag = flagged ? 1 : 0;

    string sqlQuery =
        "UPDATE reminder SET name = '" + name + "', date = '" + date + "', flagged = " + to_string(flag) + " WHERE reminder.list_id = " + to_string(listID) + " AND reminder.id = " + to_string(reminderID);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getRemind(listID, reminderID);
}

void SQLiteRepository::deleteRemind(int listID, int reminderID) {
    string sqlQuery =
        "DELETE FROM reminder "
        "WHERE reminder.list_id = " +
        to_string(listID) +
        " AND reminder.id = " + to_string(reminderID);

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQuery.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

Remind SQLiteRepository::getRemindFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;

    int reminderID = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;

    string name = fieldValues[index] ? fieldValues[index] : "";
    index++;

    int position = fieldValues[index] ? atoi(fieldValues[index]) : 0;
    index++;

    string date = fieldValues[index] ? fieldValues[index] : "";
    index++;

    int flag = fieldValues[index] ? atoi(fieldValues[index]) : 0;

    bool flagged = false;

    if (flag == 0) {

    } else if (flag == 1) {
        flagged = true;
    }

    Remind reminder(reminderID, name, position, date, flagged);
    return reminder;
}

List SQLiteRepository::getListFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;

    int listID = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;

    string name = fieldValues[index] ? fieldValues[index] : "";
    index++;

    int position = fieldValues[index] ? atoi(fieldValues[index]) : 0;

    List liste(listID, name, position);
    return liste;
}

void SQLiteRepository::handleSQLError(int statementResult, char *errorMessage) {

    if (statementResult != SQLITE_OK) {
        cout << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

int SQLiteRepository::queryListCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {
    std::vector<List> *pLists = static_cast<std::vector<List> *>(data);
    std::vector<List> &lists = *pLists;

    Remind remind = getRemindFromCallback(fieldValues, 3);

    int listID = fieldValues[0] ? atoi(fieldValues[0]) : INVALID_ID;
    bool wasListAlreadyAdded = false;

    for (List &list : lists) {
        if (list.getId() == listID) {
            wasListAlreadyAdded = true;
            if (isValid(remind.getId())) {
                list.addReminder(remind);
            }
            break;
        }
    }

    if (false == wasListAlreadyAdded) {
        List list = getListFromCallback(fieldValues, 0);

        if (isValid(remind.getId())) {
            list.addReminder(remind);
        }

        if (isValid(list.getId())) {
            lists.push_back(list);
        }
    }

    return 0;
}

int SQLiteRepository::queryRemindCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {

    std::vector<Remind> *result = static_cast<std::vector<Remind> *>(data);

    Remind remind = getRemindFromCallback(fieldValues, 0);
    if (isValid(remind.getId())) {
        result->push_back(remind);
    }

    return 0;
}
