
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <exeng/DataType.hpp>

using namespace exeng;

BOOST_AUTO_TEST_CASE(DataType_CheckSigned)
{
    /*
    enum Kind {
        Int, Float
    };
    
    enum Enum {
        UInt8, UInt16, UInt32,
        Int8, Int16, Int32,
        Float16, Float32 
    }; 
    
    static bool isSigned(DataType::Enum dt);
    static DataType::Kind getKind(DataType::Enum dataType);
    static int getSize(DataType::Enum dataType);
    */
    
    BOOST_CHECK(!DataType::isSigned(DataType::UInt8));
    BOOST_CHECK(!DataType::isSigned(DataType::UInt16));
    BOOST_CHECK(!DataType::isSigned(DataType::UInt32));
    
    BOOST_CHECK(DataType::isSigned(DataType::Int8));
    BOOST_CHECK(DataType::isSigned(DataType::Int16));
    BOOST_CHECK(DataType::isSigned(DataType::Int32));
    
    BOOST_CHECK(DataType::isSigned(DataType::Float16));
    BOOST_CHECK(DataType::isSigned(DataType::Float32));
}

BOOST_AUTO_TEST_CASE(DataType_CheckSize)
{
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::UInt8), 1);
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::UInt16), 2);
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::UInt32), 4);
    
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::Int8), 1);
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::Int16), 2);
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::Int32), 4);
    
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::Float16), 2);
    BOOST_CHECK_EQUAL(DataType::getSize(DataType::Float32), 4);
}

BOOST_AUTO_TEST_CASE(DataType_CheckKind)
{
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::UInt8), DataType::Int);
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::UInt16), DataType::Int);
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::UInt32), DataType::Int);
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::Int8), DataType::Int);
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::Int16), DataType::Int);
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::Int32), DataType::Int);
    
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::Float16), DataType::Float);
    BOOST_CHECK_EQUAL(DataType::getKind(DataType::Float32), DataType::Float);
}
