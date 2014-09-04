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

#include <cassert>
#include <cstring>

namespace exeng { 
    /**
     * @brief Helper structure, used for compute the determinant of the current matrix.
     */
    template <typename Type, int Size>
    struct MatrixDeterminant
    {
        /**
         * @brief 
         */ 
        static Type Compute(const Matrix<Type, Size, Size>& other)
        {
            Matrix<Type, Size - 1, Size - 1> SubMatrix;
            Type Result = static_cast<Type>(0);
            Type SubMatrixDet;
            const int Row = 0;

            for(int Column=0; Column<Size; ++Column)
            {
                SubMatrix = other.getSubMatrix(Row, Column);

                if ((Column + 1)%2 == 0)
                    SubMatrixDet =  other(Row, Column) * MatrixDeterminant<Type, Size-1>::Compute(SubMatrix);
                else
                    SubMatrixDet = -other(Row, Column) * MatrixDeterminant<Type, Size-1>::Compute(SubMatrix);
            
                Result += SubMatrixDet;
            }
        
            return Result;
        }
    };


    template <typename Type>
    struct MatrixDeterminant<Type, 2>
    {
        static Type Compute( const Matrix<Type, 2, 2>& other )
        {
            return other(0, 0)*other(1, 1) - other(0, 1)*other(1, 0);
        }
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

    //!Computes the determinant
    template<typename Type, int RowCount, int ColumnCount>
    Type Matrix<Type, RowCount, ColumnCount>::getDeterminant() const
    {
        return MatrixDeterminant<Type, RowCount>::Compute(*this);
    }

    //!Compute the Matrix<Type, RowCount, ColumnCount> inverse.
    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::inverse()
    {
        this->inverse( this->getDeterminant() );
    }

    //!Compute the Matrix<Type, RowCount, ColumnCount> inverse with a previously computed determinant.
    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::inverse(Type Determinant)
    {
        Matrix<Type, RowCount, ColumnCount> Adjoint;
        Type Factor;
    
        for(int i=0; i<RowCount; ++i) {
            for(int j=0; j<ColumnCount; ++j) {
                if ((i + j) % 2 == 1) {
                    Factor = 1;
                } else {
                    Factor = -1;
                }
            
                Adjoint(i, j) = Factor * this->getSubMatrix(i, j).getDeterminant();
            }
        }

        *this = Adjoint;
        this->transpose();

        *this /= Determinant;
    }

    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::transpose() {
        int BaseColumn = 1;

        for(int i=0; i<RowCount - 1; ++i) {
            for(int j=BaseColumn; j<ColumnCount; ++j) {
                std::swap( this->at(i, j), this->at(j, i) );
            }

            ++BaseColumn;
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
    void Matrix<Type, RowCount, ColumnCount>::zero() {
        this->setup(static_cast<Type>(0));
    }

    //!Identity Matrix<Type, RowCount, ColumnCount>
    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::identity() {
        this->setup(static_cast<Type>(0));
    
        for(int i=0; i<RowCount; ++i) {
            this->at(i, i) = static_cast<Type>(1);
        }
    }

    //!Make a scaling Matrix<Type, RowCount, ColumnCount>
    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::scaling(const Vector<Type, RowCount> &scale)
    {
        this->setup(static_cast<Type>(0));

        for(int i=0; i<RowCount; ++i) {
            this->at(i, i) = scale[i];
        }
    }

    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::translation( const Vector<Type, 3> &RelPos)
    {
        this->at(0, 3) = RelPos.x;
        this->at(1, 3) = RelPos.y;
        this->at(2, 3) = RelPos.z;
    }

    //!Rotation Matrix<Type, RowCount, ColumnCount>(TODO)
    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::rotation(const Vector<Type, 3> &Axis, float Angle)
    {
        float Cos, Sin;

        Angle = toRad(Angle);

        Cos = std::cos(Angle);
        Sin = std::sin(Angle);

        if (Axis == Vector<Type, 3>(1.0f, 0.0f, 0.0f)) {
            this->at(1, 1) = Cos;
            this->at(2, 2) = Cos;
            this->at(2, 1) = -Sin;
            this->at(1, 2) = Sin;
        } else if (Axis == Vector<Type, 3>(0.0f, 1.0f, 0.0f)) {
            this->at(0, 0) = Cos;
            this->at(2, 2) = Cos;
            this->at(2, 0) = -Sin;
            this->at(0, 2) = Sin;
        } else if (Axis == Vector<Type, 3>(0.0f, 0.0f, 1.0f)) {
            this->at(0, 0) = Cos;
            this->at(1, 1) = Cos;
            this->at(1, 0) = Sin;
            this->at(0, 1) = -Sin;
        } else {
            Vector<Type, 3> U(Axis), V(Axis);
            Matrix<Type, 3, 3> MatS(static_cast<Type>(0)), MatUut(static_cast<Type>(0)), MatId(static_cast<Type>(0));
        
            V.normalize();

            //Iniciar S
            MatS.At(0, 1) = -V.z;
            MatS.At(1, 0) = V.z;
        
            MatS.At(0, 2) = V.y;
            MatS.At(2, 0) = -V.y;
        
            MatS.At(1, 2) = -V.x;
            MatS.At(2, 1) = V.x;

            //Iniciar u*ut
            MatUut.At(0, 0) = V.x * V.x;
            MatUut.At(1, 0) = V.y * V.x;
            MatUut.At(2, 0) = V.z * V.x;
        
            MatUut.At(0, 1) = V.x * V.y;
            MatUut.At(1, 1) = V.y * V.y;
            MatUut.At(2, 1) = V.z * V.y;

            MatUut.At(0, 2) = V.x * V.z;
            MatUut.At(1, 2) = V.y * V.z;
            MatUut.At(2, 2) = V.z * V.z;

            //Iniciar la matriz identidad
            MatId.Identity();

            //Calcular la matriz final
            this->identity();
            *this = MatUut + Cos * (MatId - MatUut) + Sin * MatS;
        }
    }


    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::perspective(Type Fov, Type Aspect, Type ZNear, Type ZFar)
    {
        Type f(static_cast<Type>(1)/ ::tan( toRad(0.5f*Fov) ));
        Type ZDiff(ZFar - ZNear);

        this->setup(static_cast<Type>(0));

        this->at(0, 0) = f / Aspect;
        this->at(1, 1) = f;
        this->at(2, 2) = (ZFar + ZNear)/ZDiff;
        this->at(3, 2) = -1.0f;
        this->at(2, 3) = (2.0f*ZNear*ZFar)/ZDiff;
    }

    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::lookAt(const Vector<Type, 3> &Eye, const Vector<Type, 3> &At, const Vector<Type, 3> &Up)
    {
        Vector<Type, 3> foward, side, up;
        Matrix<Type, RowCount, ColumnCount> transMat;

        up = Up;
        foward = At - Eye;

        foward.normalize();
        side = foward.cross(up);
        side.normalize();
        up = side.cross(foward);

        this->identity();

        this->at(0, 0) = side.x;
        this->at(0, 1) = side.y;
        this->at(0, 2) = side.z;
    
        this->at(1, 0) = up.x;
        this->at(1, 1) = up.y;
        this->at(1, 2) = up.z;
    
        this->at(2, 0) = -foward.x;
        this->at(2, 1) = -foward.y;
        this->at(2, 2) = -foward.z;
    
        transMat.identity();
        transMat.translation(-Eye);

        (*this) *= transMat;
    }

    //!TODO: Implement based on matrix multiplication
    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::yawPitchRoll(Type Yaw, Type Pitch, Type Roll)
    {
    
    }


    //!Orthographic projection
    template<typename Type, int RowCount, int ColumnCount>
    void Matrix<Type, RowCount, ColumnCount>::ortho(const Boundary<Type, 3>& Volume)
    {
        Type left, right;
        Type bottom, top;
        Type near, far;

        left = Volume.GetSide(Side3::Left);
        right = Volume.GetSide(Side3::Right);

        bottom = Volume.GetSide(Side3::Bottom);
        top = Volume.GetSide(Side3::Top);

        near = Volume.GetSide(Side3::Near);
        far = Volume.GetSide(Side3::Far);

        this->at(0, 0) = static_cast<Type>(2) / ( right - left);
        this->at(1, 1) = static_cast<Type>(2) / ( top - bottom );
        this->at(2, 2) = static_cast<Type>(-2) / ( far - near  );
        this->at(3, 3) = static_cast<Type>(1);

        this->at(0, 3) = -( right + left ) / ( right - left );
        this->at(1, 3) = -( top + bottom ) / ( top - bottom );
        this->at(2, 3) = -( far + near ) / ( far - near );
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
        return this->at(index);
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
            Result[i] = this->at(i) / other;
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

    template<typename Type, int RowCount, int ColumnCount>
    std::ostream& operator<< (std::ostream &os, const Matrix<Type, RowCount, ColumnCount>& Other) 
    {
        for(int i=0; i<RowCount; ++i) {
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
}
