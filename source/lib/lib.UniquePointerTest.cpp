/**
 * @file      lib.UniquePointerTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::UniquePointer`. 
 */
#include "lib.UniquePointer.hpp"
#include "System.hpp"

#ifndef EOOS_GLOBAL_ENABLE_NO_HEAP

namespace eoos
{
namespace lib
{

/**
 * @class lib_UniquePointerTest
 * @test UniquePointer
 * @brief Tests UniquePointer class functionality.
 */
class lib_UniquePointerTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.
};    
    
namespace
{

/**
 * @struct ManagedAction
 * @brief Actions happened in ManagedObject.
 */
struct ManagedAction
{
    ManagedAction() : 
        isDeleted (false) {
    }
    
    bool_t isDeleted;
};

/**
 * @class ManagedObject
 * @brief Object managed by UniquePointer objects.
 */
class ManagedObject : public Object<>
{
    typedef Object<> Parent;

public:

    /**
     * @brief Constructor.
     */
    ManagedObject() : Parent(),
        value_ (0),
        action_ (NULLPTR){
    }

    /**
     * @brief Constructor.
     *
     * @param value A value to containt as member.
     */
    ManagedObject(int32_t const value) : Parent(),
        value_ (value),
        action_ (NULLPTR){
    }

    /**
     * @brief Constructor.
     *
     * @param action Flags will be set on actions.
     */
    ManagedObject(ManagedAction* const action) : Parent(),
        value_ (0),
        action_ (action){
    }
    
    /**
     * @brief Constructor.
     *
     * @param value A value to containt as member.
     * @param action Flags will be set on actions.
     */
    ManagedObject(int32_t const value, ManagedAction* const action) : Parent(),
        value_  (value),
        action_ (action){
    }    

    /**
     * @brief Destructor.
     */
    virtual ~ManagedObject()
    {
        value_ = -1;
        if(action_ != NULLPTR)
        {
            action_->isDeleted = true;
        }
    }
    
    /**
     * @brief Returns containing value.
     *
     * @return The value passed to the constructor.
     */        
    int32_t getValue() const
    {
        return value_;
    }
    
private:

    int32_t value_;
    ManagedAction* action_;
};

/**
 * @brief Creates UniquePointer for ManagedObject.
 *
 * @param value A value to containt as member.    
 * @param action Flags will be set on actions.
 * @return Created object by rvalue.
 */        
UniquePointer<ManagedObject> createObject(int32_t const value = 0, ManagedAction* const action = NULLPTR)
{
    return UniquePointer<ManagedObject>(new ManagedObject(value, action));
}

/**
 * @class TestUniquePointer<T>
 * @brief Test class with public members that are protected in the UniquePointer class.
 */
template <typename T>
class TestUniquePointer : public UniquePointer<T>
{
    typedef UniquePointer<T> Parent;
    
public:

    /**
     * @copydoc eoos::UniquePointer::UniquePointer(T*)
     */
    explicit TestUniquePointer(T* const pointer) : Parent(pointer) {}

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
 * @relates lib_UniquePointerTest
 * @brief Tests the class constructor with NULLPTR.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is constructed.
 *      - Test the pointer is NULLPTR. 
 */
TEST_F(lib_UniquePointerTest, Constructor_nullptr)
{
    UniquePointer<ManagedObject> const obj(NULLPTR);
    EXPECT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";    
    EXPECT_EQ(obj.get(), NULLPTR) << "Fatal: Unique pointer does not equal to NULLPTR";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Tests the class constructor with pointer to an object.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the object is constructed.
 *      - Test the raw pointer equal to unique pointer.
 */
TEST_F(lib_UniquePointerTest, Constructor_pointer)
{
    const int32_t VALUE(1);
    ManagedObject* const ptr(new ManagedObject(VALUE));
    UniquePointer<ManagedObject> const obj(ptr);
    EXPECT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    ASSERT_EQ(obj.get(), ptr) << "Fatal: Unique pointer does not equal to its raw pointer";
    EXPECT_EQ(obj->getValue(), VALUE) << "Fatal: Wrong value containing in managed object";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Tests move constructor.
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
TEST_F(lib_UniquePointerTest, MoveConstructor)
{
    // Test if compiler moves an obj to obj1
    const int32_t VALUE1(1);
    ManagedAction action1;
    UniquePointer<ManagedObject> obj1( createObject(VALUE1, &action1) );
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: object 1 is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: object 1 is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";
    // Test if cast moves obj1 to obj2
    ManagedObject* const ptr1( obj1.get() );
    UniquePointer<ManagedObject> const obj2( lib::move(obj1) );
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: Object 1 is not move casted to object 2";
    EXPECT_FALSE(obj2.isNull()) << "Error: object 2 is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: object 2 is not unique";
    EXPECT_EQ(obj2.get(), ptr1) << "Fatal: Unique pointer does not equal to expected value";        
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(obj1.isConstructed()) << "Fatal: Object 1 is constructed after movement to object 2";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test move assignment.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *      - Move assign objects to objects using NRVO and casting.
 *
 * @b Assert:
 *      - Test new objects are constructed.
 *      - Test released objects are not constructed.
 */
TEST_F(lib_UniquePointerTest, MoveAssignment)
{
    const int32_t VALUE1(1);
    ManagedAction action1;
    UniquePointer<ManagedObject> obj1(new ManagedObject(VALUE1, &action1));
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";        
    // Test if an obj moved to rvalue, and the rvalue assigned to obj1
    const int32_t VALUE3(3);       
    ManagedAction action3;    
    obj1 = createObject(VALUE3, &action3);
    EXPECT_TRUE(obj1.isConstructed()) << "Fatal: An object is not moved to rvalue, and the rvalue is not assigned to object 1";
    EXPECT_FALSE(obj1.isNull()) << "Error: object 1 is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: object 1 is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE3) << "Fatal: Wrong value containing in managed object";
    EXPECT_TRUE(action1.isDeleted) << "Fatal: Managed object was not deleted";
    EXPECT_FALSE(action3.isDeleted) << "Fatal: Managed object was deleted";    
    // Test if obj1 moved with lvalue to obj2
    const int32_t VALUE2(2);    
    ManagedAction action2;    
    UniquePointer<ManagedObject> obj2(new ManagedObject(VALUE2, &action2));
    EXPECT_EQ(obj2->getValue(), VALUE2) << "Fatal: Wrong value containing in managed object";        
    obj2 = lib::move(obj1);
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: An object 2 is not constructed with lvalue";
    EXPECT_FALSE(obj2.isNull()) << "Error: object 2 is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: object 2 is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE3) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(obj1.isConstructed()) << "Fatal: An object 1 is constructed but it was moved with lvalue";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_TRUE(action2.isDeleted) << "Fatal: Managed object was not deleted";
    EXPECT_FALSE(action3.isDeleted) << "Fatal: Managed object was deleted";
    // Test if an obj1 cannot be recovered
    ManagedAction action4;    
    obj1 = lib::move(UniquePointer<ManagedObject>(new ManagedObject(&action4)));
    EXPECT_FALSE(obj1.isConstructed()) << "Fatal: An object 1 is re-constructed but it was moved";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_TRUE(action4.isDeleted) << "Fatal: Managed object was not deleted";    
    // Test if an obj moved with rvalue to obj2
    const int32_t VALUE5(5);
    ManagedAction action5;
    obj2 = lib::move(UniquePointer<ManagedObject>(new ManagedObject(VALUE5, &action5)));
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: An object 2 is not constructed with rvalue of a moved object";
    EXPECT_FALSE(obj2.isNull()) << "Error: object 2 is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: object 2 is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";    
    EXPECT_EQ(obj2->getValue(), VALUE5) << "Fatal: Wrong value containing in managed object";
    EXPECT_TRUE(action3.isDeleted) << "Fatal: Managed object was not deleted";        
    EXPECT_FALSE(action5.isDeleted) << "Fatal: Managed object was deleted";    
    // Test if an obj moved with rvalue to obj2
    obj2 = lib::move(UniquePointer<ManagedObject>());
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: An object 2 is not constructed with rvalue of a moved object";
    EXPECT_TRUE(obj2.isNull()) << "Error: object 2 is not null";
    EXPECT_FALSE(obj2.isUnique()) << "Error: object 2 is unique";
    EXPECT_EQ(obj2.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_TRUE(action5.isDeleted) << "Fatal: Managed object was not deleted";    
}

/**
 * @relates lib_UniquePointerTest
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
TEST_F(lib_UniquePointerTest, isConstructed)
{
    UniquePointer<ManagedObject> const obj(new ManagedObject());
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates lib_UniquePointerTest
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
TEST_F(lib_UniquePointerTest, setConstructed)
{
    TestUniquePointer<ManagedObject> obj(new ManagedObject());
    EXPECT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not set as constructed";
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is not set as unconstructed";
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is set as constructed if it is unconstructed";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test stored pointer.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct UniquePointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_UniquePointerTest, get)
{
    const int32_t VALUE(0x12345678);
    ManagedObject* const ptr(new ManagedObject(VALUE));
    UniquePointer<ManagedObject> obj1(ptr);
    ASSERT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj1.get(), ptr) << "Fatal: Unique pointer does not equal to its raw pointer";
    EXPECT_EQ(obj1.get()->getValue(), VALUE) << "Fatal: Value in managed object is wrong";
    UniquePointer<ManagedObject> obj2;
    ASSERT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";    
    EXPECT_EQ(obj2.get(), NULLPTR) << "Fatal: Unique pointer does not equal to its raw pointer";
    UniquePointer<ManagedObject> obj3(NULLPTR);
    ASSERT_TRUE(obj3.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj3.get(), NULLPTR) << "Fatal: Unique pointer does not equal to its raw pointer";    
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test stored pointer is reset.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct UniquePointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_UniquePointerTest, reset)
{
    const int32_t VALUE1(1);
    ManagedAction action1;
    UniquePointer<ManagedObject> obj1(new ManagedObject(VALUE1, &action1));
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: object 1 is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: object 1 is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    obj1.reset();
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_TRUE(action1.isDeleted) << "Error: Managed object was not deleted";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test stored pointer is reset.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct UniquePointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_UniquePointerTest, reset_withOther)
{
    const int32_t VALUE1(1);
    ManagedAction action1;
    UniquePointer<ManagedObject> obj1(new ManagedObject(VALUE1, &action1));
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    
    const int32_t VALUE2(2);
    ManagedAction action2;
    obj1.reset(new ManagedObject(VALUE2, &action2));
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE2) << "Error: Wrong value containing in managed object";    
    EXPECT_FALSE(action2.isDeleted) << "Error: Managed object was deleted";
    EXPECT_TRUE(action1.isDeleted) << "Error: Managed object was not deleted";    
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test stored pointer is swap.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct UniquePointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_UniquePointerTest, swap)
{
    const int32_t VALUE1(1);
    ManagedAction action1;
    ManagedObject* ptr1(new ManagedObject(VALUE1, &action1));
    UniquePointer<ManagedObject> obj1(ptr1);
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";

    const int32_t VALUE2(2);
    ManagedAction action2;
    ManagedObject* ptr2(new ManagedObject(VALUE2, &action2));    
    UniquePointer<ManagedObject> obj2(ptr2);
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE2) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action2.isDeleted) << "Error: Managed object was deleted";
    
    obj1.swap(obj2);

    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.get(), ptr2) << "Fatal: Unique pointer does not equal to expected value";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE2) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action2.isDeleted) << "Error: Managed object was deleted";
    
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.get(), ptr1) << "Fatal: Unique pointer does not equal to expected value";    
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    
    obj1.reset();
    
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_TRUE(obj1.isNull()) << "Error: Object is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: Object is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_TRUE(action2.isDeleted) << "Error: Managed object was deleted";
    
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.get(), ptr1) << "Fatal: Unique pointer does not equal to expected value";        
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    
    obj1.swap(obj2);    

    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.get(), ptr1) << "Fatal: Unique pointer does not equal to expected value";        
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";

    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_TRUE(obj2.isNull()) << "Error: Object is not null";
    EXPECT_FALSE(obj2.isUnique()) << "Error: Object is unique";
    EXPECT_EQ(obj2.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test counter of unique objects for the managed object. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct UniquePointer objects.
 *
 * @b Assert:
 *      - Test if counter is correct to number of unique pointers.
 */
TEST_F(lib_UniquePointerTest, getCount)
{
    {
        UniquePointer<ManagedObject> obj1;
        EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
        UniquePointer<ManagedObject> obj2(new ManagedObject());
        EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
    }
    {
        ManagedAction action1;
        UniquePointer<ManagedObject>* obj1( new UniquePointer<ManagedObject>(new ManagedObject(&action1)) );
        EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was unexpectedly deleted";    
        EXPECT_EQ(obj1->getCount(), 1) << "Fatal: Amount of unique objects managing object is wrong";
        delete obj1;
        EXPECT_TRUE(action1.isDeleted) << "Fatal: Managed object was not deleted";  
    }
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test if unique pointer manages an object. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *
 * @b Assert:
 *      - Test if the function returns correct value.
 */
TEST_F(lib_UniquePointerTest, isNull)
{
    UniquePointer<ManagedObject> const obj1(new ManagedObject());
    EXPECT_FALSE( obj1.isNull() ) << "Fatal: Object stores NULLPTR";
    UniquePointer<ManagedObject> const obj2;
    EXPECT_TRUE( obj2.isNull() ) << "Fatal: Object doesn't store NULLPTR";
    UniquePointer<ManagedObject> const obj3(NULLPTR);
    EXPECT_TRUE( obj3.isNull() ) << "Fatal: Object doesn't store NULLPTR";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Tests if unique pointer is only one manages an object. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *
 * @b Assert:
 *      - Test if the function returns correct value.
 */
TEST_F(lib_UniquePointerTest, isUnique)
{
    UniquePointer<ManagedObject> obj1;
    EXPECT_FALSE( obj1.isUnique() ) << "Fatal: Object is unique";
    UniquePointer<ManagedObject> const obj2(new ManagedObject());
    EXPECT_TRUE( obj2.isUnique() ) << "Fatal: Object is not unique";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Tests if pointer is released by unique pointer. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *
 * @b Assert:
 *      - Test if the function returns correct value.
 */
TEST_F(lib_UniquePointerTest, release)
{
    {
        const int32_t VALUE1(1);
        ManagedAction action1;
        ManagedObject* ptr1(new ManagedObject(VALUE1, &action1));
        UniquePointer<ManagedObject> obj1(ptr1);
        EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
        EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
        EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
        EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of unique objects managing object is wrong";
        EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
        EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
        
        ManagedObject* ptr2(obj1.release());
        EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
        EXPECT_TRUE(obj1.isNull()) << "Error: Object is not null";
        EXPECT_FALSE(obj1.isUnique()) << "Error: Object is unique";
        EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
        EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
        EXPECT_EQ(ptr1, ptr2) << "Error: Original and released raw pointers don't equal to each other";
    }
    {
        UniquePointer<ManagedObject> obj1;
        EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
        EXPECT_TRUE(obj1.isNull()) << "Error: Object is not null";
        EXPECT_FALSE(obj1.isUnique()) << "Error: Object is unique";
        EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of unique objects managing object is wrong";
        
        ManagedObject* ptr2(obj1.release());        
        EXPECT_EQ(ptr2, NULLPTR) << "Error: Released raw pointers doesn't equal to null";
    }
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test operator (->). 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object.
 *
 * @b Assert:
 *      - Test if the operator returns correct pointer.
 */
TEST_F(lib_UniquePointerTest, operator_arrow)
{
    int32_t const value(0x5A5AA5A5);
    UniquePointer<ManagedObject> const obj(new ManagedObject(value));
    ASSERT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj->getValue(), value) << "Fatal: Value in managed object is wrong";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test operator (*). 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object.
 *
 * @b Assert:
 *      - Test if the operator returns correct value.
 */
TEST_F(lib_UniquePointerTest, operator_star)
{
    int32_t const value(0x7E63ABCD);
    UniquePointer<ManagedObject> const obj(new ManagedObject(value));
    ASSERT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";    
    EXPECT_EQ((*obj).getValue(), value) << "Fatal: Value in managed object is wrong";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test cast operator to bool type. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *
 * @b Assert:
 *      - Test if the operator returns correct value.
 */
TEST_F(lib_UniquePointerTest, operator_bool)
{
    UniquePointer<ManagedObject> const obj1(new ManagedObject());
    EXPECT_TRUE( obj1 ) << "Fatal: Object stores NULLPTR";
    UniquePointer<ManagedObject> const obj2;
    EXPECT_FALSE( obj2 ) << "Fatal: Object doesn't store NULLPTR";
    UniquePointer<ManagedObject> const obj3(NULLPTR);
    EXPECT_FALSE( obj3 ) << "Fatal: Object doesn't store NULLPTR";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test operator ([]) and array managment. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object to manage an array.
 *
 * @b Assert:
 *      - Test if the operator [] returns correct values.
 */
TEST_F(lib_UniquePointerTest, operator_squareBrackets)
{
    int32_t* const arr = new int32_t[3]{1,2,3};
    UniquePointer< int32_t,SmartPointerDeleterArray<int32_t> > const obj(arr);
    ASSERT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj[0], arr[0]) << "Fatal: Wrong value of element 0";
    EXPECT_EQ(obj[1], arr[1]) << "Fatal: Wrong value of element 1";
    EXPECT_EQ(obj[2], arr[2]) << "Fatal: Wrong value of element 2";    
    obj[0] = 111;
    obj[1] = 222;
    obj[2] = 333;    
    EXPECT_EQ(obj[0], arr[0]) << "Fatal: Wrong value of element 0";
    EXPECT_EQ(obj[1], arr[1]) << "Fatal: Wrong value of element 1";
    EXPECT_EQ(obj[2], arr[2]) << "Fatal: Wrong value of element 2";        
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test operator equal. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *
 * @b Assert:
 *      - Test if the operator returns correct value.
 */
TEST_F(lib_UniquePointerTest, operator_equal)
{
    UniquePointer<ManagedObject> const obj1(new ManagedObject());
    UniquePointer<ManagedObject> const obj2(new ManagedObject());
    UniquePointer<ManagedObject> const obj3;    
    EXPECT_FALSE( obj1 == obj2 ) << "Fatal: Objects equal each other";
    EXPECT_FALSE( obj1 == obj3 ) << "Fatal: Objects equal each other";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test operator equal. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *
 * @b Assert:
 *      - Test if the operator returns correct value.
 */
TEST_F(lib_UniquePointerTest, operator_unequal)
{
    UniquePointer<ManagedObject> const obj1(new ManagedObject());
    UniquePointer<ManagedObject> const obj2(new ManagedObject());
    UniquePointer<ManagedObject> const obj3;
    EXPECT_TRUE( obj1 != obj2 ) << "Fatal: Objects equal each other";
    EXPECT_TRUE( obj1 != obj3 ) << "Fatal: Objects equal each other";
}

/**
 * @relates lib_UniquePointerTest
 * @brief Test SmartPointer interface. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct objects.
 *
 * @b Assert:
 *      - Test if return values are correct.
 */
TEST_F(lib_UniquePointerTest, smartPointer)
{
    ManagedObject* const ptr(new ManagedObject());    
    UniquePointer<ManagedObject> obj(ptr);
    api::SmartPointer<ManagedObject>& smrt(obj);
    EXPECT_TRUE(smrt.isConstructed()) << "Fatal: Object is not constructed";
    EXPECT_EQ(smrt.get(), ptr) << "Fatal: Unique pointer does not equal to its raw pointer";
    EXPECT_EQ(smrt.getCount(), 1) << "Fatal: Amount of unique objects managing object is wrong";
    EXPECT_FALSE(smrt.isNull()) << "Fatal: Unique pointer is null";    
}

} // namespace lib
} // namespace eoos

#endif // EOOS_GLOBAL_ENABLE_NO_HEAP
