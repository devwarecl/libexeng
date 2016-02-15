
#ifndef __xe_struct_hpp__
#define __xe_struct_hpp__

#include <string>
#include <xe/Config.hpp>
#include <xe/DataType.hpp>

namespace xe {
	/**
	 * @brief 
	 */
	class EXENGAPI Field final {
	public:
		Field();
		Field(const std::string &name, DataType::Enum type, int count, int align);
		
		~Field();
		
		int getSize() const;
		
		std::string getName() const;
		
		void setName(const std::string &name);
		
		void setType(DataType::Enum type);
		
		DataType::Enum getType() const;
		
		void setCount(const int count);
		
		int getCount() const;
		
		void setAlign(const int align);
		
		int getAlign() const;
		
		int getOffset() const;
		
		void setOffset(const int offset);
		
	private:
		//! The name of the field
		char name[16] = {};
		
		//! The storage datatype
		DataType::Enum type = DataType::Unknown;
		
		//! The member field count of the specified type
		int count = 0;
		
		//! The member alignment 
		int align = 0;
		
		//! The memory offset 
		int offset = 0;

	public:
		template<typename BasicType>
		static Field create(const std::string &fieldName) {
			return Field (

			);
		}
	};
	
	class EXENGAPI Struct final {
	public:
		Struct();
		explicit Struct(const int field_count);
		
		~Struct();
		
		int getFieldCount() const;
		
		Field* getField(const int index);
		
		const Field* getField(const int index) const;
		
		void computeOffsets();
		
		bool isValid() const;
		
		int getSize() const;
		
	private:
		struct Private;
		Private *impl = nullptr;
	};
}

#endif 
