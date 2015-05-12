
/**
 * @file    Matrix.hpp
 * @brief   Definition and implementation of the Matrix class and companion functions.
 */


/*
 * Copyright (c) 2013-2015 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_MATRIX_HPP__
#define __EXENG_MATRIX_HPP__

#include <iosfwd>
#include <cassert>
#include <cstring>
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
        static const int Size = RowCount*ColumnCount;
        
    private:
        // Interface reading simplifications
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
        explicit Matrix(const Type* data);
        
        /**
         * @brief Documentacion pendiente.
         */
        explicit Matrix(Type value);

        /**
         * @brief Initialize the matrix from a external data 
         */
        void setup(const Type* data);

        /**
         * @brief Documentacion pendiente.
         */
        void setup(Type value);

        /**
         * @brief Get a pointer to the internal data 
         */
        Type* getPtr();

        /**
         * @brief Get a const pointer to the internal data 
         */
        const Type* getPtr() const;
        
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
         * @brief 
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
         * @brief Matrix scale
         */
        MatrixType operator* (Type other) const;

        /**
         * @brief Matrix multiplication
         */
        template<int OtherRowCount, int OtherColumnCount>
        Matrix<Type, RowCount, OtherColumnCount> operator* (const Matrix<Type, OtherRowCount, OtherColumnCount>& other) const {
            Matrix<Type, RowCount, ColumnCount> result;

            for(int i=0; i<RowCount; ++i) {
                for(int j=0; j<ColumnCount; ++j) {
                    auto v1 = this->getRowVector(i);
                    auto v2 =  other.getColumnVector(j);

                    result.at(i, j) = dot(v1, v2);
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
         * @brief Convert from another matrix type 
         * At the moment, only able to convert matrices of the same size
         */
        template<typename OtherType>
        operator Matrix<OtherType, ColumnCount, RowCount>() const
        {
            Matrix<OtherType, ColumnCount, RowCount> Result;

            for(int i=0; i<Size; ++i) {
                Result.Data[i] = static_cast<OtherType>(this->Data[i]);
			}

            return Result;
        }
        
        friend std::ostream& operator<< (std::ostream &os, const Matrix<Type, RowCount, ColumnCount>& Other) 
        {
            for (int i=0; i<RowCount; ++i) {
                os << "[";
            
                for(int j=0; j<ColumnCount; ++j) {
                    os << std::fixed << std::setprecision( 4 ) << Other.at(i, j);
                
                    if (j + 1 != ColumnCount) {
                        os << ", ";
                    }
                }
                os << "]" << std::endl;
            }
        
            return os;
        }
        
    private:
        Type Data[Size];
    };
    
    template<typename Type, int RowCount, int ColumnCount>
    int Matrix<Type, RowCount, ColumnCount>::getIndex(int i, int j) const
    {
        assert(i < RowCount);
        assert(i < ColumnCount);

        return i*ColumnCount + j;
    }

    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount-1, ColumnCount-1> 
    Matrix<Type, RowCount, ColumnCount>::getSubMatrix(int Row, int Column) const
    {
        Matrix<Type, RowCount-1, ColumnCount-1> Result;
        int ii = 0, jj = 0;

        for(int i=0; i<RowCount; ++i) {
            if (i != Row) {
                for(int j=0; j<ColumnCount; ++j) {
                    if (j != Column) {
                        Result(ii, jj) = this->at(i, j);    
                        ++jj;
                    }
                }
            
                ++ii;
                jj = 0;
            }
        }
    
        return Result;
    }

    //!Default constructor
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>::Matrix() {}

    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>::Matrix(Type value)
    {
        this->setup(value);
    }

    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>::Matrix(const Type* data)
    {
        this->setup(data);
    }

    template<typename Type, int RowCount, int ColumnCount>
    Type& Matrix<Type, RowCount, ColumnCount>::at(int i, int j)
    {
        assert(i < RowCount);
        assert(j < ColumnCount);
        
        return this->Data[this->getIndex(i, j)];
    }

    template<typename Type, int RowCount, int ColumnCount>
    const Type& Matrix<Type, RowCount, ColumnCount>::at(int i, int j) const
    {
        assert(i < RowCount);
        assert(j < ColumnCount);
    
        return this->Data[this->getIndex(i, j)];
    }

    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::setup(const Type* data)
    {
        ::memcpy(this->Data, data, sizeof(Type)*RowCount*ColumnCount);
    }

    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::setup(Type Value)
    {
        for(int i=0; i<RowCount*ColumnCount; ++i) {
            this->Data[i] = Value;
        }
    }
    
    //!Get a pointer to the internal data 
    template<typename Type, int RowCount, int ColumnCount>
    Type* Matrix<Type, RowCount, ColumnCount>::getPtr() {
        return this->Data;
    }

    //!Get a const pointer to the internal data 
    template<typename Type, int RowCount, int ColumnCount>
    const Type* Matrix<Type, RowCount, ColumnCount>::getPtr() const {
        return this->Data;
    }

    template<typename Type, int RowCount, int ColumnCount>
    Vector<Type, RowCount> Matrix<Type, RowCount, ColumnCount>::getColumnVector(int Column) const
    {
        Vector<Type, RowCount> Result;

        for(int i=0; i<RowCount; ++i) {
            Result[i] = this->at(i, Column);
        }

        return Result;
    }

    template<typename Type, int RowCount, int ColumnCount>
    Vector<Type, ColumnCount> Matrix<Type, RowCount, ColumnCount>::getRowVector(int Row) const
    {
        Vector<Type, ColumnCount> Result;

        for(int j=0; j<ColumnCount; ++j)
            Result[j] = this->at(Row, j);

        return Result;
    }


    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::setColumnVector(int Column, const Vector<Type, RowCount>& in)
    {
        for(int i=0; i<RowCount; ++i)
            this->at(i, Column) = in[i];
    }


    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::setRowVector(int Row, const Vector<Type, ColumnCount>& in)
    {
        for(int j=0; j<ColumnCount; ++j)
            this->at(Row, j) = in[j];
    }


    //!Read-Write index based accesor
    template<typename Type, int RowCount, int ColumnCount>
    Type& Matrix<Type, RowCount, ColumnCount>::operator[] (int index)
    {
        return this->Data[index];
    }


    //!Read index based accesor
    template<typename Type, int RowCount, int ColumnCount>
    const Type& Matrix<Type, RowCount, ColumnCount>::operator[] (int index) const
    {
        return this->at(index);
    }


    //!Read-Write accesor
    template<typename Type, int RowCount, int ColumnCount>
    Type& Matrix<Type, RowCount, ColumnCount>::operator() (int i, int j)
    {
        return this->at(i, j);
    }


    //!Read olny accessor (for const objects)
    template<typename Type, int RowCount, int ColumnCount>
    const Type& Matrix<Type, RowCount, ColumnCount>::operator() (int i, int j) const
    {
        return this->at(i, j);
    }


    //!Check for equality
    template<typename Type, int RowCount, int ColumnCount>
    bool Matrix<Type, RowCount, ColumnCount>::operator == (const Matrix<Type, RowCount, ColumnCount>& other) const
    {
        return arrayCompare<Type, RowCount*ColumnCount>(this->getPtr(), other.getPtr());
    }


    //!Check for inequality
    template<typename Type, int RowCount, int ColumnCount>
    bool Matrix<Type, RowCount, ColumnCount>::operator != (const Matrix<Type, RowCount, ColumnCount>& other) const
    {
        return !(*this == other);
    }


    //!Add two matrices
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> Matrix<Type, RowCount, ColumnCount>::operator+ (const Matrix<Type, RowCount, ColumnCount>& other) const
    {
        Matrix<Type, RowCount, ColumnCount> Result;

        for(int i=0; i<RowCount*ColumnCount; ++i)
            Result.Data[i] = this->Data[i] + other.Data[i];
    
        return Result;
    }


    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> Matrix<Type, RowCount, ColumnCount>::operator- (const Matrix<Type, RowCount, ColumnCount>& other) const
    {
        Matrix<Type, RowCount, ColumnCount> Result;

        for(int i=0; i<RowCount*ColumnCount; ++i)
            Result.Data[i] = this->Data[i] - other.Data[i];
    
        return Result;
    }


    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> Matrix<Type, RowCount, ColumnCount>::operator- () const
    {
        Matrix<Type, RowCount, ColumnCount> Result;

        for(int i=0; i<RowCount*ColumnCount; ++i)
            Result.Data[i] = -this->Data[i];
    
        return Result;
    }


    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> Matrix<Type, RowCount, ColumnCount>::operator* (Type other) const
    {
        Matrix<Type, RowCount, ColumnCount> Result;

        for(int i=0; i<RowCount*ColumnCount; ++i) {
            Result.Data[i] = this->Data[i] * other;
        }

        return Result;
    }

    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> Matrix<Type, RowCount, ColumnCount>::operator/ (Type other) const
    {
        Matrix<Type, RowCount, ColumnCount> Result;

        for(int i=0; i<RowCount*ColumnCount; ++i) {
            Result[i] = this->Data[i] / other;
        }

        return Result;
    }


    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>& Matrix<Type, RowCount, ColumnCount>::operator+= (const Matrix<Type, RowCount, ColumnCount>& other)
    {
        for(int i=0; i<RowCount*ColumnCount; ++i) {
            this->Data[i] += other.Data[i];
        }
    
        return *this;
    }

    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>& Matrix<Type, RowCount, ColumnCount>::operator-= (const Matrix<Type, RowCount, ColumnCount>& other)
    {
        for(int i=0; i<RowCount*ColumnCount; ++i) {
            this->Data[i] -= other.Data[i];
        }
    
        return *this;
    }

    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>& Matrix<Type, RowCount, ColumnCount>::operator*= (const Matrix<Type, RowCount, ColumnCount>& other) 
    {
        *this = *this * other;

        return *this;
    }

    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>& Matrix<Type, RowCount, ColumnCount>::operator*= (Type scalar) 
    {
        for(int i=0; i<RowCount*ColumnCount; ++i) {
            this->at(i) *= scalar;
        }
    
        return *this;
    }

    //!
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount>& Matrix<Type, RowCount, ColumnCount>::operator/= (Type scalar) 
    {
        for(int i=0; i<RowCount*ColumnCount; ++i) {
            this->Data[i] /= scalar;
        }
    
        return *this;
    }
    
    namespace __private 
    {
        template<typename Type, int Size>
        struct MatrixDeterminant 
        {
            static Type compute(const Matrix<Type, Size, Size> &matrix) 
            {
                Type factor = Type(1);
                Type result = Type(0);
                
                const int row = 0;
                
                for (int column=0; column<Size; ++column) {
					if ((column+1)%2 == 0) {
						factor = Type(1);
					} else {
						factor = Type(-1);
					}
					
					Type subDet = abs(matrix.getSubMatrix(row, column));

                    result += factor * matrix.at(row, column) * subDet;
                }
                
                return result;
            }
        };
        
        template<typename Type>
        struct MatrixDeterminant<Type, 2> 
        {
            static Type compute(const Matrix<Type, 2, 2> &m) 
            {
                return m(0, 0)*m(1, 1) - m(0, 1)*m(1, 0);
            }
        };
    }
    
    /**
     * @brief Compute the matrix determinant
     */
    template<typename Type, int Size>
    Type abs(const Matrix<Type, Size, Size> &matrix) 
    {
        return __private::MatrixDeterminant<Type, Size>::compute(matrix);
    }
    
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> adjoint(const Matrix<Type, RowCount, ColumnCount> &matrix) 
    {
        static_assert(RowCount==ColumnCount, "Only square matrices are supported.");
        
        Matrix<Type, RowCount, ColumnCount> result;
        
        for(int i=0; i<RowCount; ++i) {
            for(int j=0; j<ColumnCount; ++j) {
                
                Type factor = ((i+j)%2 == 1) ? Type(1) : Type(-1);
                result(i, j) = factor * abs(matrix.getSubMatrix(i, j));
            }
        }
        
        return result;
    }
    
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> transpose(const Matrix<Type, RowCount, ColumnCount> &matrix) 
    {
        static_assert(RowCount==ColumnCount, "Only square matrices are supported.");
        
        auto result = matrix;
        int baseColumn = 1;

        for(int i=0; i<RowCount-1; ++i) {
            for(int j=baseColumn; j<ColumnCount; ++j) {
                std::swap( result(i, j), result(j, i) );
            }

            ++baseColumn;
        }
        
        return result;
    }
    
    /*
     * Matrix factory functions for 3D graphics
     */
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> zero()
    {
        return Matrix<Type, RowCount, ColumnCount>{Type(0)};
    }

    template<typename Type, int Size>
    Matrix<Type, Size, Size> identity() 
    {
        auto result = zero<Type, Size, Size>();
        
        for(int i=0; i<Size; ++i) {
            result(i, i) = Type(1);
        }
        
        return result;
    }
    
    template<typename Type, int Size>
    Matrix<Type, Size, Size> scale(const Vector<Type, 3> &scale)
    {
        auto result = identity<Type, Size>();
        
        for(int i=0; i<3; ++i) {
            result(i, i) = scale[i];
        }
        
        return result;
    }
    
    template<typename Type>
    Matrix<Type, 4, 4> translate(const Vector<Type, 3> &RelPos)
    {
        auto result = identity<Type, 4>();
        
        result.at(0, 3) = RelPos.x;
        result.at(1, 3) = RelPos.y;
        result.at(2, 3) = RelPos.z;
        
        return result;
    }
    
    template<typename Type>
    Matrix<Type, 4, 4> rotatex(const Type radians)
    {
        auto result = identity<Type, 4>();
        
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        result.at(1, 1) = Cos;
        result.at(2, 2) = Cos;
        result.at(2, 1) = -Sin;
        result.at(1, 2) = Sin;
        
        return result;
    }
    
    template<typename Type>
    Matrix<Type, 4, 4> rotatey(const Type radians)
    {
        auto result = identity<Type, 4>();
        
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        result.at(0, 0) = Cos;
        result.at(2, 2) = Cos;
        result.at(2, 0) = -Sin;
        result.at(0, 2) = Sin;
        
        return result;
    }
    
    template<typename Type>
    Matrix<Type, 4, 4> rotatez(const Type radians)
    {
        auto result = identity<Type, 4>();
        
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        result.at(0, 0) = Cos;
        result.at(1, 1) = Cos;
        result.at(1, 0) = Sin;
        result.at(0, 1) = -Sin;
        
        return result;
    }
    
    template<typename Type>
    Matrix<Type, 4, 4> rotate(Type radians, const Vector<Type, 3> &Axis)
    {
        Type Cos = std::cos(radians);
        Type Sin = std::sin(radians);
        
        Vector<Type, 3> U(Axis), V(normalize(Axis));
        
        auto MatS = exeng::zero<Type, 3, 3>();
        auto MatUut = exeng::zero<Type, 3, 3>();
        auto MatId = exeng::identity<Type, 3>();
        
        //Iniciar S
        MatS.at(0, 1) = -V.z;
        MatS.at(1, 0) = V.z;
    
        MatS.at(0, 2) = V.y;
        MatS.at(2, 0) = -V.y;
    
        MatS.at(1, 2) = -V.x;
        MatS.at(2, 1) = V.x;

        //Iniciar u*ut
        MatUut.at(0, 0) = V.x * V.x;
        MatUut.at(1, 0) = V.y * V.x;
        MatUut.at(2, 0) = V.z * V.x;
    
        MatUut.at(0, 1) = V.x * V.y;
        MatUut.at(1, 1) = V.y * V.y;
        MatUut.at(2, 1) = V.z * V.y;
        
        MatUut.at(0, 2) = V.x * V.z;
        MatUut.at(1, 2) = V.y * V.z;
        MatUut.at(2, 2) = V.z * V.z;
        
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
    Matrix<Type, 4, 4> lookat(const Vector<Type, 3> &Eye, const Vector<Type, 3> &At, const Vector<Type, 3> &Up)
    {
        auto forward = normalize(At - Eye);
        auto side = normalize(cross(forward, Up));
        auto up = cross(side, forward);
        
        auto result = identity<Type, 4>();

        result.at(0, 0) = side.x;
        result.at(0, 1) = side.y;
        result.at(0, 2) = side.z;
    
        result.at(1, 0) = up.x;
        result.at(1, 1) = up.y;
        result.at(1, 2) = up.z;
    
        result.at(2, 0) = -forward.x;
        result.at(2, 1) = -forward.y;
        result.at(2, 2) = -forward.z;
        
        result *= translate<Type>(-Eye);
        
        return result;
    }
    
    template<typename Type>
    Matrix<Type, 4, 4> perspective(Type fov, Type aspect, Type znear, Type zfar)
    {
        Type f = Type(1) / std::tan(fov / Type(2));
        Type zdiff = zfar - znear;
        
        auto result = identity<Type, 4>();
        
        result.at(0, 0) = f / aspect;
        result.at(1, 1) = f;
        result.at(2, 2) = (zfar + znear) / zdiff;
        result.at(3, 2) = Type(-1);
        result.at(2, 3) = (Type(2)*znear*zfar) / zdiff;
        
        return result;
    }
    
    //!Orthographic projection
    template<typename Type>
    Matrix<Type, 4, 4> ortho(const Boundary<Type, 3>& Volume)
    {
        Type left = Volume.GetSide(Side3::Left);
        Type right = Volume.GetSide(Side3::Right);
        
        Type bottom = Volume.GetSide(Side3::Bottom);
        Type top = Volume.GetSide(Side3::Top);

        Type near = Volume.GetSide(Side3::Near);
        Type far = Volume.GetSide(Side3::Far);
        
        auto result = identity<Type, 4>();
        
        result.at(0, 0) = Type(2) / ( right - left);
        result.at(1, 1) = Type(2) / ( top - bottom );
        result.at(2, 2) = Type(-2) / ( far - near  );
        result.at(3, 3) = Type(1);
        
        result.at(0, 3) = -( right + left ) / ( right - left );
        result.at(1, 3) = -( top + bottom ) / ( top - bottom );
        result.at(2, 3) = -( far + near ) / ( far - near );
        
        return result;
    }
    
    /**
     * @brief Compute the inverse matrix
     */
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> inverse(const Matrix<Type, RowCount, ColumnCount> &matrix, Type det)
    {
        static_assert(RowCount==ColumnCount, "Only square matrices are supported.");
        
        return transpose(adjoint(matrix)) / det;
    }
    
    template<typename Type, int RowCount, int ColumnCount>
    Matrix<Type, RowCount, ColumnCount> inverse(const Matrix<Type, RowCount, ColumnCount> &matrix)
    {
        static_assert(RowCount==ColumnCount, "Only square matrices are supported.");
        
        return transpose(adjoint(matrix)) / abs(matrix);
    }
    
    namespace __private 
    {
        template<typename Type, int Size>
        Vector<Type, Size> transform(const Matrix<Type, Size, Size> &matrix, const Vector<Type, Size> &vector) 
        {
            Vector<Type, Size> result;
    
            for(int i=0; i<Size; ++i) {
                result[i] = dot(matrix.getRowVector(i), vector);
            }
            
            return result;
        }
        
        template<typename Type, int Size>
        struct MatrixTranformation 
        {    
            static Vector<Type, Size> compute(const Matrix<Type, Size, Size> &matrix, const Vector<Type, Size> &vector) 
            {
                return exeng::__private::transform<Type, Size>(matrix, vector);   
            } 
            
            static Vector<Type, Size> compute(const Matrix<Type, Size, Size> &matrix, const Vector<Type, Size-1> &v) 
            {
                const Vector<Type, Size> vector = static_cast<Vector<Type, Size>>(v);
                
                return exeng::__private::transform<Type, Size>(matrix, vector);
            } 
        };
        
        template<typename Type>
        struct MatrixTranformation<Type, 4>
        {    
            static Vector<Type, 4> compute(const Matrix<Type, 4, 4> &matrix, const Vector<Type, 4> &vector) 
            {
                return exeng::__private::transform<Type, 4>(matrix, vector);   
            } 
            
            static Vector<Type, 4> compute(const Matrix<Type, 4, 4> &matrix, const Vector<Type, 3> &v) 
            {
                Vector<Type, 4> vector = static_cast<Vector<Type, 4>>(v);
                
                vector[3] = Type(1);
                
                return exeng::__private::transform<Type, 4>(matrix, vector);
            } 
        };
    }
    
    template<typename Type, int Size>
    Vector<Type, Size> transform(const Matrix<Type, Size, Size> &matrix, const Vector<Type, Size> &vector) 
    {
        return exeng::__private::MatrixTranformation<Type, Size>::compute(matrix, vector);
    }
    
    template<typename Type, int Size>
    Vector<Type, Size> transform(const Matrix<Type, Size, Size> &matrix, const Vector<Type, Size-1> &vector) 
    {
        return exeng::__private::MatrixTranformation<Type, Size>::compute(matrix, vector);
    }
    
	typedef Matrix<float, 3, 3> Matrix3f;
    typedef Matrix<double, 3, 3> Matrix3d;
    typedef Matrix<float, 4, 4> Matrix4f;
    typedef Matrix<double, 4, 4> Matrix4d;
}


#endif	//__EXENG_MATRIX_HPP__
