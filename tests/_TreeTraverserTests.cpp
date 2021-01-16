#include "gtest/gtest.h"

#include "global.h"
#include "ArrayList.h"
#include "Trees\TreeTraverser.h"
#include "Trees\BinarySearchTree.h"



TEST(_TreeTraverserTests, inorder_traverse_BST)
{
    ds::BinarySearchTree<INT> tree;

    tree.insert(5);
    tree.insert(1);
    tree.insert(8);
    tree.insert(6);
    tree.insert(7);
    tree.insert(2);
    tree.insert(3);

    ds::ArrayList<INT> *list = tree.toList(new ds::InorderTraverser<INT>());
    EXPECT_EQ(1, (*list)[0]);
    EXPECT_EQ(2, (*list)[1]);
    EXPECT_EQ(3, (*list)[2]);
    EXPECT_EQ(5, (*list)[3]);
    EXPECT_EQ(6, (*list)[4]);
    EXPECT_EQ(7, (*list)[5]);
    EXPECT_EQ(8, (*list)[6]);
}