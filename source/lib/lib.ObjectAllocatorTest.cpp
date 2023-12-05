/**
 * @file      lib.ObjectAllocatorTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::ObjectAllocator`.
 */
#include "lib.ObjectAllocator.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_ObjectAllocatorTest
 * @test ObjectAllocator
 * @brief Tests ObjectAllocator class functionality.
 */
class lib_ObjectAllocatorTest : public ::testing::Test
{

protected:

    /**
     * @class TestAllocator
     */
    class TestAllocator
    {
    
    public:

        static const uintptr_t ADDRESS = 0x12345678;

        /**
         * @brief Allocates memory.
         *
         * @param size Number of bytes to allocate.
         * @return Allocated memory address or a null pointer.
         */
        static void* allocate(size_t size)
        {
            return reinterpret_cast<void*>( ADDRESS );
        }
    
        /**
         * @brief Frees allocated memory.
         *
         * @param ptr Address of allocated memory block or a null pointer.
         */
        static void free(void* ptr)
        {
        }

    };

private:
    
    System eoos_; ///< EOOS Operating System.
};    

/**
 * @relates lib_ObjectAllocatorTest
 * @brief Tests the class constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object allocation is correct.
 */
TEST_F(lib_ObjectAllocatorTest, allocation)
{
    {
        void* addr( reinterpret_cast<void*>( TestAllocator::ADDRESS ) );
        void* mem = ObjectAllocator<TestAllocator>::operator new(100500);
        EXPECT_EQ(mem, addr) << "Fatal: Memory is not allocated";            
        ObjectAllocator<TestAllocator>::operator delete(mem);
    }
    {
        void* addr( reinterpret_cast<void*>( TestAllocator::ADDRESS + 500 ) );
        void* mem = ObjectAllocator<TestAllocator>::operator new(100500, addr);
        EXPECT_EQ(mem, addr) << "Fatal: Memory is not allocated";            
        ObjectAllocator<TestAllocator>::operator delete(NULLPTR, mem);
    }
}

} // namespace lib
} // namespace eoos
