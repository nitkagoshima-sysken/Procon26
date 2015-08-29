#include <gtest/gtest.h>
#include "../procon26_modlib.hpp"
#include "../procon26_modlib.hpp"
#include "../procon26_modio.hpp"

TEST(procon26_module, StonePicker){
    std::vector<Stone *> stones, picked;
    std::vector<int> zukus;
    Stone *stone1 = getStoneByString("1                                                               ");
    Stone *stone2 = getStoneByString("11                                                              ");
    Stone *stone3 = getStoneByString("111                                                             ");
    Stone *stone4 = getStoneByString("1111                                                            ");
    zukus.push_back(3); stones.push_back(stone3);
    zukus.push_back(1); stones.push_back(stone1);
    zukus.push_back(4); stones.push_back(stone4);
    zukus.push_back(2); stones.push_back(stone2);
    StonePicker stonePicker(stones, zukus, 10);
    //0000
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 4);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone1));
    ASSERT_TRUE(isEqualStone(picked[2], stone4));
    ASSERT_TRUE(isEqualStone(picked[3], stone2));
    //1000
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone4));
    ASSERT_TRUE(isEqualStone(picked[2], stone2));
    //0100
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone1));
    ASSERT_TRUE(isEqualStone(picked[2], stone4));
    //1100
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone4));
    //0010
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1], stone4));
    ASSERT_TRUE(isEqualStone(picked[2], stone2));
    //1010
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone4));
    ASSERT_TRUE(isEqualStone(picked[1], stone2));
    //0110
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1], stone4));
    //1110
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone4));
    //0001
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 3);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone1));
    ASSERT_TRUE(isEqualStone(picked[2], stone2));
    //1001
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone2));
    //0101
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone1));
    //1101
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    //0011
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1], stone2));
    //1011
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone2));
    //0111
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone1));
    //1111
    picked.clear(); stonePicker.getNext(picked);
    ASSERT_EQ(picked.size(), 0);

    StonePicker stonePicker2(stones, zukus, 4);
    //1110
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone4));
    //0101
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    ASSERT_TRUE(isEqualStone(picked[1], stone1));
    //1101
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone3));
    //0011
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 2);
    ASSERT_TRUE(isEqualStone(picked[0], stone1));
    ASSERT_TRUE(isEqualStone(picked[1], stone2));
    //1011
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone2));
    //0111
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 1);
    ASSERT_TRUE(isEqualStone(picked[0], stone1));
    //1111
    picked.clear(); stonePicker2.getNext(picked);
    ASSERT_EQ(picked.size(), 0);
}
