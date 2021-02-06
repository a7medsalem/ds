#ifndef _TREE_NODE_
#define _TREE_NODE_

#include "global.h"

namespace ds
{
    template<typename T>
    class TreeNode
    {
    public:
      T value;
      INT count;
      TreeNode *left;
      TreeNode *rigt;
    public:
        TreeNode<T>();
        TreeNode<T>(T value);
        ~TreeNode<T>();
    };

    template<typename T>
    class AVLTreeNode : public TreeNode<T>
    {
    public:
        INT height;
    public:
        AVLTreeNode<T>(T value);
        ~AVLTreeNode<T>();
    };

    enum Color { BLACK, RED };

    template<typename T>
    class RedBlackTreeNode : public TreeNode<T>
    {
    public:
        Color color;
        RedBlackTreeNode *parent;
    public:
        RedBlackTreeNode<T>();
        RedBlackTreeNode<T>(T value);
        ~RedBlackTreeNode<T>();
    };
}



/********************************************/
/*                                          */
/*               TreeNode                   */
/*                                          */
/********************************************/

template<typename T>
ds::TreeNode<T>::TreeNode() : value()
{
    this->count = 1;
    this->left = NULL;
    this->rigt = NULL;
}

template<typename T>
ds::TreeNode<T>::TreeNode(T value) : ds::TreeNode<T>::TreeNode()
{
    this->value = value;
}

template<typename T>
ds::TreeNode<T>::~TreeNode()
{
    // no thing to do here
}



/********************************************/
/*                                          */
/*              AVLTreeNode                 */
/*                                          */
/********************************************/


template<typename T>
ds::AVLTreeNode<T>::AVLTreeNode(T value) : ds::TreeNode<T>(value)
{
    this->height = 0;
}

template<typename T>
ds::AVLTreeNode<T>::~AVLTreeNode()
{
    // no thing to do here
}


/********************************************/
/*                                          */
/*              RedBlackNode                */
/*                                          */
/********************************************/

template<typename T>
ds::RedBlackTreeNode<T>::RedBlackTreeNode() : ds::TreeNode<T>()
{
    this->parent = NULL;
    this->color = ds::Color::BLACK;
}

template<typename T>
ds::RedBlackTreeNode<T>::RedBlackTreeNode(T value) : ds::TreeNode<T>(value)
{
    this->parent = NULL;
    this->color = ds::Color::RED;
}

template<typename T>
ds::RedBlackTreeNode<T>::~RedBlackTreeNode()
{
    // no thing to do here
}

#endif // !_TREE_NODE_