/**
 * @brief Unit tests of `lib::Thread`.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#include "Tests.hpp"
#include "lib.Thread.hpp"

#ifdef EOOS_NO_STRICT_MISRA_RULES

namespace eoos
{
namespace lib
{
namespace test
{
namespace
{
    
class Task : public ::eoos::Object<>, public api::Task
{
    typedef ::eoos::Object<> Parent;
  
public:

    Task() : Parent()
    {
    }
    
    ~Task() override
    {
    }
    
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }    

    int32_t start() override
    {
        isStarted_ = true;
        return 0;
    }
    
    void setConstructed(bool_t const flag)
    {
        Parent::setConstructed(flag);
    }    
    
    int32_t getStackSize() const override
    {
        return 0;
    }
    
    bool_t isTestStarted() const
    {
        return isStarted_;
    }
    
private:

    bool_t isStarted_ {false};
};

} // namespace

TEST(lib_Thread, Constructor)
{
    Task task; 
    Thread<> obj(task);
    EXPECT_TRUE(obj.isConstructed())             << "Error: Object is not conctructed";
    EXPECT_EQ(obj.getStatus(), api::Thread::NEW) << "Error: Status of a new thread is not NEW";
}

TEST(lib_Thread, isConstructed)
{
    Task task; 
    Thread<> obj(task);
    EXPECT_TRUE(obj.isConstructed()) << "Error: Object is not conctructed";
}

TEST(lib_Thread, execute)
{
    // Execute constructed task
    {
        Task task; 
        Thread<> thread(task);
        EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not conctructed";
        bool_t isStarted {false};
        
        for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
        {
            isStarted = task.isTestStarted();
            if(isStarted)
            {
                break;
            }
        }
        EXPECT_FALSE(isStarted) << "Error: Thread was started without execute() function";
        
        thread.execute();
        for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
        {
            isStarted = task.isTestStarted();
            if(isStarted)
            {
                break;
            }
        }
        EXPECT_TRUE(isStarted) << "Error: Thread was not executed";
        thread.join();
    }
    // Execute not constructed task
    {
        Task task; 
        task.setConstructed(false);
        Thread<> thread(task);
        EXPECT_FALSE(thread.isConstructed()) << "Error: Object is conctructed";
        thread.execute();
        bool_t isStarted {false};
        for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
        {
            isStarted = task.isTestStarted();
            if(isStarted)
            {
                break;
            }
        }
        EXPECT_FALSE(isStarted) << "Error: Thread was executed";
        thread.join();
    }
}

TEST(lib_Thread, join)
{
    Task task;
    Thread<> thread(task);
    EXPECT_EQ(thread.getStatus(), api::Thread::NEW) << "Error: Status of a new thread is not NEW";
    thread.execute();
    thread.join();
    EXPECT_EQ(thread.getStatus(), api::Thread::DEAD) << "Error: Status of thread is not DEAD";
}

TEST(lib_Thread, getId)
{
    {
        Task task;
        Thread<> thread(task);
        EXPECT_NE(thread.getId(), api::Thread::WRONG_ID) << "Error: Thread ID is wrong";
    }
    {
        Task task;
        task.setConstructed(false);
        Thread<> thread(task);
        EXPECT_EQ(thread.getId(), api::Thread::WRONG_ID) << "Error: Thread ID is not wrong";
    }    
}




} // namespace test
} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
