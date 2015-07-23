#include <gtest/gtest.h>
#include "../procon26_module.h"
#include "../procon26_module.cpp"

TEST(procon26_module, checkEqual)
{
    ASSERT_TRUE(checkEqual(EMPTY_STONE, EMPTY_STONE));
    ASSERT_TRUE(checkEqual(
                getStoneByString(
                    "01110101"
                    "00011111"
                    "00011111"
                    "00000100"
                    "00000000"
                    "00000000"
                    "00000000"
                    "00000000"
                    ),
                getStoneByString(
                    "01110101"
                    "00011111"
                    "00011111"
                    "00000100"
                    "00000000"
                    "00000000"
                    "00000000"
                    "00000000"
                    )
                ));
}

TEST(procon26_module, NOT)
{
    ASSERT_TRUE(checkEqual(
                ~*getStoneByString(
                    "01110101"
                    "00011111"
                    "00011111"
                    "00000100"
                    "00000000"
                    "00000000"
                    "00000000"
                    "00000000"
                    ),
                getStoneByString(
                    "10001010"
                    "11100000"
                    "11100000"
                    "11111011"
                    "11111111"
                    "11111111"
                    "11111111"
                    "11111111"
                    )
                ));
}

TEST(procon26_module, AND)
{
    ASSERT_TRUE(checkEqual(
                *getStoneByString(
                    "01110101"
                    "00011111"
                    "00011111"
                    "00000100"
                    "00000000"
                    "00000000"
                    "00000000"
                    "00000000"
                    ) &
                *getStoneByString(
                    "00001100"
                    "00001100"
                    "00000110"
                    "00000100"
                    "00000110"
                    "00000110"
                    "00000010"
                    "00000000"
                    ),
                getStoneByString(
                    "00000100"
                    "00001100"
                    "00000110"
                    "00000100"
                    "00000000"
                    "00000000"
                    "00000000"
                    "00000000"
                    )
                ));
}

TEST(procon26_module, OR)
{
    ASSERT_TRUE(checkEqual(
                *getStoneByString(
                    "01110101"
                    "00011111"
                    "00011111"
                    "00000100"
                    "00000000"
                    "00000000"
                    "00000000"
                    "00000000"
                    ) |
                *getStoneByString(
                    "00001100"
                    "00001100"
                    "00000110"
                    "00000100"
                    "00000110"
                    "00000110"
                    "00000010"
                    "00000000"
                    ),
                getStoneByString(
                    "01111101"
                    "00011111"
                    "00011111"
                    "00000100"
                    "00000110"
                    "00000110"
                    "00000010"
                    "00000000"
                    )
                ));
}

TEST(procon26_module, XOR)
{
    ASSERT_TRUE(checkEqual(
                *getStoneByString(
                    "01110101"
                    "00011111"
                    "00011111"
                    "00000100"
                    "00000000"
                    "00000000"
                    "00000000"
                    "00000000"
                    ) ^
                *getStoneByString(
                    "00001100"
                    "00001100"
                    "00000110"
                    "00000100"
                    "00000110"
                    "00000110"
                    "00000010"
                    "00000000"
                    ),
                getStoneByString(
                    "01111001"
                    "00010011"
                    "00011001"
                    "00000000"
                    "00000110"
                    "00000110"
                    "00000010"
                    "00000000"
                    )
                ));
}
