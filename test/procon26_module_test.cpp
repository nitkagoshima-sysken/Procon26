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

TEST(procon26_module, Answers_place_and_print)
{
	Answers answer;
	Answer ans1; ans1.X = 1; ans1.Y = 0; ans1.turn = 2; ans1.flipped = false;
	Answer ans2; ans2.X = 9; ans2.Y = 5; ans2.turn = 0; ans2.flipped = true;
	State _ans2; _ans2.turn = 0; _ans2.flipped = true;
	Answer ans3; ans3.X = NULL_POINT; ans3.Y = NULL_POINT;

	answer.place(ans1.X, ans1.Y, ans1.flipped, ans1.turn);
	answer.place(&_ans2, ans2.X, ans2.Y);

	testing::internal::CaptureStdout();
	answer.print(2);
	string ans = "1 0 H 180\n9 5 T 0\n\n";
	ASSERT_EQ(testing::internal::GetCapturedStdout(), ans);
}