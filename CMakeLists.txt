# EOOS UNIT TESTS.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2020, Sergey Baigudin, Baigudin Software

enable_testing()
#find_package(GTest REQUIRED)

add_executable(target-eoos-unit-tests
    ${CMAKE_CURRENT_LIST_DIR}/source/tests.cpp
)

target_include_directories(target-eoos-unit-tests
PRIVATE
#    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/private>
)

target_link_libraries(target-eoos-unit-tests
PRIVATE
    target-eoos
    gtest_main
    #GTest::Main
)

set_target_properties(target-eoos-unit-tests PROPERTIES
    OUTPUT_NAME eoos-unit-tests
)

add_test(
    NAME test-state-client-test-serialization
    COMMAND target-eoos-unit-tests
)

install(
    TARGETS target-eoos-unit-tests
    RUNTIME DESTINATION "bintest"
)
