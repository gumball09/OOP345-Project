// Name: Nghi Phuong Huynh Pham
// Seneca Student ID: 101412203
// Seneca email: hpnpham@myseneca.ca
// Date of completion: Oct 27th, 2021
// =================================================
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// =================================================
#ifndef _SDDS_UTILITIES_H_
#define _SDDS_UTILITIES_H_

#include <string>

namespace sdds {
class Utilities {
  size_t m_fieldWidth;

  // declared as 'static' since all objects share the same delimiter
  static char m_delimiter;

  public:
  Utilities();
  void setFieldWidth(size_t);
  size_t getFieldWidth() const;
  std::string extractToken(const std::string&, size_t&, bool&);

  static void setDelimiter(char);
  static char getDelimiter();
};
} // namespace sdds

#endif // !_SDDS_UTILITIES_H_
