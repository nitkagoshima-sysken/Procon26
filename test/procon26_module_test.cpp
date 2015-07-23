#include <gtest/gtest.h>
#include "../procon26_module.h"
#include "../procon26_module.cpp"

TEST(checkEqual, Test1)
{
    ASSERT_TRUE(checkEqual(new Stone, new Stone));
    //TODO Add more cases
}
