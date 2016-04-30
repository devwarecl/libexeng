
#pragma once

#ifndef __xe_matrix__
#define __xe_matrix__

#include <cassert>
#include <cmath>
#include <iostream>
#include <xe/Vector.hpp>
#include <xe/Boundary.hpp>

namespace xe {
	template<typename Type, int RowCount, int ColumnCount>
	class Matrix {
	public:
		typedef Matrix<Type, RowCount, ColumnCount> MatrixType;
		static const int ValueCount = RowCount * ColumnCount;

	public:
		Matrix() {}

		// accessors
		const Type& get(const int i, const int j) const {
			return values[offset(i, j)];
		}

		Type& get(const int i, const int j) {
			return values[offset(i, j)];
		}
		
		template<int i, int j>
		const Type& get() const {
			return values[offset(i, j)];
		}

		template<int i, int j>
		Type& get() {
			return values[offset(i, j)];
		}

		Vector<Type, RowCount> getColumn(const int j) const {
			assert(j >= 0);
			assert(j < RowCount);

			Vector<Type, RowCount> result;

			for (int i=0; i<RowCount; i++) {
				result[i] = this->get(i, j);
			}

			return result;
		}

		Vector<Type, ColumnCount> getRow(const int i) const {
			assert(i >= 0);
			assert(i < RowCount);

			Vector<Type, ColumnCount> result;

			for (int j=0; j<ColumnCount; j++) {
				result[j] = this->get(i, j);
			}

			return result;
		}

		void setColumn(const int j, const Vector<Type, RowCount> &v) {
			assert(j >= 0);
			assert(j < RowCount);

			for (int i=0; i<RowCount; i++) {
				this->get(i, j) = v[i];
			}
		}

		void setRow(const int i, const Vector<Type, ColumnCount> &v) {
			assert(i >= 0);
			assert(i < RowCount);

			for (int j=0; j<ColumnCount; j++) {
				this->get(i, j) = v[j];
			}
		}

		Matrix2<Type, RowCount - 1, ColumnCount - 1> getSubMatrix(const int row, const int column) const {
			assert(row >= 0);
			assert(row < RowCount);

			assert(column >= 0);
			assert(column < ColumnCount);

			Matrix2<Type, RowCount-1, ColumnCount-1> result;

			int ii = 0, jj = 0;

			for (int i=0; i<RowCount; ++i) {
				if (i == row) {
					continue;
				}

				for(int j=0; j<ColumnCount; ++j) {
					if (j == column) {
						continue;
					}

					result(ii, jj) = this->get(i, j); 
					++jj;
				}
            
				++ii;
				jj = 0;
			}
    
			return result;

		}

		Type* getPtr() {
			return values;
		}

		const Type* getPtr() const {
			return values;
		}

		// operators
		friend std::ostream& operator<< (std::ostream &os, const Matrix2<Type, RowCount, ColumnCount>& Other) {
			os << std::endl;

			for (int i=0; i<RowCount; ++i) {
				os << "[";
            
				for(int j=0; j<ColumnCount; ++j) {
					os << std::fixed << std::setprecision( 4 ) << Other.get(i, j);
                
					if (j + 1 != ColumnCount) {
						os << ", ";
					}
				}
				os << "]" << std::endl;
			}

			os << std::endl;

			return os;
		}

		const Type& operator() (const int i, const int j) const {
			return this->get(i, j);
		}

		Type& operator() (const int i, const int j) {
			return this->get(i, j);
		}

		MatrixType operator*(const Type factor) const {
			MatrixType result;

			for (int i=0; i<ValueCount; i++) {
				result.values[i] = factor * values[i];
			}
			
			return result;
		}

		friend MatrixType operator*(const Type factor, const MatrixType &m) {
			return m * factor;
		}

		MatrixType operator/(const Type factor) const {
			return (*this) * (Type(1)/factor);
		}

		MatrixType operator+() const {
			return *this;
		}

		MatrixType operator-() const {
			return (*this) * Type(-1);
		}

		MatrixType operator+(const MatrixType &other) const {
			MatrixType result;

			for (int i=0; i<ValueCount; i++) {
				result.values[i] = values[i] + other.values[i];
			}
			
			return result;
		}

		MatrixType operator-(const MatrixType &other) const {
			return *this + (-other);
		}

		MatrixType operator*(const MatrixType &other) const {
			MatrixType result;

			for (int i=0; i<RowCount; i++) {
				for (int j=0; j<ColumnCount; j++) {
					result(i, j) = dot(this->getRow(i), other.getColumn(j));
				}
			}

			return result;
		}

		MatrixType& operator+= (const MatrixType &other) {
			*this = *this + other;

			return *this;
		}

		MatrixType& operator-= (const MatrixType &other) {
			*this = *this - other;

			return *this;
		}

		MatrixType& operator*= (const MatrixType &other) {
			*this = *this * other;

			return *this;
		}

		MatrixType& operator/= (const MatrixType &other) {
			*this = *this / other;

			return *this;
		}

		MatrixType& operator*= (Type factor) {
			*this = *this * factor;

			return *this;
		}

		MatrixType& operator/= (Type factor) {
			*this = *this / factor;

			return *this;
		}

		MatrixType operator/ (const MatrixType &other) const {
			return (*this) * inverse(other);
		}

		bool operator== (const MatrixType &other) const {
			for (int i=0; i<ValueCount; i++) {
				if (values[i] != other.values[i]) {
					return false;
				}
			}

			return true;
		}

		bool operator!= (const MatrixType &other) const {
			return ! (*this == other);
		}

	private:
		template<typename Type_, int Count>
		struct Determinant {
			static Type_ compute(const Matrix2<Type_, Count, Count> &m) {
				Type_ factor = Type_(1);
				Type_ result = Type_(0);
                
				const int row = 0;
                
				for (int column=0; column<Count; ++column) {
					factor = (column+1)%2 ? Type_(-1) : Type_(1);

					Type_ subDet = abs(m.getSubMatrix(row, column));

					result += factor * m.get(row, column) * subDet;
				}
                
				return result;
			}
		};

		template<typename Type_>
		struct Determinant<Type_, 2> {
			static Type_ compute(const Matrix2<Type_, 2, 2> &m) {
				return m(0, 0)*m(1, 1) - m(1, 0)*m(0, 1);
			}
		};

	public:
		friend Type abs(const Matrix2<Type, RowCount, ColumnCount> &m) {
			static_assert(RowCount == ColumnCount, "");

			return Determinant<Type, RowCount>::compute(m);
		}

		friend MatrixType adjoint(const MatrixType &matrix) {
			Matrix2<Type, RowCount, ColumnCount> result;
        
			for(int i=0; i<RowCount; ++i) {
				for(int j=0; j<ColumnCount; ++j) {
					Type factor = ((i+j)%2 == 1) ? Type(1) : Type(-1);
					result(i, j) = factor * abs(matrix.getSubMatrix(i, j));
				}
			}
        
			return result;
		}

		friend MatrixType transpose(const MatrixType &other) {
			auto result = other;
			int baseColumn = 1;

			for(int i=0; i<RowCount-1; ++i) {
				for(int j=baseColumn; j<ColumnCount; ++j) {
					std::swap( result(i, j), result(j, i) );
				}

				++baseColumn;
			}
        
			return result;
		}

		friend MatrixType inverse(const MatrixType &m, Type det) {
			return transpose(adjoint(m)) / det;
		}
		
		friend MatrixType inverse(const MatrixType &m) {
			return inverse(m, abs(m));
		}

	private:
		int offset(const int i, const int j) const {
			assert(i >= 0);
			assert(i < RowCount);

			assert(j >= 0);
			assert(j < ColumnCount);

			return j * RowCount + i;
		}
		
		template<int i, int j>
		int offset() const {
			static_assert(i >= 0, "");
			static_assert(i < RowCount, "");

			static_assert(j >= 0, "");
			static_assert(j < ColumnCount, "");

			return j * RowCount + i;
		}

	private:
		Type values[ValueCount];
	};
	
	// matrix factory functions

	template<typename Type, int RowCount, int ColumnCount>
    Matrix2<Type, RowCount, ColumnCount> zero() {
        Matrix2<Type, RowCount, ColumnCount> result;
        
        for(int i=0; i<RowCount; ++i) {
			for(int j=0; j<ColumnCount; ++j) {
				result(i, j) = Type(0);
			}
        }
        
        return result;
    }

    template<typename Type, int Size>
    Matrix2<Type, Size, Size> identity() {
        auto result = zero<Type, Size, Size>();
        
        for(int i=0; i<Size; ++i) {
            result(i, i) = Type(1);
        }
        
        return result;
    }
    
    template<typename Type, int Size>
    Matrix2<Type, Size, Size> scale(const Vector<Type, 3> &scale) {
        auto result = identity<Type, Size>();
        
        for(int i=0; i<3; ++i) {
            result(i, i) = scale[i];
        }
        
        return result;
    }
    
    template<typename Type>
    Matrix2<Type, 4, 4> translate(const Vector<Type, 3> &RelPos) {
        auto result = identity<Type, 4>();
        
        result.get(0, 3) = RelPos.x;
        result.get(1, 3) = RelPos.y;
        result.get(2, 3) = RelPos.z;
        
        return result;
    }
    
    template<typename Type>
    Matrix2<Type, 4, 4> rotatex(const Type radians) {
        auto result = identity<Type, 4>();
        
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        result.get(1, 1) = Cos;
        result.get(2, 2) = Cos;
        result.get(2, 1) = -Sin;
        result.get(1, 2) = Sin;
        
        return result;
    }
    
    template<typename Type>
    Matrix2<Type, 4, 4> rotatey(const Type radians) {
        auto result = identity<Type, 4>();
        
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        result.get(0, 0) = Cos;
        result.get(2, 2) = Cos;
        result.get(2, 0) = -Sin;
        result.get(0, 2) = Sin;
        
        return result;
    }
    
    template<typename Type>
    Matrix2<Type, 4, 4> rotatez(const Type radians) {
        auto result = identity<Type, 4>();
        
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        result.get(0, 0) = Cos;
        result.get(1, 1) = Cos;
        result.get(1, 0) = Sin;
        result.get(0, 1) = -Sin;
        
        return result;
    }
    
    template<typename Type>
    Matrix2<Type, 4, 4> rotate(Type radians, const Vector<Type, 3> &Axis) {
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        Vector<Type, 3> U(Axis), V(normalize(Axis));
        
        auto MatS = xe::zero<Type, 3, 3>();
        auto MatUut = xe::zero<Type, 3, 3>();
        auto MatId = xe::identity<Type, 3>();
        
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
        
        auto result = identity<Type, 4>();
        
        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                result(i, j) = tempResult(i, j);
            }
        }
        
        return result;
    }

    template<typename Type>
    Matrix2<Type, 4, 4> lookat(const Vector<Type, 3> &Eye, const Vector<Type, 3> &At, const Vector<Type, 3> &Up) {
        auto forward = normalize(At - Eye);
        auto side = normalize(cross(forward, Up));
        auto up = cross(side, forward);
        
        auto result = identity<Type, 4>();

        result.get(0, 0) = side.x;
        result.get(0, 1) = side.y;
        result.get(0, 2) = side.z;
    
        result.get(1, 0) = up.x;
        result.get(1, 1) = up.y;
        result.get(1, 2) = up.z;
    
        result.get(2, 0) = -forward.x;
        result.get(2, 1) = -forward.y;
        result.get(2, 2) = -forward.z;
        
        result *= translate<Type>(-Eye);
        
        return result;
    }
    
    template<typename Type>
    Matrix2<Type, 4, 4> perspective(Type fov_radians, Type aspect, Type znear, Type zfar) {
        Type f = Type(1) / std::tan(fov_radians / Type(2));
        // Type zdiff = zfar - znear;	// Reverse the projection (far objects appear in front of those near)
		Type zdiff = znear - zfar;
        
        auto result = identity<Type, 4>();
        
        result.get(0, 0) = f / aspect;
        result.get(1, 1) = f;
        result.get(2, 2) = (zfar + znear) / zdiff;
        result.get(3, 2) = Type(-1);
        result.get(2, 3) = (Type(2)*znear*zfar) / zdiff;
        
        return result;
    }
    
    //!Orthographic projection
    template<typename Type>
    Matrix2<Type, 4, 4> ortho(const Boundary<Type, 3>& Volume) {
        Type left = Volume.GetSide(Side3::Left);
        Type right = Volume.GetSide(Side3::Right);
        
        Type bottom = Volume.GetSide(Side3::Bottom);
        Type top = Volume.GetSide(Side3::Top);

        Type near = Volume.GetSide(Side3::Near);
        Type far = Volume.GetSide(Side3::Far);
        
        auto result = identity<Type, 4>();
        
        result.get(0, 0) = Type(2) / ( right - left);
        result.get(1, 1) = Type(2) / ( top - bottom );
        result.get(2, 2) = Type(-2) / ( far - near  );
        result.get(3, 3) = Type(1);
        
        result.get(0, 3) = - ( right + left ) / ( right - left );
        result.get(1, 3) = - ( top + bottom ) / ( top - bottom );
        result.get(2, 3) = - ( far + near ) / ( far - near );
        
        return result;
    }

	template<typename Type, int Size>
	Vector<Type, Size> transform(const Matrix2<Type, Size, Size> &m, Vector<Type, Size> &v) {
		Vector<Type, Size> result;

		for (int i=0; i<Size; i++) {
			result[i] = dot(m.getRow(i), v);
		}

		return result;
	}

	template<typename Type, int Size>
	Vector<Type, Size - 1> transform(const Matrix2<Type, Size, Size> &m, Vector<Type, Size - 1> &v) {
		Vector<Type, Size - 1> result;

		for (int i=0; i<Size - 1; i++) {
			result[i] = dot(m.getRow(i), Vector<Type, Size>(v, Type(1)));
		}

		return result;
	}

	typedef Matrix<float, 2, 2> Matrix2f;
	typedef Matrix<float, 3, 3> Matrix3f;
    typedef Matrix<float, 4, 4> Matrix4f;

    typedef Matrix<double, 2, 2> Matrix2d;
    typedef Matrix<double, 3, 3> Matrix3d;
    typedef Matrix<double, 4, 4> Matrix4d;
}

#endif
