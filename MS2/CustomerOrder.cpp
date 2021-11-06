// Name: Nghi Phuong Huynh Pham
// Seneca Student ID: 101412203
// Seneca email: hpnpham@myseneca.ca
// Date of completion: Oct 28th, 2021
// =================================================
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// =================================================
#include <utility>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
// Initialze static class variables
size_t CustomerOrder::m_widthField = 0;

// Custom deallocation fn
void CustomerOrder::deallocateMemory() {
    if(m_lstItem) {
      for(size_t i = 0; i < m_cntItem; i++) {
        delete m_lstItem[i];
        m_lstItem[i] = nullptr;
      }

      // delete the array of pointers
      delete[] m_lstItem;
      m_lstItem = nullptr;
    }
}

// Default constructor
CustomerOrder::CustomerOrder() : m_name {}, m_product {}, m_cntItem {0}, m_lstItem {} {};

// 1-arg constructor
// Extract tokens from a string param
CustomerOrder::CustomerOrder(const std::string& line) : CustomerOrder() {
  if(line != "") {
    Utilities utils;
    size_t pos {0};
    bool more {true};

    // Extract the name of customer
    m_name = utils.extractToken(line, pos, more);

    // Extract the order name
    m_product = utils.extractToken(line, pos, more);

    // Extract the list of items for the order
    // 1.ALLOCATE DYNAMIC MEMORY FOR THE LIST OF ITEMS
    m_lstItem = new Item*[m_cntItem + 1];

    // 2. Set the name of the item via struct's constructor
    m_lstItem[m_cntItem] = new Item(utils.extractToken(line,  pos, more));
    // Increment the # of items in list
    m_cntItem += 1;

    // If 'more' is true, means that there are more items to be added to the list
    while(more) {
      // resize the list 
      Item** temp = new Item*[m_cntItem + 1];

      // copy current array to temp array
      for(size_t i = 0; i < m_cntItem; i++) {
        temp[i] = m_lstItem[i];
      }

      // extract new item & add to temp array
      temp[m_cntItem] = new Item(utils.extractToken(line, pos, more));

      // delete current array
      delete[] m_lstItem;

      // assign temp array to current array
      m_lstItem = temp;

      // update the size of the array
      m_cntItem += 1;

      // Update m_widthField
      if(m_widthField < utils.getFieldWidth()) {
        m_widthField = utils.getFieldWidth();
      }
    }
  }
}

// Copy constructor (throw an error if called)
CustomerOrder::CustomerOrder(const CustomerOrder& src) {
  throw "CUSTOMER ORDER COPY CONSTRUCTOR SHOULD NOT BE CALLED!";
}

// Move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept : CustomerOrder() {
  // Check for self-assignment
  if(this != &src) {
    *this = std::move(src);
  }
}

// Move assignment
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
  // Check for self-assignment
  if(this != &src) {
    // Delete current resources (if there is)
    deallocateMemory();
    
    // Copy source resource address to current object's address
    m_lstItem = src.m_lstItem;

    // Swap instance variables
    m_name = src.m_name;
    m_product = src.m_product;
    m_cntItem = src.m_cntItem;

    // Initialize source resources 
    src.m_lstItem = nullptr;
    src.m_name = "";
    src.m_product = "";
    src.m_cntItem = 0;
  }

  return *this;
}

// Destructor
CustomerOrder::~CustomerOrder() {
  // Deallocate the array of pointers
  deallocateMemory();
}

// Return true if all items in the order have been filled
bool CustomerOrder::isFilled() const {
  auto checkFilled = [](const Item* item) {
    return item->m_isFilled;
  };

  return std::all_of(m_lstItem, m_lstItem + m_cntItem, checkFilled);
}

// Return true if all items specified by itemName have been filled
// If item is non-existent, the state is considered to be true
bool CustomerOrder::isItemFilled(const std::string& itemName) const {
  auto checkItemNameandFilled = [&itemName](const Item* item) {
    return item->m_itemName == itemName || !item->m_isFilled;
  };

  return std::all_of(m_lstItem, m_lstItem + m_cntItem, checkItemNameandFilled);
}

// Fill all items in the current order
void CustomerOrder::fillItem(Station& station, std::ostream& os) {
  auto fillAnItem = [this, &station, &os](Item* item) {
    if(item->m_itemName == station.getItemName()) {
      if(station.getQuantity() > 0) {
        station.updateQuantity();
        item->m_serialNumber = station.getNextSerialNumber();
        item->m_isFilled = true;

        os << "    Filled " << this->m_name << ", " 
          << this->m_product << " [" 
          << item->m_itemName << "]\n"; 
      } else {
        os << "    Unable to fill " 
          << this->m_name << ", " 
          << this->m_product << " [" 
          << item->m_itemName << "]\n";
      }
    }
  };

  std::for_each(m_lstItem, m_lstItem + m_cntItem, fillAnItem);
}

// Display the state of the current object
void CustomerOrder::display(std::ostream& os) const {
  using std::setw;
  using std::setfill;
  using std::left;
  using std::right;
  
  os << this->m_name << " - " << this->m_product << "\n";
  // loop through each item in the list and print
  auto printOutput = [&os](const Item* item) {
    os << "[" << setfill('0') << setw(6) << item->m_serialNumber << setfill(' ') << "] ";
    os << setw(m_widthField) << left << item->m_itemName << right << " - ";
    os << (item->m_isFilled ? "FILLED" : "TO BE FILLED") << "\n";
  };

  std::for_each(m_lstItem, m_lstItem + m_cntItem, printOutput);
}
} // namespace sdds
