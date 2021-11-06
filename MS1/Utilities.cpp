// Name: Nghi Phuong Huynh Pham
// Seneca Student ID: 101412203
// Seneca email: hpnpham@myseneca.ca
// Date of completion: Oct 27th, 2021
// =================================================
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// =================================================
#include "Utilities.h"

namespace sdds {
// Initialize static class variable (I chose the default to be ',')
char Utilities::m_delimiter = ','; 

// Default constructor
Utilities::Utilities() : m_fieldWidth {1} {}

// Set the field width to the value of param
void Utilities::setFieldWidth(size_t newWidth) {
  // only set new value if param > 0 
  if(newWidth > 0) {
    m_fieldWidth = newWidth;
  }
}

// Return the field width of the current object
size_t Utilities::getFieldWidth() const {
  return m_fieldWidth;
}

// Extract a token from a string
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
  std::string token {""};
  
  if(str != "" && more) {
    // find the next occurrence of ',' starting @ next_pos (returns the pos)
    size_t found = str.find(m_delimiter, next_pos);

    // npos is -1 (means "unfound")
    if(found != std::string::npos) {
      more = true;
    } else {
      more = false;
    }

    // throw an error if next occurrence of delimiter is the same as next_pos
    if(found == next_pos) {
      more = false;
      throw "No token!";
    }

    // extract the string from next_pos to the pos that is the length of the string to be extracted
    // @param next_pos: position of the 1st char to include
    // @param found - next_pos: lengh of the substring
    token = str.substr(next_pos, found - next_pos);

    // update next_pos
    // (the next occurrence of char that is not the delimiter)
    next_pos = found + 1; 

    // update the size of field width if length of token is greater
    if(token.size() > m_fieldWidth) {
      m_fieldWidth = token.size();
    }
  }
  
  return token;
}

// Set delimiter for the class
void Utilities::setDelimiter(char newDelimiter) {
  m_delimiter = newDelimiter;
}

// Return the delimiter
char Utilities::getDelimiter() {
  return m_delimiter;
}
} // namespace sdds
