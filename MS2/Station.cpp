// Name: Nghi Phuong Huynh Pham
// Seneca Student ID: 101412203
// Seneca email: hpnpham@myseneca.ca
// Date of completion: Oct 27th, 2021
// =================================================
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// =================================================
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
// initialize static class variables 
size_t Station::m_widthField = 0;
size_t Station::m_idGenerator = 0;

// Default constructor
Station::Station() : m_id {0}, m_name {}, m_desc {}, m_serialNumber {0}, m_quantity {0} {
}

// 1-arg constructor
// Extract the string param 
Station::Station(const std::string& line) : Station() {
  if(line != "") {
    Utilities utils;
    size_t pos {0};
    bool more {true};

    m_id = m_idGenerator += 1;

    // Extract the name 
    m_name = utils.extractToken(line, pos, more);

    // Extract the serial number
    m_serialNumber = static_cast<size_t>(std::stoi(utils.extractToken(line, pos, more)));

    // Extract the quantity
    m_quantity = static_cast<size_t>(std::stoi(utils.extractToken(line, pos, more)));

    // Update the field to the size (length) of m_name
    // Width is determined by the longest name read from file
    if(m_name.size() > m_widthField) {
      m_widthField = m_name.size();
    }

    // Extract the description
    m_desc = utils.extractToken(line, pos, more);
  }
}

// Return the name of current object
const std::string& Station::getItemName() const {
  return m_name;
}

// Return the next serial number
size_t Station::getNextSerialNumber() {
  // return the value before incrementing it
  return m_serialNumber++;
}

// Return the quantity 
size_t Station::getQuantity() const {
  return m_quantity;
}

// Update the quantity
void Station::updateQuantity() {
  // only subtract if existing quantity > 0
  if(m_quantity > 0) {
    m_quantity -= 1;
  }
}

// Display the information
void Station::display(std::ostream& os, bool full) const {
  if(m_id && m_name != "" && m_serialNumber && m_quantity && m_desc != "") {
    using std::setfill;
    using std::setw;
    using std::left;
    using std::right;

    os << "[" << setfill('0') << setw(3) << m_id << "]" << setfill(' ');
    os << " Item: " << left << setw(m_widthField) << m_name << right;
    os << " [" << setfill('0') << setw(6) << m_serialNumber << "]" << setfill(' ');

    if(full) {
      os << " Quantity: " << left << setw(m_widthField) << m_quantity << right;
      os << right << " Description: " << m_desc;
    }

    os << "\n";
  }
}
} // namespace sdds
