/**
 *	@brief Define la clase Array, y sus politicas de almacenamiento asociadas.
 */


#ifndef __EXENG_TARRAY_HPP__
#define __EXENG_TARRAY_HPP__

#include <cstring>

namespace exeng {
	/**
	 * @brief Implementa las clases de politicas de almacenamiento para la plantilla Array
	 */
	namespace StoragePolicies {

		/**
		 *	@brief Politica de almacenamiento estatico. 
		 *	@tparam _Type El tipo de datos a almacenar.
		 *	@tparam _Size La cantidad de elementos.
		 */
		template<typename _Type, int _Size>
		class Static {
		public:
			typedef _Type Type;
			const int size = _Size;

			Type data[size];
		};


		/**
		 *	@brief Politica de almacenamiento dinamico.
		 *	@tparam _Type El tipo de datos a almacenar.
		 *	@tparam _Size No usado. Solo esta puesto para cumplir con la firma de la clase de plantilla
		 */
		template<typename _Type, int _Size>
		class Dynamic {
		public:
			typedef Dynamic<typename _Type, int _Size> DynamicPolicy;

			typedef _Type Type;

			Type *data;
			int size;
			
			Dynamic() {
				this->data = nullptr;
				this->size = 0;
			}


			Dynamic(const DynamicPolicy &other) {
				*this = other;
			}


			virtual ~Dynamic() {
				this->free();
			}


			DynamicPolicy& operator= (const DynamicPolicy &other) {
				this->resize(other.size);
				std::memcpy(this->data, other.data, other.size);
			}

			/**
			 * @brief Cambia el tamaño del arreglo. Los elementos actualmente almacenados se eliminan.
			 */
			void resize(int size) {
				this->free();

				this->data = new Type[size];
				this->size = size;
			}


			/**
			 * @brief Libera el espacio utilizado por el arreglo dinamico.
			 */
			void free() {
				if (this->data != nullptr) {
					delete[] this->data;

					this->data = nullptr;
					this->size = 0;
				}
			};
		};
	}


	/**
	 * @brief Clase de arreglo
	 *
	 */
	template
	<
		typename Type,
		int Size,
		template<typename _Type, int _Size> StoragePolicy
	>
	class TArray : public StoragePolicy<_Type, _Size>  {
	public:
		TArray();
	};
}

#endif //__EXENG_ARRAY_HPP__
