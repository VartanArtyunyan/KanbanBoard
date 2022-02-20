#define RAPIDJSON_ASSERT(x)

#include "JsonParser.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace Reminder::Api::Parser;
using namespace Reminder::Core::Model;
using namespace rapidjson;
using namespace std;

string JsonParser::convertToApiString(List &list) {
    Document doc(kObjectType);

    Value jsonList = getJsonValueFromModel(list, doc.GetAllocator());
    return jsonValueToString(jsonList);
}

string JsonParser::convertToApiString(Board &board) {
    Document document;
    Document::AllocatorType &allocator = document.GetAllocator();

    Value jsonBoard = getJsonValueFromModel(board, allocator);
    return jsonValueToString(jsonBoard);
}

string JsonParser::convertToApiString(std::vector<List> &lists) {
    Document doc(kArrayType);
    Document::AllocatorType &allocator = doc.GetAllocator();

    for (List &list : lists) {
        Value jsonList = getJsonValueFromModel(list, allocator);
        doc.PushBack(jsonList, allocator);
    }
    return jsonValueToString(doc);
}

rapidjson::Value JsonParser::getJsonValueFromModel(Board &board, rapidjson::Document::AllocatorType &allocator) {
    Value jsonBoard(kObjectType);
    Value jsonLists(kArrayType);

    for (List &column : board.getList()) {
        Value jsonColumn = getJsonValueFromModel(column, allocator);
        jsonLists.PushBack(jsonColumn, allocator);
    }

    jsonBoard.AddMember("title", Value(board.getTitle().c_str(), allocator), allocator);
    jsonBoard.AddMember("lists", jsonLists, allocator);

    return jsonBoard;
}

rapidjson::Value JsonParser::getJsonValueFromModel(List const &list, rapidjson::Document::AllocatorType &allocator) {
    Value jsonList(kObjectType);

    jsonList.AddMember("id", list.getId(), allocator);
    jsonList.AddMember("name", Value(list.getName().c_str(), allocator), allocator);
    jsonList.AddMember("position", list.getPosition(), allocator);
    jsonList.AddMember("size", list.getSize(), allocator);

    Value jsonReminders(kArrayType);

    for (Remind const &reminder : list.getReminder()) {
        Value jsonRemind = getJsonValueFromModel(reminder, allocator);
        jsonReminders.PushBack(jsonRemind, allocator);
    }

    jsonList.AddMember("reminders", jsonReminders, allocator);

    return jsonList;
}

string JsonParser::convertToApiString(Remind &reminder) {

    string output = EMPTY_JSON;
    Document document(kObjectType);
    Value jsonRemind = getJsonValueFromModel(reminder, document.GetAllocator());
    output = jsonValueToString(jsonRemind);
    return output;
}

rapidjson::Value JsonParser::getJsonValueFromModel(Remind const &reminder, rapidjson::Document::AllocatorType &allocator) {
    Value jsonRemind(kObjectType);

    jsonRemind.AddMember("id", reminder.getId(), allocator);
    jsonRemind.AddMember("name", Value(reminder.getName().c_str(), allocator), allocator);
    jsonRemind.AddMember("position", reminder.getPosition(), allocator);
    jsonRemind.AddMember("date", Value(reminder.getDatum().c_str(), allocator), allocator);
    jsonRemind.AddMember("flagged", reminder.isFlagged(), allocator);

    return jsonRemind;
}

string JsonParser::jsonValueToString(rapidjson::Value const &json) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json.Accept(writer);

    return buffer.GetString();
}

std::optional<List> JsonParser::converToListModel(int listId, std::string &request) {

    std::optional<List> resultList;
    Document document;
    document.Parse(request.c_str());

    if (true == isValidList(document)) {
        std::string name = document["name"].GetString();
        int position = document["position"].GetInt();
        resultList = List(listId, name, position);
    }
    return resultList;
}

std::optional<Remind> JsonParser::converToRemindModel(int reminderId, std::string &request) {
    std::optional<Remind> resultRemind;

    Document document;
    document.Parse(request.c_str());

    if (true == isValidRemind(document)) {
        std::string name = document["name"].GetString();
        int position = document["position"].GetInt();
        std::string date = document["date"].GetString();
        bool flag = document["flagged"].GetBool();
        resultRemind = Remind(reminderId, name, position, date, flag);
    }
    return resultRemind;
}

bool JsonParser::isValidList(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["name"].IsString()) {
        isValid = false;
    }
    if (false == document["position"].IsInt()) {
        isValid = false;
    }

    return isValid;
}

bool JsonParser::isValidRemind(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["name"].IsString()) {
        isValid = false;
    }
    if (false == document["position"].IsInt()) {
        isValid = false;
    }
    if (false == document["date"].IsString()) {
        isValid = false;
    }
    if (false == document["flagged"].IsBool()) {
        isValid = false;
    }

    return isValid;
}
