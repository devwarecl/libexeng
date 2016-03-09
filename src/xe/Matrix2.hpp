
#pragma once

#ifndef __xe_matrix2_hpp__
#define __xe_matrix2_hpp__

#include <cassert>
#include <cmath>
#include <iostream>
#include <xe/Vector.hpp>

namespace xe {

	template<typename Type, int RowCount, int ColumnCount>
	class Matrix2 {
	public:
		typedef Matrix2<Type, RowCount, ColumnCount> MatrixType;
		static const int ValueCount = RowCount * ColumnCount;

	public:
		Matrix2() {}

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
		template<typename Type, int Count>
		struct Determinant {
			static Type compute(const Matrix2<Type, Count, Count> &m) {
				Type factor = Type(1);
				Type result = Type(0);
                
				const int row = 0;
                
				for (int column=0; column<Count; ++column) {
					factor = (column+1)%2 ? Type(-1) : Type(1);

					Type subDet = abs(m.getSubMatrix(row, column));

					result += factor * m.get(row, column) * subDet;
				}
                
				return result;
			}
		};

		template<typename Type>
		struct Determinant<Type, 2> {
			static Type compute(const Matrix2<Type, 2, 2> &m) {
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

	typedef Matrix2<float, 2, 2> Matrix2f;
	typedef Matrix2<float, 3, 3> Matrix3f;
    typedef Matrix2<float, 4, 4> Matrix4f;

    typedef Matrix2<double, 2, 2> Matrix2d;
    typedef Matrix2<double, 3, 3> Matrix3d;
    typedef Matrix2<double, 4, 4> Matrix4d;
}

#endif
