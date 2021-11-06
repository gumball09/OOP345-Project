#ifndef _SDDS_WORKSTATION_H_
#define _SDDS_WORKSTATION_H_

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {
// GLOBAL VARIABLES
extern std::deque<CustomerOrder> pending;
extern std::deque<CustomerOrder> completed;
extern std::deque<CustomerOrder> incomplete;

class Workstation : public Station {
  std::deque<CustomerOrder> m_orders;
  Workstation* m_pNextStation{nullptr};

  public:
  // DELETE COPY & MOVE OPERATORS
  Workstation(const Workstation&) = delete;
  Workstation& operator=(const Workstation&) = delete;
  Workstation(Workstation&&) = delete;
  Workstation& operator=(Workstation&&) = delete;
  // ----------------------------

  Workstation() = default;
  Workstation(const std::string&);
  void fill(std::ostream&);
  bool attemptToMoveOrder();
  void setNextStation(Workstation*);
  Workstation* getNextStation() const;
  void display(std::ostream&) const;
  Workstation& operator+=(CustomerOrder&&);
};
} // namespace sdds

#endif // !DEBUG
