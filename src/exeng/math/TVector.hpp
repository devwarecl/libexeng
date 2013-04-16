/**
 * @brief PENDIENTE
 */

#ifndef __EXENG_MATH_TVECTOR_HPP__
#define __EXENG_MATH_TVECTOR_HPP__

#include <iosfwd>
#include "Common.hpp"

namespace exeng {
    namespace math {
		template<typename Type, int size>
		struct TVectorBase {
			Type data[size];
		};


		template<typename Type> 
		struct TVectorBase<Type, 2> {
			union {
				Type data[2];
				struct { Type x, y; };
			};

			void set(Type x, Type y) {
				this->x = x;
				this->y = y;
			}
		};


		template<typename Type> 
		struct TVectorBase<Type, 3> {
			union {
				Type data[3];
				struct { Type x, y, z; };
			};


			void set(Type x, Type y, Type z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}
		};


		template<typename Type> 
		struct TVectorBase<Type, 4> {
			union {
				Type data[4];
				struct { Type x, y, z, w; };
			};


			void set(Type x, Type y, Type z, Type w) {
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}
		};


        /**
         * @brief Base vector class
         */
        template<typename Type, int Size>
        class TVector : public TVectorBase<Type, Size> {
        private:
            typedef TVector<Type, Size> Vector;

        public:
			using TVectorBase<Type, Size>::set;


            /**
             * @brief PENDIENTE
             */
            TVector();

            /**
             * @brief PENDIENTE
             */
            explicit TVector(const Type *Array);

            /**
             * @brief PENDIENTE
             */
            explicit TVector(Type Value);

            /**
             * @brief PENDIENTE
             */
            TVector(Type x, Type y);

            /**
             * @brief PENDIENTE
             */
            TVector(Type x, Type y, Type z);

            /**
             * @brief PENDIENTE
             */
            TVector(Type x, Type y, Type z, Type w);

            /**
             * @brief PENDIENTE
             */
            void set(const Type *Values);

            /**
             * @brief PENDIENTE
             */
            void set(Type Value);

            /**
             * @brief Devuelve la magnitud del vector elevada al cuadrado
             */
            Type getMagnitudeSq() const;

            /**
             * @brief Devuelve la magnitud del vector
             */
            Type getMagnitude() const;
            
            /**
             * @brief Normalize the vector.
             */
            void normalize();
            
            /**
             * @brief Establece la magnitud del vector
             */
            void setMagnitude(Type Magnitude);

            /**
             * @brief Get vector internal data pointer
             */
            Type* getPtr();

            /**
             * @brief Get vector internal data pointer
             */
            const Type* getPtr() const;
            
            /**
             * @brief Array like member access
             */
            Type& operator[] (int Index);

            /**
             * @brief Array like member access (const)
             */
            const Type& operator[] (int Index) const;

            /**
             * @brief Suma dos vectores
             */
            Vector operator+ (const Vector &Other) const;

            /**
             * @brief Suma dos vectores
             */
            Vector &operator+= (const Vector &Other);

            /**
             * @brief Resta dos vectores
             */
            Vector operator- (const Vector &Other) const;
            
            /**
             * @brief PENDIENTE
             */
            Vector &operator-= (const Vector &Other);

            /**
             * @brief Escala un vector
             */
            Vector operator* (Type Number) const;

            /**
             * @brief Escala un vector
             */
            template<typename OtherType>
            friend TVector<OtherType, Size> operator* (Type Number, const Vector& Other) {
                return Other*Number;
            }
            
            /**
             * @brief Escala un vector
             */
            Vector &operator*= (Type Number);

            /**
             * @brief Divide un vector por un numero
             */
            Vector operator/ (Type Number) const;
            
            /**
             * @brief Divide un vector por un numero
             */
            Vector &operator/= (Type Number);

            /**
             * @brief Escala un vector por otro vector
             */
            Vector operator* (const Vector &Other) const;

            /**
             * @brief Escala un vector por otro vector
             */
            Vector &operator*= (const Vector &Other);

            /**
             * @brief Divide un vector por otro vector
             */
            Vector operator/ (const Vector &Other) const;
        
            /**
             * @brief Divide un vector por otro vector
             */
            Vector &operator/= (const Vector &Other);

            /**
             * @brief Devuelve el vector negativo
             */
            Vector operator- () const;

            /**
             * @brief Operador de igualdad
             */
            bool operator == (const Vector &Other) const;

            /**
             * @brief Operador de desigualdad
             */
            bool operator != (const Vector &Other) const;

            /**
             * @brief Ve si un vector es mayor que otro vector
             */
            bool operator > (const Vector &Other) const;
            
            /**
             * @brief Ve si un vector es menor que otro vector
             */
            bool operator < (const Vector &Other) const;
            
            /**
             * @brief Ve si un vector es mayor o igual que otro vector
             */
            bool operator >= (const Vector &Other) const;
            
            /**
             * @brief Ve si un vector es menor o igual que otro vector
             */
            bool operator <= (const Vector &Other) const;


            /**
             * @brief PENDIENTE
             */
            friend TVector<Type, Size> operator* (Type scalar, const TVector<Type, Size>& other) {
                return other * scalar;
            }
            
            
            /**
             * @brief Convierte de un tipo de vector a otro
             */
            template<typename OtherType, int OtherSize>
            operator TVector<OtherType, OtherSize>() const {
                TVector<OtherType, OtherSize> Result;
                int MinSize, MaxSize;

                if (OtherSize > Size) {
                    MaxSize = OtherSize;
                    MinSize = Size;
                } else {
                    MaxSize = Size;
                    MinSize = OtherSize;
                }

                Result.set(static_cast<OtherType>(0));

				for(int i=0; i<MinSize; ++i) {
                    Result[i] = static_cast<OtherType>( this->data[i] );
				}
                
                return Result;
            }
            
        public:
            
            /**
             * @brief Calcula el producto punto entre dos vectores.
             * Este valor es representativo del coseno entre los dos vectores.
             */
            Type dot(const Vector &other) const;

            /**
             * @brief Calcula el producto cruz entre dos vectores
             */
            Vector cross(const Vector &other) const;

            /**
             * @brief Maximiza un vector
             */
            Vector maximize(const Vector &other) const;
            
            /**
             * @brief Minimiza un vector
             */
            Vector minimize(const Vector &other) const;
            

            /**
             * @brief Calcula la proyeccion vectorial del vector B sobre el vector A
             */
            Vector proj(const Vector &other) const;
            
            /**
             * @brief Calcula el componente escalar del vector B sobre el vector A
             */
            Type comp(const Vector &other) const;

			
            /**
             * @brief Interpolacion lineal
             */
            static Vector lerp(const Vector& V1, const Vector& V2, Type S);

            /**
             * @brief Interpolacion cubica
             */
            static Vector hermite(const Vector& V1, const Vector& T1, const Vector& V2, const Vector& T2, Type S);
            
            /**
             * @brief Comprueba si dos vectores son iguales. Solo tiene sentido si el vector esta basado
             * en un tipo de datos de ṕunto flotante.
             */
            bool equals(Vector &other, Type epsilon=Type()) const;
            
            
            /**
             * @brief Comprueba si el vector actual corresponde al vector zero.
             */
            bool isZero() const;
            
            /**
             * @brief Regresa el vector zero
             */
            static Vector zero();
        };
        
        
        typedef TVector<float, 2> Vector2f;
        typedef TVector<float, 3> Vector3f;
        typedef TVector<float, 4> Vector4f;
        
        typedef TVector<double, 2> Vector2d;
        typedef TVector<double, 3> Vector3d;
        typedef TVector<double, 4> Vector4d;
        
        typedef TVector<int, 2> Vector2i;
        typedef TVector<int, 3> Vector3i;
        typedef TVector<int, 4> Vector4i;
    }
}

template<typename Type, int Size>
std::ostream& operator<< (std::ostream &os, const exeng::math::TVector<Type, Size>& Vector);

#include "TVector.inl"

#endif	//__EXENG_MATH_TVECTOR_HPP__
