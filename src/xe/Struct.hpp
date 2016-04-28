
#pragma once

#ifndef __xe_struct__
#define __xe_struct__

#include <string>
#include <xe/Config.hpp>
#include <xe/DataType.hpp>
#include <xe/Vector.hpp>

namespace xe {

    /**
     * @brief Field descriptor for structures
     */
	struct Field {
		std::string name;                           //! Name of the field
		DataType::Enum type = DataType::Unknown;    //! Data type enumeration
		int count = 0;                              //! Count of elements in the field
		int align = 1;                              //! Field alignment

        /**
         * @brief Get the storage size, in bytes, of the field.
         */
		std::size_t getStorage() const {
			const int temp_size = count * xe::DataType::getSize(type);
            const int size = temp_size + temp_size%align;
            
            return size;
		}

		bool operator== (const Field &other) const {
			if (name != other.name) {return false;}
			if (type != other.type) {return false;}
			if (count != other.count) {return false;}
			if (align != other.align) {return false;}
			
			return true;
		}

        bool operator!= (const Field &other) const {
			return !(*this == other);
		}
	};

    template<typename Type>
    struct FieldBuilder {
        static Field build(const std::string &name) {
            return {"", DataTypeTraits<Type>::Enum, 1, 1}
        }
    };

    template<typename Type, int Count>
    struct FieldBuilder<Vector<Type, Count>>  {
        static Field build(const std::string &name) {
            return {name, Vector<Type, Count>::Enum, Count,  }
        }
    };

	template<typename Attrib1, typename Attrib2, typename Attrib3> 
	class Struct {
	public:

	};
}

#endif 
