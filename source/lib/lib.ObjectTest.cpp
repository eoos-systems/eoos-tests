/**
 * @file      lib.ObjectTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::Object`.
 */
#include "lib.Object.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_ObjectTest
 * @test Object
 * @brief Tests root Object class functionality.
 */
class lib_ObjectTest : public ::testing::Test
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
    Object<> const obj;
    return obj;
}

/**
 * @class TestObject
 *
 * @brief Class to provide protect functions to public scope.
 */
class TestObject : public Object<>
{
    typedef Object<> Parent;

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
 * @relates lib_ObjectTest
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
TEST_F(lib_ObjectTest, Constructor)
{
    Object<> const obj;
    EXPECT_TRUE(obj.isConstructed())        << "Fatal: Object is not constructed";    
}

/**
 * @relates lib_ObjectTest
 * @brief Tests the class copy constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class with default construct.
 *      - Consctuct an object of the class with copy construct. 
 *
 * @b Assert:
 *      - Test the objects are constructed.
 */
TEST_F(lib_ObjectTest, CopyConstructor)
{
    Object<> const obj1;
    EXPECT_TRUE(obj1.isConstructed())       << "Error: Object 1 is not constructed";
    Object<> const obj2( obj1 );
    EXPECT_TRUE(obj1.isConstructed())       << "Fatal: Object 2 is not constructed";
}

/**
 * @relates lib_ObjectTest
 * @brief Test copy assignment.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object 1 and 2.
 *      - Assign the object 1 to the object 2.
 *
 * @b Assert:
 *      - Test the object 2 is constructed.
 */
TEST_F(lib_ObjectTest, CopyAssignment)
{
    Object<> const obj1;
    EXPECT_TRUE(obj1.isConstructed())   << "Error: Object 1 is not constructed";
    Object<> obj2;
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 2 is not constructed";
    obj2 = obj1;
    EXPECT_TRUE(obj2.isConstructed())   << "Fatal: Object 2 is not assigned with object 1";
}

/**
 * @relates lib_ObjectTest
 * @brief Test if compiler calls move construct.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object of the class with returning an object from a function using NRVO. 
 *
 * @b Assert:
 *      - Test the object is constructed.
 *
 * @todo Be sure the object is constructed by move constructor, so that we have to
 *       define a child object and flag that the move constructor called.
 */
TEST_F(lib_ObjectTest, MoveConstructor_byNrvo)
{
    Object<> obj( createObject() );
    EXPECT_TRUE(obj.isConstructed())   << "Fatal: An object is not moved to object 1 by compiler";
}

/**
 * @relates lib_ObjectTest
 * @brief Test if casting calls move construct.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object 2 with casting an object 1. 
 *
 * @b Assert:
 *      - Test the object 2 is constructed.
 *      - Test the object 1 is not constructed after the casting. 
 */
TEST_F(lib_ObjectTest, MoveConstructor_byCast)
{
    Object<> obj1;
    Object<> const obj2( lib::move(obj1) );
    EXPECT_TRUE(obj2.isConstructed())   << "Fatal: Object 1 is not move casted to object 2";
    EXPECT_FALSE(obj1.isConstructed())  << "Fatal: Object 1 is constructed after movement to object 2";
}

/**
 * @relates lib_ObjectTest
 * @brief Test if compiler calls move assignment operator.
 * 
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object of the class with returning an object from a function using NRVO. 
 *      - Assign to the object an object returned by a function using NRVO.  
 *
 * @b Assert:
 *      - Test the object is constructed.
 *
 * @todo Be sure the object is assigned by move assignment operator, so that we have to
 *       define a child object and flag that the move assignment operator called.
 */
TEST_F(lib_ObjectTest, MoveAssignment_byNrvo)
{
    Object<> obj;
    // Test if a returned obj moved to rvalue, and the rvalue assigned to obj
    obj = createObject();
    EXPECT_TRUE(obj.isConstructed())   << "Fatal: An object is not moved to rvalue, and the rvalue is not assigned to object 1";
}

/**
 * @relates lib_ObjectTest
 * @brief Test if casting calls move assignment operator. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct two object. 
 *
 * @b Assert:
 *      - Test if the object 1 moved with lvalue to the object 2.
 *      - Test if the object 1 cannot be recovered.
 *      - Test if an object moved with rvalue to the object 2.
 */
TEST_F(lib_ObjectTest, MoveAssignment_byCast)
{
    Object<> obj1;
    Object<> obj2;
    // Test if obj1 moved with lvalue to obj2
    obj2 = lib::move(obj1);  
    EXPECT_TRUE(obj2.isConstructed())   << "Fatal: An object 2 is not constructed with lvalue";
    EXPECT_FALSE(obj1.isConstructed())  << "Fatal: An object 1 is constructed but it was moved with lvalue";
    // Test if an obj1 cannot be recovered
    obj1 = lib::move(Object<>());
    EXPECT_FALSE(obj1.isConstructed())   << "Fatal: An object 1 is re-constructed but it was moved";
    // Test if an obj moved with rvalue to obj2
    obj2 = lib::move(Object<>());
    EXPECT_TRUE(obj2.isConstructed())   << "Fatal: An object 2 is not constructed with rvalue of a moved object";    
}

/**
 * @relates lib_ObjectTest
 * @brief Test if the new operator and the placement new operator. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object by new.
 *      - Construct an object by placement new. 
 *
 * @b Assert:
 *      - Test if the objects are constructed.
 */
TEST_F(lib_ObjectTest, MemoryAllocation)
{
    Object<>* obj(new Object<>());
    ASSERT_NE(obj, NULLPTR)             << "Error: Object is not allocated";
    EXPECT_TRUE(obj->isConstructed())   << "Fatal: Object is not constructed, but allocated";
    delete obj;
    obj = NULLPTR;
    TestObject mem;
    mem.setConstructed(false);
    EXPECT_FALSE(mem.isConstructed())   << "Error: Some memory is not ready to be used";
    obj = new (&mem) Object<>();
    EXPECT_NE(obj, NULLPTR)             << "Error: Object is not put on memory";
    EXPECT_TRUE(obj->isConstructed())   << "Fatal: Object is not constructed, but put on memory";
}

/**
 * @relates lib_ObjectTest
 * @brief Test if object is constructed. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object.
 *      - Destruct the object. 
 *
 * @b Assert:
 *      - Test if the object is constructed and destructed.
 */
TEST_F(lib_ObjectTest, isConstructed)
{
    Object<> const obj;
    EXPECT_TRUE(obj.isConstructed())  << "Fatal: Object is not constructed";
    obj.~Object();
    EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is constructed after destruction";
}

/**
 * @relates lib_ObjectTest
 * @brief Test if object is constructed by static object function. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Allocate and construct an object.
 *      - Delete and destruct the object. 
 *
 * @b Assert:
 *      - Test if the object is constructed and destructed.
 */
TEST_F(lib_ObjectTest, isConstructed_obj)
{
    Object<>* obj( new Object<>() );
    EXPECT_TRUE(Object<>::isConstructed(obj))   << "Fatal: Object is not constructed";
    delete obj;
    obj = NULLPTR;
    EXPECT_FALSE(Object<>::isConstructed(obj))  << "Fatal: Pointer to NULLPTR object is constructed";
}

/**
 * @relates lib_ObjectTest
 * @brief Test the protected function changes constructed status of object. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object.
 *      - Delete and destruct the object. 
 *
 * @b Assert:
 *      - Test if the object construction flag changes.
 */
TEST_F(lib_ObjectTest, setConstructed)
{
    TestObject obj;
    EXPECT_TRUE(obj.isConstructed())    << "Error: Object is not constructed";
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed())    << "Fatal: Object is not set as constructed";
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed())   << "Fatal: Object is not set as unconstructed";
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed())   << "Fatal: Object is set as constructed if it is unconstructed";
}

} // namespace lib
} // namespace eoos
