#include "gtest/gtest.h"

#include "global.h"
#include "LinkedList.h"


TEST(_LinkedListTests, create_node)
{
    ds::LinkedListNode<INT> node(5);

    EXPECT_EQ(5, node.getValue());
}

TEST(_LinkedListTests, add)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(0));

    EXPECT_EQ(5, list.getCount());
}

TEST(_LinkedListTests, add_loop)
{
    ds::LinkedList<INT> list;
    for (INT i = 0; i < 100; i++)
    {
        list.add(i);
    }
    
    EXPECT_EQ(100, list.getCount());
}

TEST(_LinkedListTests, add_max_count_performance)
{
#ifdef DEBUG
    // due to ram limitation, don't use this test with full size
    INT max = INT32_MAX / 2;

    ds::LinkedList<INT> list;
    for (INT i = 0; i < max; i++)
    {
        list.add(i);
    }
    
    EXPECT_EQ(max, list.getCount());
#endif
}

TEST(_LinkedListTests, insert)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(TRUE, list.insert(0));
    EXPECT_EQ(TRUE, list.insert(0));
    EXPECT_EQ(TRUE, list.insert(0));
    EXPECT_EQ(TRUE, list.insert(0));
    EXPECT_EQ(TRUE, list.insert(0));

    EXPECT_EQ(5, list.getCount());
}


TEST(_LinkedListTests, insert_order)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(TRUE, list.insert(4));
    EXPECT_EQ(TRUE, list.insert(3));
    EXPECT_EQ(TRUE, list.insert(2));
    EXPECT_EQ(TRUE, list.insert(1));
    EXPECT_EQ(TRUE, list.insert(0));

    EXPECT_EQ(5, list.getCount());
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(1, list[1]);
    EXPECT_EQ(2, list[2]);
    EXPECT_EQ(3, list[3]);
    EXPECT_EQ(4, list[4]);
}

TEST(_LinkedListTests, get)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(1));
    EXPECT_EQ(TRUE, list.add(2));
    EXPECT_EQ(TRUE, list.add(3));
    EXPECT_EQ(TRUE, list.add(4));

    EXPECT_EQ(5, list.getCount());
    EXPECT_EQ(0, list.get(0));
    EXPECT_EQ(3, list.get(3));
    EXPECT_EQ(4, list.get(4));
}

TEST(_LinkedListTests, exists)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(1));
    EXPECT_EQ(TRUE, list.add(2));

    EXPECT_EQ(TRUE, list.exists(0));
    EXPECT_EQ(TRUE, list.exists(1));
    EXPECT_EQ(TRUE, list.exists(2));
    EXPECT_EQ(FALSE, list.exists(3));
}

TEST(_LinkedListTests, exists_with_predicate)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(1));
    EXPECT_EQ(TRUE, list.add(2));

    EXPECT_EQ(TRUE , list.exists([](const INT &item) -> BOOLEAN { return item == 0; }));
    EXPECT_EQ(TRUE , list.exists([](const INT &item) -> BOOLEAN { return item == 1; }));
    EXPECT_EQ(TRUE , list.exists([](const INT &item) -> BOOLEAN { return item == 2; }));
    EXPECT_EQ(FALSE, list.exists([](const INT &item) -> BOOLEAN { return item == 3; }));
}

TEST(_LinkedListTests, find_first)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(1);
    list.add(2);

    int result;
    EXPECT_EQ(TRUE, list.findFirst([](const INT& listItem) -> BOOLEAN { return listItem == 1; }, result));
    EXPECT_EQ(1, result);
}

TEST(_LinkedListTests, find_all)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(5);
    list.add(5);
    list.add(0);
    list.add(5);

    int count, *result = NULL;
    EXPECT_EQ(TRUE, list.findAll([](const INT& listItem) -> BOOLEAN { return listItem == 5; }, result, count));
    EXPECT_EQ(3, count);
    EXPECT_EQ(5, result[0]);
    EXPECT_EQ(5, result[1]);
    EXPECT_EQ(5, result[2]);
}

struct ForFindTest
{
public:
    INT number;
    INT result;
    ForFindTest() : number(), result() { }
    ForFindTest(INT num, INT res) : number(num), result(res) { }
};


TEST(_LinkedListTests, find_all_with_object)
{
    ds::LinkedList<ForFindTest> list;
    list.add(ForFindTest(1, 100));
    list.add(ForFindTest(2, 105));
    list.add(ForFindTest(3, 110));
    list.add(ForFindTest(4, 100));
    list.add(ForFindTest(5, 103));

    int count;
    ForFindTest *result = NULL;
    EXPECT_EQ(TRUE, list.findAll([](const ForFindTest& listItem) -> BOOLEAN { return listItem.result == 100; }, result, count));
    EXPECT_EQ(2, count);
    EXPECT_EQ(1, result[0].number);
    EXPECT_EQ(4, result[1].number);
}

TEST(_LinkedListTests, get_indexer)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(1));
    EXPECT_EQ(TRUE, list.add(2));
    EXPECT_EQ(TRUE, list.add(3));
    EXPECT_EQ(TRUE, list.add(4));

    EXPECT_EQ(5, list.getCount());
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(3, list[3]);
    EXPECT_EQ(4, list[4]);
}


TEST(_LinkedListTests, change_node_value)
{
    ds::LinkedList<INT> list;
    EXPECT_EQ(TRUE, list.add(0));
    EXPECT_EQ(TRUE, list.add(1));
    EXPECT_EQ(TRUE, list.add(2));
    EXPECT_EQ(TRUE, list.add(3));
    EXPECT_EQ(TRUE, list.add(4));

    list.set(1, 5);
    EXPECT_EQ(5, list[1]);
}

TEST(_LinkedListTests, change_node_value_using_indexer)
{
    ds::LinkedList<INT> list;
    EXPECT_EQ(TRUE, list.add(0));

    list[0] = 5;
    EXPECT_EQ(5, list[0]);
}


TEST(_LinkedListTests, remove_head_only_element)
{
    ds::LinkedList<INT> list;
    list.add(100);
    
    EXPECT_EQ(TRUE, list.removeHead());
    EXPECT_THROW(list.getHead(), ds::emptyCollectionException);
    EXPECT_THROW(list.getTail(), ds::emptyCollectionException);
}

TEST(_LinkedListTests, remove_tail_only_element)
{
    ds::LinkedList<INT> list;
    list.add(100);
    
    EXPECT_EQ(TRUE, list.removeTail());
    EXPECT_THROW(list.getHead(), ds::emptyCollectionException);
    EXPECT_THROW(list.getTail(), ds::emptyCollectionException);
}

TEST(_LinkedListTests, remove_at_all_list)
{
    ds::LinkedList<INT> list;
    list.add(100);
    list.add(100);
    list.add(100);
    list.add(100);
    
    EXPECT_EQ(TRUE, list.removeAt(2));  // remove from center
    EXPECT_EQ(TRUE, list.removeAt(2));  // remove from tail
    EXPECT_EQ(TRUE, list.removeAt(0));  // remove from head
    EXPECT_EQ(TRUE, list.removeAt(0));  // remove from head
    EXPECT_THROW(list.getHead(), ds::emptyCollectionException);
    EXPECT_THROW(list.getTail(), ds::emptyCollectionException);
}

TEST(_LinkedListTests, remove_head)
{
    ds::LinkedList<INT> list;
    for (INT i = 0; i < 100; i++)
    {
        list.add(i);
    }
    
    EXPECT_EQ(100, list.getCount());
    EXPECT_EQ(TRUE, list.removeHead());
    EXPECT_EQ(99, list.getCount());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(99, list[98]);
}

TEST(_LinkedListTests, remove_tail)
{
    ds::LinkedList<INT> list;
    for (INT i = 0; i < 100; i++)
    {
        list.add(i);
    }
    
    EXPECT_EQ(100, list.getCount());
    EXPECT_EQ(TRUE, list.removeTail());
    EXPECT_EQ(99, list.getCount());
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(98, list[98]);
}

TEST(_LinkedListTests, remove_at_index)
{
    ds::LinkedList<INT> list;
    for (INT i = 0; i < 100; i++)
    {
        list.add(i);
    }
    
    EXPECT_EQ(100, list.getCount());
    EXPECT_EQ(TRUE, list.removeAt(50));
    EXPECT_EQ(99, list.getCount());
    EXPECT_EQ(0, list[0]);
    EXPECT_EQ(51, list[50]);
    EXPECT_EQ(99, list[98]);
}

TEST(_LinkedListTests, remove_at_index_with_count_one)
{
    ds::LinkedList<INT> list;
    list.add(0);

    EXPECT_EQ(TRUE, list.removeAt(0));
    EXPECT_EQ(0, list.getCount());
}

TEST(_LinkedListTests, remove_at_index_with_count_two)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(1);

    EXPECT_EQ(TRUE, list.removeAt(0));
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(1, list[0]);
}

TEST(_LinkedListTests, remove_first)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(1);
    list.add(1);
    list.add(1);

    EXPECT_EQ(TRUE, list.removeFirst(1));
    EXPECT_EQ(3, list.getCount());
}

TEST(_LinkedListTests, remove_first_at_head)
{
    ds::LinkedList<INT> list;
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);

    EXPECT_EQ(TRUE, list.removeFirst(1));
    EXPECT_EQ(3, list.getCount());
}

TEST(_LinkedListTests, remove_first_at_tail)
{
    ds::LinkedList<INT> list;
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(0);

    EXPECT_EQ(TRUE, list.removeFirst(0));
    EXPECT_EQ(3, list.getCount());
    EXPECT_EQ(1, list.getTail());
}

TEST(_LinkedListTests, remove_first_with_not_found)
{
    ds::LinkedList<INT> list;
    list.add(1);
    list.add(1);
    list.add(1);
    list.add(1);

    EXPECT_EQ(FALSE, list.removeFirst(0));
    EXPECT_EQ(4, list.getCount());
}

TEST(_LinkedListTests, remove_first_with_empty_list)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(FALSE, list.removeFirst(0));
    EXPECT_EQ(0, list.getCount());
}

TEST(_LinkedListTests, remove_first_with_one_element_list)
{
    ds::LinkedList<INT> list;
    list.add(0);

    EXPECT_EQ(TRUE, list.removeFirst(0));
    EXPECT_EQ(0, list.getCount());
    EXPECT_THROW(list.getHead(), ds::emptyCollectionException);
    EXPECT_THROW(list.getTail(), ds::emptyCollectionException);
}

TEST(_LinkedListTests, remove_first_leaks_test)
{
    ds::LinkedList<INT> list;
    list.add(2);
    for(INT i = 0; i < 1e6; i++)
    {
        list.add(0);
        list.removeFirst(0);
    }

    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(list.getHead(), 2);
    EXPECT_EQ(list.getTail(), 2);
}

TEST(_LinkedListTests, remove_all_list)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(0);

    EXPECT_EQ(TRUE, list.removeAll(0));
    EXPECT_EQ(0, list.getCount());
    EXPECT_THROW(list.getHead(), ds::emptyCollectionException);
    EXPECT_THROW(list.getTail(), ds::emptyCollectionException);
}

TEST(_LinkedListTests, remove_all_list_except_tail)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(1);

    EXPECT_EQ(TRUE, list.removeAll(0));
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(list.getHead(), 1);
    EXPECT_EQ(list.getTail(), 1);
}

TEST(_LinkedListTests, remove_all_list_except_last_two)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(1);
    list.add(2);

    EXPECT_EQ(TRUE, list.removeAll(0));
    EXPECT_EQ(2, list.getCount());
    EXPECT_EQ(list.getHead(), 1);
    EXPECT_EQ(list.getTail(), 2);
}

TEST(_LinkedListTests, remove_all_head_tail)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(0);

    EXPECT_EQ(TRUE, list.removeAll(0));
    EXPECT_EQ(3, list.getCount());
    EXPECT_EQ(list.getHead(), 1);
    EXPECT_EQ(list.getTail(), 3);
}

TEST(_LinkedListTests, remove_all_with_empty_list)
{
    ds::LinkedList<INT> list;

    EXPECT_EQ(FALSE, list.removeAll(0));
    EXPECT_EQ(0, list.getCount());
}

TEST(_LinkedListTests, remove_all_except_head)
{
    ds::LinkedList<INT> list;
    list.add(1);
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(0);

    EXPECT_EQ(TRUE, list.removeAll(0));
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(list.getHead(), 1);
    EXPECT_EQ(list.getTail(), 1);
}


TEST(_LinkedListTests, remove_all_except_tail)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(0);
    list.add(1);

    EXPECT_EQ(TRUE, list.removeAll(0));
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(list.getHead(), 1);
    EXPECT_EQ(list.getTail(), 1);
}


TEST(_LinkedListTests, remove_all_leaks_test)
{
    ds::LinkedList<INT> list;
    list.add(2);
    for(INT i = 0; i < 1e6; i++)
    {
        list.add(0);
        list.add(0);
        list.add(0);
        list.add(0);
        list.add(0);
        list.removeAll(0);
    }

    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(list.getHead(), 2);
    EXPECT_EQ(list.getTail(), 2);
}

TEST(_LinkedListTests, reverse)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);
    list.reverse();

    EXPECT_EQ(3, list[0]);
    EXPECT_EQ(2, list[1]);
    EXPECT_EQ(1, list[2]);
    EXPECT_EQ(0, list[3]);
}



// TODO :: remove with process