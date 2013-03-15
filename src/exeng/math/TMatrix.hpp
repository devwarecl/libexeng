/**
 * @brief PENDIENTE
 */

#ifndef __EXENG_MATH_TMATRIX_HPP__
#define __EXENG_MATH_TMATRIX_HPP__

#include <iosfwd>
#include "TBoundary.hpp"
#include "TVector.hpp"

namespace exeng
{
    namespace math
    {
        /**
         * @brief Generic matrix class
         * Suitable for inmediate mode rendering.
         */
        template<typename Type, int RowCount, int ColumnCount>
        class TMatrix
        {
        private:
            enum 
            { 
                Size = RowCount*ColumnCount
            };

        private:
            // For easing the interface reading
            typedef TMatrix<Type, RowCount, ColumnCount> Matrix;	
            typedef TVector<Type, RowCount> ColumnVector;
            typedef TVector<Type, ColumnCount> RowVector;

        private:
            int getIndex(int i, int j) const;

        public:

            /**
             * @brief Default constructor
             */
            TMatrix();

            /**
             * @brief Documentacion pendiente.
             */
            TMatrix(const Type* data);


            /**
             * @brief Documentacion pendiente.
             */
            TMatrix(Type value);

            /**
             * @brief Initialize the matrix from a external data 
             */
            void setup(const Type* data);

            /**
             * @brief Documentacion pendiente.
             */
            void setup(Type value);
    
            /**
             * @brief Computes the determinant
             */
            Type getDeterminant() const;

            /**
             * @brief Compute the matrix inverse.
             */
            void inverse();

            /**
             * @brief Compute the matrix inverse with a previously computed determinant.
             */
            void inverse(Type Determinant);

            /**
             * @brief Compute the matrix inverse
             */
            void transpose();

            /**
             * @brief Get a pointer to the internal data 
             */
            Type* getPtr();

            /**
             * @brief Get a const pointer to the internal data 
             */
            const Type* getPtr() const;
            
            /**
             * @brief Zero matrix
             */
            void zero();
            
            /**
             * @brief Identity matrix
             */
            void identity();

            /**
             * @brief Make a scaling matrix
             */
            void scaling(const TVector<Type, RowCount> &scale);

            /**
             * @brief Translation matrix
             */
            void translation(const TVector<Type, 3> &RelPos);

            /**
             * @brief Rotation matrix
             */
            void rotation(const TVector<Type, 3> &Axis, float Angle);

            /**
             * @brief Perspective viewing matrix
             */
            void perspective(Type Fov, Type Aspect, Type ZNear, Type ZFar);

            /**
             * @brief Look at matrix
             */
            void lookAt(const TVector<Type, 3> &Eye, const TVector<Type, 3> &At, const TVector<Type, 3> &Up);

            /**
             * @brief Yaw pitch roll camera matrix
             */
            void yawPitchRoll(Type Yaw, Type Pitch, Type Roll);

            /**
             * @brief Orthographic projection
             */
            void ortho(const TBoundary<Type, 3>& volume);

            /**
             * @brief Get the specified column vector
             */
            ColumnVector getColumnVector(int Column) const;

            /**
             * @brief Get the specified column vector
             */
            RowVector getRowVector(int Row) const;

            /**
             * @brief Set the specified vector in the indicated column
             */
            void setColumnVector(int Column, const ColumnVector& in);
        
            /**
             * @brief Set the specified vector in the indicated row
             */
            void setRowVector(int Row, const RowVector& in);

            /**
             * @brief Read or write the specified i, j matrix element.
             */
            Type& at(int i, int j);
            
            /**
             * @brief Get a const reference to the specified element
             */
            const Type& at(int i, int j) const;
            
            /**
             * @brief Documentacion pendiente.
             */
            template<int Row, int Column>
            Type& at()
            {
                return this->at(Row, Column);
            }

            /**
             * @brief Documentacion pendiente.
             */
            template<int Row, int Column>
            const Type& at() const
            {
                return this->at(Row, Column);
            }

            /**
             * @brief Get the submatrix at i, j
             */
            TMatrix<Type, RowCount-1, ColumnCount-1> getSubMatrix(int Row, int Column) const;

            /**
             * @brief Read-Write index based accesor
             */
            Type& operator[] (int index);

            /**
             * @brief Read index based accesor
             */
            const Type& operator[] (int index) const;

            /**
             * @brief Read-Write accesor
             */
            Type& operator() (int i, int j);

            /**
             * @brief Read olny accessor (for const objects)
             */
            const Type& operator() (int i, int j) const;
            
            
            /**
             * @brief Documentacion pendiente.
             */
            template<int OtherRowCount, int OtherColumnCount>
            Matrix& operator= (const TMatrix<Type, OtherRowCount, OtherColumnCount> &In)
            {
                for(int i=0; i<OtherRowCount; ++i)
                    for(int j=0; j<OtherColumnCount; ++j)
                        this->at(i, j) = In.At(i, j);
                
                return *this;
            }
            
            /**
             * @brief Check for equality
             */
            bool operator == (const Matrix& other) const;
            
            /**
             * @brief Check for inequality
             */
            bool operator != (const Matrix& other) const;

            /**
             * @brief Add two matrices
             */
            Matrix operator+ (const Matrix& other) const;

            /**
             * @brief Documentacion pendiente.
             */
            Matrix operator- (const Matrix& other) const;

            /**
             * @brief Documentacion pendiente.
             */
            Matrix operator- () const;

            /**
             * @brief Documentacion pendiente.
             */
            Matrix operator/ (Type other) const;
            
            /**
             * @brief Documentacion pendiente.
             */
            Matrix& operator+= (const Matrix& other);

            /**
             * @brief Documentacion pendiente.
             */
            Matrix& operator-= (const Matrix& other);

            /**
             * @brief Documentacion pendiente.
             */
            Matrix& operator*= (Type scalar);

            /**
             * @brief Documentacion pendiente.
             */
            Matrix& operator/= (Type scalar);

            /**
             * @brief Documentacion pendiente.
             */
            Matrix operator* (Type other) const;


            /**
             * @brief Multiplica dos matrices
             */
            template<int OtherRowCount, int OtherColumnCount>
            TMatrix<Type, RowCount, OtherColumnCount> operator* (const TMatrix<Type, OtherRowCount, OtherColumnCount>& other) const {
                TMatrix<Type, RowCount, ColumnCount> result;

                for(int i=0; i<RowCount; ++i) {
                    for(int j=0; j<ColumnCount; ++j) {
						auto v1 = this->getRowVector(i);
                        auto v2 =  other.getColumnVector(j);

                        result.at(i, j) = v1.dot(v2);
                    }
                }
            
                return result;
            }


            /**
             * @brief Documentacion pendiente.
             */
            friend TMatrix<Type, RowCount, ColumnCount> operator*(Type value, const TMatrix<Type, RowCount, ColumnCount>& in) {
                return in*value;
            }

            /**
             * @brief Documentacion pendiente.
             */
            Matrix& operator*= (const Matrix& other);

            /**
             * @brief Transforma un vector usando la transformacion encapsulada en esta matriz
             */
            template<int VectorSize>
            TVector<Type, VectorSize> operator* (const TVector<Type, VectorSize>& point) const
            {
                TVector<Type, VectorSize> Result;

                Result.setup(static_cast<Type>(0));
                
                for(int i=0; i<VectorSize; ++i)
                {
                    Result[i] = TVector<Type, VectorSize>::dot(this->getRowVector(i), point);
                }

                return Result;
            }


            /**
             * @brief Convert from another matrix type 
             * At the moment, only able to convert matrices of the same size
             */
            template<typename OtherType>
            operator TMatrix<OtherType, ColumnCount, RowCount>() const
            {
                TMatrix<OtherType, ColumnCount, RowCount> Result;

                for(int i=0; i<Size; ++i)
                    Result.Data[i] = static_cast<OtherType>(this->Data[i]);

                return Result;
            }

        private:
            /**
             * @brief Internal values represented as a raw array
             */
            Type Data[Size];
        };
        
        
        /**
         * @brief Documentacion pendiente.
         */
        template<typename Type, int RowCount, int ColumnCount>
        std::ostream& operator<< (std::ostream &os, const TMatrix<Type, RowCount, ColumnCount>& Other);
        
        typedef TMatrix<float, 4, 4> Matrix4f;
        typedef TMatrix<double, 4, 4> Matrix4d;
        
        typedef TMatrix<float, 3, 3> Matrix3f;
        typedef TMatrix<double, 3, 3> Matrix3d;
        
    }
}

#include "TMatrix.inl"

#endif	//__EXENG_MATH_TMATRIX_HPP__
