/**
 * @brief Unit tests of `Object`.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#include "Object.hpp"
#include "lib.Types.hpp"
#include "gtest/gtest.h"

namespace eoos
{
namespace test
{
namespace 
{

Object<> createObject()
{
    Object<> obj{};
    return obj;
}

class TestObject : public ::eoos::Object<>
{
    using Parent = ::eoos::Object<>;
public:
    void setConstructed(bool_t const flag)
    {
        Parent::setConstructed(flag);
    }    
};

} // namespace

TEST(Object, isConstructed)
{
    // Test if is constructed on construction
    Object<> obj{};
    EXPECT_TRUE(obj.isConstructed());
    // Test if not is constructed on destruction
    obj.~Object();
    EXPECT_FALSE(obj.isConstructed());
}

TEST(Object, setConstructed)
{
    TestObject obj{};
    EXPECT_TRUE(obj.isConstructed());
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed());
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed());
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed());    
}

TEST(Object, CopyConstructor)
{
    Object<> obj1 {};
    Object<> obj2 { obj1 };
    // Test if both objs are conctructed
    EXPECT_TRUE(obj1.isConstructed());
    EXPECT_TRUE(obj2.isConstructed());
}

TEST(Object, MoveConstructor)
{
    // Test if compiler moves an obj to obj1
    Object<> obj1 { createObject() };
    EXPECT_TRUE( obj1.isConstructed() );
    // Test if cast moves obj1 to obj2
    Object<> obj2 { lib::move(obj1) };
    EXPECT_TRUE( obj2.isConstructed() );
    EXPECT_FALSE( obj1.isConstructed() );
}

TEST(Object, CopyAssignment)
{
    Object<> obj1 {};
    Object<> obj2 {};
    obj2 = obj1;
    // Test if both objs are conctructed
    EXPECT_TRUE(obj1.isConstructed());
    EXPECT_TRUE(obj2.isConstructed());
}

TEST(Object, MoveAssignment)
{
    Object<> obj1 {};
    Object<> obj2 {};
    // Test if an obj moved to rvalue, and the rvalue assigned to obj1
    obj1 = createObject();
    EXPECT_TRUE(obj1.isConstructed());
    // Test if obj1 moved with lvalue to obj2
    obj2 = lib::move(obj1);  
    EXPECT_TRUE(obj2.isConstructed());
    EXPECT_FALSE(obj1.isConstructed());
    // Test if an obj moved with rvalue to obj1
    obj1 = lib::move(Object<>());
    EXPECT_TRUE(obj1.isConstructed());
}

TEST(Object, MemoryAllocation)
{
    Object<>* obj {NULLPTR};
    obj = new Object<>();
    EXPECT_TRUE(obj != NULLPTR);
    EXPECT_TRUE(obj->isConstructed());
    delete obj;
    obj = NULLPTR;
    TestObject mem{};
    mem.setConstructed(false);
    EXPECT_FALSE(mem.isConstructed());
    obj = new (&mem) Object<>();
    EXPECT_TRUE(obj != NULLPTR);
    EXPECT_TRUE(obj->isConstructed());     
}

} // namespace test
} // namespace eoos
