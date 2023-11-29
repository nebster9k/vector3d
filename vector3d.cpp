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
   if(Vector3D::isNotZero(factor))
   {
      pX/=factor; pY/=factor; pZ/=factor;
   } else pZ=pY=pX=std::numeric_limits<double>::quiet_NaN();
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
   if(Vector3D::isZero(factor)) return Vector3D(std::numeric_limits<double>::quiet_NaN(),std::numeric_limits<double>::quiet_NaN(),std::numeric_limits<double>::quiet_NaN());
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

bool Vector3D::setLength(double length)
{
   if(isNotZero(length))
   {
      if(Vector3D::isZero(pX) && Vector3D::isZero(pY) && Vector3D::isZero(pZ)) return false;
      double factor=sqrt(pow(pX,2.0)+pow(pY,2.0)+pow(pZ,2.0))/length;
      pX=pX/factor; pY=pY/factor; pZ=pZ/factor;
   } else pZ=pY=pX=0.0;
   return true;
}

double Vector3D::distance(const Vector3D &vector) const
{
   return sqrt(pow(vector.pX-pX,2.0)+pow(vector.pY-pY,2.0)+pow(vector.pZ-pZ,2.0));
}

double Vector3D::distance(double x, double y, double z) const
{
   return sqrt(pow(x-pX,2.0)+pow(y-pY,2.0)+pow(z-pZ,2.0));
}

double Vector3D::angle(const Vector3D &vector, Vector3D::AngularUnits units) const
{
   return angle(vector.pX,vector.pY,vector.pZ,units);
}

double Vector3D::angle(double x, double y, double z, Vector3D::AngularUnits units) const
{
   if((Vector3D::isNotZero(x) || Vector3D::isNotZero(y) || Vector3D::isNotZero(z)) && (Vector3D::isNotZero(pX) || Vector3D::isNotZero(pY) || Vector3D::isNotZero(pZ)))
   {
      double arccos=(x*pX+y*pY+z*pZ)/(sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0))*sqrt(pow(pX,2.0)+pow(pY,2.0)+pow(pZ,2.0)));
      if(arccos>1.0) arccos=1.0;
      if(arccos<-1.0) arccos=-1.0;
      if(units==Vector3D::AngularUnits::Degrees) return acos(arccos)*M_RAD2DEG; else return acos(arccos);
   } else return 0.0;
}

void Vector3D::rotate(const Vector3D& vector, double angle, AngularUnits units)
{
   rotate(vector.pX,vector.pY,vector.pZ,angle,units);
}

void Vector3D::rotate(double x, double y, double z, double angle, AngularUnits units)
{
   if(units==Vector3D::AngularUnits::Degrees) angle*=M_DEG2RAD;

   if((Vector3D::isNotZero(x) || Vector3D::isNotZero(y) || Vector3D::isNotZero(z)) && (Vector3D::isNotZero(pX) || Vector3D::isNotZero(pY) || Vector3D::isNotZero(pZ)) && Vector3D::isNotZero(angle))
   {
      double axisLength=sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0)); x/=axisLength; y/=axisLength; z/=axisLength;
      double halfAngle=angle/-2.0,halfAngleSin=sin(halfAngle);
      Quaternion t,r={.x=x*halfAngleSin,.y=y*halfAngleSin,.z=z*halfAngleSin,.w=cos(halfAngle)};
      t.w=0.0-r.x*pX-r.y*pY-r.z*pZ; t.x=r.w*pX+r.y*pZ-r.z*pY; t.y=r.w*pY-r.x*pZ+r.z*pX; t.z=r.w*pZ+r.x*pY-r.y*pX;
      r.x*=-1.0; r.y*=-1.0; r.z*=-1.0;
      pX=t.w*r.x+t.x*r.w+t.y*r.z-t.z*r.y; pY=t.w*r.y-t.x*r.z+t.y*r.w+t.z*r.x; pZ=t.w*r.z+t.x*r.y-t.y*r.x+t.z*r.w;
   }
}

bool Vector3D::isZero() const
{
   if(Vector3D::isNotZero(pX) || Vector3D::isNotZero(pY) || Vector3D::isNotZero(pZ)) return false; else return true;
}

bool Vector3D::isNaN() const
{
   if(std::isnan(pX) || std::isnan(pY) || std::isnan(pZ)) return true; else return false;
}
