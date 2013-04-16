
#ifndef __EXENG_TYPEINFO_HPP__
#define __EXENG_TYPEINFO_HPP__

#include <typeinfo>
#include "Config.hpp"

namespace exeng {
	/**
     *  @brief Wrapper para objetos std::type_info.
     */
	class EXENGAPI TypeInfo {
	public:
		TypeInfo();
		
		TypeInfo(const std::type_info& info);

		void setStdTypeInfo(const std::type_info& info);

		const std::type_info& getStdTypeInfo() const;

		bool operator== (const TypeInfo& other) const;
		bool operator!= (const TypeInfo& other) const;

		bool operator< (const TypeInfo& other) const;
		bool operator> (const TypeInfo& other) const;

		bool operator<= (const TypeInfo& other) const;
		bool operator>= (const TypeInfo& other) const;

		bool isEmpty() const;


		template<typename Type>
		static TypeInfo get() {
			TypeInfo info;

			info.setStdTypeInfo(typeid(Type));

			return info;
		}

	private:
		std::type_info *typeInfo;
	};


}

#endif
