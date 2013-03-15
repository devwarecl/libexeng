
#include <unittest++/UnitTest++.h>

#include <exeng/scenegraph/Sphere.hpp>
#include <exeng/scenegraph/Plane.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/IntersectInfo.hpp>
#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/Light.hpp>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::scenegraph;

struct SphereFixture {
	Sphere s1, s2, s3, s4, s5, s6, s7;

	SphereFixture() : s2(2.0f), s3(3.0f, Vector3f(0.0f, 1.0f, -1.0f))  {
		s4 = s3;
        s5.setRadius(10.0f);
        s5.setCenter(Vector3f(-10.0f));
        s6.setAttributes(3.0f, Vector3f(1.0f));
        s7.setRadius(-0.01f);
	}

	~SphereFixture() {}
};


struct RayFixture {
	

	RayFixture()  {
	}
	
	~RayFixture() {}
};


SUITE(ScenegraphTestSuite) {
    TEST_FIXTURE(SphereFixture, SphereFixtureTest) {
        Sphere s1, s2(2.0f);
        Sphere s3(3.0f, Vector3f(0.0f, 1.0f, -1.0f));
        Sphere s4 = s3;
        Sphere s5, s6, s7;

        s5.setRadius(10.0f);
        s5.setCenter(Vector3f(-10.0f));
        s6.setAttributes(3.0f, Vector3f(1.0f));
        s7.setRadius(-0.01f);
        
        CHECK_EQUAL(s1.getRadius(), 1.0f);
        CHECK_EQUAL(s1.getCenter(), Vector3f(0.0f));
        
        CHECK_EQUAL(s2.getRadius(), 2.0f);
        CHECK_EQUAL(s2.getCenter(), Vector3f(0.0f));
        
        CHECK_EQUAL(s3.getRadius(), 3.0f);
        CHECK_EQUAL(s3.getCenter(), Vector3f(0.0f, 1.0f, -1.0f));
        
        CHECK_EQUAL(s3, s4);
        
        CHECK_EQUAL(s4.getRadius(), 3.0f);
        CHECK_EQUAL(s4.getCenter(), Vector3f(0.0f, 1.0f, -1.0f));
        
        CHECK_EQUAL(s5.getRadius(), 10.0f);
        CHECK_EQUAL(s5.getCenter(), Vector3f(-10.0f));
        
        CHECK_EQUAL(s6.getRadius(), 3.0f);
        CHECK_EQUAL(s6.getCenter(), Vector3f(1.0f));
        
        CHECK_EQUAL(s7.getRadius(), 0.0f);

		// Probar la interseccion de una esfera y un rayo
		Ray ray1, ray2, ray3;
		IntersectInfo info;

		ray1.setAttributes(Vector3f(0.0, 0.0, -10.0), Vector3f(0.0, 0.0, 1.0));
		ray2.setAttributes(Vector3f(10.0, 0.0, -10.0), Vector3f(0.0, 0.0, 1.0));
		ray3.setAttributes(Vector3f(10.0, 0.0, -10.0), Vector3f(0.0, 0.0, 1.0));
		
		CHECK_EQUAL(s1.intersect(ray1, &info), true);
		CHECK_EQUAL(s1.intersect(ray2, nullptr), false);
		CHECK_EQUAL(s1.intersect(ray3, nullptr), false);

		CHECK_EQUAL(info.intersect, true);
		// CHECK_EQUAL(2, info.parametricCoords.size());
    }


	// Probar los metodos de la clase ray
	TEST( RayTest ) {
		Ray ray1, ray2, ray3;

		// Comprobar atributos por defecto
		CHECK_EQUAL( ray1.getPoint(), Vector3f(0.0f, 0.0f, 0.0f) );
		CHECK_EQUAL( ray1.getDirection(), Vector3f(0.0f, 0.0f, 1.0f) );

		// Comprobar setters y getters
		ray2.setPoint( Vector3f(0.0f, 1.0f, 0.0f) );
		ray2.setDirection( Vector3f(0.0f, 10.0f, 0.0f) );
		CHECK_EQUAL( ray2.getPoint(), Vector3f(0.0f, 1.0f, 0.0f) );
		CHECK_EQUAL( ray2.getDirection(), Vector3f(0.0f, 1.0f, 0.0f) );

		// Comprobar setter de atributos
		ray3.setAttributes( Vector3f(1.0f, 0.0f, 0.0f), Vector3f(-1.0f, 0.0f, 0.0f) );
		CHECK_EQUAL( ray3.getPoint(), Vector3f(1.0f, 0.0f, 0.0f) );
		CHECK_EQUAL( ray3.getDirection(), Vector3f(-1.0f, 0.0f, 0.0f) );

		// Comprobar interpolador
		CHECK_EQUAL( ray1.getPointAt(0.0f), ray1.getPoint() );
		CHECK_EQUAL( ray1.getPointAt(1.0f), ray1.getPoint() + ray1.getDirection() );
		CHECK_EQUAL( ray1.getPointAt(0.5f), ray1.getPoint() + 0.5f * ray1.getDirection() );
	}
}
