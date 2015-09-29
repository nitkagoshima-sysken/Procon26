#include <gtest/gtest.h>
#include "../procon26_module.hpp"

TEST(procon26_module, BoardBoolean)
{
	BoardBoolean board1;
	BoardBoolean board2(-6, 7);
	BoardBoolean board3(5, 25);
	board1.place(36, 38);
	ASSERT_EQ(board1.check(28, 39), 0);
	ASSERT_EQ(board2.check(-7, 10), 0);
	ASSERT_EQ(board3.check(-5, 22), 1);
	ASSERT_EQ(board3.check(3, 34), 1);
	ASSERT_EQ(board3.check(-8, 23), -1);
	ASSERT_EQ(board3.check(4, 40), -1);
}
