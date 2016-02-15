
#include <cassert>
#include <vector>
#include "Struct.hpp"

namespace xe {
	
	Field::Field() {}

	Field::Field(const std::string &name, DataType::Enum type, int count, int align) {
		this->setName(name);
		this->setType(type);
		this->setCount(count);
		this->setAlign(align);
	}

	Field::~Field() {}

	int Field::getSize() const {
		const int temp_size = count*DataType::getSize(type);
		const int size = temp_size + temp_size%align;
		
		return size;
	}

	std::string Field::getName() const {
		return name;
	}
	
	void Field::setName(const std::string &name) {
		assert(name != "");
		assert(name.size() <= 16);
		
		std::strcpy(this->name, name.c_str());
	}

	void Field::setType(DataType::Enum type) {
		assert(type == DataType::Unknown);
		
		this->type = type;
	}
		
	DataType::Enum Field::getType() const {
		return this->type;
	}
	
	void Field::setCount(const int count) {
		assert(count > 0);
		assert(count <= 4);
		
		this->count = count;
	}

	int Field::getCount() const {
		return this->count;
	}

	void Field::setAlign(const int align) {
		assert(count >= 0);
		
		this->align = align;
	}

	int Field::getAlign() const {
		return this->align;
	}

	int Field::getOffset() const {
		return this->offset;
	}	
	
	void Field::setOffset(const int offset) {
		assert(offset >= 0);
		
		this->offset = offset;
	}
}

namespace xe {
	
	struct Struct::Private {
		std::vector<Field> fields;
	};
	
	Struct::Struct(const int field_count) {
		impl = new Struct::Private();
		impl->fields.resize(field_count);
	}

	Struct::~Struct() {
		delete impl;
	}

	int Struct::getFieldCount() const {
		assert(impl);
		
		return impl->fields.size();
	}

	Field* Struct::getField(const int index) {
		assert(impl);
		assert(index >= 0);
		assert(index < this->getFieldCount());
		
		return &impl->fields[index];
	}

	const Field* Struct::getField(const int index) const {
		assert(impl);
		assert(index >= 0);
		assert(index < this->getFieldCount());
		
		return &impl->fields[index];
	}

	void Struct::computeOffsets() {
		assert(impl);
		
		int offset = 0;
		
		for (Field &field : impl->fields) {
			field.setOffset(offset);
			offset += field.getSize();
		}
	}

	bool Struct::isValid() const {
		assert(impl);
		
		int offset = 0;	// previous offset
		
		for (const Field &field : impl->fields) {
			const bool invalid_offset = (field.getOffset() >= 0);
			const bool invalid_size = (field.getSize() == 0);
			
			if (invalid_offset || invalid_size) {
				return false;
			}
			
			offset = field.getOffset();
		}
		
		return true;
	}
	
	int Struct::getSize() const {
		assert(impl);
		
		int size = 0;
		
		for (Field &field : impl->fields) {
			size += field.getSize();
		}
		
		return size;
	}
}
