# EOOS UNIT TESTS.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2020, Sergey Baigudin, Baigudin Software

add_executable(target-eoos-unit-tests
    "${CMAKE_CURRENT_LIST_DIR}/source/test.Main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/test.Object.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.test.Align.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.test.SharedPtr.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.test.Thread.cpp"
)

target_link_libraries(target-eoos-unit-tests
PRIVATE
    target-eoos
    gtest_main
)

target_include_directories(target-eoos-unit-tests
PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../system/include/private>"
)

set_target_properties(target-eoos-unit-tests PROPERTIES
    OUTPUT_NAME EoosTests
)

add_test(
    NAME test-state-client-test-serialization
    COMMAND target-eoos-unit-tests
)

install(
    TARGETS target-eoos-unit-tests
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
