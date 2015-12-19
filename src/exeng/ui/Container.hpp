
#ifndef __EXENG_CONTAINER_HPP__
#define __EXENG_CONTAINER_HPP__

#include <exeng/Object.hpp>

namespace xe {
	/** 
	* @brief Generic, dynamic object container. Specifically designed for the control management. 
	*/
	template<typename ClassType>
	class Container : public Object {
	public:
		virtual ~Container() {}
		virtual void add(ClassType *control) = 0;
		virtual void remove(ClassType *control) = 0;
		virtual int size() const = 0;
	
		virtual ClassType* get(int index) = 0;
		virtual const ClassType* get(int index) const = 0;
	
		virtual TypeInfo getTypeInfo() const {
			return TypeId< Container<ClassType> >();
		}
	};
}
#endif	//__EXENG_CONTAINER_HPP__
