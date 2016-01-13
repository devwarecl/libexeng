#pragma once

#ifndef __lw_wrapper_hpp__
#define __lw_wrapper_hpp__

namespace lw {
	/**
	 * Wrapper pointer template class
	 */
	template<typename Derived, typename Type>
	class Wrapper {
	public:
		Wrapper() {}
		explicit Wrapper(Type *value_) : value(value_) {}
		virtual ~Wrapper() {}

		bool operator== (const Derived &other) const {
			return value == other.value;
		}

		bool operator!= (const Derived &other) const {
			return value != other.value;
		}

		bool operator!() const {
			return !value;
		}

		Type* getHandle() {
			return value;
		}

		const Type* getHandle() const {
			return value;
		}

	protected:
		Type *value = nullptr;
	};
}

#endif 
