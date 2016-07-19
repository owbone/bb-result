enable_testing()

add_executable(result_test result_test.cpp)
target_link_libraries(result_test result gtest)
add_test(NAME result_test COMMAND result_test)
