/**
 * @file      lib.LinkedListTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::LinkedList`. 
 */
#include "lib.LinkedList.hpp"
#include "System.hpp"
#include "lib.String.hpp"

namespace eoos
{
namespace lib
{
namespace
{
    
const int32_t ILLEGAL_INT32( 0x20000000 );
const int32_t LIST_ERROR_INDEX( api::List<int32_t>::ERROR_INDEX );
const int32_t LISTITERATOR_ERROR_INDEX( api::ListIterator<int32_t>::ERROR_INDEX );

/**
 * @class LinkedListUnconstructed<T,L>
 *
 * @brief Unconstructed LinkedList class.
 */
template <typename T>
class LinkedListUnconstructed : public LinkedList<T>
{
    typedef LinkedList<T> Parent;

public:
    
    LinkedListUnconstructed()
        : LinkedList<T>() {
        setConstructed(false);
    }

    LinkedListUnconstructed(T const& illegal)
        : LinkedList<T>(illegal) {
        setConstructed(false);
    }
    
protected:

    using Parent::setConstructed;

};
    
} // namespace
    
/**
 * @class lib_LinkedListTest
 * @test LinkedList
 * @brief Tests LinkedList class functionality.
 */
class lib_LinkedListTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.    
};    

/**
 * @relates lib_LinkedListTest
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
TEST_F(lib_LinkedListTest, Constructor)
{
    {
        LinkedList<int32_t> const obj;
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    }
    {
        LinkedList<int32_t> const obj( ILLEGAL_INT32 );
        EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
    }
}

/**
 * @relates lib_LinkedListTest
 * @brief Tests the class Illegal interface.
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
TEST_F(lib_LinkedListTest, illegal)
{
    {
        const int32_t NEW_ILLEGAL_INT32( ILLEGAL_INT32 - 7 );
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );
        api::IllegalValue<int32_t>* ill( que );
        EXPECT_TRUE(ill->isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(ill->getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
        ill->setIllegal(NEW_ILLEGAL_INT32);
        EXPECT_TRUE(ill->isIllegal(NEW_ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(ill->getIllegal(), NEW_ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
    }
    {
        LinkedList<int32_t> const obj( ILLEGAL_INT32 );
        api::Queue<int32_t> const* volatile que( &obj );
        api::IllegalValue<int32_t> const* volatile ill( que );
        EXPECT_TRUE(ill->isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(ill->getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
    }
}

/**
 * @relates lib_LinkedListTest
 * @brief Tests the class Collection interface.
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
TEST_F(lib_LinkedListTest, collection)
{
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );
        api::Collection<int32_t>* volatile col( que );
        EXPECT_EQ(col->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(col->isEmpty()) << "Fatal: List is not empty";
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );        
        EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
        api::Collection<int32_t>* volatile col( que );        
        EXPECT_EQ(col->getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(col->isEmpty()) << "Fatal: List is empty";                
    }
    {
        LinkedList<int32_t,NullAllocator> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );        
        EXPECT_FALSE(que->add(0x5A5A5000)) << "Fatal: Element is allocated and added";
        api::Collection<int32_t>* volatile col( que );        
        EXPECT_EQ(col->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(col->isEmpty()) << "Fatal: List is not empty";                
    }    
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );        
        EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_TRUE(que->add(0x5A5A5001)) << "Fatal: Element is not added";
        EXPECT_TRUE(que->add(0x5A5A5002)) << "Fatal: Element is not added";
        api::Collection<int32_t>* volatile col( que );
        EXPECT_EQ(col->getLength(), 3) << "Fatal: Length is wrong";
        EXPECT_FALSE(col->isEmpty()) << "Fatal: List is empty";                
    }
    {
        LinkedListUnconstructed<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );        
        api::Collection<int32_t>* volatile col( que );        
        EXPECT_EQ(col->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(col->isEmpty()) << "Fatal: List is not empty";
    }
    {
        LinkedListUnconstructed<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );        
        EXPECT_FALSE(que->add(0x5A5A5000)) << "Fatal: Element is added";
        EXPECT_FALSE(que->add(0x5A5A5001)) << "Fatal: Element is added";
        api::Collection<int32_t>* volatile col( que );
        EXPECT_EQ(col->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(col->isEmpty()) << "Fatal: List is not empty";
    }
}

/**
 * @relates lib_LinkedListTest
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
TEST_F(lib_LinkedListTest, queue)
{
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );
        EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: List is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";
        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_FALSE(que->remove()) << "Fatal: No element is removed";
        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: List is not empty";
    }
    {
        LinkedListUnconstructed<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );
        EXPECT_FALSE(que->add(0x5A5A5000)) << "Fatal: Element is added";        
        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: List is not empty";
        EXPECT_EQ(que->peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_FALSE(que->remove()) << "Fatal: No element is removed";
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::Queue<int32_t>* volatile que( &obj );

        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: List is empty";
        EXPECT_EQ(que->peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: List is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";
        
        EXPECT_TRUE(que->add(0x5A5A5001)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: List is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->add(0x5A5A5002)) << "Fatal: Element is not added";
        EXPECT_EQ(que->getLength(), 3) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: List is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5000) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(que->getLength(), 2) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: List is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5001) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(que->getLength(), 1) << "Fatal: Length is wrong";
        EXPECT_FALSE(que->isEmpty()) << "Fatal: List is empty";
        EXPECT_EQ(que->peek(), 0x5A5A5002) << "Fatal: Element value is wrong";

        EXPECT_TRUE(que->remove()) << "Fatal: Element is not removed";
        EXPECT_EQ(que->getLength(), 0) << "Fatal: Length is wrong";
        EXPECT_TRUE(que->isEmpty()) << "Fatal: List is not empty";
        EXPECT_EQ(que->peek(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
    }
}

/**
 * @relates lib_LinkedListTest
 * @brief Tests the class List interface.
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
TEST_F(lib_LinkedListTest, list)
{
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );        

        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
        EXPECT_EQ(lis->get(0), ILLEGAL_INT32) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->getFirst(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLast(), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_FALSE(lis->remove(0)) << "Fatal: Element is removed";
        EXPECT_FALSE(lis->removeFirst()) << "Fatal: Element is removed";
        EXPECT_FALSE(lis->removeLast()) << "Fatal: Element is removed";        
        EXPECT_FALSE(lis->removeElement(0x5A5A5000)) << "Fatal: Element is not removed";
        EXPECT_EQ(lis->getIndexOf(0x5A5A5000), LIST_ERROR_INDEX) << "Fatal: Element value is wrong";
        EXPECT_FALSE(lis->isIndex(0)) << "Fatal: Element index is not exist";

        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5003)) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add(0, 0x5A5A5000)) << "Fatal: Element is not added";        
        EXPECT_TRUE(lis->add(2, 0x5A5A5002)) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add(4, 0x5A5A5004)) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5005)) << "Fatal: Element is not added";        
        EXPECT_FALSE(lis->add(10, 0x5A5A5010)) << "Fatal: Element is added";
        EXPECT_FALSE(lis->add(-1, 0x5A5A50FF)) << "Fatal: Element is added";        

        EXPECT_EQ(lis->getLength(), 6) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_EQ(lis->get(0), 0x5A5A5000) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5001) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->get(2), 0x5A5A5002) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), 0x5A5A5003) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->get(4), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), 0x5A5A5005) << "Fatal: Element value is wrong";
        
        EXPECT_EQ(lis->getFirst(), 0x5A5A5000) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLast(), 0x5A5A5005) << "Fatal: Element value is wrong";
        
        EXPECT_EQ(lis->getIndexOf(0x5A5A5000), 0) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf(0x5A5A5001), 1) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->getIndexOf(0x5A5A5002), 2) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf(0x5A5A5003), 3) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->getIndexOf(0x5A5A5004), 4) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf(0x5A5A5005), 5) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf(0x5A5A5006), LIST_ERROR_INDEX) << "Fatal: Element value is wrong";

        EXPECT_TRUE(lis->isIndex(0)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(1)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(2)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(3)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(4)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(5)) << "Fatal: Element index is not exist";
        EXPECT_FALSE(lis->isIndex(6)) << "Fatal: Element index is exist";
        
        EXPECT_TRUE(lis->removeFirst()) << "Fatal: Element is not removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5002) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->get(2), 0x5A5A5003) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), 0x5A5A5005) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 5) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_TRUE(lis->removeLast()) << "Fatal: Element is not removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5002) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), 0x5A5A5003) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 4) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";
        
        EXPECT_TRUE(lis->remove(1)) << "Fatal: Element is not removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5003) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), 0x5A5A5004) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_FALSE(lis->remove(3)) << "Fatal: Element is removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5003) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_FALSE(lis->remove(-1)) << "Fatal: Element is removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5003) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_FALSE(lis->removeElement(0x5A5A5000)) << "Fatal: Element is removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5003) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_TRUE(lis->removeElement(0x5A5A5003)) << "Fatal: Element is not removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 2) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_TRUE(lis->add(0, 0x5A5A5004)) << "Fatal: Element is not added";
        EXPECT_EQ(lis->get(0), 0x5A5A5004) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->get(1), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";
        
        EXPECT_TRUE(lis->removeElement(0x5A5A5004)) << "Fatal: Element is not removed";
        EXPECT_EQ(lis->get(0), 0x5A5A5001) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x5A5A5004) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(5), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 2) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        lis->clear();
        EXPECT_EQ(lis->get(0), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(2), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(3), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(4), ILLEGAL_INT32) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );

        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Fatal: Element is not added";        
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Fatal: Element is not added";

        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";        

        lis->clear();        
        
        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );

        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
        
        lis->clear();        
        
        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
    }
}

/**
 * @relates lib_LinkedListTest
 * @brief Tests the class listIterator interface.
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
TEST_F(lib_LinkedListTest, listIterator)
{
    {
        LinkedList<int32_t,NullAllocator> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        api::ListIterator<int32_t>* volatile it( lis->getListIterator() );
        EXPECT_EQ(it, NULLPTR) << "Fatal: Iterator is not null";  
        delete it;        
    }
    {
        const int32_t INITIAL_ILLEGAL_INT32( ILLEGAL_INT32 - 10 );        
        LinkedList<int32_t> obj( INITIAL_ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        api::ListIterator<int32_t>* volatile it( lis->getListIterator() );
        EXPECT_TRUE(it->isIllegal(INITIAL_ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(it->getIllegal(), INITIAL_ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
        it->setIllegal(ILLEGAL_INT32);
        EXPECT_TRUE(it->isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(it->getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";
        EXPECT_TRUE(lis->isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(lis->getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";  
        delete it;
    }    
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        api::ListIterator<int32_t>* volatile it( lis->getListIterator() );
        
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";        
        delete it;
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";        
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Error: Element is not added";        
        api::ListIterator<int32_t>* volatile it( lis->getListIterator() );
        
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Error: Element is not added";

        EXPECT_FALSE(it->add(0x6B6B5000)) << "Fatal: Element is added";

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), LISTITERATOR_ERROR_INDEX) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";

        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), LISTITERATOR_ERROR_INDEX) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        delete it;
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";                
        api::ListIterator<int32_t>* volatile it( lis->getListIterator() );
        
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNextIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), 0x5A5A5000) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->remove()) << "Fatal: Iterator does not delete element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5000) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->remove()) << "Fatal: Iterator does not delete element";
        delete it;
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";        
        api::ListIterator<int32_t>* volatile it( lis->getListIterator() );
        
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNextIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), 0x5A5A5000) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";

        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";
        
        EXPECT_TRUE(it->add(0x6B6B5000)) << "Fatal: Element is not added";

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x6B6B5000) << "Fatal: Iterator has no illegal element";        

        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";        

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        delete it;
    }   
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        api::ListIterator<int32_t>* it( lis->getListIterator() );

        EXPECT_TRUE(it->add(0x6B6B5000)) << "Fatal: Element is not added";
        EXPECT_TRUE(it->add(0x6B6B5001)) << "Fatal: Element is not added";
        EXPECT_TRUE(it->add(0x6B6B5002)) << "Fatal: Element is not added";
        
        EXPECT_EQ(lis->get(0), 0x6B6B5000) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->get(1), 0x6B6B5001) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->get(2), 0x6B6B5002) << "Fatal: Element value is wrong";

    }   
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        api::ListIterator<int32_t>* volatile it( lis->getListIterator() );

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";        
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        
        EXPECT_TRUE(it->add(0x6B6B5000)) << "Fatal: Element is not added";
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";        

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), 0) << "Fatal: Iterator has wrong index";        

        EXPECT_TRUE(it->add(0x6B6B5001)) << "Fatal: Element is not added";

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 2) << "Fatal: Iterator has wrong index";
        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), 1) << "Fatal: Iterator has wrong index";        

        EXPECT_TRUE(it->add(0x6B6B5003)) << "Fatal: Element is not added";

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 3) << "Fatal: Iterator has wrong index";
        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), 2) << "Fatal: Iterator has wrong index";        

        EXPECT_EQ(it->getPrevious(), 0x6B6B5003) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->add(0x6B6B5002)) << "Fatal: Element is not added";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 3) << "Fatal: Iterator has wrong index";
        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), 2) << "Fatal: Iterator has wrong index";        

        EXPECT_EQ(it->getNext(), 0x6B6B5003) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";        

        EXPECT_EQ(it->getPrevious(), 0x6B6B5002) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";        

        EXPECT_EQ(it->getPrevious(), 0x6B6B5001) << "Fatal: Iterator has wrong element";
        EXPECT_EQ(it->getNext(), 0x6B6B5001) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";

        EXPECT_EQ(it->getPrevious(), 0x6B6B5000) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";        

        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";

        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";
        delete it;
    }    
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Error: Element is not added";
        
        api::ListIterator<int32_t>* volatile it(lis->getListIterator());

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";        

        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNextIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), 0x5A5A5000) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNextIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), 0x5A5A5001) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNextIndex(), 2) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), 0x5A5A5002) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 3) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";        

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 2) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5002) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5001) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5000) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";
        delete it;
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Error: Element is not added";
        
        api::ListIterator<int32_t>* it(lis->getListIterator(4));
        EXPECT_EQ(it, NULLPTR) << "Error: Iterator is created";
        delete it;
        it = lis->getListIterator(-1);
        EXPECT_EQ(it, NULLPTR) << "Error: Iterator is created";
        delete it;
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Error: Element is not added";
        
        api::ListIterator<int32_t>* volatile it(lis->getListIterator(3));
        EXPECT_NE(it, NULLPTR) << "Error: Iterator is created";        

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 3) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";
        
        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 2) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5002) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5001) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5000) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";        
        
        delete it;        
    }    
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Error: Element is not added";
        
        api::ListIterator<int32_t>* volatile it(lis->getListIterator(1));
        EXPECT_NE(it, NULLPTR) << "Error: Iterator is not created";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNextIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), 0x5A5A5001) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNextIndex(), 2) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), 0x5A5A5002) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNextIndex(), 3) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";        

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 2) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5002) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5001) << "Fatal: Iterator has wrong element";

        EXPECT_TRUE(it->hasPrevious()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getPreviousIndex(), 0) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), 0x5A5A5000) << "Fatal: Iterator has wrong element";

        EXPECT_FALSE(it->hasPrevious()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getPreviousIndex(), -1) << "Fatal: Iterator has wrong index";
        EXPECT_EQ(it->getPrevious(), ILLEGAL_INT32) << "Fatal: Iterator has wrong element";        
        
        delete it;        
    }
}

/**
 * @relates lib_LinkedListTest
 * @brief Tests the class Iterator interface.
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
TEST_F(lib_LinkedListTest, iterator)
{
    {
        LinkedList<int32_t,NullAllocator> obj( ILLEGAL_INT32 );
        api::Iterable<int32_t>* volatile ite( &obj );        
        api::Iterator<int32_t>* volatile it( ite->getIterator() );
        EXPECT_EQ(it, NULLPTR) << "Fatal: Iterator is not null";  
        delete it;        
    }
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::Iterable<int32_t>* volatile ite( &obj );        
        api::Iterator<int32_t>* volatile it( ite->getIterator() );
        
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";        
        delete it;
    }    
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";        
        api::Iterable<int32_t>* volatile ite( &obj );        
        api::Iterator<int32_t>* volatile it( ite->getIterator() );
        
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5000) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";        
        delete it;
    }    
    {
        LinkedList<int32_t> obj( ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );
        api::Iterable<int32_t>* volatile ite( &obj );        
        api::Iterator<int32_t>* volatile it( ite->getIterator() );
        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";  
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";        
        delete it;
    }        
    {
        const int32_t INITIAL_ILLEGAL_INT32( ILLEGAL_INT32 - 10 );        
        LinkedList<int32_t> obj( INITIAL_ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Error: Element is not added";

        api::Iterable<int32_t>* volatile ite( &obj ); 
        api::Iterator<int32_t>* volatile it( ite->getIterator() );
        it->setIllegal(INITIAL_ILLEGAL_INT32);
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5000) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5001) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5002) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNext(), INITIAL_ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";        
        delete it;
        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
    }
    {
        const int32_t INITIAL_ILLEGAL_INT32( ILLEGAL_INT32 - 10 );        
        LinkedList<int32_t> obj( INITIAL_ILLEGAL_INT32 );
        api::List<int32_t>* volatile lis( &obj );        
        EXPECT_TRUE(lis->add(0x5A5A5000)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5001)) << "Error: Element is not added";
        EXPECT_TRUE(lis->add(0x5A5A5002)) << "Error: Element is not added";

        api::Iterable<int32_t>* volatile ite( &obj ); 
        api::Iterator<int32_t>* volatile it( ite->getIterator() );
        
        EXPECT_TRUE(it->isIllegal(INITIAL_ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(it->getIllegal(), INITIAL_ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";        
        it->setIllegal(ILLEGAL_INT32);
        EXPECT_TRUE(it->isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(it->getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";
        EXPECT_TRUE(lis->isIllegal(ILLEGAL_INT32)) << "Fatal: Illegal value is not illegal";
        EXPECT_EQ(lis->getIllegal(), ILLEGAL_INT32) << "Fatal: Illegal value is not illegal";                

        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5000) << "Fatal: Iterator has wrong element";
        
        EXPECT_EQ(it->getNext(), 0x5A5A5001) << "Fatal: Iterator has wrong element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5002) << "Fatal: Iterator has wrong element";
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNext(), ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        delete it;
        
        it = ite->getIterator();
        it->setIllegal(INITIAL_ILLEGAL_INT32);        
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5000) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5001) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_TRUE(it->hasNext()) << "Fatal: Iterator has no element";
        EXPECT_EQ(it->getNext(), 0x5A5A5002) << "Fatal: Iterator has wrong element";
        EXPECT_TRUE(it->remove()) << "Fatal: Iterator does not delete element";
        
        EXPECT_FALSE(it->hasNext()) << "Fatal: Iterator has element";
        EXPECT_EQ(it->getNext(), INITIAL_ILLEGAL_INT32) << "Fatal: Iterator has no illegal element";
        EXPECT_FALSE(it->remove()) << "Fatal: Iterator deletes element";        
        delete it;
        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
    }
}

TEST_F(lib_LinkedListTest, list_string)
{
    {
        LinkedList<String> obj( "ILLEGAL_STRING" );
        api::List<String>* volatile lis( &obj );        

        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
        EXPECT_STREQ(lis->get(0).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";        
        EXPECT_STREQ(lis->getFirst().getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->getLast().getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_FALSE(lis->remove(0)) << "Fatal: Element is removed";
        EXPECT_FALSE(lis->removeFirst()) << "Fatal: Element is removed";
        EXPECT_FALSE(lis->removeLast()) << "Fatal: Element is removed";        
        EXPECT_FALSE(lis->removeElement("0x5A5A5000")) << "Fatal: Element is not removed";
        EXPECT_EQ(lis->getIndexOf("0x5A5A5000"), LIST_ERROR_INDEX) << "Fatal: Element value is wrong";
        EXPECT_FALSE(lis->isIndex(0)) << "Fatal: Element index is not exist";

        EXPECT_TRUE(lis->add("0x5A5A5001")) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add("0x5A5A5003")) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add(0, "0x5A5A5000")) << "Fatal: Element is not added";        
        EXPECT_TRUE(lis->add(2, "0x5A5A5002")) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add(4, "0x5A5A5004")) << "Fatal: Element is not added";
        EXPECT_TRUE(lis->add("0x5A5A5005")) << "Fatal: Element is not added";        
        EXPECT_FALSE(lis->add(10, "0x5A5A5010")) << "Fatal: Element is added";
        EXPECT_FALSE(lis->add(-1, "0x5A5A50FF")) << "Fatal: Element is added";        

        EXPECT_EQ(lis->getLength(), 6) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5000") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";        
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5002") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "0x5A5A5003") << "Fatal: Element value is wrong";        
        EXPECT_STREQ(lis->get(4).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "0x5A5A5005") << "Fatal: Element value is wrong";
        
        EXPECT_EQ(lis->getFirst(), "0x5A5A5000") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLast(), "0x5A5A5005") << "Fatal: Element value is wrong";
        
        EXPECT_EQ(lis->getIndexOf("0x5A5A5000"), 0) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf("0x5A5A5001"), 1) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->getIndexOf("0x5A5A5002"), 2) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf("0x5A5A5003"), 3) << "Fatal: Element value is wrong";        
        EXPECT_EQ(lis->getIndexOf("0x5A5A5004"), 4) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf("0x5A5A5005"), 5) << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getIndexOf("0x5A5A5006"), LIST_ERROR_INDEX) << "Fatal: Element value is wrong";

        EXPECT_TRUE(lis->isIndex(0)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(1)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(2)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(3)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(4)) << "Fatal: Element index is not exist";
        EXPECT_TRUE(lis->isIndex(5)) << "Fatal: Element index is not exist";
        EXPECT_FALSE(lis->isIndex(6)) << "Fatal: Element index is exist";
        
        EXPECT_TRUE(lis->removeFirst()) << "Fatal: Element is not removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5002") << "Fatal: Element value is wrong";        
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5003") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "0x5A5A5005") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 5) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_TRUE(lis->removeLast()) << "Fatal: Element is not removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5002") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5003") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 4) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";
        
        EXPECT_TRUE(lis->remove(1)) << "Fatal: Element is not removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5003") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";        
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_FALSE(lis->remove(3)) << "Fatal: Element is removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5003") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_FALSE(lis->remove(-1)) << "Fatal: Element is removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5003") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_FALSE(lis->removeElement("0x5A5A5000")) << "Fatal: Element is removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5003") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_TRUE(lis->removeElement("0x5A5A5003")) << "Fatal: Element is not removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 2) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        EXPECT_TRUE(lis->add(0, "0x5A5A5004")) << "Fatal: Element is not added";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";        
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 3) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";
        
        EXPECT_TRUE(lis->removeElement("0x5A5A5004")) << "Fatal: Element is not removed";
        EXPECT_STREQ(lis->get(0).getChar(), "0x5A5A5001") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "0x5A5A5004") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(5).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 2) << "Fatal: Length is wrong";        
        EXPECT_FALSE(lis->isEmpty()) << "Fatal: List is empty";

        lis->clear();
        EXPECT_STREQ(lis->get(0).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(1).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(2).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(3).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_STREQ(lis->get(4).getChar(), "ILLEGAL_STRING") << "Fatal: Element value is wrong";
        EXPECT_EQ(lis->getLength(), 0) << "Fatal: Length is wrong";        
        EXPECT_TRUE(lis->isEmpty()) << "Fatal: List is not empty";
    }
}

} // namespace lib
} // namespace eoos
