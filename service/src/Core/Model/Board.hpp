#pragma once

#include "List.hpp"
#include <string>
#include <vector>

namespace Reminder {
namespace Core {
namespace Model {

class Board {
  public:
    Board(std::string givenTitle);
    ~Board() {}

    std::string getTitle() const;

    std::vector<List> &getList();
    void setLists(std::vector<List> const &columns);

  private:
    std::string title;
    std::vector<List> lists;
};

} // namespace Model
} // namespace Core
} // namespace Reminder
