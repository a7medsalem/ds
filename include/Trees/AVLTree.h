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
        void balance(AVLTreeNode<T>* &node);
        void rebalance(AVLTreeNode<T>* &node);
        void removeNode(AVLTreeNode<T>* &node);
        AVLTreeNode<T>*& findNode(AVLTreeNode<T>* &node, T value);
        //
        AVLTreeNode<T>*& getInorderPredecessor(AVLTreeNode<T>* &node);
        INT updateNodeHeight(ds::AVLTreeNode<T>* node);
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
        BOOLEAN contains(T value);
        BOOLEAN removeOne(T value);
        BOOLEAN removeAll(T value);

        INT getCount();
        ArrayList<T>* toList(ITreeTraverser<T>* traverser);
    };
}





/********************************************/
/*                                          */
/*                 AVLTree                  */
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
ds::AVLTreeNode<T>*& ds::AVLTree<T>::getInorderPredecessor(ds::AVLTreeNode<T>* &node)
{
    ds::TreeNode<T>* inorder = node->left;
    if(!inorder->rigt) return (ds::AVLTreeNode<T>*&)node->left;

    while(inorder->rigt->rigt)
    {
        inorder = inorder->rigt;
    }
    return (ds::AVLTreeNode<T>*&)inorder->rigt;
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
INT ds::AVLTree<T>::getNodeHeight(ds::AVLTreeNode<T>* node)
{
    if(!node) return 0;
    else
    {
        return node->height;
    }
}

template<typename T>
void ds::AVLTree<T>::balance(ds::AVLTreeNode<T>* &node)
{
    INT balanceFactor = this->getNodeHeight((ds::AVLTreeNode<T>*)node->rigt) - this->getNodeHeight((ds::AVLTreeNode<T>*)node->left);
    if(balanceFactor > 1)
    {
        // right tree bigger than left one
        if(this->getNodeHeight((ds::AVLTreeNode<T>*)node->rigt->rigt) >= this->getNodeHeight((ds::AVLTreeNode<T>*)node->rigt->left))
        {
                                        // right-right case
            this->leftRotate(node);     // do left rotation
        }
        else
        {
                                        // right-left case
            this->leftSwap(node);       // swap last two nodes
            this->leftRotate(node);     // do left rotation
        }
        
    }
    else if(balanceFactor < -1)
    {
        // left tree bigger than right one
        if(this->getNodeHeight((ds::AVLTreeNode<T>*)node->left->left) >= this->getNodeHeight((ds::AVLTreeNode<T>*)node->left->rigt))
        {
                                        // left-left case
            this->rigtRotate(node);     // do right rotation
        }
        else
        {
                                        // left-right case
            this->rigtSwap(node);       // swap last two nodes
            this->rigtRotate(node);     // do right rotation
        }
    }

    INT rh = getNodeHeight((ds::AVLTreeNode<T>*)node->rigt), lh = getNodeHeight((ds::AVLTreeNode<T>*)node->left);
    node->height = (rh > lh ? rh : lh) + 1;
}

template<typename T>
void ds::AVLTree<T>::insertNode(ds::AVLTreeNode<T>* &root, T value)
{
    if(!root) root = new ds::AVLTreeNode<T>(value);
    else
    {
        INT compare = this->comparer_(value, root->value);
        if(compare > 0)
        {
            this->insertNode((ds::AVLTreeNode<T>*&)root->rigt, value);
        }
        else if(compare < 0)
        {
            this->insertNode((ds::AVLTreeNode<T>*&)root->left, value);
        }
        else
        {
            root->count++; return;
        }
    }
    //
    this->balance(root);
}

template<typename T>
ds::AVLTreeNode<T>*& ds::AVLTree<T>::findNode(ds::AVLTreeNode<T>* &node, T value)
{
    if(node == NULL) return node;

    INT compareResult = this->comparer_(value, node->value);
    //
    if(compareResult == 0)
    {
        return node;
    }
    else if(compareResult > 0)
    {
        return this->findNode((ds::AVLTreeNode<T>*&)node->rigt, value);
    }
    else
    {
        return this->findNode((ds::AVLTreeNode<T>*&)node->left, value);
    }
}

template<typename T>
INT ds::AVLTree<T>::updateNodeHeight(ds::AVLTreeNode<T>* node)
{
    if(!node) return 0;
    //
    if(!node->left && !node->rigt)
    {
        return node->height = 1;
    }
    else
    {
        INT rh = updateNodeHeight((ds::AVLTreeNode<T>*)node->rigt), lh = updateNodeHeight((ds::AVLTreeNode<T>*)node->left);
        return node->height = (rh > lh ? rh : lh) + 1;
    }
}

template<typename T>
void ds::AVLTree<T>::removeNode(ds::AVLTreeNode<T>* &node)
{
    // if node has two children
    if(node->left && node->rigt)
    {
        ds::AVLTreeNode<T>* temp = node;
        ds::AVLTreeNode<T>*& predecessor = this->getInorderPredecessor(node);
        if(predecessor == node->left)
        {
            predecessor->rigt = node->rigt;
            node = (ds::AVLTreeNode<T>*)node->left;
        }
        else
        {
            ds::AVLTreeNode<T>*& preLeft = (ds::AVLTreeNode<T>*&)predecessor->left;
            predecessor->left = node->left;
            predecessor->rigt = node->rigt;
            node = predecessor;
            //
            predecessor = preLeft;
        }
        
        delete temp;
    }
    // if node has one child
    else if(node->left)
    {
        ds::AVLTreeNode<T>* temp = node;
        node = (ds::AVLTreeNode<T>*)node->left;
        delete temp;
    }
    else if(node->rigt)
    {
        ds::AVLTreeNode<T>* temp = node;
        node = (ds::AVLTreeNode<T>*)node->rigt;
        delete temp;
    }
    // if node has no children
    else
    {
        delete node;
        node = NULL;
    }
}

template<typename T>
void ds::AVLTree<T>::rebalance(ds::AVLTreeNode<T>*& node)
{
    if(!node) return;
    if(node->left) this->rebalance((ds::AVLTreeNode<T>*&)node->left);
    if(node->rigt) this->rebalance((ds::AVLTreeNode<T>*&)node->rigt);
    //
    this->balance(node);
}

template<typename T>
BOOLEAN ds::AVLTree<T>::insert(T value)
{
    this->insertNode(this->root_, value);
    this->count_++;
    
    return TRUE;
}

template<typename T>
BOOLEAN ds::AVLTree<T>::contains(T value)
{
    return this->findNode(this->root_, value) != NULL;
}

template<typename T>
BOOLEAN ds::AVLTree<T>::removeOne(T value)
{
    ds::AVLTreeNode<T>*& node = this->findNode(this->root_, value);
    if(node != NULL)
    {
        if(node->count > 1)
        {
            node->count--;
        }
        else
        {
            this->removeNode(node);
            this->rebalance(this->root_);
        }
        
        this->count_--;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

template<typename T>
BOOLEAN ds::AVLTree<T>::removeAll(T value)
{
    ds::AVLTreeNode<T>*& node = this->findNode(this->root_, value);
    if(node != NULL)
    {
        this->count_ -= node->count;
        this->removeNode(node);
        this->rebalance(this->root_);
        //
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

template<typename T>
INT ds::AVLTree<T>::getCount()
{
    return this->count_;
}

template<typename T>
ds::ArrayList<T>* ds::AVLTree<T>::toList(ds::ITreeTraverser<T>* traverser)
{
    return traverser->toList(this->root_);
}
#endif // !_AVL_TREE_H