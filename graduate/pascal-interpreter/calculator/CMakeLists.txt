enable_testing()
add_executable(calculator_test calculator_test.cpp)
target_include_directories(calculator_test PRIVATE ../thirdparty)
add_test(calculator_test calculator_test)