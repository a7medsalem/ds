#include "gtest/gtest.h"

#include "global.h"
#include "Trees\TreeVisitor.h"
#include "Trees\RedBlackTree.h"


INT* testcase = new INT[12]{10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70};


TEST(_TreeVisitorTests, height_visitor_1_element)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(1, height);
}

TEST(_TreeVisitorTests, height_visitor_3_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(2, height);
}

TEST(_TreeVisitorTests, height_visitor_4_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(3, height);
}

// elements are 10, 18, 7, 15, 16
TEST(_TreeVisitorTests, height_visitor_5_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(3, height);
}

// elements are 10, 18, 7, 15, 16, 30
TEST(_TreeVisitorTests, height_visitor_6_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(4, height);
}


// elements are 10, 18, 7, 15, 16, 30, 25
TEST(_TreeVisitorTests, height_visitor_7_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);
    tree.insert(testcase[6]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(4, height);
}


// elements are 10, 18, 7, 15, 16, 30, 25, 40
TEST(_TreeVisitorTests, height_visitor_8_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);
    tree.insert(testcase[6]);
    tree.insert(testcase[7]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(4, height);
}


// elements are 10, 18, 7, 15, 16, 30, 25, 40, 60
TEST(_TreeVisitorTests, height_visitor_9_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);
    tree.insert(testcase[6]);
    tree.insert(testcase[7]);
    tree.insert(testcase[8]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(4, height);
}

// elements are 10, 18, 7, 15, 16, 30, 25, 40, 60, 2
TEST(_TreeVisitorTests, height_visitor_10_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);
    tree.insert(testcase[6]);
    tree.insert(testcase[7]);
    tree.insert(testcase[8]);
    tree.insert(testcase[9]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(4, height);
}

// elements are 10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1
TEST(_TreeVisitorTests, height_visitor_11_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);
    tree.insert(testcase[6]);
    tree.insert(testcase[7]);
    tree.insert(testcase[8]);
    tree.insert(testcase[9]);
    tree.insert(testcase[10]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(4, height);
}


// elements are 10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70
TEST(_TreeVisitorTests, height_visitor_12_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);
    tree.insert(testcase[6]);
    tree.insert(testcase[7]);
    tree.insert(testcase[8]);
    tree.insert(testcase[9]);
    tree.insert(testcase[10]);
    tree.insert(testcase[11]);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(5, height);
}

// elements are 10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70, 17, 19, 21
TEST(_TreeVisitorTests, height_visitor_more_elements)
{
    ds::RedBlackTree<INT> tree;
    tree.insert(testcase[0]);
    tree.insert(testcase[1]);
    tree.insert(testcase[2]);
    tree.insert(testcase[3]);
    tree.insert(testcase[4]);
    tree.insert(testcase[5]);
    tree.insert(testcase[6]);
    tree.insert(testcase[7]);
    tree.insert(testcase[8]);
    tree.insert(testcase[9]);
    tree.insert(testcase[10]);
    tree.insert(testcase[11]);
    tree.insert(17);
    tree.insert(19);
    tree.insert(21);

    ds::TreeHeight<INT> *visitor = new ds::TreeHeight<INT>();
    tree.accept(*visitor);
    INT height = visitor->getHeight();
    //
    EXPECT_EQ(5, height);
}