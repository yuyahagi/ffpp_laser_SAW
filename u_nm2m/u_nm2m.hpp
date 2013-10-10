#ifndef U_NM2M_H
#define U_NM2M_H

#include  <iostream>
#include  <fstream>
#include  <string>
#include  <vector>
#include  <map>

#include  "vectorfield.hpp"

extern bool debugFlag;
const unsigned int  BUFFSIZE = 4096;

// Default filename to read (for debugging)
const char  DEFAULTUINPUTFILE[] = "testdata/testdata_u_text.ovf";
const char  DEFAULTUOUTPUTFILE[] = "testdata/testdata_u.ovf";

void dispHelp();
// ===========================================================================
// Functions for byte order conversion
// ===========================================================================
#if BYTE_ORDER == LITTLE_ENDIAN
#define bswap(n) bswapGeneric(n)
#else
#define bswap(n) (n)
#endif

template<typename T>
inline void bswapGeneric(T& value);
inline void bswap16(unsigned short& d);
inline void bswap32(unsigned int& d);
inline void bswap64(unsigned long& d);

template<typename T>
inline void bswapGeneric(T& value) {
  enum { SIZE = sizeof(T) };
  if (SIZE == 2)
    bswap16(reinterpret_cast<unsigned short&>(value));
  else if (SIZE == 4)
    bswap32(reinterpret_cast<unsigned int&>(value));
  else if (SIZE == 8)
    bswap64(reinterpret_cast<unsigned long&>(value));
}

inline void bswap16(unsigned short& d) {
  d = ((d & 0xff) << 8) | ((d >> 8) & 0xff);
}

inline void bswap32(unsigned int& d) {
  d = (d >> 24) | (d << 24) | ((d >> 8) & 0xff00) | ((d << 8) & 0xff0000);
}

inline void bswap64(unsigned long& d) {
  d = (d >> 56) | (d << 56) | ((d >> 40) & 0xff00)
    | ((d << 40) & 0xff000000000000)
    | ((d >> 24) & 0xff0000) | ((d << 24) & 0xff0000000000)
    | ((d >> 8) & 0xff000000) | ((d << 8) & 0xff00000000);
}

#endif
