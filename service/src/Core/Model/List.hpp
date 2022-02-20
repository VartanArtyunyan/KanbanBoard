#pragma once

#include "Remind.hpp"
#include <string>
#include <vector>

namespace Reminder {
namespace Core {
namespace Model {
class List {
  public:
    List(int id, std::string name, int position);
    ~List(){};

    int getId() const;
    std::string getName() const;
    int getPosition() const;
    std::vector<Remind> getReminder() const;
    int getSize() const;

    void setID(int givenId);
    void setName(std::string givenName);
    void setPosition(int givenPosition);
    void addReminder(Remind &reminder);

  private:
    int id;
    std::string name;
    int position;
    std::vector<Remind> reminder;
};
} // namespace Model
} // namespace Core
} // namespace Reminder
