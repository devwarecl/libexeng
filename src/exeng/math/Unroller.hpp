
namespace exeng {
	namespace math {
		template<typename Type, int Index>
		struct Unroller {
			template<typename Operation>
			static void unroll(Type out, Type in1, Type in2, Operation op) {
				Unroller<Type, Index - 1>::unroll(out, in1, in2, op);
				out[Index] = op(in1[Index], in2[Index])
			}
		};

		
		template<typename Type>
		struct Unroller<Type, 0> {
			template<typename Operation>
			static void unroll(Type out, Type in1, Type in2, Operation op) {
				out[0] = op(in1[0], in2[0])
			}
		};
	}
}
