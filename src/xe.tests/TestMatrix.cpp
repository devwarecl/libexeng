
#include <iostream>
#include <iomanip>
#include <typeinfo>

#include <xe/Matrix.hpp>

#include <boost/test/unit_test.hpp>

using xe::Matrix3f;
using xe::Matrix4f;
using xe::Vector4f;
using xe::Vector3f;

struct MatrixFixture {

    Matrix3f subIdentity;
    Matrix4f identity, zero;
    Matrix4f matA, matB, aux,aux2;
    Matrix4f matAddResult, matSubResult, matMulResult, matDivResult;
    Matrix4f invMatA, invMatB, transMatA;

    float detA;
    
    MatrixFixture() {
        this->subIdentity = xe::identity<float, 3>();
        this->identity = xe::identity<float, 4>();
        this->zero = xe::zero<float, 4, 4>();
        
        this->matA.setRow(0, Vector4f(1.0f, 2.0f, 1.0f, 0.0f));
        this->matA.setRow(1, Vector4f(2.0f, 1.0f, -3.0f, -1.0f));
        this->matA.setRow(2, Vector4f(-3.0f, 2.0f, 1.0f, 0.0f));
        this->matA.setRow(3, Vector4f(2.0f, -1.0f, 0.0f, -1.0f));
        
        this->matB.setRow(0, Vector4f(-3.0f, 1.0f, 5.0f, 1.0f));
        this->matB.setRow(1, Vector4f(1.0f, 2.0f, -1.0f, 1.0f));
        this->matB.setRow(2, Vector4f(1.0f, 2.0f, 1.0f, -2.0f));
        this->matB.setRow(3, Vector4f(1.0f, -1.0f, -3.0f, -1.0f));
        
        //Resultado de la suma
        this->matAddResult.setRow(0, Vector4f(-2.0f,  3.0f,  6.0f,  1.0f));
        this->matAddResult.setRow(1, Vector4f( 3.0f,  3.0f, -4.0f,  0.0f));
        this->matAddResult.setRow(2, Vector4f(-2.0f,  4.0f,  2.0f, -2.0f));
        this->matAddResult.setRow(3, Vector4f( 3.0f, -2.0f, -3.0f, -2.0f));
        
        //Resultado de la resta
        this->matSubResult.setRow(0, Vector4f( 4.0f,  1.0f, -4.0f, -1.0f));
        this->matSubResult.setRow(1, Vector4f( 1.0f, -1.0f, -2.0f, -2.0f));
        this->matSubResult.setRow(2, Vector4f(-4.0f,  0.0f,  0.0f,  2.0f));
        this->matSubResult.setRow(3, Vector4f( 1.0f,  0.0f,  3.0f,  0.0f));
        
        //Resultado de la multiplicacion
        this->matMulResult.setRow(0, Vector4f(  0.0f,  7.0f,  4.0f,   1.0f));
        this->matMulResult.setRow(1, Vector4f( -9.0f, -1.0f,  9.0f,  10.0f));
        this->matMulResult.setRow(2, Vector4f( 12.0f,  3.0f, -16.0f, -3.0f));
        this->matMulResult.setRow(3, Vector4f( -8.0f,  1.0f,  14.0f,  2.0f));
        
        //Matriz inversa
        this->invMatA.setRow(0, Vector4f(0.25000f,  0.000f, -0.25000f,  0.000));
        this->invMatA.setRow(1, Vector4f(0.28125f,  0.125f,  0.09375f, -0.125));
        this->invMatA.setRow(2, Vector4f(0.18750f, -0.250f,  0.06250f,  0.250));
        this->invMatA.setRow(3, Vector4f(0.21875f, -0.125f, -0.59375f, -0.875));
        
        //Resultado de la division
        this->matDivResult.setRow(0, Vector4f(-1.0f, 2.0f, 0.f,  0.0f));
        this->matDivResult.setRow(1, Vector4f( 2.0f, 0.0f, 3.0f, -1.0f));
        this->matDivResult.setRow(2, Vector4f(-3.0f, 1.0f, 1.0f,  0.0f));
        this->matDivResult.setRow(3, Vector4f( 2.0f, 1.0f, 0.0f,  1.0f));
        
        detA = -32;
    }
    
    ~MatrixFixture() { }
};


BOOST_FIXTURE_TEST_CASE(TestMatrix, MatrixFixture)
{
    // matrix element retrieval by function paramenters
    BOOST_CHECK_EQUAL(matA.get(0, 0), 1.0f);
    BOOST_CHECK_EQUAL(matA.get(0, 1), 2.0f);
    BOOST_CHECK_EQUAL(matA.get(0, 2), 1.0f);
    BOOST_CHECK_EQUAL(matA.get(0, 3), 0.0f);
        
    BOOST_CHECK_EQUAL(matA.get(1, 0), 2.0f);
    BOOST_CHECK_EQUAL(matA.get(1, 1), 1.0f);
    BOOST_CHECK_EQUAL(matA.get(1, 2), -3.0f);
    BOOST_CHECK_EQUAL(matA.get(1, 3), -1.0f);
        
    BOOST_CHECK_EQUAL(matA.get(2, 0), -3.0f);
    BOOST_CHECK_EQUAL(matA.get(2, 1), 2.0f);
    BOOST_CHECK_EQUAL(matA.get(2, 2), 1.0f);
    BOOST_CHECK_EQUAL(matA.get(2, 3), 0.0f);
        
    BOOST_CHECK_EQUAL(matA.get(3, 0), 2.0f);
    BOOST_CHECK_EQUAL(matA.get(3, 1), -1.0f);
    BOOST_CHECK_EQUAL(matA.get(3, 2), 0.0f);
    BOOST_CHECK_EQUAL(matA.get(3, 3), -1.0f);
        
    // matrix element retrieval by template paramenters
    BOOST_CHECK_EQUAL( (matA.get<0, 0>()), 1.0f);
    BOOST_CHECK_EQUAL( (matA.get<0, 1>()), 2.0f);
    BOOST_CHECK_EQUAL( (matA.get<0, 2>()), 1.0f);
    BOOST_CHECK_EQUAL( (matA.get<0, 3>()), 0.0f);
        
    BOOST_CHECK_EQUAL( (matA.get<1, 0>()), 2.0f);
    BOOST_CHECK_EQUAL( (matA.get<1, 1>()), 1.0f);
    BOOST_CHECK_EQUAL( (matA.get<1, 2>()), -3.0f);
    BOOST_CHECK_EQUAL( (matA.get<1, 3>()), -1.0f);
        
    BOOST_CHECK_EQUAL( (matA.get<2, 0>()), -3.0f);
    BOOST_CHECK_EQUAL( (matA.get<2, 1>()), 2.0f);
    BOOST_CHECK_EQUAL( (matA.get<2, 2>()), 1.0f);
    BOOST_CHECK_EQUAL( (matA.get<2, 3>()), 0.0f);
        
    BOOST_CHECK_EQUAL( (matA.get<3, 0>()), 2.0f);
    BOOST_CHECK_EQUAL( (matA.get<3, 1>()), -1.0f);
    BOOST_CHECK_EQUAL( (matA.get<3, 2>()), 0.0f);
    BOOST_CHECK_EQUAL( (matA.get<3, 3>()), -1.0f);
        
    // matrix row vectors
    BOOST_CHECK_EQUAL(matA.getRow(0), Vector4f(1.0f, 2.0f, 1.0f, 0.0f));
    BOOST_CHECK_EQUAL(matA.getRow(1), Vector4f(2.0f, 1.0f, -3.0f, -1.0f));
    BOOST_CHECK_EQUAL(matA.getRow(2), Vector4f(-3.0f, 2.0f, 1.0f, 0.0f));
    BOOST_CHECK_EQUAL(matA.getRow(3), Vector4f(2.0f, -1.0f, 0.0f, -1.0f));
        
    // matrix column vectors
    BOOST_CHECK_EQUAL(matA.getColumn(0), Vector4f(1.0f, 2.0f, -3.0f, 2.0f));
    BOOST_CHECK_EQUAL(matA.getColumn(1), Vector4f(2.0f, 1.0f, 2.0f, -1.0f));
    BOOST_CHECK_EQUAL(matA.getColumn(2), Vector4f(1.0f, -3.0f, 1.0f, 0.0f));
    BOOST_CHECK_EQUAL(matA.getColumn(3), Vector4f(0.0f, -1.0f, 0.0f, -1.0f));
        
    // matrix direct comparison
    BOOST_CHECK(matA != matB);
        
    // matrix scale
    BOOST_CHECK_EQUAL(matA * -1.0f, -matA);
    BOOST_CHECK_EQUAL(matA * -1.0f, -1.0f * matA);
    BOOST_CHECK_EQUAL(matA * 1.0f, matA);
        
    // matrix adition 
    BOOST_CHECK_EQUAL(matAddResult, matA + matB);
    BOOST_CHECK_EQUAL(matSubResult, matA - matB);
        
    aux = matA; aux += matB;
    BOOST_CHECK_EQUAL(matAddResult, aux);
        
    aux = matA; aux -= matB;
    BOOST_CHECK_EQUAL(matSubResult, aux);
        
    // submatrix
    BOOST_CHECK_EQUAL(subIdentity, identity.getSubMatrix(0, 0) );
        
    // matrix determinant
    BOOST_CHECK_EQUAL( abs(identity), 1.0f );
    BOOST_CHECK_EQUAL( abs(matA), detA );
        
    //matrix multiply
    BOOST_CHECK_EQUAL(matMulResult, matA * matB);
    BOOST_CHECK_EQUAL(matMulResult, ((aux = this->matA) *= matB));
    
	BOOST_CHECK_EQUAL(identity, identity * identity);

	BOOST_CHECK_EQUAL(matA, matA * identity);
	BOOST_CHECK_EQUAL(matA, identity * matA);

    //inverse matrix
    aux = inverse(this->matA);

	BOOST_CHECK_EQUAL( invMatA, aux );

	// vector transformation
	Matrix4f translation = xe::translate<float>({1.0f, 1.0f, 1.0f});
	Vector3f position1 = {0.0f, -1.0f, 0.0f};
	Vector3f position2_1 = {1.0f,  0.0f, 1.0f};
	Vector3f position2_2 = xe::transform<float, 4>(translation, position1);
	
	BOOST_CHECK_EQUAL(position2_1, position2_2);
}
