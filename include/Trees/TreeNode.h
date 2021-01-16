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
    TreeNode *left;
    TreeNode *rigt;
  public:
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
}



/********************************************/
/*                                          */
/*               TreeNode                   */
/*                                          */
/********************************************/


template<typename T>
ds::TreeNode<T>::TreeNode(T value)
{
    this->value = value;
    this->left = NULL;
    this->rigt = NULL;
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

#endif // !_TREE_NODE_