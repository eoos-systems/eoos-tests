/**
 * @file      lib.ResourceMemoryTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2024, Sergey Baigudin, Baigudin Software
 *
 * @brief Unit tests of `lib::ResourceMemory`.
 */
#include "lib.ResourceMemory.hpp"
#include "System.hpp"

namespace eoos
{
namespace lib
{

/**
 * @class lib_ResourceMemoryTest
 * @test ResourceMemory
 * @brief Tests ResourceMemory class functionality.
 */
class lib_ResourceMemoryTest : public ::testing::Test
{

protected:

    /**
     * @class Resource
     * @brief Test resource.
     */
    class Resource
    {
        
    public:
    
        /**
         * @brief Constructor.
         */
        Resource() :
            value_ (-1) {
        }

        /**
         * @brief Returns value.
         *
         * @return This value.
         */
        int32_t getValue()
        {
            return value_;
        }
        
        /**
         * @brief Sets a new value.
         *
         * @param value a new value.
         */    
        void setValue(int32_t value)
        {
            value_ = value;
        }
        
    private:
    
        int32_t value_;        
    };

    /**
     * @class Guard
     */
    class Guard : public NonCopyable<Allocator>, public api::Guard
    {
        typedef NonCopyable<Allocator> Parent;
    
    public:
    
        /**
         * @brief Constructor.
         */
        Guard() 
            : NonCopyable<Allocator>()
            , api::Guard() {
        }
    
        /**
         * @brief Destructor.
         */
        virtual ~Guard()
        {
        }
        
        /**
         * @copydoc eoos::api::Object::isConstructed()
         */
        virtual bool_t isConstructed() const
        {
            return true;
        }
            
        /**
         * @copydoc eoos::api::Mutex::lock()
         */
        virtual bool_t lock()
        {
            return false;
        }
    
        /**
         * @copydoc eoos::api::Mutex::unlock()
         */
        virtual bool_t unlock()
        {
            return true;
        }
    
    };

    Guard guard_; ///< Test guard.
    
private:
    
    System eoos_; ///< EOOS Operating System.
};    

/**
 * @relates lib_ResourceMemoryTest
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
TEST_F(lib_ResourceMemoryTest, Constructor)
{
    ResourceMemory<Resource,3> pool(guard_);
    EXPECT_TRUE(pool.isConstructed()) << "Fatal: Object is not constructed";    
}

/**
 * @relates lib_ResourceMemoryTest
 * @brief Tests allocation and free.
 *
 * @b Arrange:
 *      - Initialize the EOOS system.
 *
 * @b Act:
 *      - Consctuct an object of the class.
 *
 * @b Assert:
 *      - Test the functionality is constructed.
 */
TEST_F(lib_ResourceMemoryTest, allocate_free)
{
    void* res[3] = { NULLPTR };
    void* tmp( NULLPTR );
    ResourceMemory<Resource,3> pool(guard_);
    EXPECT_TRUE(pool.isConstructed()) << "Fatal: Object is not constructed";
    
    res[0] = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_NE(res[0], NULLPTR) << "Fatal: Address is wrong";        
    res[1] = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_NE(res[1], NULLPTR) << "Fatal: Address is wrong";    
    res[2] = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_NE(res[2], NULLPTR) << "Fatal: Address is wrong";
    tmp = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_EQ(tmp, NULLPTR) << "Fatal: Address is wrong";

    tmp = res[1];
    pool.free(res[1]);
    res[1] = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_NE(res[1], NULLPTR) << "Fatal: Address is wrong";
    EXPECT_EQ(res[1], tmp) << "Fatal: Allocation has differnd address";    
    
    pool.free(res[0]);
    tmp = pool.allocate(sizeof(uint8_t), NULLPTR);
    EXPECT_EQ(tmp, NULLPTR) << "Fatal: Memory allocated for different size then T";

    pool.free(res[1]); 
    pool.free(res[2]);
    res[0] = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_NE(res[0], NULLPTR) << "Fatal: Address is wrong";
    res[1] = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_NE(res[1], NULLPTR) << "Fatal: Address is wrong";
    res[2] = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_NE(res[2], NULLPTR) << "Fatal: Address is wrong";
    tmp = pool.allocate(sizeof(Resource), NULLPTR);
    EXPECT_EQ(tmp, NULLPTR) << "Fatal: Address is wrong";
}

} // namespace lib
} // namespace eoos
