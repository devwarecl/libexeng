
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <xe/Vector.hpp>
#include <xe/Size.hpp>
#include <xe/Boundary.hpp>

#include <boost/test/unit_test.hpp>

using namespace xe;

struct HyperBoxFixture {
    float size;
    Size3f vsize;
    Vector3f center2;
    Vector3f center4;

    Boxf box1, box2, box3, box4, box5; 
    Boxf aux; 
    
    HyperBoxFixture() 
	{
        size = 4.0f;
        vsize = Size3f(1.0f, 2.0f, 3.0f);
        center2 = Vector3f(2.0f, 0.0f, 0.0f);
        center4 = Vector3f(10.0f, 10.0f, -4.0f);
        
        this->box1.set(size); //(0, 0, 0) - (4, 4, 4)
        
        this->box2.set(size); //(0, -2, -2), (4, 2, 2)
        this->box2.setCenter( center2 );
        
        this->box3.set(vsize);    //(0, 0, 0) - (1, 2, 3)
        
        this->box4.set(vsize);
        this->box4.setCenter(center4);
        
        this->box5.set(100.0f);
    }
    
    ~HyperBoxFixture() {}
};

BOOST_FIXTURE_TEST_CASE(HyperBoxTest, HyperBoxFixture)
{
    BOOST_CHECK_EQUAL(box1.getCenter(), Vector3f(2.0f));
    BOOST_CHECK_EQUAL(box1.getSize(), Size3f(size) );
    BOOST_CHECK_EQUAL(box2.getCenter(), center2);
    BOOST_CHECK_EQUAL(box2.getSize(), Size3f(size) );
    BOOST_CHECK_EQUAL(box3.getCenter(), Vector3f(0.5f, 1.0f, 1.5f));
    BOOST_CHECK_EQUAL(box3.getSize(), vsize);
    BOOST_CHECK_EQUAL(box4.getCenter(), center4);
    BOOST_CHECK_EQUAL(box4.getSize(), vsize );
        
    BOOST_CHECK_EQUAL(box1.intersect(box2), box2.intersect(box1) );
    
    BOOST_CHECK(box1.intersect(box2) == true );
    BOOST_CHECK(box1.intersect(box4) == false );
    BOOST_CHECK(box4.intersect(box1) == false );
    BOOST_CHECK(box5.intersect(box1) == true );
    BOOST_CHECK(box1.intersect(box5) == true );
}

struct VectorFixture {
    float values[2];
    float *tempPtr;

    Vector2f v1;
    const Vector2f& cv1;
    const Vector2f v2;
    const Vector2f v3;
    const Vector2f v4;
    const Vector2f v5;
    const Vector2f v6;
    const Vector2f v7;
    Vector2f aux;
    
    VectorFixture() : 
        cv1(v1),
        v2(-1.0f, -2.0f),
        v3(0.0f, 0.0f),
        v4(2.0f, 1.0f),
        v5(1.0f, 4.0),
        v6(1.0f, 1.0),
        v7(2.0f, 4.0)
    {
        this->aux = Vector2f(0.0f, 0.0f);
        this->values[0] = 1.0f;
        this->values[1] = -1.0f;
        this->tempPtr = NULL;
        this->v1 = Vector2f(1.0f, 2.0f);
    }
    
    ~VectorFixture() {}
};


BOOST_FIXTURE_TEST_CASE(VectorTest, VectorFixture)
{
    //Constructores y operadores comparacion
    BOOST_CHECK_EQUAL( Vector2f(1.0f, -1.0f), Vector2f(values) );
    BOOST_CHECK_EQUAL( Vector2f(0.0f, 0.0f), Vector2f(v3) );
    BOOST_CHECK_EQUAL( Vector2f(0.0f), v3 );
        
    BOOST_CHECK( v1 != v2 ); // TODO: Cambiar por la comprobacion correspondiente

    //Operadores aritmeticos
    BOOST_CHECK_EQUAL( v3, v1 + v2 );
    BOOST_CHECK_EQUAL( v3, v1 - (-v2) );
    BOOST_CHECK_EQUAL( v7, v1 + -v2 );
    BOOST_CHECK_EQUAL( 2.0f*v1, v1*2.0f);
    BOOST_CHECK_EQUAL( v1*v2, -v5);
    BOOST_CHECK_EQUAL( v1/v2, -v6);

    //2do conjunto operadores aritmeticos
    aux = v1;

    aux += v2;
    aux -= v2;
    BOOST_CHECK_EQUAL( aux, v1 );

    aux *= v2;
    aux /= v2;
    BOOST_CHECK_EQUAL( aux, v1 );

    //Metodos varios
    BOOST_CHECK(abs(v5) <  abs(v7));     // TODO: Cambiar por la comprobacion correspondiente
    BOOST_CHECK(abs(v7) >  abs(v5));     // TODO: Cambiar por la comprobacion correspondiente
    BOOST_CHECK(abs(v1) <= abs(v1));    // TODO: Cambiar por la comprobacion correspondiente
    BOOST_CHECK(abs(v1) >= abs(v1));    // TODO: Cambiar por la comprobacion correspondiente

    BOOST_CHECK_EQUAL(v1.getPtr(), cv1.getPtr() );

    aux = v1;
    aux = 10.0f * normalize(aux);

    BOOST_CHECK_EQUAL(abs(aux), 10.0f);

    //Funciones estaticas
    BOOST_CHECK_EQUAL(v7, maximize(v4, v5));
    BOOST_CHECK_EQUAL(v6, minimize(v4, v5));
    BOOST_CHECK_EQUAL(-4.0f, dot(v2, v4));
}

