#include "List.hpp"

using namespace Reminder::Core::Model;

List::List(int id, std::string givenName, int givenPosition)
    : id(id), name(givenName), position(givenPosition) {}

int List::getId() const {
    return id;
}

std::string List::getName() const {
    return name;
}

int List::getPosition() const {
    return position;
}

std::vector<Remind> List::getReminder() const {
    return reminder;
}

int List::getSize() const {
    return reminder.size();
}

void List::setID(int givenId) {
    id = givenId;
}

void List::setName(std::string givenName) {
    name = givenName;
}

void List::setPosition(int givenPos) {
    position = givenPos;
}

void List::addReminder(Remind &givenRemind) {
    reminder.push_back(givenRemind);
}
