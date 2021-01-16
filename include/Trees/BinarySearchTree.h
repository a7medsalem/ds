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
    public:
        BinarySearchTree<T>();
        BinarySearchTree<T>(std::function<INT(T,T)> comparer);
        ~BinarySearchTree<T>();
    public:
        BOOLEAN insert(T value);
        BOOLEAN contains();
        BOOLEAN removeOne();
        BOOLEAN removeAll();

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
        if(this->comparer_(value, root->value) > 0)
        {
            return this->insertNode(root->rigt, value);
        }
        else
        {
            return this->insertNode(root->left, value);
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