# EOOS UNIT TESTS.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2020, Sergey Baigudin, Baigudin Software

add_executable(target-eoos-unit-tests
    "${CMAKE_CURRENT_LIST_DIR}/source/DebugTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/MainTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/ObjectTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.AlignTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.BufferTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.CircularListTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.HeapTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.LinkedListTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.MemoryTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.MutexTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.MutexGuardTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.NonCopyableTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ObjectTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.SemaphoreTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.SharedPointerTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.StackTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.StringTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ThreadTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ToggleTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.UniquePointerTest.cpp"
)

target_link_libraries(target-eoos-unit-tests
PRIVATE
    target-eoos
    gtest_main
)

target_include_directories(target-eoos-unit-tests
PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
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
