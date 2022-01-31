#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cstdint>
#include <cmath>
#include <ostream>
#include <limits>

#ifndef M_RAD2DEG
   #define M_RAD2DEG (180.0/M_PI)
#endif

#ifndef M_DEG2RAD
   #define M_DEG2RAD (M_PI/180.0)
#endif

/**
 * @brief The Vector3D class represents a vector or vertex in 3D space
 */
class Vector3D
{
   public:
      Vector3D();
      Vector3D(double x, double y, double z);
      Vector3D(const Vector3D &vector);
      Vector3D &operator=(const Vector3D &vector);
      Vector3D &operator*=(double factor);
      Vector3D &operator/=(double factor);
      Vector3D &operator+=(const Vector3D &vector);
      Vector3D &operator-=(const Vector3D &vector);

      friend const Vector3D operator*(double factor, const Vector3D &vector);
      friend const Vector3D operator*(const Vector3D &vector, double factor);
      friend const Vector3D operator/(const Vector3D &vector, double factor);
      friend const Vector3D operator+(const Vector3D &vector1, const Vector3D &vector2);
      friend const Vector3D operator-(const Vector3D &vector1, const Vector3D &vector2);
      friend bool operator==(const Vector3D &vector1, const Vector3D &vector2);
      friend bool operator!=(const Vector3D &vector1, const Vector3D &vector2);
      friend std::ostream& operator<<(std::ostream& out, const Vector3D &vector);

      double x() const;
      double y() const;
      double z() const;

      void setX(double x);
      void setY(double y);
      void setZ(double z);

      void set(const Vector3D &vector);
      void set(double x, double y, double z);

      double length() const;

      double distance(const Vector3D &vector) const;
      double distance(double x, double y, double z) const;

      double angleRad(const Vector3D &vector) const;
      double angleRad(double x, double y, double z) const;

      double angleDeg(const Vector3D &vector) const;
      double angleDeg(double x, double y, double z) const;

      bool isZero() const;

   private:
      double pX;
      double pY;
      double pZ;

   protected:
      static inline bool isEqual(double value1, double value2);
      static inline bool isNotEqual(double value1, double value2);
      static inline bool isZero(double value);
      static inline bool isNotZero(double value);

      static constexpr double pEpsilon=std::numeric_limits<double>::epsilon();
      static constexpr double pEpsilonNeg=std::numeric_limits<double>::epsilon()*-1;
};

bool inline Vector3D::isEqual(double value1, double value2)
{
   if(value1>=value2)
   {
      if((value1-value2)<pEpsilon) return true; else return false;
   } else
   {
      if((value2-value1)<pEpsilon) return true; else return false;
   }
}

bool inline Vector3D::isNotEqual(double value1, double value2)
{
   if(value1>=value2)
   {
      if((value1-value2)<pEpsilon) return false; else return true;
   } else
   {
      if((value2-value1)<pEpsilon) return false; else return true;
   }
}

bool inline Vector3D::isZero(double value)
{
   if(value>=0.0)
   {
      if(value<pEpsilon) return true; else return false;
   } else
   {
      if(value>pEpsilonNeg) return true; else return false;
   }
}

bool inline Vector3D::isNotZero(double value)
{
   if(value>=0.0)
   {
      if(value<pEpsilon) return false; else return true;
   } else
   {
      if(value>pEpsilonNeg) return false; else return true;
   }
}

#endif // VECTOR3D_H
