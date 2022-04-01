#include <gtest/gtest.h>
#include "stdio.h"

extern "C"
{
#include "dz2_lib.h"
}

TEST(basic, TestOnBasicMaxWord)
{
    char str[] = "is something new  new";
    int max = max_word(str, strlen(str));
    EXPECT_EQ(9, max);
}

TEST(basic, TestOnBasicMaxWord2)
{
    char str[] = "my new";
    int max = max_word(str, strlen(str));
    EXPECT_EQ(3, max);
}
