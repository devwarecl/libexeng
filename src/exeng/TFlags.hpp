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
		
		TFlags(const TFlagsType& Other);

		TFlags(EnumType FlagDetail);
        
        TFlags(int value);

		TFlags<EnumType>& operator= (EnumType enumType);

		/**
         * @brief Habilita o deshabilita la flag indicada
		 */
		void setFlag(EnumType Flag, bool Status);

		/**
         * @brief Devuelve el estado actual de la flag indicada
		 */
		bool getFlag(EnumType Flag) const;
		
		/**
         * @brief Comprueba si los estados de dos contenedores de flags son exactamente los mismos
		 */
		bool operator== (const TFlags<EnumType>& Other) const;
        
		/**
         * @brief Comprueba si los estados de dos contenedores de flags son distintos
		 */
		bool operator!= (const TFlags<EnumType>& Other) const;
		
		/**
         * @brief Devuelve el valor actual contenido
		 */
		EnumType getValue() const;
		
		/**
         * @brief Establece el valor actual en el contenedor de flags.
		 */
		void setValue(EnumType Value);
        
        operator EnumType() const;
	};
}

#include <exeng/TFlags.inl>

#endif	//__EXENG_TFLAGS_HPP__
