#ifndef _TREE_TRAVERSER_H
#define _TREE_TRAVERSER_H

#include "global.h"
#include "ArrayList.h"
#include "Trees/TreeNode.h"

namespace ds
{
    template<typename T>
    class ITreeTraverser
    {
    public:
        virtual ArrayList<T>* toList(const ds::TreeNode<T> *root) = 0;
    };

    template<typename T>
    class InorderTraverser : public ITreeTraverser<T>
    {
    public:
        void addNode(ArrayList<T>* list, const ds::TreeNode<T> *node);
    public:
        ArrayList<T>* toList(const ds::TreeNode<T> *root) override;
    };
}


/********************************************/
/*                                          */
/*            InorderTraverser              */
/*                                          */
/********************************************/


template<typename T>
void ds::InorderTraverser<T>::addNode(ds::ArrayList<T> *list, const ds::TreeNode<T> *node)
{
    // add left branch
    if(node->left) 
    {
        this->addNode(list, node->left);
    }
    // add root node
    list->add(node->value);
    // add right branch
    if(node->rigt)
    {
        this->addNode(list, node->rigt);
    }
}

template<typename T>
ds::ArrayList<T>* ds::InorderTraverser<T>::toList(const ds::TreeNode<T> *root)
{
    ds::ArrayList<T>* list = new ds::ArrayList<T>();
    this->addNode(list, root);
    
    return list;
}

#endif  // !_TREE_TRAVERSER_H