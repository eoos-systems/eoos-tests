/**
 * @file      lib.FifoTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2024, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Fifo`. 
 */
#include "lib.Fifo.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{
namespace
{
    
const int32_t ILLEGAL_INT32( 0x20000000 );

/**
 * @class FifoUnconstructed<T,L>
 *
 * @brief Unconstructed Fifo class. 
 */
template <typename T, int32_t L>
class FifoUnconstructed : public Fifo<T,L>
{
    typedef Fifo<T,L> Parent;

public:

    /**
     * @copydoc eoos::lib::Fifo::Fifo() 
     */
    FifoUnconstructed()
        : Fifo<T,L>() {
        setConstructed(false);
    }

    /**
     * @copydoc eoos::lib::Fifo::Fifo(bool_t) 
     */
    FifoUnconstructed(bool_t isLocked)
        : Fifo<T,L>(isLocked) {
        setConstructed(false);
    }

    /**
     * @copydoc eoos::lib::Fifo::Fifo(bool_t, T const&) 
     */
    FifoUnconstructed(bool_t isLocked, T const& illegal)
        : Fifo<T,L>(isLocked, illegal) {
        setConstructed(false);
    }
    
protected:

    using Parent::setConstructed;

};
    
} // namespace

/**
 * @class lib_FifoTest
 * @test Fifo
 * @brief Tests Fifo class functionality.
 */
class lib_FifoTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_FifoTest
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
TEST_F(lib_FifoTest, Constructor)
{
    {
        Fifo<int32_t,3> obj;
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";        
    }
    {
        Fifo<int32_t,3> obj( false );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";
    }
    {
        Fifo<int32_t,3> obj( true );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";
    }
    {
        Fifo<int32_t,3> obj( false, ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";        
    }
    {
        Fifo<int32_t,3> obj( true, ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";        
    }
}

/**
 * @relates lib_FifoTest
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
TEST_F(lib_FifoTest, illegal)
{
    {
        const int32_t NEW_ILLEGAL_INT32( ILLEGAL_INT32 - 7 );
        Fifo<int32_t,3> obj( true, ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(obj.getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
        obj.setIllegal(NEW_ILLEGAL_INT32);
        EXPECT_TRUE(obj.isIllegal(NEW_ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(obj.getIllegal(), NEW_ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
    }
    {
        Fifo<int32_t,3> const obj( true, ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(obj.getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
    }
}

/**
 * @relates lib_FifoTest
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
TEST_F(lib_FifoTest, collection)
{
    for(int32_t i=0; i<2; i++)
    {
        bool_t isLocked = (i == 0) ? false : true;
        {
            Fifo<int32_t,3> obj( isLocked );
            api::Queue<int32_t>* volatile que( &obj );
            api::Collection<int32_t>* volatile col( que );
            EXPECT_EQ(col->getLength(), 0) << "Fatal: Length is wrong";
            EXPECT_TRUE(col->isEmpty()) << "Fatal: Collection is not empty";
        }
        {
            Fifo<int32_t,3> obj( isLocked );
            api::Queue<int32_t>* volatile que( &obj );        
            EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
            api::Collection<int32_t>* volatile col( que );        
            EXPECT_EQ(col->getLength(), 1) << "Fatal: Length is wrong";
            EXPECT_FALSE(col->isEmpty()) << "Fatal: Collection is empty";                
        }
        {
            Fifo<int32_t,3> obj( isLocked );
            api::Queue<int32_t>* volatile que( &obj );        
            EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
            EXPECT_TRUE(que->add(0x5A5A5001)) << "Fatal: Element is not added";        
            api::Collection<int32_t>* volatile col( que );        
            EXPECT_EQ(col->getLength(), 2) << "Fatal: Length is wrong";
            EXPECT_FALSE(col->isEmpty()) << "Fatal: Collection is empty";                
        }
        {
            Fifo<int32_t,3> obj( isLocked );
            api::Queue<int32_t>* volatile que( &obj );        
            EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
            EXPECT_TRUE(que->add(0x5A5A5001)) << "Fatal: Element is not added";
            EXPECT_TRUE(que->add(0x5A5A5002)) << "Fatal: Element is not added";
            api::Collection<int32_t>* volatile col( que );
            EXPECT_EQ(col->getLength(), 3) << "Fatal: Length is wrong";
            EXPECT_FALSE(col->isEmpty()) << "Fatal: Collection is empty";                
        }
        {
            Fifo<int32_t,3> obj( isLocked );
            api::Queue<int32_t>* volatile que( &obj );        
            EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
            EXPECT_TRUE(que->add(0x5A5A5001)) << "Fatal: Element is not added";
            EXPECT_TRUE(que->add(0x5A5A5002)) << "Fatal: Element is not added";
            if( isLocked )
            {
                EXPECT_FALSE(que->add(0x5A5A5003)) << "Fatal: Element is added";
            }
            else
            {
                EXPECT_TRUE(que->add(0x5A5A5003)) << "Fatal: Element is not added";                
            }
            api::Collection<int32_t>* volatile col( que );
            EXPECT_EQ(col->getLength(), 3) << "Fatal: Length is wrong";
            EXPECT_FALSE(col->isEmpty()) << "Fatal: Collection is empty";                
        }
        {
            FifoUnconstructed<int32_t,3> obj( isLocked );
            api::Queue<int32_t>* volatile que( &obj );        
            api::Collection<int32_t>* volatile col( que );        
            EXPECT_EQ(col->getLength(), 0) << "Fatal: Length is wrong";
            EXPECT_TRUE(col->isEmpty()) << "Fatal: Collection is not empty";
        }
        {
            FifoUnconstructed<int32_t,3> obj( isLocked );
            api::Queue<int32_t>* volatile que( &obj );        
            EXPECT_FALSE(que->add(0x5A5A5000)) << "Fatal: Element is added";
            EXPECT_FALSE(que->add(0x5A5A5001)) << "Fatal: Element is added";
            api::Collection<int32_t>* volatile col( que );
            EXPECT_EQ(col->getLength(), 0) << "Fatal: Length is wrong";
            EXPECT_TRUE(col->isEmpty()) << "Fatal: Collection is not empty";
        }
    }
}

/**
 * @relates lib_FifoTest
 * @brief Tests the class Queue interface.
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
TEST_F(lib_FifoTest, queue)
{
    {
        Fifo<int32_t,3> obj( true, ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );
        EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";
        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_FALSE(que->remove()) << "Fatal: No element is removed";
        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: Queue is not empty";
    }
    {
        FifoUnconstructed<int32_t,3> obj( true, ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );
        EXPECT_FALSE(que->add(0x5A5A5000)) << "Fatal: Element is added";        
        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: Queue is not empty";
        EXPECT_EQ(que->peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_FALSE(que->remove()) << "Fatal: No element is removed";
    }
    {
        Fifo<int32_t,3> obj( true, ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );

        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";
        
        EXPECT_TRUE(que->add(0x5A5A5001)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->add(0x5A5A5002)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 3) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_FALSE(que->add(0x5A5A5003)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 3) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(que->getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5001) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(que->getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: Queue is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5002) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: Queue is not empty";
        EXPECT_EQ(que->peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
    }
}

/**
 * @relates lib_FifoTest
 * @brief Tests the class locked Fifo interface.
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
TEST_F(lib_FifoTest, fifo_isLocked)
{
    {
        Fifo<int32_t,2> obj( true, ILLEGAL_INT32 );

        EXPECT_EQ(obj.getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";        
        EXPECT_EQ(obj.peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";
        
        EXPECT_TRUE(obj.add(0x5A5A5001)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_TRUE(obj.isFull()) << "Fatal: Fifo is not full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_FALSE(obj.add(0x5A5A5002)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_TRUE(obj.isFull()) << "Fatal: Fifo is not full";
        EXPECT_TRUE(obj.isOverrun()) << "Fatal: Fifo is not overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_FALSE(obj.add(0x5A5A5003)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_TRUE(obj.isFull()) << "Fatal: Fifo is not full";
        EXPECT_TRUE(obj.isOverrun()) << "Fatal: Fifo is not overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(obj.getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is not overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5001) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(obj.getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(obj.isEmpty()) << "Fatal: Fifo is not empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";                
        EXPECT_EQ(obj.peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";

        EXPECT_FALSE(obj.remove()) << "Fatal: Element is removed";
        EXPECT_EQ(obj.getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(obj.isEmpty()) << "Fatal: Fifo is not empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_TRUE(obj.isLocked()) << "Fatal: Fifo is not locked mode";
        EXPECT_EQ(obj.peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
    }
}

/**
 * @relates lib_FifoTest
 * @brief Tests the class unlocked Fifo interface.
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
TEST_F(lib_FifoTest, fifo_isNotLocked)
{
    {
        Fifo<int32_t,2> obj( false, ILLEGAL_INT32 );

        EXPECT_EQ(obj.getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";
        EXPECT_EQ(obj.peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";
        
        EXPECT_TRUE(obj.add(0x5A5A5001)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_TRUE(obj.isFull()) << "Fatal: Fifo is not full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.add(0x5A5A5002)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_TRUE(obj.isFull()) << "Fatal: Fifo is not full";
        EXPECT_TRUE(obj.isOverrun()) << "Fatal: Fifo is not overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.add(0x5A5A5003)) << "Fatal: Element is not added";
        EXPECT_EQ(obj.getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_TRUE(obj.isFull()) << "Fatal: Fifo is not full";
        EXPECT_TRUE(obj.isOverrun()) << "Fatal: Fifo is not overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(obj.getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(obj.isEmpty()) << "Fatal: Fifo is empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is not overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";        
        EXPECT_EQ(obj.peek(), 0x5A5A5003) << "Fatal: Element value is wrong";

        EXPECT_TRUE(obj.remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(obj.getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(obj.isEmpty()) << "Fatal: Fifo is not empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";                
        EXPECT_EQ(obj.peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";

        EXPECT_FALSE(obj.remove()) << "Fatal: Element is removed";
        EXPECT_EQ(obj.getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(obj.isEmpty()) << "Fatal: Fifo is not empty";
        EXPECT_FALSE(obj.isFull()) << "Fatal: Fifo is full";
        EXPECT_FALSE(obj.isOverrun()) << "Fatal: Fifo is overrun";        
        EXPECT_FALSE(obj.isLocked()) << "Fatal: Fifo is locked mode";
        EXPECT_EQ(obj.peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
    }
}

} // namespace lib
} // namespace eoos
