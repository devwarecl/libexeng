
#pragma once

#ifndef __lw_list_hpp__
#define __lw_list_hpp__

#include <boost/iterator/iterator_facade.hpp>

namespace lw {
    
    template<typename Type>
    class ListIterator : 
        public boost::iterator_facade <ListIterator<Type>, Type, boost::forward_traversal_tag> {
    
    public:
        ListIterator() {}
    
        ListIterator(Type *data_) : data(data_) {}
    
    private:
        friend class boost::iterator_core_access;
    
        void increment() {data = data->next;}
    
        bool equal(ListIterator<Type> const& other) const {return data == other.data;}
    
        Type& dereference() const {return *data; }
    
    private:
        Type *data = nullptr;
    };


	template<typename Type>
	class List {
	public:
		typedef ListIterator<Type> iterator;
		typedef ListIterator<const Type> const_iterator;

	public:
		List() {}

		explicit List(Type *first_) : first(first_) {}

		iterator begin() { return iterator(first);}
		iterator end() {return iterator(nullptr);}

		const_iterator begin() const {return const_iterator(first); };
		const_iterator end() const {return const_iterator(nullptr);}

	private:
		Type *first = nullptr;
	};
}

#endif
