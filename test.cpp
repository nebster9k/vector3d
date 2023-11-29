#include <catch2/catch_all.hpp>
#include <vector3d.h>

#include <random>

double rx;
double ry;
double rz;

TEST_CASE("Generate random")
{
   rx=Catch::Generators::random(-50.0,50.0).get();
   ry=Catch::Generators::random(-50.0,50.0).get();
   rz=Catch::Generators::random(-50.0,50.0).get();
}

TEST_CASE("Zero check")
{
   Vector3D vector;
   CHECK(vector.isZero());

   vector.set(0.0,0.0,0.0);
   CHECK(vector.isZero());

   vector.set(+0.0,-0.0,0.0);
   CHECK(vector.isZero());

   vector.set(-0.0,0.0,+0.0);
   CHECK(vector.isZero());

   vector.set(0.0,+0.0,-0.0);
   CHECK(vector.isZero());

   vector.set(42.0,0.0,0.0);
   CHECK(!vector.isZero());

   vector.set(0.0,42.0,0.0);
   CHECK(!vector.isZero());

   vector.set(0.0,0.0,42.0);
   CHECK(!vector.isZero());
}

TEST_CASE("Internal state check")
{
   CAPTURE(rx); CAPTURE(ry); CAPTURE(rz);

   Vector3D vector;
   vector.set(rx,ry,rz);
   CHECK(vector.x()==rx);
   CHECK(vector.y()==ry);
   CHECK(vector.z()==rz);
}

TEST_CASE("Constructors check")
{
   CAPTURE(rx); CAPTURE(ry); CAPTURE(rz);

   Vector3D vector;
   CHECK(vector.x()==0.0);
   CHECK(vector.y()==0.0);
   CHECK(vector.z()==0.0);

   Vector3D vector2(rx,ry,rz);
   CHECK(vector2.x()==rx);
   CHECK(vector2.y()==ry);
   CHECK(vector2.z()==rz);

   Vector3D vector3(vector2);
   CHECK(vector3.x()==rx);
   CHECK(vector3.y()==ry);
   CHECK(vector3.z()==rz);
}

TEST_CASE("Overloads check")
{
   CAPTURE(rx); CAPTURE(ry); CAPTURE(rz);

   Vector3D vector1(rx,ry,rz),vector2;

   SECTION("Set")
   {
      vector1.set(rx,ry,rz);
      CHECK(vector1.x()==rx);
      CHECK(vector1.y()==ry);
      CHECK(vector1.z()==rz);
   }

   SECTION("Assignment")
   {
      vector2=vector1;
      CHECK(vector2.x()==rx);
      CHECK(vector2.y()==ry);
      CHECK(vector2.z()==rz);
   }

   SECTION("Compare")
   {
      vector2.set(vector1);
      CHECK(vector2==vector1);
      CHECK(vector1==vector2);

      vector2.set(vector1.x()+1.0,vector1.y()-2.0,vector1.z()+3.0);
      CHECK(vector2!=vector1);
      CHECK(vector1!=vector2);
   }

   SECTION("Addition")
   {
      vector2=vector1;
      vector2+=vector2;
      CHECK(vector2==Vector3D(rx+rx,ry+ry,rz+rz));

      vector2=vector1+Vector3D(1.0,-2.0,3.0);
      CHECK(vector2==Vector3D(rx+1.0,ry-2.0,rz+3.0));
   }

   SECTION("Subtraction")
   {
      vector2=vector1;
      vector2-=vector2;
      CHECK(vector2.isZero());

      vector2=vector1-Vector3D(1.0,-2.0,3.0);
      CHECK(vector2==Vector3D(rx-1.0,ry+2.0,rz-3.0));
   }

   SECTION("Multiplication")
   {
      vector2=vector1;
      vector2*=3.42;
      CHECK(vector2==Vector3D(rx*3.42,ry*3.42,rz*3.42));

      vector2=vector1*-7.12;
      CHECK(vector2==Vector3D(rx*-7.12,ry*-7.12,rz*-7.12));

      vector2=-7.42*vector1;
      CHECK(vector2==Vector3D(-7.42*rx,-7.42*ry,-7.42*rz));
   }

   SECTION("Division")
   {
      vector2=vector1;
      vector2/=3.42;
      CHECK(vector2==Vector3D(rx/3.42,ry/3.42,rz/3.42));

      vector2=vector1/-7.12;
      CHECK(vector2==Vector3D(rx/-7.12,ry/-7.12,rz/-7.12));

      vector2=vector1;
      vector2/=0.0;
      CHECK(std::isnan(vector2.x()));
      CHECK(std::isnan(vector2.y()));
      CHECK(std::isnan(vector2.z()));
      CHECK(vector2.isNaN());

      vector2=vector1/0.0;
      CHECK(std::isnan(vector2.x()));
      CHECK(std::isnan(vector2.y()));
      CHECK(std::isnan(vector2.z()));
      CHECK(vector2.isNaN());

      vector2.set(std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity());
      vector2*=0.5;
      CHECK(std::isinf(vector2.x()));
      CHECK(std::isinf(vector2.y()));
      CHECK(std::isinf(vector2.z()));
      CHECK_FALSE(vector2.isNaN());

      vector2*=0.0;
      CHECK(std::isnan(vector2.x()));
      CHECK(std::isnan(vector2.y()));
      CHECK(std::isnan(vector2.z()));
      CHECK(vector2.isNaN());
   }

   SECTION("Stream out")
   {
      std::ostringstream oss;
      oss << Vector3D(45.969453,11.882488,-42.366982);
      CHECK(oss.str()=="Vector3D("+std::to_string(45.969453)+","+
                                   std::to_string(11.882488)+","+
                                   std::to_string(-42.366982)+", "
                         "length="+std::to_string(63.634466242577)+")");
   }
}

TEST_CASE("Length methods")
{
   double delta=1.0e-12;

   SECTION("Length")
   {
      CHECK_THAT(Vector3D(-4.503,38.875,-49.137).length(),Catch::Matchers::WithinAbs(62.8170948309455,delta));
      CHECK_THAT(Vector3D(12.338,-25.627,14.162).length(),Catch::Matchers::WithinAbs(31.7731272776225,delta));
      CHECK_THAT(Vector3D(-14.59,32.245,-24.394).length(),Catch::Matchers::WithinAbs(42.9845944612718,delta));
      CHECK_THAT(Vector3D(10.563,41.495,-36.893).length(),Catch::Matchers::WithinAbs(56.5199561482491,delta));

      CHECK_THAT(Vector3D(-12.18,27.234,21.652).length(),Catch::Matchers::WithinAbs(36.8626133094223,delta));
      CHECK_THAT(Vector3D(12.18,-27.234,-21.652).length(),Catch::Matchers::WithinAbs(36.8626133094223,delta));
      CHECK_THAT(Vector3D(-12.18,27.234,-21.652).length(),Catch::Matchers::WithinAbs(36.8626133094223,delta));
   }

   SECTION("Set length")
   {
      Vector3D vector(31.374,-34.234,11.474);
      CHECK_THAT(vector.length(),Catch::Matchers::WithinAbs(47.8324921784345,delta));

      vector.setLength(42.0);
      CHECK_THAT(vector.length(),Catch::Matchers::WithinAbs(42.0,delta));

      CHECK_THAT(vector.x(),Catch::Matchers::WithinAbs(27.548386880709,delta));
      CHECK_THAT(vector.y(),Catch::Matchers::WithinAbs(-30.0596505537767,delta));
      CHECK_THAT(vector.z(),Catch::Matchers::WithinAbs(10.074908875797,delta));
   }

   SECTION("Distance")
   {
      CHECK_THAT((Vector3D(-19.031,-20.295,-35.946)-Vector3D(1.847,14.863,-20.885)).length(),Catch::Matchers::WithinAbs(43.5753321157739,delta));
      CHECK_THAT((Vector3D(-32.201,30.777,-27.992)-Vector3D(-35.649,-33.285,46.633)).length(),Catch::Matchers::WithinAbs(98.4109707959433,delta));
      CHECK_THAT((Vector3D(16.029,-8.105,-13.236)-Vector3D(-3.848,44.050,24.921)).length(),Catch::Matchers::WithinAbs(67.6106190106258,delta));
      CHECK_THAT((Vector3D(-19.055,11.967,29.753)-Vector3D(4.383,-5.947,19.101)).length(),Catch::Matchers::WithinAbs(31.3642526453286,delta));
      CHECK_THAT((Vector3D(-16.469,-31.463,-31.352)-Vector3D(34.494,-42.150,20.695)).length(),Catch::Matchers::WithinAbs(73.6228873856493,delta));
   }
}

TEST_CASE("Angle methods")
{
   double delta=1.0e-8;

   SECTION("Radians simple instance")
   {
      CHECK_THAT(Vector3D(1.235,0.000,0.000).angle(Vector3D(23.678,0.000,0.000)),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(Vector3D(-18.90589543,23.94807212,31.77961845)),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(3.436,0,0).angle(Vector3D(0,-5.346,0)),Catch::Matchers::WithinAbs(1.570796327,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(Vector3D(21.25783696,19.24983078,-1.85961620)),Catch::Matchers::WithinAbs(1.570796327,delta));
      CHECK_THAT(Vector3D(0.000,2.567,0.000).angle(Vector3D(0.000,-14.346,0.000)),Catch::Matchers::WithinAbs(3.141592653,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(Vector3D(12.33284893,-15.62200303,-20.73074162)),Catch::Matchers::WithinAbs(3.141592653,delta));
   }

   SECTION("Radians simple coordinates")
   {
      CHECK_THAT(Vector3D(1.235,0.000,0.000).angle(23.678,0.000,0.000),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(-18.90589543,23.94807212,31.77961845),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(3.436,0,0).angle(0,-5.346,0),Catch::Matchers::WithinAbs(1.570796327,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(21.25783696,19.24983078,-1.85961620),Catch::Matchers::WithinAbs(1.570796327,delta));
      CHECK_THAT(Vector3D(0.000,2.567,0.000).angle(0.000,-14.346,0.000),Catch::Matchers::WithinAbs(3.141592653,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(12.33284893,-15.62200303,-20.73074162),Catch::Matchers::WithinAbs(3.141592653,delta));
   }

   SECTION("Radians real instance")
   {
      CHECK_THAT(Vector3D(39.216,-14.235,42.094).angle(Vector3D(46.412,47.500,-13.349)),Catch::Matchers::WithinAbs(1.42530773,delta));
      CHECK_THAT(Vector3D(-8.418,37.961,-20.712).angle(Vector3D(-25.017,31.689,42.052)),Catch::Matchers::WithinAbs(1.3579370325,delta));
      CHECK_THAT(Vector3D(-46.846,-38.050,15.318).angle(Vector3D(33.166,22.818,14.322)),Catch::Matchers::WithinAbs(2.546064985,delta));
      CHECK_THAT(Vector3D(39.216,-14.235,42.094).angle(Vector3D(46.412,47.500,-13.349),Vector3D::Radians),Catch::Matchers::WithinAbs(1.42530773,delta));
      CHECK_THAT(Vector3D(-8.418,37.961,-20.712).angle(Vector3D(-25.017,31.689,42.052),Vector3D::Radians),Catch::Matchers::WithinAbs(1.3579370325,delta));
      CHECK_THAT(Vector3D(-46.846,-38.050,15.318).angle(Vector3D(33.166,22.818,14.322),Vector3D::Radians),Catch::Matchers::WithinAbs(2.546064985,delta));
   }

   SECTION("Radians real coordinates")
   {
      CHECK_THAT(Vector3D(39.216,-14.235,42.094).angle(46.412,47.500,-13.349),Catch::Matchers::WithinAbs(1.42530773,delta));
      CHECK_THAT(Vector3D(-8.418,37.961,-20.712).angle(-25.017,31.689,42.052),Catch::Matchers::WithinAbs(1.3579370325,delta));
      CHECK_THAT(Vector3D(-46.846,-38.050,15.318).angle(33.166,22.818,14.322),Catch::Matchers::WithinAbs(2.546064985,delta));
      CHECK_THAT(Vector3D(39.216,-14.235,42.094).angle(46.412,47.500,-13.349,Vector3D::Radians),Catch::Matchers::WithinAbs(1.42530773,delta));
      CHECK_THAT(Vector3D(-8.418,37.961,-20.712).angle(-25.017,31.689,42.052,Vector3D::Radians),Catch::Matchers::WithinAbs(1.3579370325,delta));
      CHECK_THAT(Vector3D(-46.846,-38.050,15.318).angle(33.166,22.818,14.322,Vector3D::Radians),Catch::Matchers::WithinAbs(2.546064985,delta));
   }

   SECTION("Degrees simple instance")
   {
      CHECK_THAT(Vector3D(1.235,0.000,0.000).angle(Vector3D(23.678,0.000,0.000),Vector3D::Degrees),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(Vector3D(-18.90589543,23.94807212,31.77961845),Vector3D::Degrees),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(3.436,0,0).angle(Vector3D(0,-5.346,0),Vector3D::Degrees),Catch::Matchers::WithinAbs(90.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(Vector3D(21.25783696,19.24983078,-1.85961620),Vector3D::Degrees),Catch::Matchers::WithinAbs(90.0,delta));
      CHECK_THAT(Vector3D(0.000,2.567,0.000).angle(Vector3D(0.000,-14.346,0.000),Vector3D::Degrees),Catch::Matchers::WithinAbs(180.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(Vector3D(12.33284893,-15.62200303,-20.73074162),Vector3D::Degrees),Catch::Matchers::WithinAbs(180.0,delta));
   }

   SECTION("Degrees simple coordinates")
   {
      CHECK_THAT(Vector3D(1.235,0.000,0.000).angle(23.678,0.000,0.000,Vector3D::Degrees),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(-18.90589543,23.94807212,31.77961845,Vector3D::Degrees),Catch::Matchers::WithinAbs(0.0,delta));
      CHECK_THAT(Vector3D(3.436,0,0).angle(0,-5.346,0,Vector3D::Degrees),Catch::Matchers::WithinAbs(90.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(21.25783696,19.24983078,-1.85961620,Vector3D::Degrees),Catch::Matchers::WithinAbs(90.0,delta));
      CHECK_THAT(Vector3D(0.000,2.567,0.000).angle(0.000,-14.346,0.000,Vector3D::Degrees),Catch::Matchers::WithinAbs(180.0,delta));
      CHECK_THAT(Vector3D(-25.017,31.689,42.052).angle(12.33284893,-15.62200303,-20.73074162,Vector3D::Degrees),Catch::Matchers::WithinAbs(180.0,delta));
   }

   SECTION("Degrees real instance")
   {
      CHECK_THAT(Vector3D(39.216,-14.235,42.094).angle(Vector3D(46.412,47.500,-13.349),Vector3D::Degrees),Catch::Matchers::WithinAbs(81.66411745,delta));
      CHECK_THAT(Vector3D(-8.418,37.961,-20.712).angle(Vector3D(-25.017,31.689,42.052),Vector3D::Degrees),Catch::Matchers::WithinAbs(77.80406081,delta));
      CHECK_THAT(Vector3D(-46.846,-38.050,15.318).angle(Vector3D(33.166,22.818,14.322),Vector3D::Degrees),Catch::Matchers::WithinAbs(145.87877803,delta));
   }

   SECTION("Degrees real coordinates")
   {
      CHECK_THAT(Vector3D(39.216,-14.235,42.094).angle(46.412,47.500,-13.349,Vector3D::Degrees),Catch::Matchers::WithinAbs(81.66411745,delta));
      CHECK_THAT(Vector3D(-8.418,37.961,-20.712).angle(-25.017,31.689,42.052,Vector3D::Degrees),Catch::Matchers::WithinAbs(77.80406081,delta));
      CHECK_THAT(Vector3D(-46.846,-38.050,15.318).angle(33.166,22.818,14.322,Vector3D::Degrees),Catch::Matchers::WithinAbs(145.87877803,delta));
   }
}
