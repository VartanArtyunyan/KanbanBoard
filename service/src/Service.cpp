#include <iostream>
#include <string>

#include "Api/Endpoint.hpp"
#include "Api/Parser/JsonParser.hpp"
#include "Core/Manager.hpp"
#include "Repository/SQLiteRepository.hpp"
#include "crow.h"

#include "Repository/RepositoryIf.hpp"

int main() {
    crow::SimpleApp crowApplication;
    Reminder::Repository::SQLiteRepository sqliteRepository;
    Reminder::Api::Parser::JsonParser jsonParser;

    Reminder::Core::Manager manager(jsonParser, sqliteRepository);
    Reminder::Api::Endpoint endpoint(crowApplication, manager);

    // sqliteRepository.postList("Liste1", 0);
    // sqliteRepository.postList("Liste2", 1);

    //  sqliteRepository.postRemind(1, "ERinnerung1", 0, "2018-12-10", false);
    //  sqliteRepository.postRemind(1, "ERinnerung1", 1, "2018-12-10", false);
    // sqliteRepository.postRemind(2, "ERinnerung1", 0, "2018-12-10", true);

    // Reminder::Core::Model::Board blib = sqliteRepository.getAllLists();

    // std::cout << manager.getAll();

    crowApplication.port(8080)
        //.multithreaded()
        .run();
}
