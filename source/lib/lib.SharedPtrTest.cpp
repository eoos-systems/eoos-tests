/**
 * @file      lib.SharedPtrTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020-2021, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::SharedPtr`. 
 */
#include "System.hpp"
#include "lib.SharedPtr.hpp"

#ifdef EOOS_NO_STRICT_MISRA_RULES

namespace eoos
{
namespace lib
{

/**
 * @class SharedPtrTest
 * @test SharedPtr
 * @brief Tests SharedPtr class functionality.
 */
class SharedPtrTest : public ::testing::Test
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
 * @class ManagedObject
 * @brief Object managed by SharedPtr objects.
 */
class ManagedObject : public Object<>
{

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
    ManagedObject(int32_t const value) :
        value_ (value){
    }

    /**
     * @brief Constructor.
     *
     * @param isDeleted Flag will be set on destructor call.
     */
    ManagedObject(bool_t* const isDeleted) :
        isDeleted_ (isDeleted){
    }        

    /**
     * @brief Destructor.
     */
    ~ManagedObject() override
    {
        value_ = -1;
        if(isDeleted_ != NULLPTR)
        {
            *isDeleted_ = true;
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

    int32_t value_     {0};
    bool_t* isDeleted_ {NULLPTR};
};

/**
 * @brief Creates SharedPtr for ManagedObject.
 *
 * @return Created object by rvalue.
 */        
SharedPtr<ManagedObject> createObject()
{
    SharedPtr<ManagedObject> const obj {new ManagedObject()};
    return obj;
}

/**
 * @class TestSharedPtr<T>
 * @brief Test class with public members that are protected in the SharedPtr class.
 */
template <typename T>
class TestSharedPtr : public SharedPtr<T>
{
    using Parent = SharedPtr<T>;
    
public:

    /**
     * @copydoc eoos::SharedPtr::SharedPtr(T*)
     */
    explicit TestSharedPtr(T* const pointer) : Parent(pointer)
    {
    }

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
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, Constructor_nullptr)
{
    SharedPtr<ManagedObject> const obj {NULLPTR};
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not constructed";    
    EXPECT_EQ(obj.get(), NULLPTR)        << "Error: Shared pointer does not equal to NULLPTR";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, Constructor_pointer)
{
    ManagedObject* const ptr {new ManagedObject()};
    SharedPtr<ManagedObject> const obj {ptr};
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not constructed";
    EXPECT_EQ(obj.get(), ptr)            << "Error: Shared pointer does not equal to its raw pointer";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, CopyConstructor)
{
    SharedPtr<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_TRUE(obj1.isConstructed())       << "Error: Object 1 is not constructed";
    SharedPtr<ManagedObject> const obj2 { obj1 };
    EXPECT_TRUE(obj2.isConstructed())       << "Error: Object 2 is not constructed";
    EXPECT_EQ(obj1.get(), obj2.get())       << "Error: Both shared object don't point to the same managed object";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, CopyAssignment)
{
    SharedPtr<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_TRUE(obj1.isConstructed())   << "Error: Object 1 is not constructed";
    
    SharedPtr<ManagedObject> obj2 {};
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 2 is not constructed";
    obj2 = obj1;
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 2 is not assigned with object 1";    
    EXPECT_EQ(obj1.get(), obj2.get())   << "Error: Both shared object don't point to the same managed object";
    
    SharedPtr<ManagedObject> obj3 {new ManagedObject()};
    EXPECT_TRUE(obj3.isConstructed())   << "Error: Object 3 is not constructed";
    obj3 = obj1;
    EXPECT_TRUE(obj3.isConstructed())   << "Error: Object 3 is not assigned with object 1";    
    EXPECT_EQ(obj1.get(), obj3.get())   << "Error: Both shared object don't point to the same managed object";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, MoveConstructor)
{
    // Test if compiler moves an obj to obj1
    SharedPtr<ManagedObject> obj1 { createObject() };
    EXPECT_TRUE(obj1.isConstructed())   << "Error: An object is not moved to object 1 by compiler";
    // Test if cast moves obj1 to obj2
    SharedPtr<ManagedObject> const obj2 { lib::move(obj1) };
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 1 is not move casted to object 2";
    EXPECT_FALSE(obj1.isConstructed())  << "Error: Object 1 is constructed after movement to object 2";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, MoveAssignment)
{
    SharedPtr<ManagedObject> obj1 {new ManagedObject()};
    SharedPtr<ManagedObject> obj2 {new ManagedObject()};
    // Test if an obj moved to rvalue, and the rvalue assigned to obj1
    obj1 = createObject();
    EXPECT_TRUE(obj1.isConstructed())   << "Error: An object is not moved to rvalue, and the rvalue is not assigned to object 1";
    // Test if obj1 moved with lvalue to obj2
    obj2 = lib::move(obj1);  
    EXPECT_TRUE(obj2.isConstructed())   << "Error: An object 2 is not constructed with lvalue";
    EXPECT_FALSE(obj1.isConstructed())  << "Error: An object 1 is constructed but it was moved with lvalue";
    // Test if an obj1 cannot be recovered
    obj1 = lib::move(SharedPtr<ManagedObject>());
    EXPECT_FALSE(obj1.isConstructed())   << "Error: An object 1 is re-constructed but it was moved"; 
    // Test if an obj moved with rvalue to obj1
    obj2 = lib::move(SharedPtr<ManagedObject>());
    EXPECT_TRUE(obj2.isConstructed())   << "Error: An object 2 is not constructed with rvalue of a moved object";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, isConstructed)
{
    SharedPtr<ManagedObject> const obj {new ManagedObject()};
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not constructed";
    obj.~SharedPtr();
    EXPECT_FALSE(obj.isConstructed()) << "Error: Object is constructed after destruction";    
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, setConstructed)
{
    TestSharedPtr<ManagedObject> obj{new ManagedObject()};
    EXPECT_TRUE(obj.isConstructed())    << "Error: Object is not constructed";
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed())    << "Error: Object is not set as constructed";
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed())   << "Error: Object is not set as unconstructed";
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed())   << "Error: Object is set as constructed if it is unconstructed";
}

/**
 * @relates SharedPtrTest
 * @brief Test if object is not constructed. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPtr with NullAllocator to create ControlBlock using it.
 *      - Allocate a new ManagedObject.
 *      - Copy and assign SharedPtr to others SharedPtrs
 *
 * @b Assert:
 *      - Test if ownership on ManagedObject is gotten.
 *      - Test if SharedPtrDeleter is called for ManagedObject and it is deleted.
 *      - Test of the others SharedPtrs did not get ownership on ManagedObject.
 */
TEST_F(SharedPtrTest, isNotConstructed)
{
    using SharedPtr = SharedPtr<ManagedObject,SharedPtrDeleter<ManagedObject>,NullAllocator>;
    bool_t isDeleted {false};
    SharedPtr const obj1 {new ManagedObject(&isDeleted)};
    EXPECT_FALSE(obj1.isConstructed())  << "Error: Object is constructed";
    EXPECT_EQ(obj1.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_TRUE(isDeleted)              << "Error: Managed object was not deleted";
    
    SharedPtr obj2 {obj1};
    EXPECT_FALSE(obj2.isConstructed())  << "Error: Object is constructed";
    EXPECT_EQ(obj1.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj2.getCount(), 0)       << "Error: Number of shared objects is wrong";

    SharedPtr obj3 {};
    obj3 = obj1;
    EXPECT_FALSE(obj3.isConstructed())  << "Error: Object is constructed";
    EXPECT_EQ(obj1.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj2.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj3.getCount(), 0)       << "Error: Number of shared objects is wrong";
}

/**
 * @relates SharedPtrTest
 * @brief Test stored pointer.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPtr objects.
 *
 * @b Assert:
 *      - Test if the stored pointes have correct values.
 */
TEST_F(SharedPtrTest, get)
{
    int32_t const value = 0x12345678;
    ManagedObject* const ptr {new ManagedObject(value)};
    SharedPtr<ManagedObject> obj1 {ptr};
    ASSERT_TRUE(obj1.isConstructed())        << "Error: Object is not constructed";
    EXPECT_EQ(obj1.get(), ptr)               << "Error: Shared pointer does not equal to its raw pointer";
    EXPECT_EQ(obj1.get()->getValue(), value) << "Error: Value in managed object is wrong";
    SharedPtr<ManagedObject> obj2 {};
    ASSERT_TRUE(obj2.isConstructed())        << "Error: Object is not constructed";    
    EXPECT_EQ(obj2.get(), NULLPTR)           << "Error: Shared pointer does not equal to its raw pointer";
    SharedPtr<ManagedObject> obj3 {NULLPTR};
    ASSERT_TRUE(obj3.isConstructed())        << "Error: Object is not constructed";
    EXPECT_EQ(obj3.get(), NULLPTR)           << "Error: Shared pointer does not equal to its raw pointer";    
}

/**
 * @relates SharedPtrTest
 * @brief Test counter of shared objects for the managed object. 
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Construct SharedPtr objects.
 *
 * @b Assert:
 *      - Test if counter is correct to number of shared pointers.
 */
TEST_F(SharedPtrTest, getCount)
{
    bool_t isDeleted1 {false};
    SharedPtr<ManagedObject>* obj1 { new SharedPtr<ManagedObject>(new ManagedObject(&isDeleted1)) };
    EXPECT_EQ(obj1->getCount(), 1)  << "Error: Number of shared objects is wrong";
    SharedPtr<ManagedObject>* obj2 { new SharedPtr<ManagedObject>(*obj1) };
    EXPECT_EQ(obj1->getCount(), 2)  << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj2->getCount(), 2)  << "Error: Number of shared objects is wrong";    
    delete obj2;
    EXPECT_FALSE(isDeleted1)        << "Error: Managed object was unexpectedly deleted";    
    EXPECT_EQ(obj1->getCount(), 1)  << "Error: Number of shared objects is wrong";
    delete obj1;
    EXPECT_TRUE(isDeleted1)         << "Error: Managed object was not deleted";  

    isDeleted1 = false;
    bool_t isDeleted2 {false};
    obj1 = new SharedPtr<ManagedObject>(new ManagedObject(&isDeleted1));
    EXPECT_EQ(obj1->getCount(), 1)  << "Error: Number of shared objects is wrong";
    obj2 = new SharedPtr<ManagedObject>(new ManagedObject(&isDeleted2));
    EXPECT_EQ(obj2->getCount(), 1)  << "Error: Number of shared objects is wrong";    
    *obj2 = *obj1;
    EXPECT_TRUE(isDeleted2)         << "Error: Managed object was not deleted";
    EXPECT_EQ(obj1->getCount(), 2)  << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj2->getCount(), 2)  << "Error: Number of shared objects is wrong";    
    delete obj2;
    EXPECT_FALSE(isDeleted1)        << "Error: Managed object was unexpectedly deleted";    
    EXPECT_EQ(obj1->getCount(), 1)  << "Error: Number of shared objects is wrong";
    delete obj1;
    EXPECT_TRUE(isDeleted1)         << "Error: Managed object was not deleted";  
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, operator_arrow)
{
    int32_t const value {0x5A5AA5A5};
    SharedPtr<ManagedObject> const obj {new ManagedObject(value)};
    ASSERT_TRUE(obj.isConstructed())  << "Error: Object is not constructed";
    EXPECT_EQ(obj->getValue(), value) << "Error: Value in managed object is wrong";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, operator_star)
{
    int32_t const value {0xE763ABCD};
    SharedPtr<ManagedObject> const obj {new ManagedObject(value)};
    ASSERT_TRUE(obj.isConstructed())    << "Error: Object is not constructed";    
    EXPECT_EQ((*obj).getValue(), value) << "Error: Value in managed object is wrong";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, operator_bool)
{
    SharedPtr<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_TRUE( obj1 )  << "Error: Object stores NULLPTR";
    SharedPtr<ManagedObject> const obj2 {};
    EXPECT_FALSE( obj2 ) << "Error: Object doesn't store NULLPTR";
    SharedPtr<ManagedObject> const obj3 {NULLPTR};
    EXPECT_FALSE( obj3 ) << "Error: Object doesn't store NULLPTR";
}

/**
 * @relates SharedPtrTest
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
TEST_F(SharedPtrTest, operator_square_brackets)
{
    int32_t* const arr = new int32_t[3]{1,2,3};
    SharedPtr< int32_t,SharedPtrDeleterArray<int32_t> > const obj {arr};
    ASSERT_TRUE(obj.isConstructed()) << "Error: Object is not constructed";
    EXPECT_EQ(obj[0], arr[0]) << "Error: Wrong value of element 0";
    EXPECT_EQ(obj[1], arr[1]) << "Error: Wrong value of element 1";
    EXPECT_EQ(obj[2], arr[2]) << "Error: Wrong value of element 2";    
    obj[0] = 111;
    obj[1] = 222;
    obj[2] = 333;    
    EXPECT_EQ(obj[0], arr[0]) << "Error: Wrong value of element 0";
    EXPECT_EQ(obj[1], arr[1]) << "Error: Wrong value of element 1";
    EXPECT_EQ(obj[2], arr[2]) << "Error: Wrong value of element 2";        
}

} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
