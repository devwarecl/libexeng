
#include <boost/test/unit_test.hpp>

#include <xe/Buffer.hpp>
#include <xe/HeapBuffer.hpp>

// Probar los metodos de la clase ray
BOOST_AUTO_TEST_CASE(TestBuffer) 
{
	xe::HeapBuffer buffer;

	// test allocation size
	buffer.alloc(10);
	BOOST_CHECK_EQUAL(buffer.getSize(), 10);

	buffer.alloc(20);
	BOOST_CHECK_EQUAL(buffer.getSize(), 20);

	buffer.free();
	BOOST_CHECK_EQUAL(buffer.getSize(), 0);

	// test buffer initialization
	{
		const int values1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		const int values2[] = {1, 2, 3, 4, 5, 6, 7};
	
		xe::HeapBuffer buffer1(sizeof(values1), values1);
		xe::HeapBuffer buffer2(sizeof(values2), values2);

		{
			auto locker1 = buffer1.getLocker(xe::BufferLockMode::Read);
			auto locker2 = buffer2.getLocker(xe::BufferLockMode::Read);

			BOOST_CHECK_EQUAL(std::memcmp(values1, locker1.getPointer(), sizeof(values1)), 0);
			BOOST_CHECK_EQUAL(std::memcmp(values2, locker2.getPointer(), sizeof(values2)), 0);
		}

		// test buffer write
		buffer1.write(values1);
		buffer2.write(values2);
		{
			auto locker1 = buffer1.getLocker(xe::BufferLockMode::Read);
			auto locker2 = buffer2.getLocker(xe::BufferLockMode::Read);

			BOOST_CHECK_EQUAL(std::memcmp(values1, locker1.getPointer(), sizeof(values1)), 0);	
			BOOST_CHECK_EQUAL(std::memcmp(values2, locker2.getPointer(), sizeof(values2)), 0);	
		}

		// test buffer read
		int values1_out[9];
		int values2_out[7];

		buffer1.read(values1_out);
		buffer2.read(values2_out);

		BOOST_CHECK_EQUAL(std::memcmp(values1, values1_out, sizeof(values1)), 0);
		BOOST_CHECK_EQUAL(std::memcmp(values2, values2_out, sizeof(values2)), 0);
	}

	// test buffer write detailed method
	const int values3[] = {1, 2, 3, -1, -2, 6, 7, 8, 9};
	const int values4[] = {1, -1, -2, -3, 5, 6, 7};

	xe::HeapBuffer buffer3(8);
	xe::HeapBuffer buffer4(12);

	buffer3.write(values3, 8, 12, 0);
	buffer4.write(values4, 12, 4, 0);

	{
		auto locker3 = buffer3.getLocker(xe::BufferLockMode::Read);
		auto locker4 = buffer4.getLocker(xe::BufferLockMode::Read);

		BOOST_CHECK_NE(std::memcmp(values3, locker3.getPointer(), buffer3.getSize()), 0);
		BOOST_CHECK_NE(std::memcmp(values4, locker4.getPointer(), buffer4.getSize()), 0);

		BOOST_CHECK_EQUAL(std::memcmp(&values3[3], locker3.getPointer(), buffer3.getSize()), 0);
		BOOST_CHECK_EQUAL(std::memcmp(&values4[1], locker4.getPointer(), buffer4.getSize()), 0);
	}
}
