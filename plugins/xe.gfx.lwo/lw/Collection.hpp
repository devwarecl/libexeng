#pragma once

#ifndef __lw_collection_hpp__
#define __lw_collection_hpp__

#include "Wrapper.hpp"

namespace lw {
	
	template<typename Derived, typename Type>
	class Collection : public Wrapper<Derived, Type> {
	public:
		template<typename Derived, typename Type>
		class Iterator {
		public:
			Iterator() : value(nullptr) {}
			explicit Iterator(Type *value_) : value(value_), wrapped(value_) {}

			// pre increment
			Iterator operator++(int) {
				assert(this->value);

				this->value = this->value->next;
				this->wrapped = Derived(this->value);

				return Iterator(this->value);
			}

			// post increment
			Iterator operator++() {
				assert(this->value);

				Type *value = this->value;

				this->value = this->value->next;
				this->wrapped = Derived(this->value);

				return Iterator(value);
			}
		
			Iterator operator--() {
				assert(this->value);

				this->value = this->value->prev;
				this->wrapped = Derived(this->value);
				return *this;
			}

			Derived& operator*() {
				return wrapped;
			}

			const Derived& operator*() const {
				return wrapped;
			}

			Derived* operator->() {
				return &wrapped;
			}

			const Derived* operator->() const {
				return const_cast<const Wrapped*>(&wrapped);
			}

			bool operator==(const Iterator<Derived, Type> &other) const {
				return this->value == other.value;
			}

			bool operator!=(const Iterator<Derived, Type> &other) const {
				return !(*this == other);
			}

		private:
			Type *value;
			Derived wrapped;
		};

	public:
		typedef Iterator<Derived, Type> iterator;
		typedef Iterator<Derived, Type> const_iterator;

	public:
		Collection() {}
		explicit Collection(Type *value_) : Wrapper<Derived, Type>(value_) {}

		iterator begin() {
			return iterator(value);
		}

		iterator end() {
			return iterator();
		}

		const_iterator begin() const {
			return iterator(value);
		}

		const_iterator end() const {
			return const_iterator();
		}
	};
}

#endif 
