#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#include <functional>
#include "global.h"
#include "ArrayList.h"
#include "Trees/TreeNode.h"
#include "Trees/TreeTraverser.h"
#include "Trees/TreeVisitor.h"


namespace ds
{
    template<typename T>
    class RedBlackTree : public ITreeHost<T>
    {
    private:
        RedBlackTreeNode<T> *root_;
        std::function<INT(T,T)> comparer_;
        INT count_;
    private:
        void insertNode(RedBlackTreeNode<T>* parent, RedBlackTreeNode<T>* &root, T value);
        RedBlackTreeNode<T>* getGrandfather(RedBlackTreeNode<T> *node);
        RedBlackTreeNode<T>* getUncle(RedBlackTreeNode<T> *node);
        //
        void recolor(RedBlackTreeNode<T> *node);
        void leftRotateAbout(RedBlackTreeNode<T>* center);
        void rghtRotateAbout(RedBlackTreeNode<T>* center);
        void balance(RedBlackTreeNode<T> *node);
    public:
        RedBlackTree<T>();
        RedBlackTree<T>(std::function<INT(T,T)> comparer);
        ~RedBlackTree<T>();
    public:
        BOOLEAN insert(T value);

        INT getCount();
        //
        void accept(ITreeVisitor<T> &visitor);
        ArrayList<T> toList(ITreeTraverser<T> traverser);
    };
}



/********************************************/
/*                                          */
/*               RedBlackTree               */
/*                                          */
/********************************************/


template<typename T>
ds::RedBlackTree<T>::RedBlackTree()
{
    this->count_ = 0;
    this->root_ = NULL;
    this->comparer_ = [](T f, T s) -> INT
    {
        if(f > s) return 1;
        else if( f < s) return -1;
        else return 0;
    };
}

template<typename T>
ds::RedBlackTree<T>::RedBlackTree(std::function<INT(T,T)> comparer)
{
    this->count_ = 0;
    this->root_ = NULL;
    this->comparer_ = comparer;
}

template<typename T>
ds::RedBlackTree<T>::~RedBlackTree()
{
    // no thing to do here... yet
}


template<typename T>
void ds::RedBlackTree<T>::recolor(ds::RedBlackTreeNode<T> *node)
{
    if(node->color == ds::Color::BLACK) node->color = ds::Color::RED;
    else node->color = ds::Color::BLACK;
}

template<typename T>
ds::RedBlackTreeNode<T>* ds::RedBlackTree<T>::getGrandfather(ds::RedBlackTreeNode<T> *node)
{
    return (ds::RedBlackTreeNode<T>*)node->parent->parent;
}

template<typename T>
ds::RedBlackTreeNode<T>* ds::RedBlackTree<T>::getUncle(ds::RedBlackTreeNode<T> *node)
{
    ds::RedBlackTreeNode<T>* grandfather = this->getGrandfather(node);
    if(!grandfather) return NULL;

    if(grandfather->left == node->parent)
    {
        return (ds::RedBlackTreeNode<T>*)grandfather->rigt;
    }
    else
    {
        return (ds::RedBlackTreeNode<T>*)grandfather->left;
    }
    
}


template<typename T>
void ds::RedBlackTree<T>::rghtRotateAbout(ds::RedBlackTreeNode<T>* center)
{
    ds::RedBlackTreeNode<T>* grandfather = center->parent->parent;
    ds::RedBlackTreeNode<T>* parent = center->parent;

    if(grandfather)
    {
        if(grandfather->left == parent) { grandfather->left = center; }
        else { grandfather->rigt = center; }
    }
    else
    {
        this->root_ = center;
    }
    center->parent = grandfather;
    //
    ds::RedBlackTreeNode<T>* oldCenterRight = (ds::RedBlackTreeNode<T>*)center->rigt;
    center->rigt = parent;
    parent->parent = center;
    //
    parent->left = oldCenterRight;
    if(oldCenterRight) oldCenterRight->parent = parent;
}

template<typename T>
void ds::RedBlackTree<T>::leftRotateAbout(ds::RedBlackTreeNode<T>* center)
{
    ds::RedBlackTreeNode<T>* grandfather = center->parent->parent;
    ds::RedBlackTreeNode<T>* parent = center->parent;

    if(grandfather)
    {
        if(grandfather->left == parent) { grandfather->left = center; }
        else { grandfather->rigt = center; }
    }
    else
    {
        this->root_ = center;
    }
    center->parent = grandfather;
    //
    ds::RedBlackTreeNode<T>* oldCenterLeft = (ds::RedBlackTreeNode<T>*)center->left;
    center->left = parent;
    parent->parent = center;
    //
    parent->rigt = oldCenterLeft;
    if(oldCenterLeft) oldCenterLeft->parent = parent;
}


template<typename T>
void ds::RedBlackTree<T>::balance(ds::RedBlackTreeNode<T> *node)
{
    if(!node) return;
    // if it was the root, mark it as black
    if(node == this->root_) { node->color = ds::Color::BLACK; return; }
    // if node is black, do nothing
    if(node->color == ds::Color::BLACK) return;
    // if parent is black, do nothing
    if(node->parent->color == ds::Color::BLACK) return;


    // else, node and its parent are red,
    // violate red-black tree role 'no two adjacent red nodes'

    ds::RedBlackTreeNode<T> *grandfather = node->parent->parent;
    ds::RedBlackTreeNode<T> *uncle = this->getUncle(node);
    ds::RedBlackTreeNode<T> *parent = node->parent;

    if(!uncle || uncle->color == ds::Color::BLACK)
    {
        // rotate
        if(parent == grandfather->left)
        {
            if(node == parent->left)
            {
                // left - left node
                this->rghtRotateAbout(parent);
                //
                this->recolor(parent);
                this->recolor(grandfather);
            }
            else
            {
                // left - right node
                this->leftRotateAbout(node);
                this->rghtRotateAbout(node);
                //
                this->recolor(node);
                this->recolor(grandfather);
            }
        }
        else
        {
            if(node == parent->left)
            {
                // right - left node
                this->rghtRotateAbout(node);
                this->leftRotateAbout(node);
                //
                this->recolor(node);
                this->recolor(grandfather);
            }
            else
            {
                // right - right node
                this->leftRotateAbout(parent);
                //
                this->recolor(parent);
                this->recolor(grandfather);
            }
        }
        
    }
    else
    {
        // recolor
        this->recolor(parent);
        this->recolor(uncle);
        // recolor grandfather if it wasn't the root of tree
        if(grandfather != this->root_)
        {
            this->recolor(grandfather);
        }
    }

}

template<typename T>
void ds::RedBlackTree<T>::insertNode(RedBlackTreeNode<T>* parent, RedBlackTreeNode<T>* &root, T value)
{
    // if root is null, create a new 'red' node and assign it to that node.
    if(!root)
    {
        root = new ds::RedBlackTreeNode<T>(value);
        root->left = NULL;
        root->rigt = NULL;
        root->parent = parent;
    }
    else
    {
        INT compare = this->comparer_(value, root->value);
        if(compare > 0)
        {
            this->insertNode(root, (ds::RedBlackTreeNode<T>*&)root->rigt, value);
        }
        else if(compare < 0)
        {
            this->insertNode(root, (ds::RedBlackTreeNode<T>*&)root->left, value);
        }
        else
        {
            root->count++; return;
        }
    }

    this->balance(root);
}


template<typename T>
BOOLEAN ds::RedBlackTree<T>::insert(T value)
{
    this->insertNode(NULL, this->root_, value);
    this->count_++;
    return TRUE;
}


template<typename T>
void ds::RedBlackTree<T>::accept(ds::ITreeVisitor<T> &visitor)
{
    visitor.visit(this->root_);
}

#endif // !_RED_BLACK_TREE_H_