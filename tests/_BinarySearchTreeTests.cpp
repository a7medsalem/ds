#include "gtest/gtest.h"

#include "global.h"
#include "Trees\BinarySearchTree.h"



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