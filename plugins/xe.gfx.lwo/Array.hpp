
#pragma once

#ifndef __lw_array_hpp__
#define __lw_array_hpp__

#include <cassert>
#include <boost/iterator/iterator_facade.hpp>

namespace lw {

	template<typename Type>
	class Array {
	public:
		template<typename Type>
		class Iterator : 
			public boost::iterator_facade <Iterator<Type>, Type, boost::forward_traversal_tag> {

		public:
			Iterator() {}
			explicit Iterator(Type *data_) : data(data_), pointer(data_) {}

		private:
			friend class boost::iterator_core_access;

			void increment() {
				assert(data);
				data++;
			}

			bool equal(Iterator<Type> const& other) const { 
				return data == other.data;
			}

			Type& dereference() const {
				assert(data);
				return *data; 
			}

		private:
			Type *data = nullptr;
		};

	public:
		typedef Iterator<Type> iterator;
		typedef Iterator<const Type> const_iterator;

	public:
		Array() {}

		Array(Type *values_, int count_) : values(values_), count(count_) {}

		int getCount() const {
			return count;
		}

		Type& operator[](const int index) {
			assert(values);
			assert(index >= 0);
			assert(index < size);
			return values[index];
		}

		const Type& operator[](const int index) const {
			assert(values);
			assert(index >= 0);
			assert(index < size);

			return values[index];
		}

		iterator begin() { return iterator(values);}
		iterator end() {return iterator(values + size);}

		const_iterator begin() const {return const_iterator(values);}
		const_iterator end() const {return const_iterator(values + size);}

	private:
		Type *values = nullptr;
		int count = 0;
	};
}

#endif
