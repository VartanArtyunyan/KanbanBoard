#include "Endpoint.hpp"

#include <iostream>

using namespace Reminder::Api;
using namespace Reminder::Core;
using namespace crow;

Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp),
                                                                 manager(givenManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {
    CROW_ROUTE(app, "/reminder")
    ([this](const request &req, response &res) {
        std::string jsonAllLists = manager.getAll();
        res.write(jsonAllLists);
        res.end();
    });

    CROW_ROUTE(app, "/reminder/list")
        .methods("POST"_method)([this](const request &req, response &res) {
            std::string jsonLists;

            switch (req.method) {
            case HTTPMethod::Post: {
                jsonLists = manager.postList(req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonLists);
            res.end();
        });

    CROW_ROUTE(app, "/reminder/list/<int>")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID) {
            std::string jsonColumn = "{}";

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumn = manager.getList(listID);
                break;
            }
            case HTTPMethod::Post: {
                jsonColumn = manager.postReminder(listID, req.body);
                break;
            }

            case HTTPMethod::Put: {
                jsonColumn = manager.putList(listID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteList(listID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumn);
            res.end();
        });

    CROW_ROUTE(app, "/reminder/list/<int>/reminder<int>")
        .methods("PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listID, int reminderID) {
            std::string jsonColumn = "{}";

            switch (req.method) {

            case HTTPMethod::Put: {
                jsonColumn = manager.putReminder(listID, reminderID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteReminder(listID, reminderID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumn);
            res.end();
        });
}
