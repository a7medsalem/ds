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

TEST(_LinkedListTests, add_max_count)
{
    ds::LinkedList<INT> list;
    for (INT i = 0; i < 300e6; i++)
    {
        list.add(i);
    }
    
    //EXPECT_EQ(FALSE, list.add(0));
    //EXPECT_EQ(INT32_MAX, list.getCount());
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

TEST(_LinkedListTests, change_node_value_using_index)
{
    ds::LinkedList<INT> list;
    EXPECT_EQ(TRUE, list.add(0));

    list[0] = 5;
    EXPECT_EQ(5, list[0]);
}


TEST(_LinkedListTests, remove_only_element_by_head)
{
    ds::LinkedList<INT> list;
    list.add(100);
    
    EXPECT_EQ(TRUE, list.removeHead());
    EXPECT_THROW(list.getHead(), ds::emptyCollectionException);
    EXPECT_THROW(list.getTail(), ds::emptyCollectionException);
}

TEST(_LinkedListTests, remove_only_element_by_tail)
{
    ds::LinkedList<INT> list;
    list.add(100);
    
    EXPECT_EQ(TRUE, list.removeTail());
    EXPECT_THROW(list.getHead(), ds::emptyCollectionException);
    EXPECT_THROW(list.getTail(), ds::emptyCollectionException);
}

TEST(_LinkedListTests, remove_all_by_at)
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

TEST(_LinkedListTests, remove_at_index_1_count)
{
    ds::LinkedList<INT> list;
    list.add(0);

    EXPECT_EQ(TRUE, list.removeAt(0));
    EXPECT_EQ(0, list.getCount());
}

TEST(_LinkedListTests, remove_at_index_2_count)
{
    ds::LinkedList<INT> list;
    list.add(0);
    list.add(1);

    EXPECT_EQ(TRUE, list.removeAt(0));
    EXPECT_EQ(1, list.getCount());
    EXPECT_EQ(1, list[0]);
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