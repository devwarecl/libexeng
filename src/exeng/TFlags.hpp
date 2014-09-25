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
	 * @brief Flags management
	 */
	template < typename _EnumType, typename _StorageType = int >
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
		StorageType value;
		
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
}

#include <exeng/TFlags.inl>

#endif	//__EXENG_TFLAGS_HPP__
