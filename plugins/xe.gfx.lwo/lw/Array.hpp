
#pragma once

#ifndef __lw_array_hpp__
#define __lw_array_hpp__

#include <boost/iterator/iterator_facade.hpp>

namespace lw {

	template<typename Pointer>
	class Array {
	public:
		typedef typename Pointer::type type;

	public:
		template<typename Pointer>
		class Iterator : 
			public boost::iterator_facade <Iterator<Pointer>, Pointer, boost::forward_traversal_tag> {

		public:
			typedef typename Pointer::type type;

		public:
			Iterator() {}

			explicit Iterator(type *data_) : data(data_), pointer(data_) {}

		private:
			friend class boost::iterator_core_access;

			void increment() {pointer = Pointer(++data);}

			bool equal(Iterator<Pointer> const& other) const { return pointer == other.pointer;}

			Pointer& dereference() const {return pointer; }

		private:
			Pointer pointer;
			type *data = nullptr;
		};

	public:
		typedef Iterator<Pointer> iterator;
		typedef Iterator<const Pointer> const_iterator;

	public:
		Array() {}

		Array(type *values_, int count_) : values(values_), count(count_) {}

		int getCount() const {
			return count;
		}

		Pointer operator[](const int index) {
			assert(index >= 0);
			assert(index < size);
			return Pointer(values[index]);
		}

		const Pointer operator[](const int index) const {
			assert(index >= 0);
			assert(index < size);
			return Pointer(values[index]);
		}

		iterator begin() { return iterator(values);}
		iterator end() {return iterator(values + size);}

		const_iterator begin() const {return const_iterator(values);}
		const_iterator end() const {return const_iterator(values + size);}

	private:
		type *values = nullptr;
		int count = 0;
	};
}

#endif
