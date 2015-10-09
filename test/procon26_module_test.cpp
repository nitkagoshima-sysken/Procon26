#include <gtest/gtest.h>
#include "../procon26_modlib.hpp"
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

TEST(procon26_module, StonePicker){
    std::vector<std::vector<State *> > states, picked;
    std::vector<int> zukus, stoneNumbers;
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
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 4);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3)); ASSERT_EQ(0, stoneNumbers[0]);
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1)); ASSERT_EQ(1, stoneNumbers[1]);
    ASSERT_TRUE(isEqualStone(picked[2][0], stone4)); ASSERT_EQ(2, stoneNumbers[2]);
    ASSERT_TRUE(isEqualStone(picked[3][0], stone2)); ASSERT_EQ(3, stoneNumbers[3]);
    //1000
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone2));
    //0100
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone4));
    //1100
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4));
    //0010
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone2));
    //1010
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone4));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //0110
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1)); ASSERT_EQ(1, stoneNumbers[0]);
    ASSERT_TRUE(isEqualStone(picked[1][0], stone4)); ASSERT_EQ(2, stoneNumbers[1]);
    //1110
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone4));
    //0001
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[2][0], stone2));
    //1001
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //0101
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    //1101
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    //0011
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //1011
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone2));
    //0111
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    //1111
    picked.clear(); stoneNumbers.clear(); stonePicker.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 0);

    StonePicker stonePicker2(states, zukus, 4);
    //1110
    picked.clear(); stoneNumbers.clear(); stonePicker2.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone4));
    //0101
    picked.clear(); stoneNumbers.clear(); stonePicker2.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone1));
    //1101
    picked.clear(); stoneNumbers.clear(); stonePicker2.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone3));
    //0011
    picked.clear(); stoneNumbers.clear(); stonePicker2.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1][0], stone2));
    //1011
    picked.clear(); stoneNumbers.clear(); stonePicker2.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone2));
    //0111
    picked.clear(); stoneNumbers.clear(); stonePicker2.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0][0], stone1));
    //1111
    picked.clear(); stoneNumbers.clear(); stonePicker2.getNext(picked, stoneNumbers);
    ASSERT_EQ(picked.size(), 0);
}

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
