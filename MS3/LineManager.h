#ifndef _SDDS_LINEMANAGER_H_
#define _SDDS_LINEMANAGER_H_

#include <vector>
#include "Workstation.h"

namespace sdds {
class LineManager : public Workstation {
  std::vector<Workstation*> activeLine;
  size_t m_cntCustomerOrder {0};
  Workstation* m_firstStation {nullptr};

  public:
  LineManager(const std::string&, const std::vector<Workstation*>&);
  void linkStations();
  bool run(std::ostream&);
  void display(std::ostream&) const;
};
} // namespace sdds

#endif // !_SDDS_LINEMANAGER_H_
