
#pragma once

#ifndef __lw_pointer_hpp__
#define __lw_pointer_hpp__

namespace lw {
	template<typename Type>
	class Pointer {
	public:
		typedef Type type;

	public:
		Pointer() {}
		explicit Pointer(Type *value_) : value(value_) {}

		Type* operator->() {return value;}
		const Type* operator->() const {return value;}

		Type& operator*() {return *value;}
		const Type& operator*() const {return *value;}

		operator Type*() {return value;}
		operator const Type*() const {return value;}

		bool operator== (const Pointer<Type> &other) const {
			return value == other.value;
		}

		bool operator!= (const Pointer<Type> &other) const {
			return value != other.value;
		}

	protected:
		Type *value = nullptr;
	};
}

#endif
