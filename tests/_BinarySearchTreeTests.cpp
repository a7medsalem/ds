#include "gtest/gtest.h"

#include "global.h"
#include "Trees\BinarySearchTree.h"


INT* threeLevelsCase = new INT[7] { 50, 25, 75, 12, 37, 63, 87 };


TEST(_BinarySearchTreeTests, create_tree)
{
    ds::BinarySearchTree<INT> tree;

    EXPECT_EQ(0, tree.getCount());
}

TEST(_BinarySearchTreeTests, create_tree_with_custom_comparer)
{
    ds::BinarySearchTree<INT> tree([](INT f, INT s) -> INT{
        if(f < s) return 1;
        else if(f > s) return -1;
        else return 0;
    });

    EXPECT_EQ(0, tree.getCount());
}

TEST(_BinarySearchTreeTests, create_insert)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);

    EXPECT_EQ(5, tree.getCount());
}

TEST(_BinarySearchTreeTests, create_insert_same_in_order)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(threeLevelsCase[0]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[2]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[1]);

    EXPECT_EQ(5, tree.getCount());
}

TEST(_BinarySearchTreeTests, create_insert_same_out_of_order)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(threeLevelsCase[0]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[2]);
    tree.insert(threeLevelsCase[3]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[1]);

    EXPECT_EQ(6, tree.getCount());
}

TEST(_BinarySearchTreeTests, contains)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);

    EXPECT_EQ(TRUE, tree.contains(3));
    EXPECT_EQ(TRUE, tree.contains(4));
    EXPECT_EQ(TRUE, tree.contains(2));
    EXPECT_EQ(TRUE, tree.contains(1));
    EXPECT_EQ(TRUE, tree.contains(5));
    EXPECT_EQ(FALSE, tree.contains(8));
    EXPECT_EQ(FALSE, tree.contains(-1));
}


TEST(_BinarySearchTreeTests, remove_leaf)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);

    EXPECT_EQ(TRUE, tree.removeOne(1));
    EXPECT_EQ(4, tree.getCount());
}


TEST(_BinarySearchTreeTests, remove_one_with_left_child)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);

    EXPECT_EQ(TRUE, tree.removeOne(2));
    EXPECT_EQ(4, tree.getCount());
}


TEST(_BinarySearchTreeTests, remove_one_with_right_child)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);

    EXPECT_EQ(TRUE, tree.removeOne(4));
    EXPECT_EQ(4, tree.getCount());
}

TEST(_BinarySearchTreeTests, remove_root_in_3_element_triangle_tree)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(threeLevelsCase[0]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[2]);

    EXPECT_EQ(TRUE, tree.removeOne(threeLevelsCase[0]));
    EXPECT_EQ(2, tree.getCount());
}

TEST(_BinarySearchTreeTests, remove_root_in_4_element_triangle_tree)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(threeLevelsCase[0]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[2]);
    tree.insert(threeLevelsCase[3]);

    EXPECT_EQ(TRUE, tree.removeOne(threeLevelsCase[0]));
    EXPECT_EQ(3, tree.getCount());
}

TEST(_BinarySearchTreeTests, remove_root_with_no_children_to_predecessor)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(threeLevelsCase[0]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[2]);
    tree.insert(threeLevelsCase[3]);
    tree.insert(threeLevelsCase[4]);
    tree.insert(threeLevelsCase[5]);
    tree.insert(threeLevelsCase[6]);

    EXPECT_EQ(TRUE, tree.removeOne(threeLevelsCase[0]));
    EXPECT_EQ(6, tree.getCount());
}

TEST(_BinarySearchTreeTests, remove_root_with_child_to_predecessor)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(threeLevelsCase[0]);
    tree.insert(threeLevelsCase[1]);
    tree.insert(threeLevelsCase[2]);
    tree.insert(threeLevelsCase[3]);
    tree.insert(threeLevelsCase[4]);
    tree.insert(threeLevelsCase[5]);
    tree.insert(threeLevelsCase[6]);
    tree.insert(30);

    EXPECT_EQ(TRUE, tree.removeOne(threeLevelsCase[0]));
    EXPECT_EQ(7, tree.getCount());
}


TEST(_BinarySearchTreeTests, remove_all)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(30);
    tree.insert(20);
    tree.insert(25);
    tree.insert(20);

    EXPECT_EQ(TRUE, tree.removeAll(20));
    EXPECT_EQ(2, tree.getCount());
}