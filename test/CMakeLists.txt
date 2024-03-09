add_subdirectory(${PROJECT_SOURCE_DIR}/lib/googletest-1.14.0 googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES "*.cpp")
add_executable(runUnitTests ${TEST_SOURCES})

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests MethodsOfComputationalMathematics_lib)
