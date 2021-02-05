#ifndef _TREE_OPERATOR_H_
#define _TREE_OPERATOR_H_

#include "global.h"
#include "Trees/TreeNode.h"

namespace ds
{
    template<typename T>
    class ITreeVisitor
    {
    public:
        virtual void visit(const ds::TreeNode<T> *root) = 0;
    };

    template<typename T>
    class ITreeHost
    {
    public:
        virtual void accept(ITreeVisitor<T> &visitor) = 0;
    };
    





    template<typename T>
    class TreeHeight : public ITreeVisitor<T>
    {
    private:
        INT height_;
    private:
        void countHeight(INT& height, const ds::TreeNode<T> *root);
    public:
        void visit(const ds::TreeNode<T> *root) override;
        INT getHeight();
    };
}


template<typename T>
void ds::TreeHeight<T>::countHeight(INT& currentHeight, const ds::TreeNode<T> *root)
{
    if(root == NULL) return;
    currentHeight++;
    
    // count left branch
    if(root->left) 
    {
        this->countHeight(currentHeight, root->left);
    }
    if(root->rigt)
    {
        this->countHeight(currentHeight, root->rigt);
    }

    // record current height
    if(currentHeight > this->height_)
    {
        this->height_ = currentHeight;
    }
    currentHeight--;
}

template<typename T>
void ds::TreeHeight<T>::visit(const ds::TreeNode<T> *root)
{
    this->height_ = 0;
    INT currentHeight = 0;

    this->countHeight(currentHeight, root);
}

template<typename T>
INT ds::TreeHeight<T>::getHeight()
{
    return this->height_;
}

#endif // !_TREE_OPERATOR_H_