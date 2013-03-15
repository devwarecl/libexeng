
#include "Version.hpp"

namespace exeng
{
    void Version::setup(int Major, int Minor, int Revision, int Build)
    {
        this->setMajor(Major);
        this->setMinor(Minor);
        this->setRevision(Revision);
        this->setBuild(Build);
    }
    
    
    bool Version::operator!= (const Version &Other) const
    {
        return ! (*this == Other);
    }
    
    
    bool Version::operator== (const Version &Other) const
    {
        if ( this->getMajor() != Other.getMajor() )		
			return false;

        if ( this->getMinor() != Other.getMinor() )	
			return false;

        if ( this->getRevision() != Other.getRevision() ) 
			return false;

        if ( this->getBuild() != Other.getBuild() )  
			return false;
        
        return true;
    }

    
    bool Version::operator>= (const Version &Other) const
    {
		return *this == Other || *this > Other;
    }
    
    
    bool Version::operator<= (const Version &Other) const
    {
        return *this == Other || *this < Other;
    }

    
    bool Version::operator> (const Version &Other) const
    {
		if (this->_major > Other._major)
			return true;

		if (this->_minor > Other._minor)
			return true;

		if (this->revision > Other.revision)
			return true;

        return false;
    }
    
    
    bool Version::operator<  (const Version &Other) const
    {
		if (this->_major < Other._major)
			return true;

		if (this->_minor < Other._minor)
			return true;

		if (this->revision < Other.revision)
			return true;

        return false;
    }
}
