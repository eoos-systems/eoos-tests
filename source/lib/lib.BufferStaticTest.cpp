/**
 * @file      lib.BufferStaticTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Buffer`. 
 */
#include "lib.Buffer.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
namespace
{
    
const int32_t ILLEGAL_INT32( 0x20000000 );

/**
 * @class TestBuffer<T,L>
 *
 * @brief Class to provide protect functions to public scope.
 */
template <typename T, int32_t L>
class TestBuffer : public Buffer<T,L>
{
    typedef Buffer<T,L> Parent;

public:

    TestBuffer()
        : Buffer<T,L>() {
    }

    TestBuffer(T const& illegal)
        : Buffer<T,L>(illegal) {
    }
    
    /**
     * @copydoc eoos::Object::setConstructed(bool_t)
     */
    void setConstructed(bool_t const flag)
    {
        Parent::setConstructed(flag);
    }    
};

    
} // namespace

/**
 * @class lib_BufferStaticTest
 * @test Buffer
 * @brief Tests Buffer class functionality.
 */
class lib_BufferStaticTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_BufferStaticTest
 * @brief Tests the class constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is constructed.
 */
TEST_F(lib_BufferStaticTest, Constructor)
{
    {
        Buffer<int32_t,3> obj;
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    }
    {
        Buffer<int32_t,3> obj( ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    }
}

/**
 * @relates lib_BufferStaticTest
 * @brief Tests the class illegal value interface.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BufferStaticTest, illegal)
{
    {
        const int32_t NEW_ILLEGAL_INT32( ILLEGAL_INT32 - 7 );
        Buffer<int32_t,3> obj( ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(obj.getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
        obj.setIllegal(NEW_ILLEGAL_INT32);
        EXPECT_TRUE(obj.isIllegal(NEW_ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(obj.getIllegal(), NEW_ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
    }
    {
        Buffer<int32_t,3> const obj( ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(obj.getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
    }
}

/**
 * @relates lib_BufferStaticTest
 * @brief Tests the class collection interface.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BufferStaticTest, collection)
{
    {
        Buffer<int32_t,3> const obj( ILLEGAL_INT32 );
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Buffer has no elements";
        EXPECT_EQ(obj.getLength(), 3) << "Fatal: Buffer length is wrong";        
    }
    {
        TestBuffer<int32_t,3> obj( ILLEGAL_INT32 );
        obj.setConstructed(false);
        EXPECT_TRUE(obj.isEmpty()) << "Fatal: Buffer has elements";
        EXPECT_EQ(obj.getLength(), 0) << "Fatal: Buffer length is not zero";        
    }
}

/**
 * @relates lib_BufferStaticTest
 * @brief Tests the class get address of data.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BufferStaticTest, getData)
{
    {
        Buffer<int32_t,2> obj(ILLEGAL_INT32);
        obj[0] = 0x5A5A5A00;
        obj[1] = 0x5A5A5A01;
        int32_t* data( obj.getData() );
        EXPECT_EQ(data, &obj[0]) << "Fatal: Address of buffer is wrong";
        EXPECT_EQ(*data, 0x5A5A5A00) << "Fatal: Buffer element is wrong";        
    }
    {
        TestBuffer<int32_t,2> obj(ILLEGAL_INT32);
        obj.setConstructed(false);
        int32_t* data( obj.getData() );
        EXPECT_EQ(data, NULLPTR) << "Fatal: Address of buffer is wrong";
    }
}

/**
 * @relates lib_BufferStaticTest
 * @brief Tests the class collection interface.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BufferStaticTest, fill_operator_subscript)
{
    {
        Buffer<int32_t,5> obj(ILLEGAL_INT32);
        obj.fill(0x12345678);
        EXPECT_EQ(obj[0], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], 0x12345678) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";                
    }
    {
        Buffer<int32_t,5> obj(ILLEGAL_INT32);
        obj.fill(0xEEEEEEEE);
        obj.fill(0x12345678, 3);        
        EXPECT_EQ(obj[0], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";                
    }    
    {
        Buffer<int32_t,5> obj(ILLEGAL_INT32);
        obj.fill(0xEEEEEEEE);
        obj.fill(0x12345678, 0, 3);        
        EXPECT_EQ(obj[0], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";                
    }    
    {
        Buffer<int32_t,5> obj(ILLEGAL_INT32);
        obj.fill(0xEEEEEEEE);
        obj.fill(0x12345678, 1, 3);        
        EXPECT_EQ(obj[0], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";                
    }
    {
        Buffer<int32_t,5> obj(ILLEGAL_INT32);
        obj.fill(0xEEEEEEEE);
        obj.fill(0x12345678, 2, 3);        
        EXPECT_EQ(obj[0], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], 0x12345678) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";                
    }
    {
        Buffer<int32_t,5> obj(ILLEGAL_INT32);
        obj.fill(0xEEEEEEEE);
        obj.fill(0x12345678, 3, 3);        
        EXPECT_EQ(obj[0], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], 0xEEEEEEEE) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], 0x12345678) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], 0x12345678) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";                
    }
    {
        TestBuffer<int32_t,5> obj(ILLEGAL_INT32);
        obj.setConstructed(false);
        obj.fill(0xEEEEEEEE);
        obj.fill(0x12345678, 3, 3);        
        EXPECT_EQ(obj[0], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";                
    }
}

/**
 * @relates lib_BufferStaticTest
 * @brief Tests the class collection interface.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BufferStaticTest, operator_subscript)
{
    {
        const int32_t NEW_ILLEGAL_INT32( ILLEGAL_INT32 - 7 );
        Buffer<int32_t,5> obj(ILLEGAL_INT32);
        obj[0] = 0x5A5A5A00;
        obj[1] = 0x5A5A5A01;
        obj[2] = 0x5A5A5A02;
        obj[3] = 0x5A5A5A03;
        obj[4] = 0x5A5A5A04;
        obj[5] = NEW_ILLEGAL_INT32;
        EXPECT_EQ(obj[0], 0x5A5A5A00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[1], 0x5A5A5A01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[2], 0x5A5A5A02) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[3], 0x5A5A5A03) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[4], 0x5A5A5A04) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(obj[5], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(obj[99], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
    }
}

/**
 * @relates lib_BufferStaticTest
 * @brief Tests the class accignment of interface.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is correct.
 */
TEST_F(lib_BufferStaticTest, operator_assignment_sequenceContainer)
{
    {
        Buffer<int32_t,3> dst;
        dst[0] = 0x5A5A5A00;
        dst[1] = 0x5A5A5A01;
        dst[2] = 0x5A5A5A02;
        Buffer<int32_t,3> src;
        src[0] = 0x6B6B6B00;
        src[1] = 0x6B6B6B01;
        src[2] = 0x6B6B6B02;
        api::SequenceContainer<int32_t> const& isrc( src );
        dst = isrc;
        EXPECT_EQ(dst[0], 0x6B6B6B00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[1], 0x6B6B6B01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[2], 0x6B6B6B02) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[0], 0x6B6B6B00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[1], 0x6B6B6B01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[2], 0x6B6B6B02) << "Fatal: Buffer element is wrong";
    }
    {
        Buffer<int32_t,3> dst(ILLEGAL_INT32);
        dst[0] = 0x5A5A5A00;
        dst[1] = 0x5A5A5A01;
        dst[2] = 0x5A5A5A02;
        Buffer<int32_t,2> src(ILLEGAL_INT32);
        src[0] = 0x6B6B6B00;
        src[1] = 0x6B6B6B01;
        api::SequenceContainer<int32_t> const& isrc( src );
        dst = isrc;
        EXPECT_EQ(dst[0], 0x6B6B6B00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[1], 0x6B6B6B01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[2], 0x5A5A5A02) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[0], 0x6B6B6B00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[1], 0x6B6B6B01) << "Fatal: Buffer element is wrong";
    }
    {
        Buffer<int32_t,3> dst(ILLEGAL_INT32);
        dst[0] = 0x5A5A5A00;
        dst[1] = 0x5A5A5A01;
        dst[2] = 0x5A5A5A02;
        Buffer<int32_t,4> src(ILLEGAL_INT32);
        src[0] = 0x6B6B6B00;
        src[1] = 0x6B6B6B01;
        src[2] = 0x6B6B6B02;
        src[3] = 0x6B6B6B03;
        api::SequenceContainer<int32_t> const& isrc( src );
        dst = isrc;
        EXPECT_EQ(dst[0], 0x6B6B6B00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[1], 0x6B6B6B01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[2], 0x6B6B6B02) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[3], ILLEGAL_INT32) << "Fatal: Buffer element is wrong";        
        EXPECT_EQ(src[0], 0x6B6B6B00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[1], 0x6B6B6B01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[2], 0x6B6B6B02) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[3], 0x6B6B6B03) << "Fatal: Buffer element is wrong";
    }
    {
        const int32_t NEW_ILLEGAL_INT32( ILLEGAL_INT32 - 7 );                            
        TestBuffer<int32_t,3> dst(ILLEGAL_INT32);
        Buffer<int32_t,3>& obj( dst );                
        dst.setConstructed(false);
        dst[0] = 0x5A5A5A00;
        dst[1] = 0x5A5A5A01;
        dst[2] = NEW_ILLEGAL_INT32;
        Buffer<int32_t,3> src;
        src[0] = 0x6B6B6B00;
        src[1] = 0x6B6B6B01;
        src[2] = 0x6B6B6B02;
        api::SequenceContainer<int32_t> const& isrc( src );
        obj.operator=(isrc);
        EXPECT_EQ(dst[0], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[1], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[2], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[0], 0x6B6B6B00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[1], 0x6B6B6B01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[2], 0x6B6B6B02) << "Fatal: Buffer element is wrong";
    }
    {
        const int32_t NEW_ILLEGAL_INT32( ILLEGAL_INT32 - 7 );
        Buffer<int32_t,3> dst;
        dst[0] = 0x5A5A5A00;
        dst[1] = 0x5A5A5A01;
        dst[2] = 0x5A5A5A02;
        TestBuffer<int32_t,3> src(ILLEGAL_INT32);
        src.setConstructed(false);
        src[0] = 0x6B6B6B00;
        src[1] = 0x6B6B6B01;
        src[2] = NEW_ILLEGAL_INT32;
        api::SequenceContainer<int32_t> const& isrc( src );
        dst = isrc;
        EXPECT_EQ(dst[0], 0x5A5A5A00) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[1], 0x5A5A5A01) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(dst[2], 0x5A5A5A02) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[0], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[1], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
        EXPECT_EQ(src[2], NEW_ILLEGAL_INT32) << "Fatal: Buffer element is wrong";
    }
}

} // namespace lib
} // namespace eoos
