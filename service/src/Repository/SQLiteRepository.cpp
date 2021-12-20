#include "SQLiteRepository.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
using namespace Reminder::Repository;

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
}

SQLiteRepository::~SQLiteRepository() {
    sqlite3_close(database);
}
