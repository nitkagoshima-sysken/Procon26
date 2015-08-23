#include <gtest/gtest.h>
#include "../procon26_module.hpp"
#include "../procon26_module.cpp"

TEST(procon26_module, BoardBoolean)
{
	BoardBoolean board1;
	BoardBoolean board2(-6, 7);
	BoardBoolean board3(5, 25);
	board1.readCoordinate(36, 38);
	ASSERT_EQ(board1.checkBoolean(28, 39), 0);
	ASSERT_EQ(board2.checkBoolean(-7, 10), 0);
	ASSERT_EQ(board3.checkBoolean(-5, 22), 1);
	ASSERT_EQ(board3.checkBoolean(3, 34), 1);
	ASSERT_EQ(board3.checkBoolean(-8, 23), -1);
	ASSERT_EQ(board3.checkBoolean(4, 40), -1);
}
