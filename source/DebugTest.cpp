/**
 * @file      DebugTest.cpp
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

class DebugTest : public ::testing::Test
{

protected:

    class Task : public ::eoos::Object<>, public api::Task
    {
        using Parent = ::eoos::Object<>;
      
    public:
    
        
    private:    
        
        bool_t isConstructed() const override
        {
            return Parent::isConstructed();
        }    
    
        int32_t start() override
        {
            return 0;
        }
        
        size_t getStackSize() const override
        {
            return 0;
        }
    
    };
    
private:

    System eoos;
};  

TEST_F(DebugTest, DISABLED_thread)
{
    Task task;
    lib::Thread<> thread(task);
    bool volatile isRun {true};
    while(isRun);
    thread.execute();
    isRun = true;
    while(isRun);
}

} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
