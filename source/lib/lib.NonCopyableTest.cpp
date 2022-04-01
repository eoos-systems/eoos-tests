/**
 * @file      lib.NonCopyableTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::NonCopyable`.
 */
#include "lib.NonCopyable.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_NonCopyableTest
 * @test NonCopyable
 * @brief Tests root NonCopyable class functionality.
 */
class lib_NonCopyableTest : public ::testing::Test
{

private:
    
    System eoos_; ///< EOOS Operating System.
};    
    
namespace 
{

/**
 * @class TestNonCopyable
 *
 * @brief Class to provide protect functions to public scope.
 */
class TestNonCopyable : public NonCopyable<>
{
    using Parent = NonCopyable<>;

public:

    /**
     * @copydoc eoos::NonCopyable::setConstructed(bool_t)
     */
    void setConstructed(bool_t const flag)
    {
        Parent::setConstructed(flag);
    }    
};

} // namespace

/**
 * @relates lib_NonCopyableTest
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
TEST_F(lib_NonCopyableTest, Constructor)
{
    NonCopyable<> const obj {};
    EXPECT_TRUE(obj.isConstructed())        << "Error: NonCopyable is not constructed";    
}

/**
 * @relates lib_NonCopyableTest
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
TEST_F(lib_NonCopyableTest, MemoryAllocation)
{
    NonCopyable<>* obj {new NonCopyable<>()};
    ASSERT_NE(obj, NULLPTR)             << "Error: NonCopyable is not allocated";
    EXPECT_TRUE(obj->isConstructed())   << "Error: NonCopyable is not constructed, but allocated";
    delete obj;
    obj = NULLPTR;
    TestNonCopyable mem{};
    mem.setConstructed(false);
    EXPECT_FALSE(mem.isConstructed())   << "Error: Some memory is not ready to be used";
    obj = new (&mem) NonCopyable<>();
    EXPECT_NE(obj, NULLPTR)             << "Error: NonCopyable is not put on memory";
    EXPECT_TRUE(obj->isConstructed())   << "Error: NonCopyable is not constructed, but put on memory";
}

/**
 * @relates lib_NonCopyableTest
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
TEST_F(lib_NonCopyableTest, isConstructed)
{
    NonCopyable<> const obj{};
    EXPECT_TRUE(obj.isConstructed())  << "Error: NonCopyable is not constructed";
    obj.~NonCopyable();
    EXPECT_FALSE(obj.isConstructed()) << "Error: NonCopyable is constructed after destruction";
}

/**
 * @relates lib_NonCopyableTest
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
TEST_F(lib_NonCopyableTest, isConstructed_obj)
{
    NonCopyable<>* obj {new NonCopyable<>()};
    EXPECT_TRUE(NonCopyable<>::isConstructed(obj))   << "Error: NonCopyable is not constructed";
    delete obj;
    obj = NULLPTR;
    EXPECT_FALSE(NonCopyable<>::isConstructed(obj))  << "Error: Pointer to NULLPTR object is constructed";
}

/**
 * @relates lib_NonCopyableTest
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
TEST_F(lib_NonCopyableTest, setConstructed)
{
    TestNonCopyable obj{};
    EXPECT_TRUE(obj.isConstructed())    << "Error: NonCopyable is not constructed";
    obj.setConstructed(true);
    EXPECT_TRUE(obj.isConstructed())    << "Error: NonCopyable is not set as constructed";
    obj.setConstructed(false);
    EXPECT_FALSE(obj.isConstructed())   << "Error: NonCopyable is not set as unconstructed";
    obj.setConstructed(true);
    EXPECT_FALSE(obj.isConstructed())   << "Error: NonCopyable is set as constructed if it is unconstructed";
}

} // namespace lib
} // namespace eoos
