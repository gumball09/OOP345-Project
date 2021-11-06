#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

namespace sdds {
LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
  std::ifstream f(file);

  if(!f) {
    throw std::string("Cannot open file: " + file + "!\n");
  }

  Utilities utils;
  std::string line;

  while(getline(f, line)) {
    size_t pos = 0;
    bool more = true;
    std::string firstToken, nextToken;
    Workstation* firstWorkStation;
    Workstation* nextWorkStation;

    firstToken = utils.extractToken(line, pos, more);
    firstWorkStation = *std::find_if(stations.begin(), stations.end(), [&firstToken](const Workstation* ws) {
      return ws->getItemName() == firstToken;
    });

    if(more) {
      nextToken = utils.extractToken(line, pos, more);

      nextWorkStation = *std::find_if(stations.begin(), stations.end(), [&nextToken](const Workstation* ws) {
        return ws->getItemName() == nextToken;
      });

      if(nextWorkStation) {
        firstWorkStation->setNextStation(nextWorkStation);
      }
    }


    activeLine.push_back(firstWorkStation);
    m_firstStation = activeLine.front();
    m_cntCustomerOrder = pending.size();
  }
}

void LineManager::linkStations() {
  std::vector<Workstation*> sortedStations;

  sortedStations.push_back(m_firstStation);
  if(m_firstStation->getNextStation()) {
    sortedStations.push_back(m_firstStation->getNextStation());
  }

  std::for_each(activeLine.begin(), activeLine.end() -2, [&](Workstation* ws) {
    sortedStations.push_back(sortedStations.back()->getNextStation());
  });

  activeLine = sortedStations;
}

bool LineManager::run(std::ostream& os) {
  static size_t cnt = 0;

  os << "Line Manager Iteration: " << ++cnt << "\n";

  if(!pending.empty()) {
    *m_firstStation += std::move(pending.front());
    pending.pop_front();
  }

  std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws) {
    ws->fill(os);
  });

  std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ws){
    ws->attemptToMoveOrder();
  });

  return m_cntCustomerOrder == (completed.size() + incomplete.size());
}

void LineManager::display(std::ostream& os) const {
  std::for_each(activeLine.begin(), activeLine.end(), [&os](const Workstation* ws){
    ws->display(os);
  });
}
} // namespace sdds

