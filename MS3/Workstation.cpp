#include "Workstation.h"
#include "CustomerOrder.h"
#include <iterator>
#include <pthread.h>

namespace sdds {
// Definition of extern variables
std::deque<CustomerOrder> pending{};
std::deque<CustomerOrder> completed{};
std::deque<CustomerOrder> incomplete{};

// 1-arg constructor
// pass the param to Station base class
Workstation::Workstation(const std::string& line) : Station(line) {};

// Fill the order @ the front of queue, if there are CustomerOrders
void Workstation::fill(std::ostream& os) {
  // Check if the queue has items
  if(!m_orders.empty()) {
    // Get the 1st item of the queue
    // Check if the 1st item of queue has already been filled
    if(!m_orders.front().isItemFilled(getItemName())) {
      // If not, fill the item
      m_orders.front().fillItem(*this, os);
    }
  }
}

// Move the order order @ the front of the queue to the next station
bool Workstation::attemptToMoveOrder() {
  bool ok = false;

  if(!m_orders.empty()) {
    if(m_orders.front().isItemFilled(getItemName())) {
      if(!m_pNextStation) {
        completed.push_back(std::move(m_orders.front()));
      } else {
        *m_pNextStation += std::move(m_orders.front());
      }

      m_orders.pop_front();
      ok = true;

    } else if(getQuantity() < 1) {
      if(!m_pNextStation) {
        incomplete.push_back(std::move(m_orders.front()));
      } else {
        *m_pNextStation += std::move(m_orders.front());
      }

      m_orders.pop_front();
      ok = true;
    }
  }

  std::deque<CustomerOrder> tmpOrders = std::move(completed);
  size_t tmpOrdersSize = tmpOrders.size();

  for(size_t i = 0; i < tmpOrdersSize; i++) {
    if(tmpOrders.front().isFilled()) {
      completed.push_back(std::move(tmpOrders.front()));
    } else {
      incomplete.push_back(std::move(tmpOrders.front()));
    }

    tmpOrders.pop_front();
  }

  return ok;
}

// Store the address of referenced Workstation obj in ptr to the next m_pNextStation
void Workstation::setNextStation(Workstation* station) {
  m_pNextStation = station;
}

// Return the address of next Workstation
Workstation* Workstation::getNextStation() const {
  return m_pNextStation;;
}

// Display
void Workstation::display(std::ostream& os) const {
  os << Station::getItemName() << " --> ";
  if(!m_pNextStation) {
    os << "End of Line";
  } else {
     os << m_pNextStation->getItemName();
  }

  os << "\n";
}

// Move CustomerOrders referenced in param newOrder to the back of the queue
Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
  m_orders.push_back(std::move(newOrder));
  return *this;
}
} // namespace sdds
