#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"

namespace sdds {
// 2-arg constructor
LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) : Workstation() {
  std::ifstream f(file);

  if(f.is_open()) {
    m_cntCustomerOrder = pending.size(); // get the original size from pending 

    Utilities utils;
    size_t pos {0};
    bool more {true};

    std::string line;
    std::string token;
    Workstation* current {nullptr};
    Workstation* next {nullptr};

    while(std::getline(f, line)) {
      // extract the FIRST token in line
      token = utils.extractToken(line, pos, more);

      if(more) {
        // find the STATION having the same name as the FIRST token above
        current = *std::find_if(stations.begin(), stations.end(), [&token](const Workstation& ws) {
          return ws.getItemName() == token;
        });

        // extract the SECOND token on the same line
        token = utils.extractToken(line, pos, more);

        // find the NEXT STATION having the same name as SECOND token above
        next = *std::find_if(stations.begin(), stations.end(), [&token](const Workstation& ws) {
          return ws.getItemName() == token;
        });
        if(next) {
          // set the next token as the next station from the CURRENT STATION
          current->setNextStation(next);
        } 
      }

      // reset the variables for next extraction
      more = true;
      pos = 0;
    }

    // update the size of customer order
    m_cntCustomerOrder = pending.size();

    // assign the very first TOKEN as the FIRST station
    m_firstStation = this->activeLine.front();
  }
}


} // namespace sdds
