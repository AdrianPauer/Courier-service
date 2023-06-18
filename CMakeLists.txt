cmake_minimum_required(VERSION 3.6.2)

set(TARGET_NAME exercise9)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        1_Address.cpp
        2_Package.cpp
        3_CourierCar.cpp
        3_ReadFile.cpp
        4_ShippingArea.cpp
        5_ShortestPath.cpp
        )

set(TEST_FILES
        testyUloha_1.cpp
        testyUloha_2.cpp
        testyUloha_3.cpp
        testyUloha_4.cpp
        testyUloha_5.cpp
        )

set(GTEST_SOURCE_FILES
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

add_library(tests OBJECT ${TEST_FILES})
add_library(gtest OBJECT ${GTEST_SOURCE_FILES})

find_package(Threads)

include_directories(GoogleTest)
add_executable(${TARGET_NAME} ${SOURCE_FILES} $<TARGET_OBJECTS:gtest> $<TARGET_OBJECTS:tests>)
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})

# Enable warning messages
set(FLAGS_WARNINGS -Wall -Wextra -Wshadow -Wconversion -Wpedantic -pedantic)
set(FLAGS_AUTO_PATTERN -ftrivial-auto-var-init=pattern)
target_compile_options(${TARGET_NAME} PRIVATE ${FLAGS_WARNINGS})

# If available, enable automatic variable initialization to pattern
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "12")
        target_compile_options(${TARGET_NAME} PRIVATE ${FLAGS_AUTO_PATTERN})
    endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "8")
        target_compile_options(${TARGET_NAME} PRIVATE ${FLAGS_AUTO_PATTERN})
    endif()
endif()

add_custom_command(TARGET exercise9 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/packages.srt
        ${CMAKE_SOURCE_DIR}/shippingArea1.srt
        ${CMAKE_SOURCE_DIR}/shippingarea2.srt
        $<TARGET_FILE_DIR:exercise9>
        VERBATIM)