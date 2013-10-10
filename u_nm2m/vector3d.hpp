#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3d {
protected:
  double  x, y, z;
public:
  Vector3d() { x = y = z = 0.; }
  Vector3d(double _x, double _y, double _z) {x=_x; y=_y; z=_z;}
  inline void put(double _x, double _y, double _z) {x=_x; y=_y; z=_z;}
  inline double getx(void) const { return x; }
  inline double gety(void) const { return y; }
  inline double getz(void) const { return z; }
  inline double getsq(void) const { return x*x+y*y+z*z; }
  inline Vector3d& operator=(const Vector3d& v);
  friend inline double operator*( const Vector3d& u, const Vector3d& v );
  inline double magsq(void) { return x*x+y*y+z*z; }
};

inline Vector3d& Vector3d::operator=(const Vector3d& v) {
    x = v.x; y = v.y; z = v.z;
    return *this;
}

inline double operator*( const Vector3d& u, const Vector3d& v ) {
  return u.x*v.x+u.y+v.y+u.z*v.z;
}

#endif
