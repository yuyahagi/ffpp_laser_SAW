#ifndef VECTORFIELD_H
#define VECTORFIELD_H

#include  <iostream>
#include  <fstream>
#include  <sstream>
#include  <string>
#include  <vector>
#include  <map>
#include  <algorithm>

#include  "vector3d.hpp"

class VectorField {
private:
  enum { BUFFSIZE = 4096 };
  std::vector<Vector3d>  vec;
  std::vector<std::pair<std::string,std::string> > header;
  int xnodes, ynodes, znodes, size;
  double  xstepsize, ystepsize, zstepsize;
  double  xbase, ybase, zbase;
  double  valuemultiplier;
  int binarysize;

  int toInt(std::string s);
  float toFloat(std::string s);
  double toDouble(std::string s);
public:
  VectorField(std::ifstream& ifs);
  VectorField(const std::vector<std::pair<std::string,std::string> > header_in, const double vector_in[][3]);
  VectorField(const VectorField& input);  // A copy constructor
  Vector3d getVector(int i) const { return vec[i]; }
  //Vector3d getVector(int i, int j, int k) const;
  inline double getx(int i, int j, int k) const;
  inline double getx(int i) const { return valuemultiplier*vec[i].getx(); }
  inline double gety(int i, int j, int k) const;
  inline double gety(int i) const { return valuemultiplier*vec[i].gety(); }
  inline double getz(int i, int j, int k) const;
  inline double getz(int i) const { return valuemultiplier*vec[i].getz(); }
  inline std::vector<std::pair<std::string,std::string> > getheader() const {
    return header;
  }
  int getxnodes(void) const { return xnodes; }
  int getynodes(void) const { return ynodes; }
  int getznodes(void) const { return znodes; }
  double getxbase(void) const { return xbase; }
  double getybase(void) const { return ybase; }
  double getzbase(void) const { return zbase; }
  double getxstepsize(void) const { return xstepsize; }
  double getystepsize(void) const { return ystepsize; }
  double getzstepsize(void) const { return zstepsize; }
  int getsize(void) const { return xnodes*ynodes*znodes; }
  double getvaluemultiplier(void) const { return valuemultiplier; }
  std::vector<bool> getmask(void);

  void writeVectorToFileB4(std::ofstream& ofs);
  void writeVectorToFileB8(std::ofstream& ofs);
  int readOhfHeaderItem(std::string& s, std::string* item);
  size_t getBinarySize(void) { return binarysize; }
};

// Returns the vector at a point with x, y, z indices of i, j, k
// 0 <= i < xnodes
//////////////////////////////////////////////////////////////////////////////
// Add an multiplication operator and multiply valuemultiplier!!!
//////////////////////////////////////////////////////////////////////////////
//inline Vector3d VectorField::getVector(int i, int j, int k) {
//  return vec[i+j*xnodes+k*xnodes*ynodes];
//}

inline double VectorField::getx(int i, int j, int k) const {
  return valuemultiplier*vec[i+j*xnodes+k*xnodes*ynodes].getx();
}

inline double VectorField::gety(int i, int j, int k) const {
  return valuemultiplier*vec[i+j*xnodes+k*xnodes*ynodes].gety();
}

inline double VectorField::getz(int i, int j, int k) const {
  return valuemultiplier*vec[i+j*xnodes+k*xnodes*ynodes].getz();
}

inline int VectorField::toInt(std::string s) {
  int v;
  std::istringstream sin(s);
  sin >> v;
  return v;
}

inline float VectorField::toFloat(std::string s) {
  float v;
  std::istringstream sin(s);
  sin >> v;
  return v;
}

inline double VectorField::toDouble(std::string s) {
  double v;
  std::istringstream sin(s);
  sin >> v;
  return v;
}

#endif
