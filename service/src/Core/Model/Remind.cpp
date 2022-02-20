#include "Remind.hpp"

using namespace Reminder::Core::Model;

Remind::Remind(int id, std::string givenTitle, int givenPosition, std::string givenDate, bool givenFlag)
    : id(id), name(givenTitle), position(givenPosition), date(givenDate), flagged(givenFlag) {}

int Remind::getId() const {
    return id;
}

std::string Remind::getName() const {
    return name;
}

int Remind::getPosition() const {
    return position;
}

std::string Remind::getDatum() const {
    return date;
}

bool Remind::isFlagged() const {
    return flagged;
}

void Remind::setID(int givenID) {
    id = givenID;
}

void Remind::setName(std::string givenName) {
    name = givenName;
}

void Remind::setPosition(int givenPos) {
    position = givenPos;
}

void Remind::setDatum(std::string givenDate) {
    date = givenDate;
}
