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
	TFlags<_EnumType, _StorageType>::TFlags(_EnumType FlagDetail) : value(FlagDetail) { }
	
    template< typename _EnumType, typename _StorageType>
    TFlags<_EnumType, _StorageType>::TFlags(int value) {
        this->value = value;
    }

	template< typename _EnumType, typename _StorageType>
	void TFlags<_EnumType, _StorageType>::activate(_EnumType Flag, bool Status) {
		bool flagStatus = this->isActivated(Flag);

		if (flagStatus == false && Status == true) {
			this->value |= Flag;
        }
		else if (flagStatus == true && Status == false) {
			this->value ^= Flag;
        }
	}
	
	template< typename _EnumType, typename _StorageType>
	bool TFlags<_EnumType, _StorageType>::isActivated(_EnumType Flag) const {
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
    TFlags<_EnumType, _StorageType>::operator EnumType() const {
        return static_cast<EnumType>(this->value);
    }
}
