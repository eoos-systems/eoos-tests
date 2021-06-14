/**
 * @file      lib.test.SharedPtr.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
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
namespace test
{

class test_lib_SharedPtr : public ::testing::Test
{

protected:
    
    System eoos;    
};    
    
namespace
{
    
class NullAllocator
{

public:

    static void* allocate(size_t)
    {
        return NULL;
    }

    static void free(void* ptr)
    {
    }

};    
    
class ManagedObject : public Object<>
{

public:

    ManagedObject()
    {
    }
    
    ManagedObject(int32_t const value) :
        value_ (value){
    }
    
    ManagedObject(bool_t* const isDeleted) :
        isDeleted_ (isDeleted){
    }        

    virtual ~ManagedObject()
    {
        value_ = -1;
        if(isDeleted_ != NULLPTR)
        {
            *isDeleted_ = true;
        }
    }
    
    int32_t getValue() const
    {
        return value_;
    }
    
private:

    int32_t value_     {0};
    bool_t* isDeleted_ {NULLPTR};
};

SharedPtr<ManagedObject> createObject()
{
    SharedPtr<ManagedObject> const obj {new ManagedObject()};
    return obj;
}

template <typename T>
class TestSharedPtr : public SharedPtr<T>
{
    using Parent = SharedPtr<T>;
    
public:

    explicit TestSharedPtr(T* const pointer) : Parent(pointer)
    {
    }

    void setConstructed(bool_t const flag)
    {
        Parent::setConstructed(flag);
    }    
};

} // namespace

TEST_F(test_lib_SharedPtr, Constructor)
{
    SharedPtr<ManagedObject> const obj {NULLPTR};
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not conctructed";    
    EXPECT_EQ(obj.get(), NULLPTR)        << "Error: Shared pointer does not equal to NULLPTR";
}

TEST_F(test_lib_SharedPtr, Constructor_pointer)
{
    ManagedObject* const ptr {new ManagedObject()};
    SharedPtr<ManagedObject> const obj {ptr};
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not conctructed";
    EXPECT_EQ(obj.get(), ptr)            << "Error: Shared pointer does not equal to its raw pointer";
}

TEST_F(test_lib_SharedPtr, CopyConstructor)
{
    SharedPtr<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_TRUE(obj1.isConstructed())       << "Error: Object 1 is not conctructed";
    SharedPtr<ManagedObject> const obj2 { obj1 };
    EXPECT_TRUE(obj2.isConstructed())       << "Error: Object 2 is not conctructed";
    EXPECT_EQ(obj1.get(), obj2.get())       << "Error: Both shared object don't point to the same managed object";
}

TEST_F(test_lib_SharedPtr, MoveConstructor)
{
    // Test if compiler moves an obj to obj1
    SharedPtr<ManagedObject> obj1 { createObject() };
    EXPECT_TRUE(obj1.isConstructed())   << "Error: An object is not moved to object 1 by compiler";
    // Test if cast moves obj1 to obj2
    SharedPtr<ManagedObject> const obj2 { lib::move(obj1) };
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 1 is not move casted to object 2";
    EXPECT_FALSE(obj1.isConstructed())  << "Error: Object 1 is conctructed after movement to object 2";
}

TEST_F(test_lib_SharedPtr, CopyAssignment)
{
    SharedPtr<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_TRUE(obj1.isConstructed())   << "Error: Object 1 is not conctructed";
    
    SharedPtr<ManagedObject> obj2 {};
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 2 is not conctructed";
    obj2 = obj1;
    EXPECT_TRUE(obj2.isConstructed())   << "Error: Object 2 is not assigned with object 1";    
    EXPECT_EQ(obj1.get(), obj2.get())   << "Error: Both shared object don't point to the same managed object";
    
    SharedPtr<ManagedObject> obj3 {new ManagedObject()};
    EXPECT_TRUE(obj3.isConstructed())   << "Error: Object 3 is not conctructed";
    obj3 = obj1;
    EXPECT_TRUE(obj3.isConstructed())   << "Error: Object 3 is not assigned with object 1";    
    EXPECT_EQ(obj1.get(), obj3.get())   << "Error: Both shared object don't point to the same managed object";

}

TEST_F(test_lib_SharedPtr, MoveAssignment)
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

TEST_F(test_lib_SharedPtr, isConstructed)
{
    SharedPtr<ManagedObject> const obj {new ManagedObject()};
    EXPECT_TRUE(obj.isConstructed())     << "Error: Object is not conctructed";
}

TEST_F(test_lib_SharedPtr, setConstructed)
{
    TestSharedPtr<ManagedObject> obj{new ManagedObject()};
    EXPECT_TRUE(obj.isConstructed())    << "Error: Object is not conctructed";
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed())    << "Error: Object is not set as conctructed";
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed())   << "Error: Object is not set as unconctructed";
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed())   << "Error: Object is set as conctructed if it is unconctructed";
}

TEST_F(test_lib_SharedPtr, isNotConstructed)
{
    using SharedPtr = SharedPtr<ManagedObject,SharedPtrDeleter<ManagedObject>,NullAllocator>;
    bool_t isDeleted {false};
    SharedPtr const obj1 {new ManagedObject(&isDeleted)};
    EXPECT_FALSE(obj1.isConstructed())  << "Error: Object is conctructed";
    EXPECT_EQ(obj1.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_TRUE(isDeleted)              << "Error: Managed object was not deleted";
    
    SharedPtr obj2 {obj1};
    EXPECT_FALSE(obj2.isConstructed())  << "Error: Object is conctructed";
    EXPECT_EQ(obj1.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj2.getCount(), 0)       << "Error: Number of shared objects is wrong";

    SharedPtr obj3 {};
    obj3 = obj1;
    EXPECT_FALSE(obj3.isConstructed())  << "Error: Object is conctructed";
    EXPECT_EQ(obj1.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj2.getCount(), 0)       << "Error: Number of shared objects is wrong";
    EXPECT_EQ(obj3.getCount(), 0)       << "Error: Number of shared objects is wrong";
}

TEST_F(test_lib_SharedPtr, get)
{
    int32_t const value = 0x12345678;
    ManagedObject* const ptr {new ManagedObject(value)};
    SharedPtr<ManagedObject> obj1 {ptr};
    ASSERT_TRUE(obj1.isConstructed())        << "Error: Object is not conctructed";
    EXPECT_EQ(obj1.get(), ptr)               << "Error: Shared pointer does not equal to its raw pointer";
    EXPECT_EQ(obj1.get()->getValue(), value) << "Error: Value in managed object is wrong";
    SharedPtr<ManagedObject> obj2 {};
    ASSERT_TRUE(obj2.isConstructed())        << "Error: Object is not conctructed";    
    EXPECT_EQ(obj2.get(), NULLPTR)           << "Error: Shared pointer does not equal to its raw pointer";
    SharedPtr<ManagedObject> obj3 {NULLPTR};
    ASSERT_TRUE(obj3.isConstructed())        << "Error: Object is not conctructed";
    EXPECT_EQ(obj3.get(), NULLPTR)           << "Error: Shared pointer does not equal to its raw pointer";    
}

TEST_F(test_lib_SharedPtr, getCount)
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

TEST_F(test_lib_SharedPtr, operator_arrow)
{
    int32_t const value = 0x5A5AA5A5;
    SharedPtr<ManagedObject> const obj {new ManagedObject(value)};
    ASSERT_TRUE(obj.isConstructed())  << "Error: Object is not conctructed";
    EXPECT_EQ(obj->getValue(), value) << "Error: Value in managed object is wrong";
}

TEST_F(test_lib_SharedPtr, operator_star)
{
    int32_t const value = 0xE763ABCD;
    SharedPtr<ManagedObject> const obj {new ManagedObject(value)};
    ASSERT_TRUE(obj.isConstructed())    << "Error: Object is not conctructed";    
    EXPECT_EQ((*obj).getValue(), value) << "Error: Value in managed object is wrong";
}

TEST_F(test_lib_SharedPtr, operator_bool)
{
    SharedPtr<ManagedObject> const obj1 {new ManagedObject()};
    EXPECT_TRUE( obj1 )  << "Error: Object stores NULLPTR";
    SharedPtr<ManagedObject> const obj2 {};
    EXPECT_FALSE( obj2 ) << "Error: Object doesn't store NULLPTR";
    SharedPtr<ManagedObject> const obj3 {NULLPTR};
    EXPECT_FALSE( obj3 ) << "Error: Object doesn't store NULLPTR";
}

TEST_F(test_lib_SharedPtr, operator_square_brackets)
{
    int32_t* const arr = new int32_t[3]{1,2,3};
    SharedPtr< int32_t,SharedPtrDeleterArray<int32_t> > const obj {arr};
    ASSERT_TRUE(obj.isConstructed()) << "Error: Object is not conctructed";
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

} // namespace test
} // namespace lib
} // namespace eoos

#endif // EOOS_NO_STRICT_MISRA_RULES
