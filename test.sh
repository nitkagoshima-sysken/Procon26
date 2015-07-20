"cmake_minimum_required(VERSION 3.0)
set(GTEST_ROOT /usr/local/lib)
include_directories(/usr/local/include)" > test/CMakeLists.txt
for file in "$@"
do
    "add_executable(${file}_test ${file}_test.cpp)
    target_link_libraries(${file}_test
    pthread
    ${GTEST_ROOT}/libgtest.a
    ${GTEST_ROOT}/libgtest_main.a
    )" >> test/CMakeLists.txt
done
mkdir test/build
cd test/build
cmake ..
make
for file in "$@"
do
    ./${file}_test
done
cd ../..
