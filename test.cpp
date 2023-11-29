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

   SECTION("Equality")
   {
      vector2.set(vector1);
      CHECK(vector2==vector1);
      CHECK(vector1==vector2);

      vector2.set(vector1.x()+1.0,vector1.y()-2.0,vector1.z()+3.0);
      CHECK(vector2!=vector1);
      CHECK(vector1!=vector2);
   }

   SECTION("Comparison")
   {
      Vector3D vec1(-4.1688734,-18.39178297,-2.31577495);
      Vector3D vec2(9.35135936,16.52288031,0.73925923);
      Vector3D vec3(15.5702147,-11.62387025,-1.64440101);
      CHECK(vec3>vec1);
      CHECK(vec3>vec2);
      CHECK_FALSE(vec1>vec3);
      CHECK_FALSE(vec2>vec3);
      CHECK(vec3>=vec1);
      CHECK(vec3>=vec2);
      CHECK_FALSE(vec1>=vec3);
      CHECK_FALSE(vec2>=vec3);
      CHECK(vec1<vec3);
      CHECK(vec2<vec3);
      CHECK_FALSE(vec3<vec1);
      CHECK_FALSE(vec3<vec2);
      CHECK(vec1<=vec3);
      CHECK(vec2<=vec3);
      CHECK_FALSE(vec3<=vec1);
      CHECK_FALSE(vec3<=vec2);
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

TEST_CASE("Simple rotate")
{
   Vector3D vector=Vector3D(5.0,0.0,0.0);
   Vector3D axis=Vector3D(0.0,0.0,-1.0);
   double angle=90.0;
   Vector3D check=Vector3D(0.0,5.0,0.0);
   double delta=1.0e-12;

   vector.rotate(axis,angle,Vector3D::Degrees);
   CHECK_THAT(vector.x(),Catch::Matchers::WithinAbs(check.x(),delta));
   CHECK_THAT(vector.y(),Catch::Matchers::WithinAbs(check.y(),delta));
   CHECK_THAT(vector.z(),Catch::Matchers::WithinAbs(check.z(),delta));
}

TEST_CASE("Rotate methods")
{
   std::vector<Vector3D> vector,axis,check; std::vector<double> angle;
   double deltaRad=1.0e-6;
   double deltaDeg=1.0e-8;

   SECTION("Radians simple instance")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(-23.384,-27.427,-23.769)); axis.push_back(Vector3D(17.217,11.341,31.965)); angle.push_back(0.0); check.push_back(Vector3D(-23.384,-27.427,-23.769));
      vector.push_back(Vector3D(-2.549,17.927,0.467)); axis.push_back(Vector3D(20.130,49.176,-21.931)); angle.push_back(1.57079633); check.push_back(Vector3D(-2.24346891,11.39441477,-13.90061072));
      vector.push_back(Vector3D(9.955,-34.501,4.158)); axis.push_back(Vector3D(39.861,-35.181,-49.683)); angle.push_back(-1.57079633); check.push_back(Vector3D(-14.99708164,-18.40323112,-27.26020207));
      vector.push_back(Vector3D(-10.927,-14.151,24.814)); axis.push_back(Vector3D(36.016,21.735,-8.425)); angle.push_back(3.14159265); check.push_back(Vector3D(-24.69392769,-7.34558105,-16.48141682));
      vector.push_back(Vector3D(-48.551,-6.099,42.352)); axis.push_back(Vector3D(-6.250,-35.281,36.325)); angle.push_back(-3.14159265); check.push_back(Vector3D(38.67389465,-49.6568646,15.05373628));
      vector.push_back(Vector3D(19.859,-15.055,46.167)); axis.push_back(Vector3D(-40.104,1.501,1.380)); angle.push_back(6.28318531); check.push_back(Vector3D(19.859,-15.055,46.167));
      vector.push_back(Vector3D(-27.703,29.240,49.907)); axis.push_back(Vector3D(-22.222,29.404,-2.766)); angle.push_back(-6.28318531); check.push_back(Vector3D(-27.703,29.240,49.907));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      std::vector<Vector3D> vector2=vector;
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i],angle[i]);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));

         vector2[i].rotate(axis[i],angle[i],Vector3D::Radians);
         CHECK_THAT(vector2[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector2[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector2[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));
      }
   }

   SECTION("Radians simple coordinates")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(-23.384,-27.427,-23.769)); axis.push_back(Vector3D(17.217,11.341,31.965)); angle.push_back(0.0); check.push_back(Vector3D(-23.384,-27.427,-23.769));
      vector.push_back(Vector3D(-2.549,17.927,0.467)); axis.push_back(Vector3D(20.130,49.176,-21.931)); angle.push_back(1.57079633); check.push_back(Vector3D(-2.24346891,11.39441477,-13.90061072));
      vector.push_back(Vector3D(9.955,-34.501,4.158)); axis.push_back(Vector3D(39.861,-35.181,-49.683)); angle.push_back(-1.57079633); check.push_back(Vector3D(-14.99708164,-18.40323112,-27.26020207));
      vector.push_back(Vector3D(-10.927,-14.151,24.814)); axis.push_back(Vector3D(36.016,21.735,-8.425)); angle.push_back(3.14159265); check.push_back(Vector3D(-24.69392769,-7.34558105,-16.48141682));
      vector.push_back(Vector3D(-48.551,-6.099,42.352)); axis.push_back(Vector3D(-6.250,-35.281,36.325)); angle.push_back(-3.14159265); check.push_back(Vector3D(38.67389465,-49.6568646,15.05373628));
      vector.push_back(Vector3D(19.859,-15.055,46.167)); axis.push_back(Vector3D(-40.104,1.501,1.380)); angle.push_back(6.28318531); check.push_back(Vector3D(19.859,-15.055,46.167));
      vector.push_back(Vector3D(-27.703,29.240,49.907)); axis.push_back(Vector3D(-22.222,29.404,-2.766)); angle.push_back(-6.28318531); check.push_back(Vector3D(-27.703,29.240,49.907));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      std::vector<Vector3D> vector2=vector;
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i].x(),axis[i].y(),axis[i].z(),angle[i]);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));

         vector2[i].rotate(axis[i].x(),axis[i].y(),axis[i].z(),angle[i],Vector3D::Radians);
         CHECK_THAT(vector2[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector2[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector2[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));
      }
   }

   SECTION("Radians real instance")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(43.375,4.320,22.388)); axis.push_back(Vector3D(2.023,-30.325,-37.247)); angle.push_back(3.33715680); check.push_back(Vector3D(-46.16307447,11.84879786,11.39526717));
      vector.push_back(Vector3D(-11.872,48.280,-35.682)); axis.push_back(Vector3D(-37.360,-30.796,-30.118)); angle.push_back(-3.87112283); check.push_back(Vector3D(-21.62114171,-25.10782215,51.45125271));
      vector.push_back(Vector3D(-3.108,25.264,37.777)); axis.push_back(Vector3D(8.748,40.266,39.068)); angle.push_back(1.15718820); check.push_back(Vector3D(-5.86075978,35.86042393,27.47203267));
      vector.push_back(Vector3D(11.707,-48.161,22.777)); axis.push_back(Vector3D(48.561,23.648,36.697)); angle.push_back(9.60243503); check.push_back(Vector3D(0.71638585,48.49324995,-24.96435458));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      std::vector<Vector3D> vector2=vector;
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i],angle[i]);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));

         vector2[i].rotate(axis[i],angle[i],Vector3D::Radians);
         CHECK_THAT(vector2[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector2[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector2[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));
      }
   }

   SECTION("Radians real coordinates")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(43.375,4.320,22.388)); axis.push_back(Vector3D(2.023,-30.325,-37.247)); angle.push_back(3.33715680); check.push_back(Vector3D(-46.16307447,11.84879786,11.39526717));
      vector.push_back(Vector3D(-11.872,48.280,-35.682)); axis.push_back(Vector3D(-37.360,-30.796,-30.118)); angle.push_back(-3.87112283); check.push_back(Vector3D(-21.62114171,-25.10782215,51.45125271));
      vector.push_back(Vector3D(-3.108,25.264,37.777)); axis.push_back(Vector3D(8.748,40.266,39.068)); angle.push_back(1.15718820); check.push_back(Vector3D(-5.86075978,35.86042393,27.47203267));
      vector.push_back(Vector3D(11.707,-48.161,22.777)); axis.push_back(Vector3D(48.561,23.648,36.697)); angle.push_back(9.60243503); check.push_back(Vector3D(0.71638585,48.49324995,-24.96435458));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      std::vector<Vector3D> vector2=vector;
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i].x(),axis[i].y(),axis[i].z(),angle[i]);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));

         vector2[i].rotate(axis[i].x(),axis[i].y(),axis[i].z(),angle[i],Vector3D::Radians);
         CHECK_THAT(vector2[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaRad));
         CHECK_THAT(vector2[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaRad));
         CHECK_THAT(vector2[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaRad));
      }
   }

   SECTION("Degrees simple instance")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(-23.384,-27.427,-23.769)); axis.push_back(Vector3D(17.217,11.341,31.965)); angle.push_back(0.0); check.push_back(Vector3D(-23.384,-27.427,-23.769));
      vector.push_back(Vector3D(-2.549,17.927,0.467)); axis.push_back(Vector3D(20.130,49.176,-21.931)); angle.push_back(90.0); check.push_back(Vector3D(-2.24346891,11.39441477,-13.90061072));
      vector.push_back(Vector3D(9.955,-34.501,4.158)); axis.push_back(Vector3D(39.861,-35.181,-49.683)); angle.push_back(-90.0); check.push_back(Vector3D(-14.99708164,-18.40323112,-27.26020207));
      vector.push_back(Vector3D(-10.927,-14.151,24.814)); axis.push_back(Vector3D(36.016,21.735,-8.425)); angle.push_back(180.0); check.push_back(Vector3D(-24.69392769,-7.34558105,-16.48141682));
      vector.push_back(Vector3D(-48.551,-6.099,42.352)); axis.push_back(Vector3D(-6.250,-35.281,36.325)); angle.push_back(-180.0); check.push_back(Vector3D(38.67389465,-49.6568646,15.05373628));
      vector.push_back(Vector3D(19.859,-15.055,46.167)); axis.push_back(Vector3D(-40.104,1.501,1.380)); angle.push_back(360.0); check.push_back(Vector3D(19.859,-15.055,46.167));
      vector.push_back(Vector3D(-27.703,29.240,49.907)); axis.push_back(Vector3D(-22.222,29.404,-2.766)); angle.push_back(-360.0); check.push_back(Vector3D(-27.703,29.240,49.907));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i],angle[i],Vector3D::Degrees);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaDeg));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaDeg));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaDeg));
      }
   }

   SECTION("Degrees simple coordinates")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(-23.384,-27.427,-23.769)); axis.push_back(Vector3D(17.217,11.341,31.965)); angle.push_back(0.0); check.push_back(Vector3D(-23.384,-27.427,-23.769));
      vector.push_back(Vector3D(-2.549,17.927,0.467)); axis.push_back(Vector3D(20.130,49.176,-21.931)); angle.push_back(90.0); check.push_back(Vector3D(-2.24346891,11.39441477,-13.90061072));
      vector.push_back(Vector3D(9.955,-34.501,4.158)); axis.push_back(Vector3D(39.861,-35.181,-49.683)); angle.push_back(-90.0); check.push_back(Vector3D(-14.99708164,-18.40323112,-27.26020207));
      vector.push_back(Vector3D(-10.927,-14.151,24.814)); axis.push_back(Vector3D(36.016,21.735,-8.425)); angle.push_back(180.0); check.push_back(Vector3D(-24.69392769,-7.34558105,-16.48141682));
      vector.push_back(Vector3D(-48.551,-6.099,42.352)); axis.push_back(Vector3D(-6.250,-35.281,36.325)); angle.push_back(-180.0); check.push_back(Vector3D(38.67389465,-49.6568646,15.05373628));
      vector.push_back(Vector3D(19.859,-15.055,46.167)); axis.push_back(Vector3D(-40.104,1.501,1.380)); angle.push_back(360.0); check.push_back(Vector3D(19.859,-15.055,46.167));
      vector.push_back(Vector3D(-27.703,29.240,49.907)); axis.push_back(Vector3D(-22.222,29.404,-2.766)); angle.push_back(-360.0); check.push_back(Vector3D(-27.703,29.240,49.907));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i].x(),axis[i].y(),axis[i].z(),angle[i],Vector3D::Degrees);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaDeg));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaDeg));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaDeg));
      }
   }

   SECTION("Degrees real instance")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(43.375,4.320,22.388)); axis.push_back(Vector3D(2.023,-30.325,-37.247)); angle.push_back(191.205); check.push_back(Vector3D(-46.16307447,11.84879786,11.39526717));
      vector.push_back(Vector3D(-11.872,48.280,-35.682)); axis.push_back(Vector3D(-37.360,-30.796,-30.118)); angle.push_back(-221.799); check.push_back(Vector3D(-21.62114171,-25.10782215,51.45125271));
      vector.push_back(Vector3D(-3.108,25.264,37.777)); axis.push_back(Vector3D(8.748,40.266,39.068)); angle.push_back(66.302); check.push_back(Vector3D(-5.86075978,35.86042393,27.47203267));
      vector.push_back(Vector3D(11.707,-48.161,22.777)); axis.push_back(Vector3D(48.561,23.648,36.697)); angle.push_back(550.179); check.push_back(Vector3D(0.71638585,48.49324995,-24.96435458));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i],angle[i],Vector3D::Degrees);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaDeg));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaDeg));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaDeg));
      }
   }

   SECTION("Degrees real coordinates")
   {
      vector.clear(); axis.clear(); check.clear(); angle.clear();
      vector.push_back(Vector3D(43.375,4.320,22.388)); axis.push_back(Vector3D(2.023,-30.325,-37.247)); angle.push_back(191.205); check.push_back(Vector3D(-46.16307447,11.84879786,11.39526717));
      vector.push_back(Vector3D(-11.872,48.280,-35.682)); axis.push_back(Vector3D(-37.360,-30.796,-30.118)); angle.push_back(-221.799); check.push_back(Vector3D(-21.62114171,-25.10782215,51.45125271));
      vector.push_back(Vector3D(-3.108,25.264,37.777)); axis.push_back(Vector3D(8.748,40.266,39.068)); angle.push_back(66.302); check.push_back(Vector3D(-5.86075978,35.86042393,27.47203267));
      vector.push_back(Vector3D(11.707,-48.161,22.777)); axis.push_back(Vector3D(48.561,23.648,36.697)); angle.push_back(550.179); check.push_back(Vector3D(0.71638585,48.49324995,-24.96435458));
      REQUIRE(((vector.size()==axis.size()) && (axis.size()==check.size()) && (check.size()==angle.size())));
      for(int i=0;i<vector.size();i++)
      {
         vector[i].rotate(axis[i].x(),axis[i].y(),axis[i].z(),angle[i],Vector3D::Degrees);
         CHECK_THAT(vector[i].x(),Catch::Matchers::WithinAbs(check[i].x(),deltaDeg));
         CHECK_THAT(vector[i].y(),Catch::Matchers::WithinAbs(check[i].y(),deltaDeg));
         CHECK_THAT(vector[i].z(),Catch::Matchers::WithinAbs(check[i].z(),deltaDeg));
      }
   }
}
