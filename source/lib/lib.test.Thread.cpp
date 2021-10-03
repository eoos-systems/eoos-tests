/**
 * @file      lib.test.Thread.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Thread`. 
 */
#include "System.hpp"
#include "lib.Thread.hpp"

#ifdef EOOS_NO_STRICT_MISRA_RULES

namespace eoos
{
namespace lib
{
namespace test
{

class test_lib_Thread : public ::testing::Test
{

protected:

    class Task : public ::eoos::Object<>, public api::Task
    {
        using Parent = ::eoos::Object<>;
      
    public:
    
        Task() : Parent()
        {
        }
        
        Task(bool_t isConstructed) : Parent()
        {
            setConstructed(isConstructed);
        }
    
        Task(int32_t error) : Parent(),
            error_ (error){
        }
        
        int32_t getCounter() const
        {
            return count_;
        }       

        bool waitIsStarted()
        {
            bool_t isStarted {false};
            for(uint32_t i=0; i<TESTS_WAIT_CYCLE_TIME; i++)
            {
                isStarted = isStarted_;
                if(isStarted)
                {
                    break;
                }
            }
            return isStarted;
        }
        
    private:    
        
        bool_t isConstructed() const override
        {
            return Parent::isConstructed();
        }    
    
        int32_t start() override
        {
            isStarted_ = true;
            count_++;
            Thread<>::yield();
            count_++;              
            return error_;
        }
        
        size_t getStackSize() const override
        {
            return 0;
        }
    
        bool_t isStarted_ {false};
        int32_t error_ {0};
        int32_t count_ {0};
    };
    
protected:    

    static int32_t TASK_RETURN_ERROR;

    struct Tasks
    {
        Task normal;
        Task unconstructed {false};
        Task error {TASK_RETURN_ERROR};
    } task;

    // @note Re-define the api::Thread constants here as GTest on GCC doesn't like static variables 
    // and constants defined in scope of fixture classes as well as in scope of tested classes.
    int32_t const ID_WRONG {api::Thread::ID_WRONG};
    
    int32_t const PRIORITY_WRONG {api::Thread::PRIORITY_WRONG};
    int32_t const PRIORITY_MAX {api::Thread::PRIORITY_MAX};
    int32_t const PRIORITY_MIN {api::Thread::PRIORITY_MIN};
    int32_t const PRIORITY_NORM {api::Thread::PRIORITY_NORM};
    int32_t const PRIORITY_LOCK  {api::Thread::PRIORITY_LOCK};
    
private:

    System eoos;
};  
    
int32_t test_lib_Thread::TASK_RETURN_ERROR {333};

TEST_F(test_lib_Thread, Constructor)
{
    Thread<> obj(task.normal);
    EXPECT_TRUE(obj.isConstructed())                    << "Fatal: Object is not conctructed";
    EXPECT_EQ(obj.getStatus(), api::Thread::STATUS_NEW) << "Fatal: Status of a new thread is not NEW";
}

TEST_F(test_lib_Thread, isConstructed)
{
    Thread<> obj(task.normal);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not conctructed";
}

TEST_F(test_lib_Thread, execute)
{
    // Execute constructed task
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.isConstructed()) << "Error: Object is not conctructed";
        EXPECT_FALSE(task.normal.waitIsStarted()) << "Error: Thread was started without execute() function";
        thread.execute();
        EXPECT_EQ(thread.getStatus(), api::Thread::STATUS_RUNNABLE) << "Fatal: Status of a new thread is not RUNNABLE";
        EXPECT_TRUE(task.normal.waitIsStarted()) << "Fatal: Thread was not executed";
        thread.join();
    }
    // Execute not constructed task
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.isConstructed()) << "Error: Object is conctructed";
        thread.execute();
        EXPECT_EQ(thread.getStatus(), api::Thread::STATUS_DEAD) << "Fatal: Status of a new unconstructed thread is not DEAD";
        EXPECT_FALSE(task.unconstructed.waitIsStarted()) << "Fatal: Unconstructed thread was executed";
        thread.join();
    }
}

TEST_F(test_lib_Thread, join)
{
    Thread<> thread(task.normal);
    EXPECT_EQ(thread.getStatus(), api::Thread::STATUS_NEW) << "Error: Status of a new thread is not NEW";
    thread.execute();
    thread.join();
    EXPECT_EQ(thread.getStatus(), api::Thread::STATUS_DEAD) << "Fatal: Status of thread is not DEAD";
}

TEST_F(test_lib_Thread, getId)
{
    {
        Thread<> thread(task.normal);
        EXPECT_NE(thread.getId(), ID_WRONG) << "Fatal: Thread ID is Wrong";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_EQ(thread.getId(), ID_WRONG) << "Fatal: Thread ID is not Wrong";
    }    
}

TEST_F(test_lib_Thread, getPriority)
{
    {
        Thread<> thread(task.normal);
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Fatal: Thread priority is not Normal";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_EQ(thread.getPriority(), PRIORITY_WRONG) << "Fatal: Thread priority is not Wrong";
    }    
}

TEST_F(test_lib_Thread, setPriority)
{
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.setPriority(PRIORITY_LOCK)) << "Error: Thread priority is not set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_LOCK) << "Fatal: Thread priority is wrong";
    }
    {
        Thread<> thread(task.unconstructed);
        EXPECT_FALSE(thread.setPriority(PRIORITY_LOCK)) << "Error`: Thread priority is set"; 
        EXPECT_EQ(thread.getPriority(), PRIORITY_WRONG) << "Fatal: Thread priority is not wrong";        
    }
    for(int32_t priority=PRIORITY_MIN; priority<=PRIORITY_MAX; priority++)
    {
        Thread<> thread(task.normal);
        EXPECT_TRUE(thread.setPriority(priority)) << "Error: Thread priority is not set";
        EXPECT_EQ(thread.getPriority(), priority) << "Fatal: Thread priority is wrong";
    }
    {
        Thread<> thread(task.normal);
        EXPECT_FALSE(thread.setPriority(PRIORITY_MAX + 1)) << "Error: Thread priority is set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Fatal: Thread priority is wrong";
    }  
    {
        Thread<> thread(task.normal);
        EXPECT_FALSE(thread.setPriority(PRIORITY_MIN - 2)) << "Error: Thread priority is set";
        EXPECT_EQ(thread.getPriority(), PRIORITY_NORM) << "Fatal: Thread priority is wrong";
    }      
}

TEST_F(test_lib_Thread, getExecutionError)
{
    {
        Thread<> thread(task.normal);
        thread.execute();
        thread.join();
        EXPECT_EQ(thread.getExecutionError(), 0) << "Fatal: Exit code is wrong";
    }
    {
        Thread<> thread(task.error);
        thread.execute();
        thread.join();
        EXPECT_EQ(thread.getExecutionError(), TASK_RETURN_ERROR) << "Fatal: Exit code is wrong";
    } 
}

TEST_F(test_lib_Thread, sleep)
{   
}

TEST_F(test_lib_Thread, yield)
{   
}

} // namespace test
} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
