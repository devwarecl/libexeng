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

namespace exeng {
	template< typename _EnumType, typename _StorageType>
	TFlags<_EnumType, _StorageType>::TFlags() : value(StorageType()) { }
	
    
	template< typename _EnumType, typename _StorageType>
	TFlags<_EnumType, _StorageType>::TFlags(const TFlagsType& Other) : value(Other.value) { }

    
	template< typename _EnumType, typename _StorageType>
	TFlags<_EnumType, _StorageType>::TFlags(_EnumType FlagDetail) : value(FlagDetail) { }
	
    template< typename _EnumType, typename _StorageType>
    TFlags<_EnumType, _StorageType>::TFlags(int value) {
        this->value = value;
    }
    

	template< typename _EnumType, typename _StorageType>
	TFlags<_EnumType>& TFlags<_EnumType, _StorageType>::operator= (_EnumType enumType) {
		this->value = enumType;
	}


	template< typename _EnumType, typename _StorageType>
	void TFlags<_EnumType, _StorageType>::setFlag(_EnumType Flag, bool Status) {
		bool flagStatus = this->getFlag(Flag);

		if (flagStatus == false && Status == true) {
			this->value |= Flag;
        }
		else if (flagStatus == true && Status == false) {
			this->value ^= Flag;
        }
	}

		
	template< typename _EnumType, typename _StorageType>
	bool TFlags<_EnumType, _StorageType>::getFlag(_EnumType Flag) const {
		return this->value&Flag ? true : false;
	}

		
	template< typename _EnumType, typename _StorageType>
	bool TFlags<_EnumType, _StorageType>::operator== (const TFlags<_EnumType>& Other) const {
		return this->value == Other.value;
	}

		
	template< typename _EnumType, typename _StorageType>
	bool TFlags<_EnumType, _StorageType>::operator!= (const TFlags<_EnumType>& Other) const {
		return this->value != Other.value;
	}
		
		
	template< typename _EnumType, typename _StorageType>
	_EnumType TFlags<_EnumType, _StorageType>::getValue() const {
		return this->value;
	}
		
		
	template< typename _EnumType, typename _StorageType>
	void TFlags<_EnumType, _StorageType>::setValue(_EnumType Value) {
		this->value = Value;
	}
    
    template< typename _EnumType, typename _StorageType>
    TFlags<_EnumType, _StorageType>::operator EnumType() const {
        return static_cast<EnumType>(this->value);
    }
}
