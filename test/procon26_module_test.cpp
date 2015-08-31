#include <gtest/gtest.h>
#include "../procon26_module.hpp"

TEST(procon26_module, BoardBoolean)
{
	BoardBoolean board1;
	BoardBoolean *p;
	p = board1.place(-2, 7);
	ASSERT_EQ(p -> check(-2, 8), 0);
	ASSERT_EQ(p -> check(-7, 7), 0);
	ASSERT_EQ(p -> check(-1, 15), 0);
	ASSERT_EQ(p -> check(10, 5), 1);
	ASSERT_EQ(p -> check(-3, -2), 1);
	ASSERT_EQ(p -> check(-8, 4), -1);
}
