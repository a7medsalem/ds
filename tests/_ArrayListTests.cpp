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

TEST(_ArrayListTests, create_list_with_negative_size)
{
    EXPECT_THROW(ds::ArrayList<INT> list(-1), ds::exception);
}

TEST(_ArrayListTests, create_list_with_max_size)
{
    ds::ArrayList<INT> list(INT32_MAX);
    EXPECT_EQ(0 , list.getCount());
    EXPECT_EQ(INT32_MAX, list.getSize());
}

TEST(_ArrayListTests, create_list_using_copy_constructor)
{
    ds::ArrayList<INT> list(10);
    ds::ArrayList<INT> copy = list;

    EXPECT_EQ(0 , copy.getCount());
    EXPECT_EQ(10, copy.getSize());
}



TEST(_ArrayListTests, add)
{
    ds::ArrayList<INT> list;
    
    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(3, list.getSize());
}

struct STRUCT_TEST { INT number; INT code; };
static INT operator ==(const STRUCT_TEST f, const STRUCT_TEST s) { return f.number == s.number;}
TEST(_ArrayListTests, add_object)
{
    ds::ArrayList<STRUCT_TEST> list;
    STRUCT_TEST obj;

    EXPECT_EQ(TRUE, list.add(obj));
    EXPECT_EQ(obj, list[0]);
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(3, list.getSize());
}

TEST(_ArrayListTests, add_object_pointer)
{
    ds::ArrayList<STRUCT_TEST*> list;
    STRUCT_TEST *obj = new STRUCT_TEST();

    EXPECT_EQ(TRUE, list.add(obj));
    EXPECT_EQ(obj, list[0]);
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(3, list.getSize());
}

TEST(_ArrayListTests, add_million_element)
{
    ds::ArrayList<INT> list(10);
    for (INT i = 0; i < 1e6; i++) list.add(i);
    
    EXPECT_EQ(1e6 , list.getCount());
    EXPECT_EQ(1310720 , list.getSize());
}

TEST(_ArrayListTests, add_elements_and_get)
{
    ds::ArrayList<INT> list;
    list.add(00);
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    EXPECT_EQ(5 , list.getCount());
    EXPECT_EQ(00, list.get(0));
    EXPECT_EQ(10, list.get(1));
    EXPECT_EQ(20, list.get(2));
    EXPECT_EQ(30, list.get(3));
    EXPECT_EQ(40, list.get(4));
}

TEST(_ArrayListTests, insert)
{
    ds::ArrayList<INT> list;
    
    EXPECT_EQ(TRUE, list.insert(1));
    EXPECT_EQ(TRUE, list.insert(0));
    EXPECT_EQ(2, list.getCount());
    EXPECT_EQ(3, list.getSize());
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(1, list[1]);
}

TEST(_ArrayListTests, remove_one_by_element)
{
    ds::ArrayList<INT> list;
    list.add(00);
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    list.removeOne(20);
    EXPECT_EQ(4 , list.getCount());
    EXPECT_EQ(00, list.get(0));
    EXPECT_EQ(10, list.get(1));
    EXPECT_EQ(30, list.get(2));
    EXPECT_EQ(40, list.get(3));
}

TEST(_ArrayListTests, remove_one_by_element_at_start)
{
    ds::ArrayList<INT> list;
    list.add(00);
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    list.removeOne(0);
    EXPECT_EQ(4 , list.getCount());
    EXPECT_EQ(10, list.get(0));
    EXPECT_EQ(20, list.get(1));
    EXPECT_EQ(30, list.get(2));
    EXPECT_EQ(40, list.get(3));
}

TEST(_ArrayListTests, remove_one_by_element_at_last)
{
    ds::ArrayList<INT> list;
    list.add(00);
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    list.removeOne(40);
    EXPECT_EQ(4 , list.getCount());
    EXPECT_EQ(00, list.get(0));
    EXPECT_EQ(10, list.get(1));
    EXPECT_EQ(20, list.get(2));
    EXPECT_EQ(30, list.get(3));
}

TEST(_ArrayListTests, remove_all)
{
    ds::ArrayList<INT> list;
    list.add(1);
    list.add(9);
    list.add(2);
    list.add(9);
    list.add(3);
    list.add(9);
    list.add(4);
    list.add(9);
    list.add(5);
    list.add(9);
    list.add(6);

    list.removeAll(9);
    EXPECT_EQ(6, list.getCount());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(2, list[1]);
    EXPECT_EQ(3, list[2]);
    EXPECT_EQ(4, list[3]);
    EXPECT_EQ(5, list[4]);
    EXPECT_EQ(6, list[5]);
}

TEST(_ArrayListTests, remove_all_till_empty)
{
    ds::ArrayList<INT> list;
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);

    list.removeAll(1);
    EXPECT_EQ(0, list.getCount());
}

TEST(_ArrayListTests, remove_all_with_2_duplicated_in_row)
{
    ds::ArrayList<INT> list;
    list.add(1);
    list.add(1);
    list.add(5);
    list.add(5);
    list.add(1);
    list.add(1);


    list.removeAll(5);
    EXPECT_EQ(4, list.getCount());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(1, list[1]);
    EXPECT_EQ(1, list[2]);
    EXPECT_EQ(1, list[3]);
}

TEST(_ArrayListTests, remove_all_with_only_one_at_start)
{
    ds::ArrayList<INT> list;
    list.add(5);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);


    list.removeAll(5);
    EXPECT_EQ(4, list.getCount());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(1, list[1]);
    EXPECT_EQ(1, list[2]);
    EXPECT_EQ(1, list[3]);
}

TEST(_ArrayListTests, remove_all_with_only_one_at_end)
{
    ds::ArrayList<INT> list;
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(5);


    list.removeAll(5);
    EXPECT_EQ(4, list.getCount());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(1, list[1]);
    EXPECT_EQ(1, list[2]);
    EXPECT_EQ(1, list[3]);
}

TEST(_ArrayListTests, remove_by_index)
{
    ds::ArrayList<INT> list;
    list.add(00);
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);

    list.removeAt(2);
    EXPECT_EQ(4 , list.getCount());
    EXPECT_EQ(00, list.get(0));
    EXPECT_EQ(10, list.get(1));
    EXPECT_EQ(30, list.get(2));
    EXPECT_EQ(40, list.get(3));
}


TEST(_ArrayListTests, get_out_of_index)
{
    ds::ArrayList<INT> list;
    EXPECT_THROW(list.get(-1), ds::negativeIndexNotAllowedException);
    EXPECT_THROW(list.get(0), ds::exception);
    EXPECT_THROW(list.get(+1), ds::exception);
}

TEST(_ArrayListTests, remove_at_out_of_index)
{
    ds::ArrayList<INT> list;
    EXPECT_THROW(list.removeAt(-1), ds::negativeIndexNotAllowedException);
    EXPECT_EQ(FALSE, list.removeAt(0));
    EXPECT_EQ(FALSE, list.removeAt(+1));
}


TEST(_ArrayListTests, get_using_indexer)
{
    ds::ArrayList<INT> list;
    for (INT i = 0; i < 100; i++)
    {
        list.add(i);
    }
    
    EXPECT_EQ(00, list[0]);
    EXPECT_EQ(99, list[99]);
}

TEST(_ArrayListTests, modify_value_using_indexer)
{
    ds::ArrayList<INT> list;
    for (INT i = 0; i < 100; i++)
    {
        list.add(i);
    }
    
    list[0] = 100;
    list[99] = 0;
    EXPECT_EQ(100, list[0]);
    EXPECT_EQ(000, list[99]);
}


TEST(_ArrayListTests, iterator_for_loop)
{
    ds::ArrayList<INT> list;
    for (INT i = 0; i < 100; i++) list.add(i);
    
    INT counter = 0;
    for (auto i : list)
    {
        EXPECT_EQ(counter++, i);
    };
}


TEST(_ArrayListTests, iterator_std_fill)
{
    ds::ArrayList<INT> list;
    for (INT i = 0; i < 100; i++) list.add(i);
    
    std::fill(list.begin(), list.end(), 5);
    for (auto i : list)
    {
        EXPECT_EQ(5, i);
    };
}

#include <algorithm>
TEST(_ArrayListTests, iterator_)
{
    ds::ArrayList<INT> list;
    list.add(5);
    list.add(2);
    list.add(7);
    list.add(1);
    list.add(6);
    list.add(3);
    list.add(4);

    std::sort(list.begin(), list.end());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(2, list[1]);
    EXPECT_EQ(3, list[2]);
    EXPECT_EQ(4, list[3]);
    EXPECT_EQ(5, list[4]);
    EXPECT_EQ(6, list[5]);
    EXPECT_EQ(7, list[6]);
}
