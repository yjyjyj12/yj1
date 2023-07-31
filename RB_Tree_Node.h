#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H

#include "stdafx.h"

template <class T>
class RB_Tree_Node
{
public:
    RB_Tree_Node(T data_in);
    ~RB_Tree_Node(void);
    RB_Tree_Node* Left_child;   //指向左子节点的指针
    RB_Tree_Node* Right_child;
    RB_Tree_Node* Father_Node;
    T data;
    int color_tag;  //用来表示结点颜色: 0代表黑色，1代表红色
};

#endif