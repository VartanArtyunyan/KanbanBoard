#include "Manager.hpp"
#include "Model/List.hpp"
#include "Model/Remind.hpp"
#include <iostream>
#include <optional>
#include <vector>

using namespace Reminder::Core;
using namespace Reminder::Core::Model;
using namespace Reminder::Api::Parser;
using namespace Reminder::Repository;
using namespace std;

Manager::Manager(ParserIf &givenParser, RepositoryIf &givenRepository)
    : parser(givenParser), repository(givenRepository) {
}

Manager::~Manager() {
}

std::string Manager::getAll() {
    std::cout << "Ich bin der get All befehl";
    Board board = repository.getAllLists();

    return parser.convertToApiString(board);
}

std::string Manager::getList(int listID) {
    std::optional<List> optL = repository.getList(listID);
    if (optL) {
        List list = optL.value();
        return parser.convertToApiString(list);
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::postList(std::string request) {
    std::cout << request;
    int const dummyId = -1;
    std::optional<List> parsedListOptional = parser.converToListModel(dummyId, request);
    if (false == parsedListOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    List parsedList = parsedListOptional.value();
    std::optional<List> postedList = repository.postList(parsedList.getName(), parsedList.getPosition());

    if (postedList) {
        return parser.convertToApiString(postedList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::postReminder(int listID, std::string request) {
    std::cout << listID << " " << request;
    int const dummyId = -1;
    std::optional<Remind> parsedReminderOptional = parser.converToRemindModel(dummyId, request);
    if (false == parsedReminderOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Remind reminder = parsedReminderOptional.value();
    std::optional<Remind> postetRemind = repository.postRemind(listID, reminder.getName(), reminder.getPosition(), reminder.getDatum(), reminder.isFlagged());
    if (postetRemind) {
        return parser.convertToApiString(postetRemind.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::putList(int listID, std::string request) {
    std::optional<List> parsedOptionalList = parser.converToListModel(listID, request);

    if (false == parsedOptionalList.has_value()) {
        return parser.getEmptyResponseString();
    }

    List liste = parsedOptionalList.value();
    std::optional<List> putList = repository.putList(listID, liste.getName());

    if (putList) {
        return parser.convertToApiString(putList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::putReminder(int listID, int reminderID, std::string request) {

    std::optional parsedReminderOptional = parser.converToRemindModel(reminderID, request);
    if (false == parsedReminderOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Remind reminder = parsedReminderOptional.value();
    std::optional<Remind> putRemind = repository.putRemind(listID, reminderID, reminder.getName(), reminder.getDatum(), reminder.isFlagged());

    if (putRemind) {
        return parser.convertToApiString(putRemind.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

void Manager::deleteList(int listID) {
    repository.deleteList(listID);
}

void Manager::deleteReminder(int listID, int reminderID) {
    repository.deleteRemind(listID, reminderID);
}
