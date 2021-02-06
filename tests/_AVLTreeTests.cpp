#include "gtest/gtest.h"

#include "global.h"
#include "Trees\AVLTree.h"



TEST(_AVLTreeTests, create_tree)
{
    ds::AVLTree<INT> tree;
}


TEST(_AVLTreeTests, add_right_right)
{
    ds::AVLTree<INT> tree;

    tree.insert(3);
    tree.insert(1);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);

    ds::ArrayList<INT> list = *tree.toList(new ds::InorderTraverser<INT>());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(3, list[1]);
    EXPECT_EQ(6, list[2]);
    EXPECT_EQ(7, list[3]);
    EXPECT_EQ(8, list[4]);
}

TEST(_AVLTreeTests, add_right_left)
{
    ds::AVLTree<INT> tree;

    tree.insert(3);
    tree.insert(1);
    tree.insert(7);
    tree.insert(9);
    tree.insert(8);

    ds::ArrayList<INT> list = *tree.toList(new ds::InorderTraverser<INT>());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(3, list[1]);
    EXPECT_EQ(7, list[2]);
    EXPECT_EQ(8, list[3]);
    EXPECT_EQ(9, list[4]);
}



TEST(_AVLTreeTests, add_left_left)
{
    ds::AVLTree<INT> tree;

    tree.insert(8);
    tree.insert(9);
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);

    ds::ArrayList<INT> list = *tree.toList(new ds::InorderTraverser<INT>());
    EXPECT_EQ(5, list[0]);
    EXPECT_EQ(6, list[1]);
    EXPECT_EQ(7, list[2]);
    EXPECT_EQ(8, list[3]);
    EXPECT_EQ(9, list[4]);
}

TEST(_AVLTreeTests, add_left_right)
{
    ds::AVLTree<INT> tree;

    tree.insert(8);
    tree.insert(9);
    tree.insert(7);
    tree.insert(5);
    tree.insert(6);

    ds::ArrayList<INT> list = *tree.toList(new ds::InorderTraverser<INT>());
    EXPECT_EQ(5, list[0]);
    EXPECT_EQ(6, list[1]);
    EXPECT_EQ(7, list[2]);
    EXPECT_EQ(8, list[3]);
    EXPECT_EQ(9, list[4]);
}

TEST(_AVLTreeTests, add_left_left_to_second_degree)
{
    ds::AVLTree<INT> tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(40);
    tree.insert(05);
    tree.insert(15);
    tree.insert(03);

    ds::ArrayList<INT> list = *tree.toList(new ds::InorderTraverser<INT>());
    EXPECT_EQ(03, list[0]);
    EXPECT_EQ(05, list[1]);
    EXPECT_EQ(10, list[2]);
    EXPECT_EQ(15, list[3]);
    EXPECT_EQ(20, list[4]);
    EXPECT_EQ(40, list[5]);
}

TEST(_AVLTreeTests, add_left_right_to_second_degree)
{
    ds::AVLTree<INT> tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(40);
    tree.insert(05);
    tree.insert(15);
    tree.insert(07);

    ds::ArrayList<INT> list = *tree.toList(new ds::InorderTraverser<INT>());
    EXPECT_EQ(05, list[0]);
    EXPECT_EQ(07, list[1]);
    EXPECT_EQ(10, list[2]);
    EXPECT_EQ(15, list[3]);
    EXPECT_EQ(20, list[4]);
    EXPECT_EQ(40, list[5]);
}



TEST(_AVLTreeTests, remove_one_3_element_triangle_tree)
{
    ds::AVLTree<INT> tree;
    //
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    //
    tree.removeOne(10);
    //
    EXPECT_EQ(2, tree.getCount());
}

TEST(_AVLTreeTests, remove_one_4_element_triangle_tree)
{
    ds::AVLTree<INT> tree;
    //
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    //
    tree.removeOne(5);
    //
    EXPECT_EQ(3, tree.getCount());
}

TEST(_AVLTreeTests, remove_one_to_unbalance)
{
    ds::AVLTree<INT> tree;
    //
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(45);
    tree.insert(3);
    //
    tree.removeOne(45);
    //
    EXPECT_EQ(6, tree.getCount());
}