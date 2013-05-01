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

#include <cmath>
#include <algorithm>

namespace exeng
{
    namespace math
    {
        template<typename VectorType, int size>
        VectorType& add(VectorType& out, const VectorType& vparam1, const VectorType& vparam2)
        {
            return add<VectorType>(out, vparam1, vparam2, size);
        }
        
        
        template<typename VectorType>
        VectorType& add(VectorType& out, const VectorType& vparam1, const VectorType& vparam2, int size)
        {
            for (int i=0; i<size; ++i)
                out[i] = vparam1[i] + vparam2[i];
            
            return out;
        }
        
     
        template<typename VectorType, int size>
        VectorType& sub(VectorType& out, const VectorType& vparam1, const VectorType& vparam2)
        {
            return sub<VectorType>(out, vparam1, vparam2, size);
        }
        
        
        template<typename VectorType>
        VectorType& sub(VectorType& out, const VectorType& vparam1, const VectorType& vparam2, int size)
        {
            for (int i=0; i<size; ++i)
                out[i] = vparam1[i] - vparam2[i];
            
            return out;
        }
        
        
        template<typename VectorType, int size>
        VectorType& mul(VectorType& out, const VectorType& vparam1, const VectorType& vparam2)
        {
            return mul<VectorType>(out, vparam1, vparam2, size);
        }
        
        
        template<typename VectorType>
        VectorType& mul(VectorType& out, const VectorType& vparam1, const VectorType& vparam2, int size)
        {
            for (int i=0; i<size; ++i)
                out[i] = vparam1[i] * vparam2[i];
            
            return out;
        }
        
        
        template<typename VectorType, typename ValueType, int size>
        VectorType& mul(VectorType &out, const VectorType &vparam, ValueType scalar)
        {
            return mul<VectorType, ValueType>(out, vparam, scalar, size);
        }
        
        
        template<typename VectorType, typename ValueType>
        VectorType& mul(VectorType &out, const VectorType &vparam, ValueType scalar, int size)
        {
            for (int i=0; i<size; ++i)
                out[i] = vparam[i] * scalar;
            
            return out;
        }
        
        
        template<typename VectorType, int size>
        VectorType& div(VectorType& out, const VectorType& vparam1, const VectorType& vparam2)
        {
            return div(out, vparam1, vparam2, size);
        }
        
        
        template<typename VectorType>
        VectorType& div(VectorType& out, const VectorType& vparam1, const VectorType& vparam2, int size)
        {
            for (int i=0; i<size; ++i)
                out[i] = vparam1[i] * vparam2[i];
            
            return out;
        }
        
        
        template<typename VectorType, int Size, typename ValueType>
        VectorType& div(VectorType &out, const VectorType &vparam, ValueType scale)
        {
            return div<VectorType, ValueType>(out, vparam, scale, size);
        }
        
        
        template<typename VectorType, typename ValueType>
        VectorType& div(VectorType &out, const VectorType &vparam, ValueType scale, int size)
        {   
            for (int i=0; i<size; ++i)
                out[i] = vparam[i] * scale;
            
            return out;
        }
        
        
        template<typename VectorType, int size>
        VectorType& neg(VectorType& out, const VectorType& vparam)
        {   
            return neg<VectorType>(out, vparam, size);
        }
        
        
        template<typename VectorType>
        VectorType& neg(VectorType& out, const VectorType& vparam, int size)
        {
            for(int i=0; i<size; ++i)
            {
                out[i] = -vparam[i];
            }
            
            return out;
        }
        
        
        template<typename VectorType, int size, typename ValueType>
        ValueType dot(const VectorType& vparam1, const VectorType& vparam2)
        {
            return dot<VectorType, ValueType>(vparam1, vparam2, size);
        }
        
        
        template<typename VectorType, typename ValueType>
        ValueType dot(const VectorType& vparam1, const VectorType& vparam2, int size)
        {
            ValueType result = static_cast<ValueType>(0);
            
            for (int i=0; i<size; ++i)
                result += vparam1[i]*vparam2[i];
            
            return result;
        }
        
        
        template<typename VectorType, int size, typename ValueType>
        ValueType mag2(const VectorType& vparam)
        {
            return dot<VectorType, size, ValueType>(vparam, vparam);
        }
        
        
        template<typename VectorType, typename ValueType>
        ValueType mag2(const VectorType& vparam, int size)
        {
            return dot<VectorType, ValueType>(vparam, vparam, size);
        }

        
        template<typename VectorType, int size, typename ValueType>
        ValueType mag(const VectorType& vparam)
        {
            return std::sqrt( mag2<VectorType, ValueType, size>(vparam) );
        }
        
        
        template<typename VectorType, typename ValueType>
        ValueType mag(const VectorType& vparam, int size)
        {
            return std::sqrt( mag2<VectorType, ValueType>(vparam, size) );
        }
        
        
        template<typename VectorType, int size>
        VectorType& maximize(VectorType& out, const VectorType& vparam1, const VectorType& vparam2)
        {
            return maximize<VectorType>(out, vparam1, vparam2, size);
        }
        
        
        template<typename VectorType>
        VectorType& maximize(VectorType& out, const VectorType& vparam1, const VectorType& vparam2, int size)
        {
            for (int i=0; i<size; ++i)
            {
                out[i] = std::max(vparam1[i], vparam2[i]);
            }
            
            return out;
        }
        
        
        template<typename VectorType, int size>
        VectorType& minimize(VectorType& out, const VectorType& vparam1, const VectorType& vparam2)
        {
            return minimize<VectorType>(out, vparam1, vparam2, size);
        }

        
        template<typename VectorType>
        VectorType& minimize(VectorType& out, const VectorType& vparam1, const VectorType& vparam2, int size)
        {
            for (int i=0; i<size; ++i)
            {
                out[i] = std::min(vparam1[i], vparam2[i]);
            }
            
            return out;
        }
    }
}
