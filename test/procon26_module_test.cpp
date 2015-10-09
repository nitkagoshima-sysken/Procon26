#include <gtest/gtest.h>
#include "../procon26_modlib.hpp"
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

TEST(procon26_module, StonePicker){
    std::vector<std::vector<State *> > states, picked;
    std::vector<int> zukus;
    Stone *stone1 = getStoneByString("1                                                               ");
    Stone *stone2 = getStoneByString("11                                                              ");
    Stone *stone3 = getStoneByString("111                                                             ");
    Stone *stone4 = getStoneByString("1111                                                            ");
    std::vector<State *> states1, states2, states3, states4;
    getStatesOfStone(stone3, states3);
    getStatesOfStone(stone1, states1);
    getStatesOfStone(stone4, states4);
    getStatesOfStone(stone2, states2);
    zukus.push_back(3); states.push_back(states3);
    zukus.push_back(1); states.push_back(states1);
    zukus.push_back(4); states.push_back(states4);
    zukus.push_back(2); states.push_back(states2);
    StonePicker stonePicker(states, zukus, 10);
    //0000
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 4);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone4));
    ASSERT_TRUE(isEqualStone(picked[3][0], stone2));
    //1000
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone2));
    //0100
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone4));
    //1100
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4));
    //0010
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone2));
    //1010
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone4));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //0110
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4));
    //1110
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone4));
    //0001
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone2));
    //1001
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //0101
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    //1101
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    //0011
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //1011
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone2));
    //0111
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    //1111
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 0);

    StonePicker stonePicker2(states, zukus, 4);
    //1110
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone4));
    //0101
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    //1101
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    //0011
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //1011
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone2));
    //0111
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    //1111
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 0);
}

TEST(procon26_module, BoardBoolean)
{
	BoardBoolean board1;
	BoardBoolean *p;
	p = board1.place(1, 1);
	ASSERT_FALSE(board1.check(-7, -7));
	ASSERT_TRUE(p -> check(-7, -7));
	ASSERT_FALSE(p -> check(10, 10));
	p = board1.place(23, 1);
	ASSERT_FALSE(board1.check(31, -7));
	ASSERT_TRUE(p -> check(31, -7));
	ASSERT_FALSE(p -> check(14, 10));
	p = board1.place(1, 23);
	ASSERT_FALSE(board1.check(1, 31));
	ASSERT_TRUE(p -> check(1, 31));
	ASSERT_FALSE(p -> check(10, 14));
	p = board1.place(23, 23);
	ASSERT_FALSE(board1.check(31, 31));
	ASSERT_TRUE(p -> check(31, 31));
	ASSERT_FALSE(p -> check(14, 14));
	p = board1.place(12, 12);
	ASSERT_FALSE(board1.check(20, 8));
	ASSERT_TRUE(p -> check(20, 8));
	ASSERT_FALSE(p -> check(21, 21));
}

TEST(procon26_module, Answers)
{
	Answers answer(6);
	Answer ans1; ans1.X = 1; ans1.Y = 0; ans1.turn = 2; ans1.flipped = false;
	Answer ans2; ans2.X = 9; ans2.Y = 5; ans2.turn = 0; ans2.flipped = true;
	State _ans2; _ans2.turn = 0; _ans2.flipped = true;

	answer.place(2, ans1.X, ans1.Y, ans1.flipped, ans1.turn);
	answer.place(4, &_ans2, ans2.X, ans2.Y);

	testing::internal::CaptureStdout();
	answer.print(cout);
	string ans = "\n\n1 0 H 180\n\n9 5 T 0\n\n";
	ASSERT_EQ(testing::internal::GetCapturedStdout(), ans);

}
