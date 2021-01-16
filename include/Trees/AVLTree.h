#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <functional>
#include "global.h"
#include "ArrayList.h"
#include "Trees/TreeNode.h"
#include "Trees/TreeTraverser.h"

namespace ds
{
    template<typename T>
    class AVLTree
    {
    private:
        AVLTreeNode<T> *root_;
        std::function<INT(T,T)> comparer_;
        INT count_;
    private:
        void insertNode(AVLTreeNode<T>* &root, T value);
        void rigtRotate(AVLTreeNode<T>* &root);
        void rigtSwap(AVLTreeNode<T>* &root);
        void leftRotate(AVLTreeNode<T>* &root);
        void leftSwap(AVLTreeNode<T>* &root);
        INT getNodeHeight(AVLTreeNode<T>* node);
        INT setNodeHeight(AVLTreeNode<T>* node);
    public:
        AVLTree<T>();
        AVLTree<T>(std::function<INT(T,T)> comparer);
        ~AVLTree<T>();
    public:
        BOOLEAN insert(T value);
        BOOLEAN contains();
        BOOLEAN removeOne();
        BOOLEAN removeAll();

        INT getCount();
        ArrayList<T>* toList(ITreeTraverser<T>* traverser);
    };
}





/********************************************/
/*                                          */
/*            BinarySearchTree              */
/*                                          */
/********************************************/


template<typename T>
ds::AVLTree<T>::AVLTree()
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
ds::AVLTree<T>::AVLTree(std::function<INT(T,T)> comparer)
{
    this->count_ = 0;
    this->root_ = NULL;
    this->comparer_ = comparer;
}

template<typename T>
ds::AVLTree<T>::~AVLTree()
{
    // no thing to do here... yet
}

template<typename T>
void ds::AVLTree<T>::rigtRotate(ds::AVLTreeNode<T>* &root)
{
    ds::AVLTreeNode<T>* oldRoot = root;
    ds::AVLTreeNode<T>* newRoot = (ds::AVLTreeNode<T>*)root->left;
    //
    oldRoot->left = newRoot->rigt;
    //
    root = newRoot;
    root->rigt = oldRoot;
    //
    oldRoot->height--;
}

template<typename T>
void ds::AVLTree<T>::rigtSwap(ds::AVLTreeNode<T>* &root)
{
    
    ds::AVLTreeNode<T>* oldTail = (ds::AVLTreeNode<T>*)root->left->rigt;
    ds::AVLTreeNode<T>* newTail = (ds::AVLTreeNode<T>*)root->left;
    root->left = oldTail;
    oldTail->left = newTail;
    newTail->rigt = NULL;

    newTail->height--;
    oldTail->height++;
}

template<typename T>
void ds::AVLTree<T>::leftRotate(ds::AVLTreeNode<T>* &root)
{
    ds::AVLTreeNode<T>* oldRoot = root;
    ds::AVLTreeNode<T>* newRoot = (ds::AVLTreeNode<T>*)root->rigt;
    //
    oldRoot->rigt = newRoot->left;
    //
    root = newRoot;
    root->left = oldRoot;
    //
    oldRoot->height--;
}

template<typename T>
void ds::AVLTree<T>::leftSwap(ds::AVLTreeNode<T>* &root)
{
    ds::AVLTreeNode<T>* oldTail = (ds::AVLTreeNode<T>*)root->rigt->left;
    ds::AVLTreeNode<T>* newTail = (ds::AVLTreeNode<T>*)root->rigt;
    root->rigt = oldTail;
    oldTail->rigt = newTail;
    newTail->left = NULL;

    newTail->height--;
    oldTail->height++;
}

template<typename T>
void ds::AVLTree<T>::insertNode(ds::AVLTreeNode<T>* &root, T value)
{
    ds::AVLTreeNode<T>* result = NULL;

    if(!root) root = new ds::AVLTreeNode<T>(value);
    else
    {
        if(this->comparer_(value, root->value) > 0)
        {
            this->insertNode((ds::AVLTreeNode<T>*&)root->rigt, value);
        }
        else
        {
            this->insertNode((ds::AVLTreeNode<T>*&)root->left, value);
        }
    }
    
    INT balance = this->getNodeHeight((ds::AVLTreeNode<T>*)root->rigt) - this->getNodeHeight((ds::AVLTreeNode<T>*)root->left);
    if(balance > 1)
    {
        // right tree bigger than left one
        if(this->getNodeHeight((ds::AVLTreeNode<T>*)root->rigt->rigt) >= this->getNodeHeight((ds::AVLTreeNode<T>*)root->rigt->left))
        {
                                        // right-right case
            this->leftRotate(root);     // do left rotation
        }
        else
        {
                                        // right-left case
            this->leftSwap(root);       // swap last two nodes
            this->leftRotate(root);     // do left rotation
        }
        
    }
    else if(balance < -1)
    {
        // left tree bigger than right one
        if(this->getNodeHeight((ds::AVLTreeNode<T>*)root->left->left) >= this->getNodeHeight((ds::AVLTreeNode<T>*)root->left->rigt))
        {
                                        // left-left case
            this->rigtRotate(root);     // do right rotation
        }
        else
        {
                                        // left-right case
            this->rigtSwap(root);       // swap last two nodes
            this->rigtRotate(root);     // do right rotation
        }
        
    }

    INT rh = getNodeHeight((ds::AVLTreeNode<T>*)root->rigt), lh = getNodeHeight((ds::AVLTreeNode<T>*)root->left);
    root->height = (rh > lh ? rh : lh) + 1;
}

template<typename T>
BOOLEAN ds::AVLTree<T>::insert(T value)
{
    this->insertNode(this->root_, value);
    this->count_++;
    
    return TRUE;
}

template<typename T>
INT ds::AVLTree<T>::getNodeHeight(ds::AVLTreeNode<T>* node)
{
    if(!node) return 0;
    else
    {
        return node->height;
    }
}

template<typename T>
ds::ArrayList<T>* ds::AVLTree<T>::toList(ds::ITreeTraverser<T>* traverser)
{
    return traverser->toList(this->root_);
}
#endif // !_AVL_TREE_H