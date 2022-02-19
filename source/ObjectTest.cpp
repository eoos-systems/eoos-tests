/**
 * @file      ObjectTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `Object`.
 */
#include "System.hpp"
#include "Object.hpp"
#include "lib.Types.hpp"

namespace eoos
{

/**
 * @class ObjectTest
 * @test Object
 * @brief Tests root Object class functionality.
 */
class ObjectTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.
};    
    
namespace 
{

/**
 * @brief Creates an object to test it.
 *
 * @return an object of Object class. 
 */
Object<> createObject()
{
    Object<> const obj{};
    return obj;
}

/**
 * @class TestObject
 *
 * @brief Class to provide protect functions to public scope.
 */
class TestObject : public ::eoos::Object<>
{
    using Parent = ::eoos::Object<>;

public:

    /**
     * @copydoc eoos::Object::setConstructed(bool_t)
     */
    void setConstructed(bool_t const flag)
    {
        Parent::setConstructed(flag);
    }    
};

} // namespace

/**
 * @relates ObjectTest
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
TEST_F(ObjectTest, Constructor)
{
    Object<> const obj {};
    EXPECT_TRUE(obj.isConstructed())        << "Error: Object is not constructed";    
}

TEST_F(ObjectTest, CopyConstructor)
{
    Object<> const obj1 {};
    EXPECT_TRUE(obj1.isConstructed())       << "Error: Object 1 is not constructed";
    Object<> const obj2 { obj1 };
    EXPECT_TRUE(obj1.isConstructed())       << "Error: Object 2 is not constructed";
}

TEST_F(ObjectTest, MoveConstructor)
{
    // Test if compiler moves an obj to obj1
    Object<> obj1 { createObject() };
    EXPECT_TRUE(obj1.isConstructed())   << "Error: An object is not moved to object 1 by compiler";
    // Test if cast moves obj1 to obj2
    Object<> const obj2 { lib::move(obj1) };
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 1 is not move casted to object 2";
    EXPECT_FALSE(obj1.isConstructed())  << "Error: Object 1 is constructed after movement to object 2";
}

TEST_F(ObjectTest, CopyAssignment)
{
    Object<> const obj1 {};
    EXPECT_TRUE(obj1.isConstructed())   << "Error: Object 1 is not constructed";
    Object<> obj2 {};
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 2 is not constructed";
    obj2 = obj1;
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 2 is not assigned with object 1";
}

TEST_F(ObjectTest, MoveAssignment)
{
    Object<> obj1 {};
    Object<> obj2 {};
    // Test if an obj moved to rvalue, and the rvalue assigned to obj1
    obj1 = createObject();
    EXPECT_TRUE(obj1.isConstructed())   << "Error: An object is not moved to rvalue, and the rvalue is not assigned to object 1";
    // Test if obj1 moved with lvalue to obj2
    obj2 = lib::move(obj1);  
    EXPECT_TRUE(obj2.isConstructed())   << "Error: An object 2 is not constructed with lvalue";
    EXPECT_FALSE(obj1.isConstructed())  << "Error: An object 1 is constructed but it was moved with lvalue";
    // Test if an obj1 cannot be recovered
    obj1 = lib::move(Object<>());
    EXPECT_FALSE(obj1.isConstructed())   << "Error: An object 1 is re-constructed but it was moved"; 
    // Test if an obj moved with rvalue to obj1
    obj2 = lib::move(Object<>());
    EXPECT_TRUE(obj2.isConstructed())   << "Error: An object 2 is not constructed with rvalue of a moved object";
}

TEST_F(ObjectTest, MemoryAllocation)
{
    Object<>* obj {new Object<>()};
    ASSERT_NE(obj, NULLPTR)             << "Error: Object is not allocated";
    EXPECT_TRUE(obj->isConstructed())   << "Error: Object is not constructed, but allocated";
    delete obj;
    obj = NULLPTR;
    TestObject mem{};
    mem.setConstructed(false);
    EXPECT_FALSE(mem.isConstructed())   << "Error: Some memory is not ready to be used";
    obj = new (&mem) Object<>();
    EXPECT_NE(obj, NULLPTR)             << "Error: Object is not put on memory";
    EXPECT_TRUE(obj->isConstructed())   << "Error: Object is not constructed, but put on memory";
}

TEST_F(ObjectTest, isConstructed)
{
    Object<> const obj{};
    EXPECT_TRUE(obj.isConstructed())  << "Error: Object is not constructed";
    obj.~Object();
    EXPECT_FALSE(obj.isConstructed()) << "Error: Object is constructed after destruction";
}

TEST_F(ObjectTest, isConstructed_obj)
{
    Object<>* obj {new Object<>()};
    EXPECT_TRUE(Object<>::isConstructed(obj))   << "Error: Object is not constructed";
    delete obj;
    obj = NULLPTR;
    EXPECT_FALSE(Object<>::isConstructed(obj))  << "Error: Pointer to NULLPTR object is constructed";
}

TEST_F(ObjectTest, setConstructed)
{
    TestObject obj{};
    EXPECT_TRUE(obj.isConstructed())    << "Error: Object is not constructed";
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed())    << "Error: Object is not set as constructed";
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed())   << "Error: Object is not set as unconstructed";
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed())   << "Error: Object is set as constructed if it is unconstructed";
}

} // namespace eoos
