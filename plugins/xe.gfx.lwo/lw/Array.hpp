#pragma once

namespace lw {
	template<typename Wrapper, typename Type>
	class Array {
	public:
		Array() {}
		Array(Type *data, int size) : _data(data), _size(size) {}

		int size() const {
			return _size;
		}

		Wrapper operator[](const int index) const {
			assert(index >= 0);
			assert(index < size());

			return Wrapper(&_data[index]);
		}

	private:
		Type *_data = nullptr;
		int _size = 0;
	};
}