/*
#include <unittest++/UnitTest++.h>

#include <exeng/math/Size.hpp>
#include <exeng/math/Boundary.hpp>
#include <exeng/math/Matrix.hpp>
#include <exeng/math/Vector.hpp>

using namespace exeng;
using namespace exeng::math;

struct BoxFixture
{
    float size;
    Size3f vsize;
    Vector3f center2;
    Vector3f center4;

    Boxf box1, box2, box3, box4, box5; 
    Boxf aux; 
    
    BoxFixture()
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
    
    ~BoxFixture()
    {
    }
};



struct VectorFixture
{
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
    
    ~VectorFixture()
    {
    }
};



struct MatrixFixture
{
    Matrix3f subIdentity;
    Matrix4f identity;
    Matrix4f zero;

    Matrix4f matA;
    Matrix4f matB;
    Matrix4f aux;
    Matrix4f aux2;

    Matrix4f matAddResult;
    Matrix4f matSubResult;
    Matrix4f matMulResult;
    Matrix4f matDivResult;

    Matrix4f invMatA;
    Matrix4f invMatB;

    Matrix4f transMatA;

    float detA;
    
    
    MatrixFixture()
    {
        this->subIdentity.identity();
            
        this->identity.identity();
        this->zero.setup(0.0f);
        
        this->matA.setRowVector(0, Vector4f(1.0f, 2.0f, 1.0f, 0.0f));
        this->matA.setRowVector(1, Vector4f(2.0f, 1.0f, -3.0f, -1.0f));
        this->matA.setRowVector(2, Vector4f(-3.0f, 2.0f, 1.0f, 0.0f));
        this->matA.setRowVector(3, Vector4f(2.0f, -1.0f, 0.0f, -1.0f));
        
        this->matB.setRowVector(0, Vector4f(-3.0f, 1.0f, 5.0f, 1.0f));
        this->matB.setRowVector(1, Vector4f(1.0f, 2.0f, -1.0f, 1.0f));
        this->matB.setRowVector(2, Vector4f(1.0f, 2.0f, 1.0f, -2.0f));
        this->matB.setRowVector(3, Vector4f(1.0f, -1.0f, -3.0f, -1.0f));
        
        //Resultado de la suma
        this->matAddResult.setRowVector(0, Vector4f(-2.0f,  3.0f,  6.0f,  1.0f));
        this->matAddResult.setRowVector(1, Vector4f( 3.0f,  3.0f, -4.0f,  0.0f));
        this->matAddResult.setRowVector(2, Vector4f(-2.0f,  4.0f,  2.0f, -2.0f));
        this->matAddResult.setRowVector(3, Vector4f( 3.0f, -2.0f, -3.0f, -2.0f));
        
        //Resultado de la resta
        this->matSubResult.setRowVector(0, Vector4f( 4.0f,  1.0f, -4.0f, -1.0f));
        this->matSubResult.setRowVector(1, Vector4f( 1.0f, -1.0f, -2.0f, -2.0f));
        this->matSubResult.setRowVector(2, Vector4f(-4.0f,  0.0f,  0.0f,  2.0f));
        this->matSubResult.setRowVector(3, Vector4f( 1.0f,  0.0f,  3.0f,  0.0f));
        
        //Resultado de la multiplicacion
        this->matMulResult.setRowVector(0, Vector4f(  0.0f,  7.0f,  4.0f,   1.0f));
        this->matMulResult.setRowVector(1, Vector4f( -9.0f, -1.0f,  9.0f,  10.0f));
        this->matMulResult.setRowVector(2, Vector4f( 12.0f,  3.0f, -16.0f, -3.0f));
        this->matMulResult.setRowVector(3, Vector4f( -8.0f,  1.0f,  14.0f,  2.0f));
        
        //Matriz inversa
        this->invMatA.setRowVector(0, Vector4f(0.25000f,  0.000f, -0.25000f,  0.000));
        this->invMatA.setRowVector(1, Vector4f(0.28125f,  0.125f,  0.09375f, -0.125));
        this->invMatA.setRowVector(2, Vector4f(0.18750f, -0.250f,  0.06250f,  0.250));
        this->invMatA.setRowVector(3, Vector4f(0.21875f, -0.125f, -0.59375f, -0.875));
        
        //Resultado de la division
        this->matDivResult.setRowVector(0, Vector4f(-1.0f, 2.0f, 0.f,  0.0f));
        this->matDivResult.setRowVector(1, Vector4f( 2.0f, 0.0f, 3.0f, -1.0f));
        this->matDivResult.setRowVector(2, Vector4f(-3.0f, 1.0f, 1.0f,  0.0f));
        this->matDivResult.setRowVector(3, Vector4f( 2.0f, 1.0f, 0.0f,  1.0f));
        
        detA = -32;
    }
    
    ~MatrixFixture()
    {
    }
};



SUITE(MathTestSuite)
{
    TEST_FIXTURE(BoxFixture, BoxTestFixture)
    {
        CHECK_EQUAL(box1.getCenter(), Vector3f(2.0f));
        CHECK_EQUAL(box1.geSize(), Size3f(size) );
        CHECK_EQUAL(box2.getCenter(), center2);
        CHECK_EQUAL(box2.geSize(), Size3f(size) );
        CHECK_EQUAL(box3.getCenter(), Vector3f(0.5f, 1.0f, 1.5f));
        CHECK_EQUAL(box3.geSize(), vsize);
        CHECK_EQUAL(box4.getCenter(), center4);
        CHECK_EQUAL(box4.geSize(), vsize );
        
        CHECK_EQUAL(box1.intersect(box2), box2.intersect(box1) );
        
        CHECK(box1.intersect(box2) == true );
        CHECK(box1.intersect(box4) == false );
        CHECK(box4.intersect(box1) == false );
        CHECK(box5.intersect(box1) == true );
        CHECK(box1.intersect(box5) == true );
    }

    
    TEST_FIXTURE(VectorFixture, TesVectorFixture)
    {
        //Constructores y operadores comparacion
        CHECK_EQUAL( Vector2f(1.0f, -1.0f), Vector2f(values) );
        CHECK_EQUAL( Vector2f(0.0f, 0.0f), Vector2f(v3) );
        CHECK_EQUAL( Vector2f(0.0f), v3 );
        
        CHECK( v1 != v2 ); // TODO: Cambiar por la comprobacion correspondiente

        //Operadores aritmeticos
        CHECK_EQUAL( v3, v1 + v2 );
        CHECK_EQUAL( v3, v1 - (-v2) );
        CHECK_EQUAL( v7, v1 + -v2 );
        CHECK_EQUAL( 2.0f*v1, v1*2.0f);
        CHECK_EQUAL( v1*v2, -v5);
        CHECK_EQUAL( v1/v2, -v6);

        //2do conjunto operadores aritmeticos
        aux = v1;

        aux += v2;
        aux -= v2;
        CHECK_EQUAL( aux, v1 );

        aux *= v2;
        aux /= v2;
        CHECK_EQUAL( aux, v1 );

        //Operaciones de desigualdad
        CHECK( v5 < v7 );   // TODO: Cambiar por la comprobacion correspondiente
        CHECK( v7 > v5 );   // TODO: Cambiar por la comprobacion correspondiente
        CHECK( v1 <= v1 );  // TODO: Cambiar por la comprobacion correspondiente
        CHECK( v1 >= v1 );  // TODO: Cambiar por la comprobacion correspondiente
        
        //Metodos varios
        CHECK( v5.getMagnitude() < v7.getMagnitude() );     // TODO: Cambiar por la comprobacion correspondiente
        CHECK( v7.getMagnitude() > v5.getMagnitude() );     // TODO: Cambiar por la comprobacion correspondiente
        CHECK( v1.getMagnitude() <= v1.getMagnitude() );    // TODO: Cambiar por la comprobacion correspondiente
        CHECK( v1.getMagnitude() >= v1.getMagnitude() );    // TODO: Cambiar por la comprobacion correspondiente

        CHECK_EQUAL(v1.getPtr(), cv1.getPtr() );

        aux = v1;
        aux.setMagnitude(10.0f);

        CHECK_EQUAL( aux.getMagnitude(), 10.0f);

		CHECK( aux.getMagnitudeSq() > 0.0f );

        //Funciones estaticas
        CHECK_EQUAL(v7, v4.maximize(v5) );
        CHECK_EQUAL(v6, v4.minimize(v5) );
        CHECK_EQUAL(-4.0f, v2.dot(v4) );
    }

    
    TEST_FIXTURE(MatrixFixture, TesMatrixFixture)
    {
        // float floatAux;
        
        //Elemento por elemento (funcion)
        CHECK_EQUAL(matA.at(0, 0), 1.0f);
        CHECK_EQUAL(matA.at(0, 1), 2.0f);
        CHECK_EQUAL(matA.at(0, 2), 1.0f);
        CHECK_EQUAL(matA.at(0, 3), 0.0f);
        
        CHECK_EQUAL(matA.at(1, 0), 2.0f);
        CHECK_EQUAL(matA.at(1, 1), 1.0f);
        CHECK_EQUAL(matA.at(1, 2), -3.0f);
        CHECK_EQUAL(matA.at(1, 3), -1.0f);
        
        CHECK_EQUAL(matA.at(2, 0), -3.0f);
        CHECK_EQUAL(matA.at(2, 1), 2.0f);
        CHECK_EQUAL(matA.at(2, 2), 1.0f);
        CHECK_EQUAL(matA.at(2, 3), 0.0f);
        
        CHECK_EQUAL(matA.at(3, 0), 2.0f);
        CHECK_EQUAL(matA.at(3, 1), -1.0f);
        CHECK_EQUAL(matA.at(3, 2), 0.0f);
        CHECK_EQUAL(matA.at(3, 3), -1.0f);
        
        //Elemento por elemento (plantilla)
        CHECK_EQUAL( (matA.at<0, 0>()), 1.0f);
        CHECK_EQUAL( (matA.at<0, 1>()), 2.0f);
        CHECK_EQUAL( (matA.at<0, 2>()), 1.0f);
        CHECK_EQUAL( (matA.at<0, 3>()), 0.0f);
        
        CHECK_EQUAL( (matA.at<1, 0>()), 2.0f);
        CHECK_EQUAL( (matA.at<1, 1>()), 1.0f);
        CHECK_EQUAL( (matA.at<1, 2>()), -3.0f);
        CHECK_EQUAL( (matA.at<1, 3>()), -1.0f);
        
        CHECK_EQUAL( (matA.at<2, 0>()), -3.0f);
        CHECK_EQUAL( (matA.at<2, 1>()), 2.0f);
        CHECK_EQUAL( (matA.at<2, 2>()), 1.0f);
        CHECK_EQUAL( (matA.at<2, 3>()), 0.0f);
        
        CHECK_EQUAL( (matA.at<3, 0>()), 2.0f);
        CHECK_EQUAL( (matA.at<3, 1>()), -1.0f);
        CHECK_EQUAL( (matA.at<3, 2>()), 0.0f);
        CHECK_EQUAL( (matA.at<3, 3>()), -1.0f);
        
        //Vectores fila
        CHECK_EQUAL(matA.getRowVector(0), Vector4f(1.0f, 2.0f, 1.0f, 0.0f));
        CHECK_EQUAL(matA.getRowVector(1), Vector4f(2.0f, 1.0f, -3.0f, -1.0f));
        CHECK_EQUAL(matA.getRowVector(2), Vector4f(-3.0f, 2.0f, 1.0f, 0.0f));
        CHECK_EQUAL(matA.getRowVector(3), Vector4f(2.0f, -1.0f, 0.0f, -1.0f));
        
        //Vectores columna
        CHECK_EQUAL(matA.getColumnVector(0), Vector4f(1.0f, 2.0f, -3.0f, 2.0f));
        CHECK_EQUAL(matA.getColumnVector(1), Vector4f(2.0f, 1.0f, 2.0f, -1.0f));
        CHECK_EQUAL(matA.getColumnVector(2), Vector4f(1.0f, -3.0f, 1.0f, 0.0f));
        CHECK_EQUAL(matA.getColumnVector(3), Vector4f(0.0f, -1.0f, 0.0f, -1.0f));
        
        //Comparaciones
        CHECK(matA != matB);  // TODO: Cambiar por la comprobacion correspondiente
        
        //Multiplicacion por un escalar
        CHECK_EQUAL(matA * -1.0f, -matA);
        CHECK_EQUAL(matA * -1.0f, -1.0f * matA);
        CHECK_EQUAL(matA * 1.0f, matA);
        
        //Sumas y restas
        CHECK_EQUAL(matAddResult, matA + matB);
        CHECK_EQUAL(matSubResult, matA - matB);
        
        aux = matA; aux += matB;
        CHECK_EQUAL(matAddResult, aux);
        
        aux = matA; aux -= matB;
        CHECK_EQUAL(matSubResult, aux);
        
        //Submatriz
        CHECK_EQUAL(subIdentity, identity.getSubMatrix(0, 0) );
        
        //Determinante
        CHECK_EQUAL( identity.getDeterminant(), 1.0f );
        CHECK_EQUAL( matA.getDeterminant(), detA );
        
        //Multiplicacion
        CHECK_EQUAL(matMulResult, matA * matB);
        CHECK_EQUAL(matMulResult, ((aux = this->matA) *= matB));
        
        //Matriz inversa
        aux = this->matA;
        aux.inverse();
        CHECK_EQUAL( invMatA, aux );
    }
}
*/
