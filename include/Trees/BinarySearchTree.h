#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include <functional>
#include "global.h"
#include "ArrayList.h"
#include "Trees/TreeNode.h"
#include "Trees/TreeTraverser.h"

namespace ds
{
    template<typename T>
    class BinarySearchTree
    {
    private:
        TreeNode<T> *root_;
        std::function<INT(T,T)> comparer_;
        INT count_;
    private:
        TreeNode<T>* insertNode(ds::TreeNode<T>* &root, T value);
        TreeNode<T>*& findNode(ds::TreeNode<T>* &node, T value);
        TreeNode<T>*& getInorderPredecessor(ds::TreeNode<T>* &node);
        void removeNode(ds::TreeNode<T>* &node);
    public:
        BinarySearchTree<T>();
        BinarySearchTree<T>(std::function<INT(T,T)> comparer);
        ~BinarySearchTree<T>();
    public:
        BOOLEAN insert(T value);
        BOOLEAN contains(T value);
        BOOLEAN removeOne(T value);
        BOOLEAN removeAll(T value);

        INT getCount();
        ArrayList<T>* toList(ITreeTraverser<T> *traverser);
    };
}




/********************************************/
/*                                          */
/*            BinarySearchTree              */
/*                                          */
/********************************************/


template<typename T>
ds::BinarySearchTree<T>::BinarySearchTree()
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
ds::BinarySearchTree<T>::BinarySearchTree(std::function<INT(T,T)> comparer)
{
    this->count_ = 0;
    this->root_ = NULL;
    this->comparer_ = comparer;
}

template<typename T>
ds::BinarySearchTree<T>::~BinarySearchTree()
{
    // no thing to do here... yet
}

template<typename T>
ds::TreeNode<T>* ds::BinarySearchTree<T>::insertNode(ds::TreeNode<T>* &root, T value)
{
    if(!root)  return (root = new ds::TreeNode<T>(value));
    else
    {
        INT result = this->comparer_(value, root->value);
        if(result > 0)
        {
            return this->insertNode(root->rigt, value);
        }
        else if(result < 0)
        {
            return this->insertNode(root->left, value);
        }
        else
        {
            // if same value, insert new node to direct left of current node
            // useful for delete bulk elements. if this part removed, re-modify removeAll function
            ds::TreeNode<T>* inserted = new ds::TreeNode<T>(value);
            inserted->left = root->left;
            root->left = inserted;
            return inserted;
        }
    }
}

template<typename T>
BOOLEAN ds::BinarySearchTree<T>::insert(T value)
{
    if(this->insertNode(this->root_, value))
    {
        this->count_++;
        return TRUE;
    }
    
    return FALSE;
}

template<typename T>
ds::TreeNode<T>*& ds::BinarySearchTree<T>::findNode(ds::TreeNode<T>* &node, T value)
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
        return this->findNode(node->rigt, value);
    }
    else
    {
        return this->findNode(node->left, value);
    }
}

template<typename T>
BOOLEAN ds::BinarySearchTree<T>::contains(T value)
{
    return this->findNode(this->root_, value) != NULL;
}

template<typename T>
ds::TreeNode<T>*& ds::BinarySearchTree<T>::getInorderPredecessor(ds::TreeNode<T>* &node)
{
    ds::TreeNode<T>* inorder = node->left;
    if(!inorder->rigt) return node->left;

    while(inorder->rigt->rigt)
    {
        inorder = inorder->rigt;
    }
    return inorder->rigt;
}

template<typename T>
void ds::BinarySearchTree<T>::removeNode(ds::TreeNode<T>* &node)
{
    // if node has two children
    if(node->left && node->rigt)
    {
        ds::TreeNode<T>* temp = node;
        ds::TreeNode<T>*& predecessor = this->getInorderPredecessor(node);
        if(predecessor == node->left)
        {
            predecessor->rigt = node->rigt;
            node = node->left;
        }
        else
        {
            ds::TreeNode<T>* preLeft = predecessor->left;
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
        ds::TreeNode<T>* temp = node;
        node = node->left;
        delete temp;
    }
    else if(node->rigt)
    {
        ds::TreeNode<T>* temp = node;
        node = node->rigt;
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
BOOLEAN ds::BinarySearchTree<T>::removeOne(T value)
{
    ds::TreeNode<T>*& node = this->findNode(this->root_, value);
    if(node != NULL)
    {
        this->removeNode(node);
        this->count_--;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

template<typename T>
BOOLEAN ds::BinarySearchTree<T>::removeAll(T value)
{
    ds::TreeNode<T>*& node = this->findNode(this->root_, value);
    if(node != NULL)
    {
        do
        {
            this->removeNode(node);
            this->count_--;
        }
        while (this->comparer_(node->value, value) == 0);
        //
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

template<typename T>
INT ds::BinarySearchTree<T>::getCount()
{
    return this->count_;
}

template<typename T>
ds::ArrayList<T>* ds::BinarySearchTree<T>::toList(ds::ITreeTraverser<T> *traverser)
{
    return traverser->toList(this->root_);
}

#endif // !_BINARY_SEARCH_TREE_H