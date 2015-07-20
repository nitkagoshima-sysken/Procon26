import sys

result = """
cmake_minimum_required(VERSION 3.0)
set(GTEST_ROOT /usr/local/lib)
include_directories(/usr/local/include)
"""
for arg in sys.argv[1:]:
    result = result + """
add_executable(%(arg)s_test %(arg)s_test.cpp)
target_link_libraries(%(arg)s_test
    pthread
    ${GTEST_ROOT}/libgtest.a
    ${GTEST_ROOT}/libgtest_main.a
    )
""" % locals()

with open("test/CMakeLists.txt", mode="w") as fp:
    fp.write(result)
    print(result)
