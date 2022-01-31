#include "vector3d.h"

Vector3D::Vector3D()
{
   pX=0.0; pY=0.0; pZ=0.0;
}

Vector3D::Vector3D(double x, double y, double z)
{
   pX=x; pY=y; pZ=z;
}

Vector3D::Vector3D(const Vector3D &vector)
{
   pX=vector.pX; pY=vector.pY; pZ=vector.pZ;
}

Vector3D &Vector3D::operator=(const Vector3D &vector)
{
   pX=vector.pX; pY=vector.pY; pZ=vector.pZ;
   return *this;
}

Vector3D &Vector3D::operator*=(double factor)
{
   pX*=factor; pY*=factor; pZ*=factor;
   return *this;
}

Vector3D &Vector3D::operator/=(double factor)
{
   if(Vector3D::isZero(factor)) return *this;
   pX/=factor; pY/=factor; pZ/=factor;
   return *this;
}

Vector3D &Vector3D::operator+=(const Vector3D &vector)
{
   pX+=vector.pX; pY+=vector.pY; pZ+=vector.pZ;
   return *this;
}

Vector3D &Vector3D::operator-=(const Vector3D &vector)
{
   pX-=vector.pX; pY-=vector.pY; pZ-=vector.pZ;
   return *this;
}

const Vector3D operator*(double factor, const Vector3D &vector)
{
   return Vector3D(vector.pX*factor,vector.pY*factor,vector.pZ*factor);
}

const Vector3D operator*(const Vector3D &vector, double factor)
{
   return Vector3D(vector.pX*factor,vector.pY*factor,vector.pZ*factor);
}

const Vector3D operator/(const Vector3D &vector, double factor)
{
   if(Vector3D::isZero(factor)) return vector;
   return Vector3D(vector.pX/factor,vector.pY/factor,vector.pZ/factor);
}

const Vector3D operator+(const Vector3D &vector1, const Vector3D &vector2)
{
   return Vector3D(vector1.pX+vector2.pX,vector1.pY+vector2.pY,vector1.pZ+vector2.pZ);
}

const Vector3D operator-(const Vector3D &vector1, const Vector3D &vector2)
{
   return Vector3D(vector1.pX-vector2.pX,vector1.pY-vector2.pY,vector1.pZ-vector2.pZ);
}

bool operator==(const Vector3D &vector1, const Vector3D &vector2)
{
   if(Vector3D::isNotEqual(vector1.pX,vector2.pX) || Vector3D::isNotEqual(vector1.pY,vector2.pY) || Vector3D::isNotEqual(vector1.pZ,vector2.pZ)) return false; else return true;
}

bool operator!=(const Vector3D &vector1, const Vector3D &vector2)
{
   if(Vector3D::isNotEqual(vector1.pX,vector2.pX) || Vector3D::isNotEqual(vector1.pY,vector2.pY) || Vector3D::isNotEqual(vector1.pZ,vector2.pZ)) return true; else return false;
}

std::ostream& operator<<(std::ostream& out, const Vector3D &vector)
{
   std::string str="Vector3D(";
   str+=std::to_string(vector.pX)+","+std::to_string(vector.pY)+","+std::to_string(vector.pZ)+", ";
   str+="length="+std::to_string(vector.length())+")";
   out << str;
   return out;
}

double Vector3D::x() const
{
   return pX;
}

double Vector3D::y() const
{
   return pY;
}

double Vector3D::z() const
{
   return pZ;
}

void Vector3D::setX(double x)
{
   pX=x;
}

void Vector3D::setY(double y)
{
   pY=y;
}

void Vector3D::setZ(double z)
{
   pZ=z;
}

void Vector3D::set(const Vector3D &vector)
{
   pX=vector.pX; pY=vector.pY; pZ=vector.pZ;
}

void Vector3D::set(double x, double y, double z)
{
   pX=x; pY=y; pZ=z;
}

double Vector3D::length() const
{
   return sqrt(pow(pX,2.0)+pow(pY,2.0)+pow(pZ,2.0));
}

double Vector3D::distance(const Vector3D &vector) const
{
   return sqrt(pow(vector.pX-pX,2.0)+pow(vector.pY-pY,2.0)+pow(vector.pZ-pZ,2.0));
}

double Vector3D::distance(double x, double y, double z) const
{
   return sqrt(pow(x-pX,2.0)+pow(y-pY,2.0)+pow(z-pZ,2.0));
}

double Vector3D::angleRad(const Vector3D &vector) const
{
   if((Vector3D::isNotZero(vector.pX) || Vector3D::isNotZero(vector.pY) || Vector3D::isNotZero(vector.pZ)) && (Vector3D::isNotZero(pX) || Vector3D::isNotZero(pY) || Vector3D::isNotZero(pZ)))
   {
      double arccos=(vector.pX*pX+vector.pY*pY+vector.pZ*pZ)/(sqrt(pow(vector.pX,2.0)+pow(vector.pY,2.0)+pow(vector.pZ,2.0))*sqrt(pow(pX,2.0)+pow(pY,2.0)+pow(pZ,2.0)));
      if(arccos>1.0) arccos=1.0;
      if(arccos<-1.0) arccos=-1.0;
      return acos(arccos);
   } else return 0.0;
}

double Vector3D::angleRad(double x, double y, double z) const
{
   if((Vector3D::isNotZero(x) || Vector3D::isNotZero(y) || Vector3D::isNotZero(z)) && (Vector3D::isNotZero(pX) || Vector3D::isNotZero(pY) || Vector3D::isNotZero(pZ)))
   {
      double arccos=(x*pX+y*pY+z*pZ)/(sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0))*sqrt(pow(pX,2.0)+pow(pY,2.0)+pow(pZ,2.0)));
      if(arccos>1.0) arccos=1.0;
      if(arccos<-1.0) arccos=-1.0;
      return acos(arccos);
   } else return 0.0;
}

double Vector3D::angleDeg(const Vector3D &vector) const
{
   return angleRad(vector)*M_RAD2DEG;
}

double Vector3D::angleDeg(double x, double y, double z) const
{
   return angleRad(x,y,z)*M_RAD2DEG;
}

bool Vector3D::isZero() const
{
   if(Vector3D::isNotZero(pX) || Vector3D::isNotZero(pY) || Vector3D::isNotZero(pZ)) return false; else return true;
}
