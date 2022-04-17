/**
 * @file      lib.SharedPointerTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::SharedPointer`. 
 */
#include "lib.SharedPointer.hpp"
#include "System.hpp"

#ifdef EOOS_NO_STRICT_MISRA_RULES

namespace eoos
{
namespace lib
{

/**
 * @class lib_SharedPointerTest
 * @test SharedPointer
 * @brief Tests SharedPointer class functionality.
 */
class lib_SharedPointerTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.
};    
    
namespace
{
    
/**
 * @class NullAllocator
 * @brief No memory allocator.
 */
class NullAllocator
{

public:

    /**
     * @brief Returns nullptr.
     *
     * @return the null pointer.
     */    
    static void* allocate(size_t)
    {
        return NULLPTR;
    }

    /**
     * @brief Does nothing.
     */    
    static void free(void*)
    {
    }

};    

/**
 * @struct ManagedAction
 * @brief Actions happened in ManagedObject.
 */
struct ManagedAction
{
    bool_t isDeleted {false};
};

/**
 * @class ManagedObject
 * @brief Object managed by SharedPointer objects.
 */
class ManagedObject : public Object<>
{

    typedef Object<> Parent;

public:

    /**
     * @brief Constructor.
     */
    ManagedObject() = default;

    /**
     * @brief Constructor.
     *
     * @param value A value to containt as member.
     */
    ManagedObject(int32_t const value) : Parent(),
        value_ (value){
    }

    /**
     * @brief Constructor.
     *
     * @param action Flags will be set on actions.
     */
    ManagedObject(ManagedAction* const action) : Parent(),
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
    ~ManagedObject() override
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

    int32_t value_ {0};
    ManagedAction* action_ {NULLPTR};
};

/**
 * @brief Creates SharedPointer for ManagedObject.
 *
 * @param value A value to containt as member.    
 * @param action Flags will be set on actions.
 * @return Created object by rvalue.
 */        
SharedPointer<ManagedObject> createObject(int32_t const value = 0, ManagedAction* const action = NULLPTR)
{
    SharedPointer<ManagedObject> const obj {new ManagedObject(value, action)};
    return obj;
}

/**
 * @class TestSharedPointer<T>
 * @brief Test class with public members that are protected in the SharedPointer class.
 */
template <typename T>
class TestSharedPointer : public SharedPointer<T>
{
    using Parent = SharedPointer<T>;
    
public:

    /**
     * @copydoc eoos::SharedPointer::SharedPointer(T*)
     */
    explicit TestSharedPointer(T* const pointer) : Parent(pointer) {}

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
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, Constructor_nullptr)
{
    SharedPointer<ManagedObject> const obj {NULLPTR};
    EXPECT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";    
    EXPECT_EQ(obj.get(), NULLPTR) << "Fatal: Shared pointer does not equal to NULLPTR";
}

/**
 * @relates lib_SharedPointerTest
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
 *      - Test the raw pointer equal to shared pointer.
 */
TEST_F(lib_SharedPointerTest, Constructor_pointer)
{
    const int32_t VALUE {1};
    ManagedObject* const ptr {new ManagedObject(VALUE)};
    SharedPointer<ManagedObject> const obj {ptr};
    EXPECT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    ASSERT_EQ(obj.get(), ptr) << "Fatal: Shared pointer does not equal to its raw pointer";
    EXPECT_EQ(obj->getValue(), VALUE) << "Fatal: Wrong value containing in managed object";
}

/**
 * @relates lib_SharedPointerTest
 * @brief Tests copy constructor.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class with user defined construct.
 *      - Consctuct an object of the class with copy construct. 
 *
 * @b Assert:
 *      - Test the objects are constructed.
 *      - Test the pointers equal each other.
 */
TEST_F(lib_SharedPointerTest, CopyConstructor)
{
    const int32_t VALUE1 {1};
    ManagedAction action1;
    SharedPointer<ManagedObject> const obj1 {new ManagedObject(VALUE1, &action1)};
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object 1 is not constructed";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";    
    SharedPointer<ManagedObject> const obj2 { obj1 };
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: Object 2 is not constructed";
    ASSERT_EQ(obj1.get(), obj2.get()) << "Fatal: Both shared object don't point to the same managed object";
    EXPECT_EQ(obj1.getCount(), 2) << "Fatal: Amount of shared objects managing object is wrong";    
    EXPECT_EQ(obj2.getCount(), 2) << "Fatal: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted)  << "Fatal: Managed object was deleted";
    
    SharedPointer<ManagedObject> obj3;
    EXPECT_TRUE(obj3.isConstructed()) << "Error: Object 2 is not constructed";
    EXPECT_EQ(obj3.get(), NULLPTR) << "Fatal: Shared pointer does not equal to null";
    EXPECT_EQ(obj3.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    SharedPointer<ManagedObject> obj4 {obj3};
    EXPECT_TRUE(obj4.isConstructed()) << "Error: Object 2 is not constructed";
    EXPECT_EQ(obj4.get(), NULLPTR) << "Fatal: Shared pointer does not equal to null";
    EXPECT_EQ(obj4.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj3.get(), NULLPTR) << "Fatal: Shared pointer does not equal to null";
    EXPECT_EQ(obj3.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test copy assignment.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct an object 1, 2, and 3.
 *      - Assign the object 1 to the object 2.
 *      - Assign the object 1 to the object 3. 
 *
 * @b Assert:
 *      - Test the objects are constructed.
 *      - Test the pointer are correct. 
 */
TEST_F(lib_SharedPointerTest, CopyAssignment)
{
    const int32_t VALUE1 {1};
    ManagedAction action1;
    SharedPointer<ManagedObject> const obj1 {new ManagedObject(VALUE1, &action1)};
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object 1 is not constructed";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";
    
    SharedPointer<ManagedObject> obj2;
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object 2 is not constructed";
    EXPECT_EQ(obj2.get(), NULLPTR) << "Fatal: Shared pointer does not equal to null";
    EXPECT_EQ(obj2.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    obj2 = obj1;
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: Object 2 is not assigned with object 1";    
    EXPECT_EQ(obj1.get(), obj2.get()) << "Fatal: Both shared object don't point to the same managed object";
    EXPECT_EQ(obj1.getCount(), 2) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2.getCount(), 2) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";    
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";    
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";
    
    const int32_t VALUE3 {3};
    ManagedAction action3;
    SharedPointer<ManagedObject> obj3 {new ManagedObject(VALUE3, &action3)};
    EXPECT_TRUE(obj3.isConstructed()) << "Error: Object 3 is not constructed";
    EXPECT_EQ(obj3->getValue(), VALUE3) << "Fatal: Wrong value containing in managed object";    
    obj3 = obj2;   
    EXPECT_TRUE(obj3.isConstructed()) << "Fatal: Object 3 is not assigned with object 1";    
    EXPECT_EQ(obj1.get(), obj3.get()) << "Fatal: Both shared object don't point to the same managed object";
    EXPECT_EQ(obj1.getCount(), 3) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2.getCount(), 3) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj3.getCount(), 3) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_EQ(obj3->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";    
    EXPECT_TRUE(action3.isDeleted) << "Fatal: Managed object was not deleted"; 
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";

    SharedPointer<ManagedObject> obj4;
    EXPECT_TRUE(obj4.isConstructed()) << "Error: Object 2 is not constructed";
    EXPECT_EQ(obj4.get(), NULLPTR) << "Fatal: Shared pointer does not equal to null";
    EXPECT_EQ(obj4.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    SharedPointer<ManagedObject> obj5;
    obj5 = obj4;
    EXPECT_TRUE(obj5.isConstructed()) << "Error: Object 2 is not constructed";
    EXPECT_EQ(obj5.get(), NULLPTR) << "Fatal: Shared pointer does not equal to null";
    EXPECT_EQ(obj5.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj4.get(), NULLPTR) << "Fatal: Shared pointer does not equal to null";
    EXPECT_EQ(obj4.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, MoveConstructor)
{
    // Test if compiler moves an obj to obj1
    const int32_t VALUE1 {1};
    ManagedAction action1;
    SharedPointer<ManagedObject> obj1 { createObject(VALUE1, &action1) };
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: object 1 is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: object 1 is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";
    // Test if cast moves obj1 to obj2
    ManagedObject* ptr1 = obj1.get();
    SharedPointer<ManagedObject> const obj2 { lib::move(obj1) };
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: Object 1 is not move casted to object 2";
    EXPECT_FALSE(obj2.isNull()) << "Error: object 2 is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: object 2 is not unique";
    EXPECT_EQ(obj2.get(), ptr1) << "Fatal: Shared pointer does not equal to expected value";        
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(obj1.isConstructed()) << "Fatal: Object 1 is constructed after movement to object 2";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, MoveAssignment)
{
    const int32_t VALUE1 {1};
    ManagedAction action1;
    SharedPointer<ManagedObject> obj1 {new ManagedObject(VALUE1, &action1)};
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was deleted";        
    // Test if an obj moved to rvalue, and the rvalue assigned to obj1
    const int32_t VALUE3 {3};       
    ManagedAction action3;    
    obj1 = createObject(VALUE3, &action3);
    EXPECT_TRUE(obj1.isConstructed()) << "Fatal: An object is not moved to rvalue, and the rvalue is not assigned to object 1";
    EXPECT_FALSE(obj1.isNull()) << "Error: object 1 is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: object 1 is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE3) << "Fatal: Wrong value containing in managed object";
    EXPECT_TRUE(action1.isDeleted) << "Fatal: Managed object was not deleted";
    EXPECT_FALSE(action3.isDeleted) << "Fatal: Managed object was deleted";    
    // Test if obj1 moved with lvalue to obj2
    const int32_t VALUE2 {2};    
    ManagedAction action2;    
    SharedPointer<ManagedObject> obj2 {new ManagedObject(VALUE2, &action2)};
    EXPECT_EQ(obj2->getValue(), VALUE2) << "Fatal: Wrong value containing in managed object";        
    obj2 = lib::move(obj1);
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: An object 2 is not constructed with lvalue";
    EXPECT_FALSE(obj2.isNull()) << "Error: object 2 is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: object 2 is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE3) << "Fatal: Wrong value containing in managed object";
    EXPECT_FALSE(obj1.isConstructed()) << "Fatal: An object 1 is constructed but it was moved with lvalue";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_TRUE(action2.isDeleted) << "Fatal: Managed object was not deleted";
    EXPECT_FALSE(action3.isDeleted) << "Fatal: Managed object was deleted";
    // Test if an obj1 cannot be recovered
    ManagedAction action4;    
    obj1 = lib::move(SharedPointer<ManagedObject>(new ManagedObject(&action4)));
    EXPECT_FALSE(obj1.isConstructed()) << "Fatal: An object 1 is re-constructed but it was moved";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_TRUE(action4.isDeleted) << "Fatal: Managed object was not deleted";    
    // Test if an obj moved with rvalue to obj2
    const int32_t VALUE5 {5};
    ManagedAction action5;
    obj2 = lib::move(SharedPointer<ManagedObject>(new ManagedObject(VALUE5, &action5)));
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: An object 2 is not constructed with rvalue of a moved object";
    EXPECT_FALSE(obj2.isNull()) << "Error: object 2 is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: object 2 is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";    
    EXPECT_EQ(obj2->getValue(), VALUE5) << "Fatal: Wrong value containing in managed object";
    EXPECT_TRUE(action3.isDeleted) << "Fatal: Managed object was not deleted";        
    EXPECT_FALSE(action5.isDeleted) << "Fatal: Managed object was deleted";    
    // Test if an obj moved with rvalue to obj2
    obj2 = lib::move(SharedPointer<ManagedObject>());
    EXPECT_TRUE(obj2.isConstructed()) << "Fatal: An object 2 is not constructed with rvalue of a moved object";
    EXPECT_TRUE(obj2.isNull()) << "Error: object 2 is not null";
    EXPECT_FALSE(obj2.isUnique()) << "Error: object 2 is unique";
    EXPECT_EQ(obj2.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_TRUE(action5.isDeleted) << "Fatal: Managed object was not deleted";    
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, isConstructed)
{
    SharedPointer<ManagedObject> const obj {new ManagedObject()};
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not constructed";
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, setConstructed)
{
    TestSharedPointer<ManagedObject> obj{new ManagedObject()};
    EXPECT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed()) << "Fatal: Object is not set as constructed";
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is not set as unconstructed";
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed()) << "Fatal: Object is set as constructed if it is unconstructed";
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test if object is not constructed. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPointer with NullAllocator to create ControlBlock using it.
 *      - Allocate a new ManagedObject.
 *      - Copy and assign SharedPointer to others SharedPointers
 *
 * @b Assert:
 *      - Test if ownership on ManagedObject is gotten.
 *      - Test if SharedPointerDeleter is called for ManagedObject and it is deleted.
 *      - Test of the others SharedPointers did not get ownership on ManagedObject.
 */
TEST_F(lib_SharedPointerTest, isNotConstructed)
{
    using SharedPointer = SharedPointer<ManagedObject,SharedPointerDeleter<ManagedObject>,NullAllocator>;
    ManagedAction action;
    SharedPointer const obj1 {new ManagedObject(&action)};
    EXPECT_FALSE(obj1.isConstructed()) << "Error: Object is constructed";
    EXPECT_EQ(obj1.getCount(), 0) << "Fatal: Amount of shared objects managing object is wrong";
    EXPECT_TRUE(action.isDeleted) << "Fatal: Managed object was not deleted";
    
    SharedPointer obj2 {obj1};
    EXPECT_FALSE(obj2.isConstructed()) << "Error: Object is constructed";
    EXPECT_EQ(obj1.getCount(), 0) << "Fatal: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2.getCount(), 0) << "Fatal: Amount of shared objects managing object is wrong";

    SharedPointer obj3;
    obj3 = obj1;
    EXPECT_FALSE(obj3.isConstructed()) << "Error: Object is constructed";
    EXPECT_EQ(obj1.getCount(), 0) << "Fatal: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2.getCount(), 0) << "Fatal: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj3.getCount(), 0) << "Fatal: Amount of shared objects managing object is wrong";
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test stored pointer.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_SharedPointerTest, get)
{
    const int32_t VALUE {0x12345678};
    ManagedObject* const ptr {new ManagedObject(VALUE)};
    SharedPointer<ManagedObject> obj1 {ptr};
    ASSERT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj1.get(), ptr) << "Fatal: Shared pointer does not equal to its raw pointer";
    EXPECT_EQ(obj1.get()->getValue(), VALUE) << "Fatal: Value in managed object is wrong";
    SharedPointer<ManagedObject> obj2;
    ASSERT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";    
    EXPECT_EQ(obj2.get(), NULLPTR) << "Fatal: Shared pointer does not equal to its raw pointer";
    SharedPointer<ManagedObject> obj3 {NULLPTR};
    ASSERT_TRUE(obj3.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj3.get(), NULLPTR) << "Fatal: Shared pointer does not equal to its raw pointer";    
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test stored pointer is reset.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_SharedPointerTest, reset)
{
    const int32_t VALUE1 {1};
    ManagedAction action1;
    SharedPointer<ManagedObject> obj1 {new ManagedObject(VALUE1, &action1)};
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: object 1 is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: object 1 is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    obj1.reset();
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_TRUE(obj1.isNull()) << "Error: object 1 is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: object 1 is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_TRUE(action1.isDeleted) << "Error: Managed object was not deleted";
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test stored pointer is reset.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_SharedPointerTest, reset_withOther)
{
    const int32_t VALUE1 {1};
    ManagedAction action1;
    SharedPointer<ManagedObject> obj1 {new ManagedObject(VALUE1, &action1)};
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    
    SharedPointer<ManagedObject> obj2 {obj1};        
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_FALSE(obj2.isUnique()) << "Error: Object is unique";
    EXPECT_EQ(obj2.getCount(), 2) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";

    const int32_t VALUE2 {2};
    ManagedAction action2;
    obj1.reset(new ManagedObject(VALUE2, &action2));
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE2) << "Error: Wrong value containing in managed object";    
    EXPECT_FALSE(action2.isDeleted) << "Error: Managed object was deleted";

    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";

    const int32_t VALUE3 {2};
    ManagedAction action3;
    obj2.reset(new ManagedObject(VALUE3, &action3));
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE3) << "Error: Wrong value containing in managed object";
    EXPECT_TRUE(action1.isDeleted) << "Error: Managed object was not deleted";
    EXPECT_FALSE(action3.isDeleted) << "Error: Managed object was not deleted";    
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test stored pointer is swap.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPointer objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(lib_SharedPointerTest, swap)
{
    const int32_t VALUE1 {1};
    ManagedAction action1;
    ManagedObject* ptr1 {new ManagedObject(VALUE1, &action1)};
    SharedPointer<ManagedObject> obj1 {ptr1};
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";

    const int32_t VALUE2 {2};
    ManagedAction action2;
    ManagedObject* ptr2 {new ManagedObject(VALUE2, &action2)};    
    SharedPointer<ManagedObject> obj2 {ptr2};
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE2) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action2.isDeleted) << "Error: Managed object was deleted";
    
    obj1.swap(obj2);

    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.get(), ptr2) << "Fatal: Shared pointer does not equal to expected value";
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE2) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action2.isDeleted) << "Error: Managed object was deleted";
    
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.get(), ptr1) << "Fatal: Shared pointer does not equal to expected value";    
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    
    obj1.reset();
    
    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_TRUE(obj1.isNull()) << "Error: Object is not null";
    EXPECT_FALSE(obj1.isUnique()) << "Error: Object is unique";
    EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_TRUE(action2.isDeleted) << "Error: Managed object was deleted";
    
    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj2.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj2.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj2.get(), ptr1) << "Fatal: Shared pointer does not equal to expected value";        
    EXPECT_EQ(obj2.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj2->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";
    
    obj1.swap(obj2);    

    EXPECT_TRUE(obj1.isConstructed()) << "Error: Object is not constructed";
    EXPECT_FALSE(obj1.isNull()) << "Error: Object is null";
    EXPECT_TRUE(obj1.isUnique()) << "Error: Object is not unique";
    EXPECT_EQ(obj1.get(), ptr1) << "Fatal: Shared pointer does not equal to expected value";        
    EXPECT_EQ(obj1.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
    EXPECT_EQ(obj1->getValue(), VALUE1) << "Error: Wrong value containing in managed object";
    EXPECT_FALSE(action1.isDeleted) << "Error: Managed object was deleted";

    EXPECT_TRUE(obj2.isConstructed()) << "Error: Object is not constructed";
    EXPECT_TRUE(obj2.isNull()) << "Error: Object is not null";
    EXPECT_FALSE(obj2.isUnique()) << "Error: Object is unique";
    EXPECT_EQ(obj2.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test counter of shared objects for the managed object. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPointer objects.
 *
 * @b Assert:
 *      - Test if counter is correct to number of shared pointers.
 */
TEST_F(lib_SharedPointerTest, getCount)
{
    {
        SharedPointer<ManagedObject> obj1;
        EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
        SharedPointer<ManagedObject> obj2 { obj1 };
        EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj2.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
        SharedPointer<ManagedObject> obj3;
        EXPECT_EQ(obj1.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj2.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj3.getCount(), 0) << "Error: Amount of shared objects managing object is wrong";
        SharedPointer<ManagedObject> obj4 {new ManagedObject()};
        EXPECT_EQ(obj4.getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
        obj3 = obj4;
        EXPECT_EQ(obj4.getCount(), 2) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj3.getCount(), 2) << "Error: Amount of shared objects managing object is wrong";
        obj2 = obj3;
        EXPECT_EQ(obj4.getCount(), 3) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj3.getCount(), 3) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj2.getCount(), 3) << "Error: Amount of shared objects managing object is wrong";
        obj1 = obj2;
        EXPECT_EQ(obj4.getCount(), 4) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj3.getCount(), 4) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj2.getCount(), 4) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj2.getCount(), 4) << "Error: Amount of shared objects managing object is wrong";        
    }
    {
        ManagedAction action1;
        SharedPointer<ManagedObject>* obj1 { new SharedPointer<ManagedObject>(new ManagedObject(&action1)) };
        EXPECT_EQ(obj1->getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
        SharedPointer<ManagedObject>* obj2 { new SharedPointer<ManagedObject>(*obj1) };
        EXPECT_EQ(obj1->getCount(), 2) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj2->getCount(), 2) << "Error: Amount of shared objects managing object is wrong";    
        delete obj2;
        EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was unexpectedly deleted";    
        EXPECT_EQ(obj1->getCount(), 1) << "Fatal: Amount of shared objects managing object is wrong";
        delete obj1;
        EXPECT_TRUE(action1.isDeleted) << "Fatal: Managed object was not deleted";  
    }
    {
        ManagedAction action1;
        ManagedAction action2;        
        SharedPointer<ManagedObject>* obj1 { new SharedPointer<ManagedObject>(new ManagedObject(&action1)) };
        EXPECT_EQ(obj1->getCount(), 1) << "Error: Amount of shared objects managing object is wrong";
        SharedPointer<ManagedObject>* obj2 { new SharedPointer<ManagedObject>(new ManagedObject(&action2)) };
        EXPECT_EQ(obj2->getCount(), 1) << "Error: Amount of shared objects managing object is wrong";    
        *obj2 = *obj1;
        EXPECT_TRUE(action2.isDeleted) << "Error: Managed object was not deleted";
        EXPECT_EQ(obj1->getCount(), 2) << "Error: Amount of shared objects managing object is wrong";
        EXPECT_EQ(obj2->getCount(), 2) << "Error: Amount of shared objects managing object is wrong";    
        delete obj2;
        EXPECT_FALSE(action1.isDeleted) << "Fatal: Managed object was unexpectedly deleted";    
        EXPECT_EQ(obj1->getCount(), 1) << "Fatal: Amount of shared objects managing object is wrong";
        delete obj1;
        EXPECT_TRUE(action1.isDeleted) << "Fatal: Managed object was not deleted";  
    }
}

/**
 * @relates lib_SharedPointerTest
 * @brief Test if shared pointer manages an object. 
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
TEST_F(lib_SharedPointerTest, isNull)
{
    SharedPointer<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_FALSE( obj1.isNull() ) << "Fatal: Object stores NULLPTR";
    SharedPointer<ManagedObject> const obj2;
    EXPECT_TRUE( obj2.isNull() ) << "Fatal: Object doesn't store NULLPTR";
    SharedPointer<ManagedObject> const obj3 {NULLPTR};
    EXPECT_TRUE( obj3.isNull() ) << "Fatal: Object doesn't store NULLPTR";
}

/**
 * @relates lib_SharedPointerTest
 * @relates lib_SharedPointerTest
 * @brief Tests if shared pointer is only one manages an object 
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
TEST_F(lib_SharedPointerTest, isUnique)
{
    SharedPointer<ManagedObject> obj1;
    EXPECT_FALSE( obj1.isUnique() ) << "Fatal: Object is unique";
    SharedPointer<ManagedObject> const obj2 {new ManagedObject()};
    EXPECT_TRUE( obj2.isUnique() ) << "Fatal: Object is not unique";
    obj1 = obj2;
    EXPECT_FALSE( obj1.isUnique() ) << "Fatal: Object is unique";
    EXPECT_FALSE( obj2.isUnique() ) << "Fatal: Object is unique";    
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, operator_arrow)
{
    int32_t const value {0x5A5AA5A5};
    SharedPointer<ManagedObject> const obj {new ManagedObject(value)};
    ASSERT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj->getValue(), value) << "Fatal: Value in managed object is wrong";
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, operator_star)
{
    int32_t const value {0x7E63ABCD};
    SharedPointer<ManagedObject> const obj {new ManagedObject(value)};
    ASSERT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";    
    EXPECT_EQ((*obj).getValue(), value) << "Fatal: Value in managed object is wrong";
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, operator_bool)
{
    SharedPointer<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_TRUE( obj1 ) << "Fatal: Object stores NULLPTR";
    SharedPointer<ManagedObject> const obj2;
    EXPECT_FALSE( obj2 ) << "Fatal: Object doesn't store NULLPTR";
    SharedPointer<ManagedObject> const obj3 {NULLPTR};
    EXPECT_FALSE( obj3 ) << "Fatal: Object doesn't store NULLPTR";
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, operator_squareBrackets)
{
    int32_t* const arr = new int32_t[3]{1,2,3};
    SharedPointer< int32_t,SharedPointerDeleterArray<int32_t> > const obj {arr};
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
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, smartPointer)
{
    ManagedObject* const ptr {new ManagedObject()};    
    SharedPointer<ManagedObject> obj {ptr};
    api::SmartPointer<ManagedObject>& smrt {obj};
    EXPECT_TRUE(smrt.isConstructed()) << "Fatal: Object is not constructed";
    EXPECT_EQ(smrt.get(), ptr) << "Fatal: Shared pointer does not equal to its raw pointer";
    EXPECT_EQ(smrt.getCount(), 1) << "Fatal: Amount of shared objects managing object is wrong";
    EXPECT_FALSE(smrt.isNull()) << "Fatal: Shared pointer is null";    
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, operator_equal)
{
    ManagedObject* ptr {new ManagedObject()};
    SharedPointer<ManagedObject> const obj1 {ptr};
    SharedPointer<ManagedObject> const obj2 {new ManagedObject()};
    SharedPointer<ManagedObject> const obj3 {ptr};    
    EXPECT_FALSE( obj1 == obj2 ) << "Fatal: Objects equal each other";
    EXPECT_TRUE( obj1 == obj3 ) << "Fatal: Objects don't equal each other";
}

/**
 * @relates lib_SharedPointerTest
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
TEST_F(lib_SharedPointerTest, operator_unequal)
{
    ManagedObject* ptr {new ManagedObject()};
    SharedPointer<ManagedObject> const obj1 {ptr};
    SharedPointer<ManagedObject> const obj2 {new ManagedObject()};
    SharedPointer<ManagedObject> const obj3 {ptr};    
    EXPECT_TRUE( obj1 != obj2 ) << "Fatal: Objects equal each other";
    EXPECT_FALSE( obj1 != obj3 ) << "Fatal: Objects don't equal each other";
}

} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
