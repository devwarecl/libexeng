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

#include "VertexBufferFormat.hpp"

#include <cstring>
#include <cassert>
#include <stdexcept>

namespace exeng
{
    namespace graphics
    {
        VertexBufferFormat::VertexBufferFormat() : 
            coordCount      (0),
            colorStatus     (false),
            colorCount      (0),
            normals         (false),
            texUnitCount    (0)
            
        {
            ::memset(texCoordCount, 0, sizeof(texCoordCount));
        }


        int VertexBufferFormat::getCoordCount() const
        {
            return this->coordCount;
        }
        
        
        int VertexBufferFormat::getColorCount() const
        {
            return this->colorCount;
        }


        int VertexBufferFormat::getTexCoordCount(int Unit) const
        {
            assert( Unit < this->getTexUnitCount() );
            
            if (Unit < this->getTexUnitCount())
            {
                
            }
            
            return this->texCoordCount[Unit];
        }
        
        
        int VertexBufferFormat::getTexUnitCount() const
        {
            return this->texUnitCount;
        }


        bool VertexBufferFormat::getNormalStatus() const
        {
            return this->normals;
        }


        void VertexBufferFormat::setCoordCount( int Count )
        {
            assert(Count >= 2 && Count <= 4);
            
            this->coordCount = Count;
        }
        
        
        void VertexBufferFormat::setColorCount( int Count )
        {
            assert(Count >= 3 && Count <= 4);
            
            this->colorCount = Count;
        }
        
        
        void VertexBufferFormat::setTexCoordCount( int Unit, int Count )
        {
            assert(Count >= 2 && Count <= 4);
            assert(Unit  < this->getTexUnitCount());
            
            this->texCoordCount[Unit] = Count;
        }


        void VertexBufferFormat::setNormalStatus(bool Value)
        {
            this->normals = Value;
        }


        void VertexBufferFormat::setColorStatus(bool Value)
        {
            this->colorStatus = Value;
        }

        
        bool VertexBufferFormat::getColorStatus() const
        {
            return this->colorStatus;
        }


        int VertexBufferFormat::getStorageSize() const
        {
            int Result = 0;
            
            Result += 4 * this->getCoordCount();
            
            if (this->getColorStatus() == true)
                Result += 4 * this->getColorCount();
                
            if (this->getNormalStatus() == true)
                Result += 12;
            
			for(int i=0; i<this->getTexUnitCount(); ++i)
				Result += 4 * this->getTexCoordCount(i);
            
            return Result;
        }
    }
}
