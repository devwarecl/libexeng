
#ifndef __EXENG_MATH_TQUATERNION_HPP__
#define __EXENG_MATH_TQUATERNION_HPP__

#include "TVector.hpp"

namespace exeng {
    namespace math {
        
        template<typename Type>
        class TQuaternion {
            typedef TQuaternion<Type> Quaternion;
            typedef TVector<Type, 3> Vector3;
            typedef TVector<Type, 4> Vector4;
            
        public:
            /**
             * @brief Constructor por defecto.
             * 
             * Inicializa a un cuaternion cero.
             */
            TQuaternion();
            
            /**
             * @brief Constructor copia.
             */
            TQuaternion(const Quaternion &other);
            
            /**
             * @brief Inicializa el cuaternion a partir de un eje de rotacion, y el elemento w
             */
            TQuaternion(const Vector3& V, Type W);
            
            /**
             * @brief Inicializa el cuaternion a partir de un eje de rotacion, y el elemento w, 
             * como valores independientes.
             */
            TQuaternion(Type X, Type Y, Type Z, Type W);
            
            /**
             * @brief Constructor que toma sus valores desde el arreglo bruto indicado.
             */
            explicit TQuaternion(const Type* values);
            
            /**
             * @brief Convierte el cuaternion a una representacion basada en el eje y angulo de rotacion.
             */
            Vector4 getAxisAngle() const;
            
            /**
             * @brief Calcula la inversa del cuaternion actual.
             */
            Quaternion getInversed() const;
            
            /**
             * @brief Calcula el conjugado del cuaternion actual
             */
            Quaternion getConjugated() const;
            
            /**
             * @brief Calcula el cuaternion normalizado del cuaternion actual.
             */
            Quaternion getNormalized() const;
            
            /**
             * @brief Normaliza el cuaternion actual.
             */
            void normalize();
            
            /**
             * @brief Calcula el cuaternion actual.
             */
            void inverse();
            
            /**
             * @brief Conjuga el cuaternion actual.
             */
            void conjugate();
            
            /**
             * @brief Comprueba si el cuaternion actual corresponde al cuaternion zero.
             */
            bool isZero() const;
            
            /**
             * @brief Comprueba si el cuaternion actual corresponde al cuaternion identidad.
             */
            bool isIdentity() const;
            
            /**
             * @brief Devuelve la magnitud de un cuaternion, elevada al cuadrado.
             */
            Type getMagnitude2() const;
            
            /**
             * @brief Devuelve la magnitud de un cuaternion.
             */
            Type getMagnitude() const;
            
            /**
             * @brief Aplica el signo + al cuaternion.
             */
            Quaternion operator+() const;
            
            /**
             * @brief Negativiza el cuaternion actual.
             */
            Quaternion operator-() const;
            
            /**
             * @brief Suma dos cuaterniones
             */
            Quaternion operator+(const Quaternion &other) const;
            
            /**
             * @brief Resta dos cuaterniones
             */
            Quaternion operator-(const Quaternion &other) const;
            
            /**
             * @brief Multiplica un cuaternion por otro.
             */
            Quaternion operator*(const Quaternion &other) const;
            
            /**
             * @brief Divide un cuaternion por otro.
             */
            Quaternion operator/(const Quaternion &other) const;
            
            /**
             * @brief Escala un cuaternion.
             */
            Quaternion operator*(Type scalar) const;
            
            /**
             * @brief Divide un cuaternion por un escalar.
             */
            Quaternion operator/(Type scalar) const;
            
            /**
             * @brief Suma dos cuaterniones.
             */
            Quaternion& operator+=(const Quaternion &other);
            
            /**
             * @brief Resta dos cuaterniones.
             */
            Quaternion& operator-=(const Quaternion &other);
            
            /**
             * @brief Multiplica dos cuaterniones.
             */
            Quaternion& operator*=(const Quaternion &other);
            
            /**
             * @brief Divide dos cuaterniones.
             */
            Quaternion& operator/=(const Quaternion &other);
            
            /**
             * @brief Multiplica un cuaternion por un escalar.
             */
            Quaternion& operator*=(Type scalar);
            
            /**
             * @brief Divide un cuaternion por un escalar.
             */
            Quaternion& operator/=(Type scalar);

            /**
             * @brief Comprueba si dos cuaterniones son iguales
             */
            bool operator== (const Quaternion &other) const;
            
            /**
             * @brief Comprueba si dos cuaterniones son distintas.
             */
            bool operator!= (const Quaternion &other) const;
            
            /**
             * @brief Comprueba si un cuaternion es 'menor' que otro cuaternion
             */
            bool operator< (const Quaternion &other) const;
            
            /**
             * @brief Comprueba si un cuaternion es 'mayor' que otra cuaternion
             */
            bool operator> (const Quaternion &other) const;
            
            /**
             * @brief Comprueba si un cuaternion es 'menor' o igual que otra cuaternion
             */
            bool operator<= (const Quaternion &other) const;
            
            /**
             * @brief Comprueba si un cuaternion es 'mayor' o igual que otra cuaternion
             */
            bool operator>= (const Quaternion &other) const;
        
        public:
            /**
             * @brief Devuelve el cuaternion cero.
             */
            static Quaternion zero();
            
            /**
             * @brief Devuelve el cuaternion identidad.
             */
            static Quaternion identity();
            
        public:
            /**
             * @brief Parte imaginaria del cuaternion
             */
            TVector<Type, 3> v;
            
            /**
             * @brief Parte real del cuaternion
             */
            Type w;
        };

        /**
         * @brief Cuaternion de tipo 'float'
         */
        typedef TQuaternion<float> Quaternionf;
        
        /**
         * @brief Cuaternion de tipo 'double'
         */
        typedef TQuaternion<double> Quaterniond;
    }
}


#include "TQuaternion.inl"

#endif  //__EXENG_MATH_TQUATERNION_HPP__
