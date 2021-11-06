// Name: Nghi Phuong Huynh Pham
// Seneca Student ID: 101412203
// Seneca email: hpnpham@myseneca.ca
// Date of completion: Oct 27th, 2021
// =================================================
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// =================================================
#ifndef _SDDS_STATION_H_
#define _SDDS_STATION_H_

#include <string>
#include <ostream>

namespace sdds { 
class Station {
  size_t m_id;
  std::string m_name;
  std::string m_desc;
  size_t m_serialNumber;
  size_t m_quantity;

  // declared 'static' since all objects share these members 
  static size_t m_widthField;
  static size_t m_idGenerator;

  public:
  Station();
  Station(const std::string&);

  const std::string& getItemName() const;
  size_t getNextSerialNumber();
  size_t getQuantity() const;
  void updateQuantity();
  void display(std::ostream&, bool) const;
};
} // namespace sdds

#endif // !_SDDS_STATION_H_
