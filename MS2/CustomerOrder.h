// Name: Nghi Phuong Huynh Pham
// Seneca Student ID: 101412203
// Seneca email: hpnpham@myseneca.ca
// Date of completion: Oct 28th, 2021
// =================================================
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// =================================================
#ifndef _SDDS_CUSTOMERORDER_H_
#define _SDDS_CUSTOMERORDER_H_

#include <string>
#include "Station.h"

namespace sdds {
  struct Item {
    std::string m_itemName;
    size_t m_serialNumber {0};
    bool m_isFilled {false};

    Item(const std::string& src) : m_itemName(src) {};
  };

class CustomerOrder {
  std::string m_name;
  std::string m_product;
  size_t m_cntItem;
  Item** m_lstItem;

  // declared 'static' as all objects of this class share the same member
  static size_t m_widthField;

  // custom deallocation fn
  void deallocateMemory();

  public:
  CustomerOrder();
  CustomerOrder(const std::string&);

  // COPY ASSIGNMENT operators
  CustomerOrder(const CustomerOrder&);
  CustomerOrder& operator=(const CustomerOrder&) = delete;

  // MOVE ASSIGNMENT operators 
  CustomerOrder(CustomerOrder&&) noexcept;
  CustomerOrder& operator=(CustomerOrder&&) noexcept;

  // DESTRUCTOR
  ~CustomerOrder();

  bool isFilled() const;
  bool isItemFilled(const std::string&) const;
  void fillItem(Station&, std::ostream&);
  void display(std::ostream&) const;
};
} // namespace sdds

#endif // !_SDDS_CUSTOMERORDER_H_
