add_executable(unit_tests tests_lab.cpp)

target_compile_definitions(unit_tests PRIVATE TESTING)

target_link_libraries(unit_tests gtest_main lab1_lib lab2_lib lab3_lib lab4_lib lab5_lib)

include(GoogleTest)

gtest_discover_tests(unit_tests)