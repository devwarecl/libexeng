/**
 * @brief Contiene funciones de plantilla varias para operar con secuencias de valores
 * 
 * Salvo algunas excepciones, todas las funciones devuelven en su primer
 * parametro el resultado de la operacion
 * 
 */

#ifndef __EXENG_MATH_OPERATIONS_HPP__
#define __EXENG_MATH_OPERATIONS_HPP__

#define EXENG_DECLARE_BIN_OP(Name, Op)	\
template<typename Type>					\
struct Name {                           \
	static Type eval(Type v1, Type v2) { \
		return v1 Op v2;                \
	}                                   \
}


#define EXENG_DECLARE_ASSIGN_BIN_OP(Name, Op)	\
template<typename Type>							\
struct Name {									\
	static Type& eval(Type &v1, Type v2) {		\
		return v1 Op v2;						\
	}									\
}


#define EXENG_DECLARE_COMPARE_OP(Name, Op)	\
template<typename Type>						\
struct Name {								\
	static bool eval(Type v1, Type v2) {	\
		return v1 Op v2;					\
	}										\
}

namespace exeng {
    namespace math {
		namespace BinaryOperators {
			EXENG_DECLARE_BIN_OP(Add, +);
			EXENG_DECLARE_BIN_OP(Sub, -);
			EXENG_DECLARE_BIN_OP(Mul, *);
			EXENG_DECLARE_BIN_OP(Div, /);

			EXENG_DECLARE_ASSIGN_BIN_OP(AddAssign, +=);
			EXENG_DECLARE_ASSIGN_BIN_OP(SubAssign, -=);
			EXENG_DECLARE_ASSIGN_BIN_OP(MulAssign, *=);
			EXENG_DECLARE_ASSIGN_BIN_OP(DivAssign, /=);
		}

		
		template<typename SequenceType>
		struct SequenceTypeTraits {
        };
        
        
		/**
		 *	@brief Aplica una operacion
		 */
		template< typename _SequenceTypeTraits, int Index=_SequenceTypeTraits::Dimension-1 >
		struct Unroller {
            
            typedef typename _SequenceTypeTraits::SequenceType      Sequence;
            typedef typename _SequenceTypeTraits::SequenceValueType Type;
            typedef Unroller<_SequenceTypeTraits, Index - 1>        PrevUnroller;
            
            
			template< template<typename T> class BinaryOperator >
			static void unroll(Sequence &out, const Sequence &arr1, const Sequence &arr2) {
                PrevUnroller::unroll< BinaryOperator >(out, arr1, arr2);
                out[Index] = BinaryOperator<Type>::eval(arr1[Index], arr2[Index]);
			}
			
			
			template< template<typename T> class AssignBinaryOperator >
			static void unrollAssign(Sequence &out, const Sequence &arr) {
                
				PrevUnroller::unrollAssign < AssignBinaryOperator >(out, arr);
                AssignBinaryOperator<Type>::eval(out[Index], arr[Index]);
			}


			template< template<typename T> class BinaryOperator >
			static void unrollScalar(Sequence &out, const Sequence &arr, Type scalar) {
                
                PrevUnroller::unrollScalar<BinaryOperator>(out, arr, scalar);
                out[Index] = BinaryOperator<Type>::eval(arr[Index], scalar);
			}
		};


		template<typename _SequenceTypeTraits>
		struct Unroller<_SequenceTypeTraits, 0> {
            
            typedef typename _SequenceTypeTraits::SequenceType      Sequence;
            typedef typename _SequenceTypeTraits::SequenceValueType Type;
            
			template< template<typename> class BinaryOperator >
			static void unroll(Sequence &out, const Sequence &arr1, const Sequence &arr2) {
                out[0] = BinaryOperator<Type>::eval(arr1[0], arr2[0]);
			}


			template< template<typename> class AssignBinaryOperator >
			static void unrollAssign(Sequence &out, const Sequence &arr) {
                AssignBinaryOperator<Type>::eval(out[0], arr[0]);
			}
			
			
			template< template<typename> class BinaryOperator >
            static void unrollAssign(Sequence &out, const Sequence &arr, Type scalar) {
                out[0] = BinaryOperator<Type>::eval(arr[0], scalar);
            }
		};
    }
}

#endif // __EXENG_MATH_OPERATIONS_HPP__
