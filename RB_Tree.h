#ifndef RB_TREE_H
#define RB_TREE_H

#include "RB_Tree_Node.cpp"

template <class T>
class RB_Tree
{
public:
    RB_Tree(T Root_Data);
    ~RB_Tree();
    void Left_Rotate(RB_Tree_Node<T>* current_Node);    //左旋
    void Right_Rotate(RB_Tree_Node<T>* current_Node);   
    void Insert_Node(T insert_data);    //插入节点，将新节点插入红黑树中并保持红黑树的平衡
    void Fix_Tree_Insert(RB_Tree_Node<T>* current_Node);   //修复红黑树，当进行插入操作后可能破坏了红黑树的平衡，需要调用该函数进行修复

    void transplant(RB_Tree_Node<T> *u, RB_Tree_Node<T> *v);      // 移植函数
    bool Delete_Node(T data);     //删除节点，删除红黑树中指定的节点并保持红黑树的平衡
    void del_node(RB_Tree_Node<T> *del);       // 删除指定节点
    void Fix_Tree_Delete(RB_Tree_Node<T> *x, RB_Tree_Node<T> *f);
    RB_Tree_Node<T>* Find_Successor_Node(RB_Tree_Node<T>* current_Node);    //查找节点
    RB_Tree_Node<T>* find(T data);


    void erase_Node(RB_Tree_Node<T>*  Node_del); //擦除节点，将指定节点从红黑树中删除并保持平衡

    void print_Inorder(RB_Tree_Node<T>* root);  //中序遍历输出结点
    RB_Tree_Node<T>* Root_Node; //红黑树的根节点


};

#endif