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
const int32_t MEMORY_SIZE(4096);

/**
 * @brief Heap memory.
 */
static uint64_t memory_[MEMORY_SIZE / 8];
    
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
    Mutex<> mutex;
    uintptr_t address( reinterpret_cast<uintptr_t>(memory_) );
    Heap* heap( new (address) Heap(MEMORY_SIZE, mutex) );
    EXPECT_TRUE(heap->isConstructed()) << "Fatal: Object is not constructed";    
}

} // namespace lib
} // namespace eoos
