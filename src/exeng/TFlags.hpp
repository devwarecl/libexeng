/**
 * @file TFlags.hpp
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_TFLAGS_HPP__
#define __EXENG_TFLAGS_HPP__

#include <cstdint>

namespace exeng {

	/**
	 * @brief Flag management class.
	 */
	template <typename _EnumType, typename _StorageType = int>
	class TFlags {
	public:
		// Definir alias para posibilitar el uso en un ambiente de 
		// programacion de plantillas
		typedef _EnumType EnumType;
		typedef _StorageType StorageType;

	private:
		// Definir un alias para hacer que la interfaz plublica sea facil de entender
		typedef TFlags<_EnumType, _StorageType> TFlagsType;

	private:
		/**
         * @brief Almacenamiento interno de las flags
		 */
		StorageType value = StorageType(0);
		
	public:
		TFlags();
		TFlags(EnumType FlagDetail);
        TFlags(int value);

		void activate(EnumType Flag, bool Status);
		bool isActivated(EnumType Flag) const;

		bool operator== (const TFlags<EnumType>& Other) const;
		bool operator!= (const TFlags<EnumType>& Other) const;
		
        operator EnumType() const;
	};

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

#endif	//__EXENG_TFLAGS_HPP__
