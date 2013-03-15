
#ifndef __EXENG_OBJECT_HPP__
#define __EXENG_OBJECT_HPP__

#include <string>

#include "Config.hpp"
#include "DataTypes.hpp"
#include "TypeInfo.hpp"

namespace exeng
{
	/**
	 * @brief Clase base de la jerarquia de objetos del motor multimedia. Se utiliza una clase raiz para que los objetos
	 * creados dinamicamente por el engine tengan un comportamiento homogeneo con respecto a ciertas operaciones comunes. 
	 * Los objetos heredados son dinamicos y mutables.
	 */
	
	class EXENGAPI Object
	{
	public:
		virtual ~Object() = 0;
		
		/**
		 * @brief Devuelve una representacion del objeto como una cadena de texto
		 */
		virtual std::string	toString() const;
		
		/**
		 * @brief Clona un objeto, haciendolo totalmente independiente del objeto que lo origino.
		 * Debe ser reimplementado en clases derivadas.
		 */
		virtual Object* clone() const;

		/**
		 * @brief Compara dos objetos para comprobar si existe igualdad. Por defecto, comprueba los 
		 * RTTI de ambas referencias, y posteriormente, las referencias en si. 
		 * Es deseable que en clases derivadas se reimplemente apropiadamente.
		 */
		virtual bool equals(const Object &other) const;

		/**
		 * @brief Compara dos objetos para comprobar si uno de ellos es "menor" que el otro. 
		 * Este metodo es utilizado para incluir a los objetos el ordenamiento dentro de una coleccion. Por 
		 * defecto compara las direcciones de memoria de ambas referencias
		 */
		virtual bool lesserThan(const Object& other) const;

		/**
		 * @brief Copia todos los atributos del objeto externo.
		 * @param other El otro objeto a partir del cual copiar la informacion
		 */
		virtual void assign(const Object& other);

		/**
		 * @brief Operador de igualdad entre referencias
		 */
		bool operator == (const Object& other) const;

		/**
		 * @brief Operador de desigualdad entre referencias
		 */
		bool operator != (const Object& other) const;

		/**
		 * @brief Operador de "menor que"
		 */
		bool operator < (const Object& other) const;

		/**
		 * @brief Operador de "mayor que"
		 */
		bool operator > (const Object& other) const;

		/**
		 * @brief Operador de "menor o igual que"
		 */
		bool operator <= (const Object& other) const;

		/**
		 * @brief Operador de "mayor o igual que"
		 */
		bool operator >= (const Object& other) const;

		/**
		 * @brief Operador de asignacion
		 */
		Object& operator= (const Object& other);

		/**
		 * @brief Devuelve el identificador de tipo del objeto.
		 */
		virtual TypeInfo getTypeInfo() const;
	};
}

#endif	//__EXENG_OBJECT_HPP__
