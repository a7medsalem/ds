#include "gtest/gtest.h"

#include "global.h"
#include "ArrayList.h"

TEST(_ArrayListTests, create_empty_list)
{
    ds::ArrayList<INT> list;
    EXPECT_EQ(0, list.getCount());
    EXPECT_EQ(3, list.getSize());
}

TEST(_ArrayListTests, create_list_with_init_size)
{
    ds::ArrayList<INT> list(10);
    EXPECT_EQ(0 , list.getCount());
    EXPECT_EQ(10, list.getSize());
}

TEST(_ArrayListTests, create_list_using_copy_constructor)
{
    ds::ArrayList<INT> list(10);
    ds::ArrayList<INT> copy = list;

    EXPECT_EQ(0 , copy.getCount());
    EXPECT_EQ(10, copy.getSize());
}