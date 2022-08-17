/**
 * @file      lib.HeapTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Heap`. 
 */
#include "lib.Heap.hpp"
#include "lib.Memory.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @brief Heap size in Bytes.
 */    
const size_t MEMORY_SIZE( 4096U );

/**
 * @brief Heap memory.
 */
static uint64_t memory_[MEMORY_SIZE / sizeof(uint64_t)];

/**
 * @brief Heap memory address.
 */
static uintptr_t address_( reinterpret_cast<uintptr_t>(memory_) );

namespace
{

/**
 * @class HeapUnconstructed
 *
 * @brief Class to provide protect functions to public scope.
 */
class HeapUnconstructed : public Heap
{
    typedef Heap Parent;

public:

    HeapUnconstructed(size_t size, api::Mutex& mutex)
        : Heap(size, mutex) {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    virtual bool_t isConstructed() const
    {
        return false;
    }

};
    
} // namespace

    
/**
 * @class lib_HeapTest
 * @test Heap
 * @brief Tests Heap class functionality.
 */
class lib_HeapTest : public ::testing::Test
{

protected:

    /**
     * @brief Sets a test up before the test run
     */
    virtual void SetUp() 
    {
        Memory::memset(memory_, 0xFF, sizeof(memory_));
    }

    /**
     * @brief Tears a test down after the test done
     */
    virtual void TearDown() 
    {
    }    
    
private:
    
    System eoos_; ///< EOOS Operating System.    

protected:

    Mutex<> mutex_; ///< Heap mutex defined after EOOS to be it initialized.

};    

/**
 * @relates lib_HeapTest
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
TEST_F(lib_HeapTest, Constructor)
{
    {
        Heap* heap( new (address_) Heap(MEMORY_SIZE, mutex_) );
        ASSERT_NE(heap, NULLPTR) << "Fatal: Heap object is not allocated";    
        EXPECT_TRUE(heap->isConstructed()) << "Fatal: Object is not constructed";
        delete heap;        
    }
    {
        Heap* heap( new (0U) Heap(MEMORY_SIZE, mutex_) );
        ASSERT_EQ(heap, NULLPTR) << "Fatal: Heap object is allocated on null memory";    
        delete heap;        
    }
}

/**
 * @relates lib_HeapTest
 * @brief Tests memory allocation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Allocate memory.
 */
TEST_F(lib_HeapTest, allocate_fragmentation)
{
    {
        Heap* heap( new (address_) Heap(MEMORY_SIZE, mutex_) );
        ASSERT_NE(heap, NULLPTR) << "Fatal: Heap object is not allocated";    
        
        void* addr070( heap->allocate(7, NULLPTR) );
        EXPECT_NE(addr070, NULLPTR) << "Fatal: Memory is not allocated";

        void* addr081( heap->allocate(8, NULLPTR) );
        EXPECT_NE(addr081, NULLPTR) << "Fatal: Memory is not allocated";

        void* addr082( heap->allocate(8, NULLPTR) );
        EXPECT_NE(addr082, NULLPTR) << "Fatal: Memory is not allocated";

        heap->free(addr081);
        
        void* addr160( heap->allocate(16, NULLPTR) );
        EXPECT_NE(addr160, NULLPTR) << "Fatal: Memory is not allocated";        
        
        void* addr083( heap->allocate(8, NULLPTR) );
        EXPECT_NE(addr083, NULLPTR) << "Fatal: Memory is not allocated";
        EXPECT_EQ(addr083, addr081) << "Fatal: Memory is fragmentation detected";        

        heap->free(addr160);
        heap->free(addr082);
        heap->free(addr083);        
        heap->free(addr070);
    }
}

/**
 * @relates lib_HeapTest
 * @brief Tests memory allocation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Allocate memory.
 */
TEST_F(lib_HeapTest, allocate_unfit)
{
    {
        Heap* heap( new (address_) Heap(MEMORY_SIZE, mutex_) );
        ASSERT_NE(heap, NULLPTR) << "Fatal: Heap object is not allocated";    
        
        void* block0( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block0, NULLPTR) << "Fatal: Memory is not allocated";
        void* block1( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block1, NULLPTR) << "Fatal: Memory is not allocated";
        void* block2( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block2, NULLPTR) << "Fatal: Memory is not allocated";
        void* block3( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block3, NULLPTR) << "Fatal: Memory is not allocated";

        heap->free(block2);
        heap->free(block1);

        void* block1new( heap->allocate(16, NULLPTR) );
        EXPECT_EQ(block1new, block1) << "Fatal: Memory is not allocated";
        void* block2new( heap->allocate(16, NULLPTR) );
        EXPECT_NE(block2new, block2) << "Fatal: Memory is not allocated";

        heap->free(block3);        
        heap->free(block2new);        
        heap->free(block1new);
        heap->free(block0);
    }
}

/**
 * @relates lib_HeapTest
 * @brief Tests memory allocation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Allocate memory.
 */
TEST_F(lib_HeapTest, allocate_deletionSequence)
{
    {
        Heap* heap( new (address_) Heap(MEMORY_SIZE, mutex_) );
        ASSERT_NE(heap, NULLPTR) << "Fatal: Heap object is not allocated";    
        
        void* block0( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block0, NULLPTR) << "Fatal: Memory is not allocated";
        void* block1( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block1, NULLPTR) << "Fatal: Memory is not allocated";
        void* block2( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block2, NULLPTR) << "Fatal: Memory is not allocated";
        void* block3( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block3, NULLPTR) << "Fatal: Memory is not allocated";
        void* block4( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block4, NULLPTR) << "Fatal: Memory is not allocated";
        void* block5( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block5, NULLPTR) << "Fatal: Memory is not allocated";
        void* block6( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block6, NULLPTR) << "Fatal: Memory is not allocated";
        void* block7( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block7, NULLPTR) << "Fatal: Memory is not allocated";        
        void* block8( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block8, NULLPTR) << "Fatal: Memory is not allocated";
        void* block9( heap->allocate(8, NULLPTR) );
        EXPECT_NE(block9, NULLPTR) << "Fatal: Memory is not allocated";
        void* blockA( heap->allocate(8, NULLPTR) );
        EXPECT_NE(blockA, NULLPTR) << "Fatal: Memory is not allocated";
        void* blockB( heap->allocate(8, NULLPTR) );
        EXPECT_NE(blockB, NULLPTR) << "Fatal: Memory is not allocated";
        void* blockC( heap->allocate(8, NULLPTR) );
        EXPECT_NE(blockC, NULLPTR) << "Fatal: Memory is not allocated";
        void* blockD( heap->allocate(8, NULLPTR) );
        EXPECT_NE(blockD, NULLPTR) << "Fatal: Memory is not allocated";
        void* blockE( heap->allocate(8, NULLPTR) );
        EXPECT_NE(blockE, NULLPTR) << "Fatal: Memory is not allocated";
        void* blockF( heap->allocate(8, NULLPTR) );
        EXPECT_NE(blockF, NULLPTR) << "Fatal: Memory is not allocated";

        // Delete if next free
        heap->free(blockF);
        // Delete if prev or next free        
        heap->free(blockD);        
        heap->free(blockE);
        // Delete first
        heap->free(block0);        
        // Delete if prev free
        heap->free(blockA);
        heap->free(blockB);        
        // Delete just
        heap->free(blockC);
        heap->free(block9);
        heap->free(block8);
        heap->free(block7);
        heap->free(block7);
        heap->free(block5);
        heap->free(block4);
        heap->free(block3);
        heap->free(block2);
        heap->free(block1);
    }
}

    
/**
 * @relates lib_HeapTest
 * @brief Tests memory allocation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Allocate memory.
 */
TEST_F(lib_HeapTest, allocate_unconstructed)
{    
    HeapUnconstructed* heap( new (address_) HeapUnconstructed(MEMORY_SIZE, mutex_) );
    ASSERT_NE(heap, NULLPTR) << "Fatal: Heap object is not allocated";    
    void* addr( heap->allocate(8, NULLPTR) );
    EXPECT_EQ(addr, NULLPTR) << "Fatal: Memory is allocated by unconstructed Heap";
    heap->free(addr);
}

/**
 * @relates lib_HeapTest
 * @brief Tests memory allocation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Allocate memory.
 */
TEST_F(lib_HeapTest, allocate_zeroSize)
{    
    Heap* heap( new (address_) Heap(MEMORY_SIZE, mutex_) );
    ASSERT_NE(heap, NULLPTR) << "Fatal: Heap object is not allocated";    
    void* addr( heap->allocate(0U, NULLPTR) );
    EXPECT_EQ(addr, NULLPTR) << "Fatal: Memory of zero size is allocated";
    heap->free(addr);
}

/**
 * @relates lib_HeapTest
 * @brief Tests memory allocation.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct as many objects as heap can allocate.
 *
 * @b Assert:
 *      - Test overflow has not happened.
 */
TEST_F(lib_HeapTest, allocate_overflow)
{
    const uint32_t NEXT_TO_HEAP( 0x19822014U );
    const size_t HEAP_SIZE( 1024U );
    const size_t HEAP_COUNT( HEAP_SIZE / sizeof(uint32_t) );
    uint32_t* nextToHeapAddr( reinterpret_cast<uint32_t*>( &memory_[HEAP_COUNT] ) );
    uint32_t& nextToHeap( *nextToHeapAddr );
    nextToHeap = NEXT_TO_HEAP;
    
    Heap* heap( new (address_) Heap(HEAP_SIZE, mutex_) );
    EXPECT_EQ(nextToHeap, NEXT_TO_HEAP) << "Fatal: Integrity of heap memory is damaged";
    
    uint32_t count(HEAP_COUNT);
    while(true)
    {
        void* const addr( heap->allocate(8, NULLPTR) );
        if(addr == NULLPTR)
        {
            break;
        }
        Memory::memset(addr, 0x77, 8);            
        --count;
        if(count == 0U)
        {
            break;
        }
    }
    EXPECT_NE(count, 0U) << "Fatal: allocation limit is reached";
    EXPECT_EQ(nextToHeap, NEXT_TO_HEAP) << "Fatal: Integrity of heap memory is damaged by overflow";
}

} // namespace lib
} // namespace eoos
