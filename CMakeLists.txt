# EOOS UNIT TESTS.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2020-2024, Sergey Baigudin, Baigudin Software

add_executable(UnitTests
    "${CMAKE_CURRENT_LIST_DIR}/source/Main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/ProgramTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.AlignTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ArgumentParserTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.BaseStringStaticTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.BaseStringDynamicTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.BufferStaticTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.BufferDynamicTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.CharTraitTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.CircularListTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.FifoTest.cpp"    
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.GuardTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.HeapTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.LinkedListTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.MemoryTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.MutexTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.NoAllocatorTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.NonCopyableTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ObjectAllocatorTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ObjectTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.RegisterTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ResourceMemoryTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.SemaphoreTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.SharedPointerTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.StreamTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.ThreadTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/lib/lib.UniquePointerTest.cpp"
)

if(EOOS_CMAKE_TARGET_OS STREQUAL "KOS")
    add_dependencies(UnitTests target-eoos-unit-tests-edl-files)
endif()

target_link_libraries(UnitTests
PRIVATE
    target-eoos
    gtest
)

target_include_directories(UnitTests
PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
)

if(NOT EOOS_CMAKE_TARGET_OS STREQUAL "KOS")
    set_target_properties(UnitTests PROPERTIES
        OUTPUT_NAME EoosTests
    )
    
    add_test(
        NAME test-eoos-unit-tests
        COMMAND UnitTests
    )
    
    install(
        TARGETS UnitTests
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
