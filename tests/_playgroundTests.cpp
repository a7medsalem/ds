#include "gtest/gtest.h"
#include <vector>

#include "global.h"

TEST(_playground, vector_insert_max)
{
    std::vector<int> vector;
    for (INT i = 0; i < INT32_MAX; i++)
    {
        vector.push_back(i);
    }

    EXPECT_EQ(INT32_MAX , vector.size());
}