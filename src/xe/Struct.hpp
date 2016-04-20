
#pragma once

#ifndef __xe_struct__
#define __xe_struct__

#include <string>
#include <xe/Config.hpp>
#include <xe/DataType.hpp>

namespace xe {

	struct Field {
		std::string name;
		DataType::Enum type = DataType::Unknown;
		int count = 0;
		int align = 1;

		std::size_t getSize() const {
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

	struct Format {
		std::vector<Field> fields;

		std::size_t getSize() const {
			int size = 0;

			for (const Field &field : fields) {
				size += field.getSize();
			}

			return size;
		}
	};

	template<typename Attrib1, typename Attrib2, typename Attrib3> 
	class Struct {
	public:
		static StructFormat getFormat() {
		}
	};
}

#endif 
