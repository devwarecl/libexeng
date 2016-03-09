
#include <iostream>
#include <iomanip>
#include <typeinfo>

#include <xe/Matrix2.hpp>

#include <boost/test/unit_test.hpp>

template<typename Type, int RowCount, int ColumnCount>
void zero(xe::Matrix2<Type, RowCount, ColumnCount> &out) {
	for (int j=0; j<ColumnCount; j++) {
		for (int i=0; i<RowCount; i++) {
			out(i, j) = Type(0);
		}
	}
}

template<typename Type, int Count>
void identity(xe::Matrix2<Type, Count, Count> &out) {
	zero(out);

	for (int i=0; i<Count; i++) {
		out(i, i) = Type(1);
	}
}

template<typename Type, int Count>
void scale(xe::Matrix2<Type, Count, Count> &out, const xe::Vector<Type, Count> &scale) {
	zero(out);

    for(int i=0; i<3; ++i) {
        out(i, i) = scale[i];
    }
        
    return result;
}
    
template<typename Type>
void translate(xe::Matrix2<Type, 4, 4> &out, const xe::Vector<Type, 4> &position) {
	identity(out);

	for (int i=0; i<4; i++) {
		out(i, 3) = position[i];
	}
}
    
template<typename Type>
void rotatex(xe::Matrix2<Type, 4, 4> &out, const Type radians) {
	identity(out);

    Type cos = std::cos(radians);
    Type sin = std::sin(radians);
        
    out(1, 1) = cos;
    out(2, 2) = cos;
    out(2, 1) = -sin;
    out(1, 2) = sin;
}
    
template<typename Type>
void rotatey(xe::Matrix2<Type, 4, 4> &out, const Type radians) {
    identity(out);
        
    Type cos = std::cos(radians);
    Type sin = std::sin(radians);
        
    out(0, 0) = cos;
    out(2, 2) = cos;
    out(2, 0) = -sin;
    out(0, 2) = sin;
}
    
template<typename Type>
void rotatez(xe::Matrix2<Type, 4, 4> &out, const Type radians) {
    identity(out);
        
    Type cos = std::cos(radians);
    Type sin = std::sin(radians);
        
    out(0, 0) = cos;
    out(1, 1) = cos;
    out(1, 0) = sin;
    out(0, 1) = -sin;
}

template<typename Type>
void rotate(xe::Matrix2<Type, 4, 4> &out, Type radians, const xe::Vector<Type, 3> &Axis) {
    Type Cos = std::cos(radians);
    Type Sin = std::sin(radians);
        
    xe::Vector<Type, 3> U(Axis), V(normalize(Axis));
    
	xe::Matrix2<Type, 3, 3> MatS;
	xe::Matrix2<Type, 3, 3> MatUut;
	xe::Matrix2<Type, 3, 3> MatId;

	zero(MatS);
	zero(MatUut);
	identity(MatId);
    
    //Iniciar S
    MatS.get(0, 1) = -V.z;
    MatS.get(1, 0) = V.z;
    
    MatS.get(0, 2) = V.y;
    MatS.get(2, 0) = -V.y;
    
    MatS.get(1, 2) = -V.x;
    MatS.get(2, 1) = V.x;

    //Iniciar u*ut
    MatUut.get(0, 0) = V.x * V.x;
    MatUut.get(1, 0) = V.y * V.x;
    MatUut.get(2, 0) = V.z * V.x;
    
    MatUut.get(0, 1) = V.x * V.y;
    MatUut.get(1, 1) = V.y * V.y;
    MatUut.get(2, 1) = V.z * V.y;
        
    MatUut.get(0, 2) = V.x * V.z;
    MatUut.get(1, 2) = V.y * V.z;
    MatUut.get(2, 2) = V.z * V.z;
        
    auto tempResult = MatUut + Cos * (MatId - MatUut) + Sin * MatS;
    
	identity(out);

    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            out(i, j) = tempResult(i, j);
        }
    }
}

template<typename Type, int RowCount, int ColumnCount>
void increased(xe::Matrix2<Type, RowCount, ColumnCount> &out) {
	Type current = 0;

	for (int j=0; j<ColumnCount; j++) {
		for (int i=0; i<RowCount; i++) {
			out(i, j) = ++current;
		}
	}
}

struct MatrixTestFixture {
	xe::Matrix2f m1, m2, m3;
	xe::Matrix4f m4, m5;

	MatrixTestFixture() {
		zero(m1);
		identity(m2);
		increased(m3);

		rotate(m4, xe::rad(60.0f), xe::Vector3f(1.0f, 1.0f, 1.0f));
		rotate(m5, xe::rad(-60.0f), xe::Vector3f(1.0f, 1.0f, 1.0f));
	}
};

BOOST_FIXTURE_TEST_CASE(MatrixTest, MatrixTestFixture) 
{
	// check accessors
	BOOST_CHECK_EQUAL(m1(0, 0), 0.0f);
	BOOST_CHECK_EQUAL(m1(1, 0), 0.0f);
	BOOST_CHECK_EQUAL(m1(0, 1), 0.0f);
	BOOST_CHECK_EQUAL(m1(1, 1), 0.0f);

	BOOST_CHECK_EQUAL(m2(0, 0), 1.0f);
	BOOST_CHECK_EQUAL(m2(1, 0), 0.0f);
	BOOST_CHECK_EQUAL(m2(0, 1), 0.0f);
	BOOST_CHECK_EQUAL(m2(1, 1), 1.0f);

	BOOST_CHECK_EQUAL(m3(0, 0), 1.0f);
	BOOST_CHECK_EQUAL(m3(1, 0), 2.0f);
	BOOST_CHECK_EQUAL(m3(0, 1), 3.0f);
	BOOST_CHECK_EQUAL(m3(1, 1), 4.0f);

	// check matrix comparisons
	BOOST_CHECK_NE(m1, m2);
	BOOST_CHECK_NE(m2, m3);
	BOOST_CHECK_NE(m1, m3);
	BOOST_CHECK_EQUAL(m1, m1);
	BOOST_CHECK_EQUAL(m2, m2);
	BOOST_CHECK_EQUAL(m3, m3);

	// check matrix basic operations
	BOOST_CHECK_EQUAL(m1*m1, m1);
	BOOST_CHECK_EQUAL(m2*m2, m2);
	BOOST_CHECK_NE(m3*m3, m3);

	BOOST_CHECK_EQUAL(m2 + m2 - m1, (m2 + m1) * 2.0f);

	// check matrix inverse and rotation
	BOOST_CHECK_EQUAL(m4, m4);
	BOOST_CHECK_EQUAL(inverse(m4), m5);
}
