/**
 * @brief Unit tests of `lib::SharedPtr`.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#include "lib.SharedPtr.hpp"
#include "gtest/gtest.h"

#ifdef EOOS_NO_STRICT_MISRA_RULES

namespace eoos
{
namespace lib
{
namespace test
{
namespace
{
    
class TestObject : public Object<>
{

public:

    TestObject()
    {
    }

    virtual ~TestObject()
    {
    }
    
private:
    
};    

} // namespace

TEST(lib_SharedPtr, isConstructed)
{
    TestObject* ptr = new TestObject();
    // Test if is constructed on construction
    SharedPtr<TestObject> obj {new TestObject()};
    EXPECT_TRUE(obj.isConstructed());
    // Test if not is constructed on destruction
    obj.~SharedPtr();
    EXPECT_FALSE(obj.isConstructed());
}

} // namespace test
} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
