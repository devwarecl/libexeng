/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_MATH_Matrix_HPP__
#define __EXENG_MATH_Matrix_HPP__

#include <iosfwd>
#include "Boundary.hpp"
#include "Vector.hpp"

namespace exeng { 
    /**
     * @brief Generic matrix class
     * Suitable for inmediate mode rendering.
     */
    template<typename Type, int RowCount, int ColumnCount>
    class Matrix {
    private:
        enum  { 
            Size = RowCount*ColumnCount
        };

    private:
        // For easing the interface reading
        typedef Matrix<Type, RowCount, ColumnCount> MatrixType;	
        typedef Vector<Type, RowCount> ColumnVectorType;
        typedef Vector<Type, ColumnCount> RowVectorType;

    private:
        int getIndex(int i, int j) const;

    public:
        /**
         * @brief Default constructor
         */
        Matrix();

        /**
         * @brief Documentacion pendiente.
         */
        Matrix(const Type* data);


        /**
         * @brief Documentacion pendiente.
         */
        Matrix(Type value);

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
        void scaling(const Vector<Type, RowCount> &scale);

        /**
         * @brief Translation matrix
         */
        void translation(const Vector<Type, 3> &RelPos);

        /**
         * @brief Rotation matrix
         */
        void rotation(const Vector<Type, 3> &Axis, float Angle);

        /**
         * @brief Perspective viewing matrix
         */
        void perspective(Type Fov, Type Aspect, Type ZNear, Type ZFar);

        /**
         * @brief Look at matrix
         */
        void lookAt(const Vector<Type, 3> &Eye, const Vector<Type, 3> &At, const Vector<Type, 3> &Up);

        /**
         * @brief Yaw pitch roll camera matrix
         */
        void yawPitchRoll(Type Yaw, Type Pitch, Type Roll);

        /**
         * @brief Orthographic projection
         */
        void ortho(const Boundary<Type, 3>& volume);

        /**
         * @brief Get the specified column vector
         */
        ColumnVectorType getColumnVector(int Column) const;

        /**
         * @brief Get the specified column vector
         */
        RowVectorType getRowVector(int Row) const;

        /**
         * @brief Set the specified vector in the indicated column
         */
        void setColumnVector(int Column, const ColumnVectorType& in);

        /**
         * @brief Set the specified vector in the indicated row
         */
        void setRowVector(int Row, const RowVectorType& in);

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
        Type& at() {
            return this->at(Row, Column);
        }

        /**
         * @brief Documentacion pendiente.
         */
        template<int Row, int Column>
        const Type& at() const {
            return this->at(Row, Column);
        }

        /**
         * @brief Get the submatrix at i, j
         */
        Matrix<Type, RowCount-1, ColumnCount-1> getSubMatrix(int Row, int Column) const;

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
        MatrixType& operator= (const Matrix<Type, OtherRowCount, OtherColumnCount> &In) {
            for(int i=0; i<OtherRowCount; ++i) {
                for(int j=0; j<OtherColumnCount; ++j) {
                    this->at(i, j) = In.at(i, j);
                }
            }
            
            return *this;
        }
    
        /**
         * @brief Check for equality
         */
        bool operator == (const MatrixType& other) const;
    
        /**
         * @brief Check for inequality
         */
        bool operator != (const MatrixType& other) const;

        /**
         * @brief Add two matrices
         */
        MatrixType operator+ (const MatrixType& other) const;

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType operator- (const MatrixType& other) const;

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType operator- () const;

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType operator/ (Type other) const;
    
        /**
         * @brief Documentacion pendiente.
         */
        MatrixType& operator+= (const MatrixType& other);

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType& operator-= (const MatrixType& other);

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType& operator*= (Type scalar);

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType& operator/= (Type scalar);

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType operator* (Type other) const;

        /**
         * @brief Multiplica dos matrices
         */
        template<int OtherRowCount, int OtherColumnCount>
        Matrix<Type, RowCount, OtherColumnCount> operator* (const Matrix<Type, OtherRowCount, OtherColumnCount>& other) const {
            Matrix<Type, RowCount, ColumnCount> result;

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
        friend Matrix<Type, RowCount, ColumnCount> operator*(Type value, const Matrix<Type, RowCount, ColumnCount>& in) {
            return in*value;
        }

        /**
         * @brief Documentacion pendiente.
         */
        MatrixType& operator*= (const MatrixType& other);

        /**
         * @brief Transforma un vector usando la transformacion encapsulada en esta matriz
         */
        template<int VectorSize>
        Vector<Type, VectorSize> operator* (const Vector<Type, VectorSize>& point) const {
			Vector<Type, VectorSize> result{Type(0)};
            
            for(int i=0; i<VectorSize; ++i) {
                result[i] = dot<Type, VectorSize>(this->getRowVector(i), point);
            }

            return result;
        }


        /**
         * @brief Convert from another matrix type 
         * At the moment, only able to convert matrices of the same size
         */
        template<typename OtherType>
        operator Matrix<OtherType, ColumnCount, RowCount>() const
        {
            Matrix<OtherType, ColumnCount, RowCount> Result;

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
    std::ostream& operator<< (std::ostream &os, const Matrix<Type, RowCount, ColumnCount>& Other);

    typedef Matrix<float, 4, 4> Matrix4f;
    typedef Matrix<double, 4, 4> Matrix4d;

    typedef Matrix<float, 3, 3> Matrix3f;
    typedef Matrix<double, 3, 3> Matrix3d;
}

#include "Matrix.inl"

#endif	//__EXENG_MATH_Matrix_HPP__
