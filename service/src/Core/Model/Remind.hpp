#pragma once

#include <string>

namespace Reminder {
namespace Core {
namespace Model {

class Remind {
  public:
    Remind(int id, std::string givenName, int givenPosition, std::string givenDate, bool givenFlag);
    ~Remind(){};

    int getId() const;
    std::string getName() const;
    int getPosition() const;
    std::string getDatum() const;
    bool isFlagged() const;
    bool isToday();

    void setID(int givenID);
    void setName(std::string givenName);
    void setPosition(int givenPos);
    void setDatum(std::string Datum);
    void setFlagged(bool flag);
    void setFlagged(int flag);

  private:
    int id;
    std::string name;
    int position;
    std::string date;
    bool flagged;
};

} // namespace Model
} // namespace Core
} // namespace Reminder
