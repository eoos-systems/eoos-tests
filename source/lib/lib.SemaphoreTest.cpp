/**
 * @file      lib.SemaphoreTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Semaphore`. 
 */
#include "lib.Semaphore.hpp"
#include "lib.Thread.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_SemaphoreTest
 * @test Semaphore
 * @brief Tests Semaphore class functionality.
 */
class lib_SemaphoreTest : public ::testing::Test
{

protected:

    /**
     * @class Task
     * @brief Semaphore task for the test.
     */
    class Task : public ::eoos::Object<>, public api::Task
    {
        using Parent = ::eoos::Object<>;
      
    public:
    
        /**
         * @brief Constructor.
         */
        Task() : Parent()
        {
        }
                        
    private:    
        
        /**
         * @copydoc eoos::api::Object::isConstructed()
         */        
        bool_t isConstructed() const override
        {
            return Parent::isConstructed();
        }    
    
        /**
         * @copydoc eoos::api::Task::start()
         */        
        void start() override
        {
        }

        /**
         * @copydoc eoos::api::Task::getStackSize()
         */
        size_t getStackSize() const override
        {
            return 0;
        }

    };
    
protected:    

    /**
     * @struct Tasks
     * @brief Task collection under test.
     */
    struct Tasks
    {
        Task normal;
    } task;
    
private:

    System eoos_; ///< EOOS Operating System.
};  

/**
 * @relates lib_SemaphoreTest
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
TEST_F(lib_SemaphoreTest, Constructor)
{
    Semaphore<> obj {0};
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates lib_SemaphoreTest
 * @brief Test if object is constructed. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct a constructed and unconstructed objects of the class.
 *
 * @b Assert:
 *      - Test the object is constructed.
 */
TEST_F(lib_SemaphoreTest, isConstructed)
{
    Semaphore<> obj {1};
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

} // namespace lib
} // namespace eoos
