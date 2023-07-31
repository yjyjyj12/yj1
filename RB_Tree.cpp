#include "stdafx.h"
#include "RB_Tree.h"

template <class T>
RB_Tree<T>::RB_Tree(T Root_Data):Root_Node(NULL)
{	
	if (Root_Node == NULL)
	{
		Root_Node = new RB_Tree_Node<T>(Root_Data);
		Root_Node->color_tag = 0;
	}
}

template <class T>
RB_Tree<T>::~RB_Tree()
{

}


//函数功能：向红黑树中插入一个节点
//入口参数：插入的数据
//返回值：无
template <class T>
void RB_Tree<T>::Insert_Node(T insert_data)
{
	
	RB_Tree_Node<T>* temp_Node = Root_Node;
	while(temp_Node != NULL)
	{
		if (insert_data > temp_Node->data)
		{
			if (temp_Node->Right_child == NULL)
			{
				temp_Node->Right_child = new RB_Tree_Node<T>(insert_data);
				temp_Node->Right_child->color_tag = 1;
				temp_Node->Right_child->Father_Node = temp_Node;
				if (temp_Node->color_tag == 1)
				{
					Fix_Tree_Insert(temp_Node->Right_child);
				}				
				break;
			}
			else
			{
				temp_Node = temp_Node->Right_child;
			}			
		}
		else
		{
			if (temp_Node->Left_child == NULL)
			{
				temp_Node->Left_child  = new RB_Tree_Node<T>(insert_data);
				temp_Node->Left_child->color_tag = 1;
				temp_Node->Left_child->Father_Node = temp_Node;
				if (temp_Node->color_tag == 1)
				{
					Fix_Tree_Insert(temp_Node->Left_child);
				}				
				break;
			}
			else
			{
				temp_Node = temp_Node->Left_child;
			}			
		}
	}	
}

/************************************************************************/
/* 函数功能：插入节点后修整红黑树，保证满足性质                         */
// 入口参数：插入的节点
// 返回值：无
//                             pp            插入结点的祖父结点
//                            /  \
//                            p   s          插入结点的父节点，叔叔结点
//                           /
//                          I                插入结点
/************************************************************************/
template <class T>
void RB_Tree<T>::Fix_Tree_Insert(RB_Tree_Node<T>* current_Node)
{
	RB_Tree_Node<T>* temp_Node = current_Node;
	RB_Tree_Node<T>* uncle_Node;
	while (true)
	{
		//红黑树为空树
		if (temp_Node->Father_Node == nullptr)
		{
			break;
		}
		//插入结点的父节点为黑结点
		if (temp_Node->Father_Node->color_tag != 1) 
		{
			break;
		}
		RB_Tree_Node<T>* father_Node = temp_Node->Father_Node;
		RB_Tree_Node<T>* grand_Node = father_Node->Father_Node;
		if (grand_Node)
		{
			//父亲结点是祖父结点的左子结点
			if (father_Node == grand_Node->Left_child)
			{
				//叔叔结点
				uncle_Node = grand_Node->Right_child;
				//如果叔叔结点存在
				if (uncle_Node)
				{
					//叔叔结点为红色    4.1
					if (uncle_Node->color_tag == 1)
					{
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;
						grand_Node->color_tag = 1;
						temp_Node = grand_Node;
					}
					//叔叔结点为黑色，插入结点是父节点的左子结点    4.2.1
					else if(temp_Node == father_Node->Left_child)
					{
						father_Node->color_tag = 0;
						grand_Node->color_tag = 1;
						Right_Rotate(grand_Node);
					}
					//叔叔结点为黑色，插入结点是父节点的右子结点   4.2.2
					else
					{
						Left_Rotate(father_Node);
						temp_Node = father_Node;
					}
				}
				//叔叔结点不存在
				else
				{
					//叔叔结点为黑色，插入结点是父节点的左子结点
					if(temp_Node == father_Node->Left_child)
					{
						father_Node->color_tag = 0;
						grand_Node->color_tag = 1;
						Right_Rotate(grand_Node);
					}
					//叔叔结点为黑色，插入结点是父节点的左子结点
					else
					{
						Left_Rotate(father_Node);
						temp_Node = father_Node;
					}
				} 
			}

			//父亲结点是祖父结点的右子结点
			else
			{
				//叔叔结点
				uncle_Node = grand_Node->Left_child; 
				//如果叔叔结点存在
				if (uncle_Node)
				{
					//叔叔结点为红色
					if (uncle_Node->color_tag == 1)
					{
						uncle_Node->color_tag = 0;
						father_Node->color_tag = 0;
						grand_Node->color_tag = 1;
						temp_Node = grand_Node;
					}
					//叔叔结点为黑色，插入结点是父节点的右子结点
					else if(temp_Node == father_Node->Right_child)
					{
						father_Node->color_tag = 0;
						grand_Node->color_tag = 1;
						Left_Rotate(grand_Node);
					}
					//叔叔结点为黑色，插入结点是父节点的左子结点
					else
					{
						Right_Rotate(father_Node);
						temp_Node = father_Node;
					}
				}
				//叔叔结点不存在
				else
				{
					//叔叔结点为黑色，插入结点是父节点的右子结点
					if(temp_Node == father_Node->Right_child)
					{
						father_Node->color_tag = 0;
						grand_Node->color_tag = 1;
						Left_Rotate(grand_Node);
					}
					//叔叔结点为黑色，插入结点是父节点的左子结点
					else
					{
						Right_Rotate(father_Node);
						temp_Node = father_Node;
					}
				} 
			
			}
		}
	}
	Root_Node->color_tag = 0;
}


//函数功能：对当前节点进行左旋操作
//入口参数：左旋的当前节点
//返回值：无
template <class T>
void RB_Tree<T>::Left_Rotate(RB_Tree_Node<T>* current_Node)
{
    RB_Tree_Node<T>*Right_child = current_Node->Right_child;
    RB_Tree_Node<T>*father_Node = current_Node->Father_Node;
    current_Node->Right_child = Right_child->Left_child;
    Right_child->Father_Node = father_Node;
    if (father_Node == nullptr)
    {
        Root_Node = Right_child;
    }
    else if(current_Node == father_Node->Left_child)
    {
        father_Node->Left_child = Right_child;
    }
    else {
        father_Node->Right_child = Right_child;
    }

    Right_child->Left_child = current_Node;
    current_Node->Father_Node = Right_child;
}


//函数功能：对当前节点进行右旋操作
//入口参数：右旋的当前节点
//返回值：无
template <class T>
void RB_Tree<T>::Right_Rotate(RB_Tree_Node<T>* current_Node)
{
    RB_Tree_Node<T>*Left_child = current_Node->Left_child;
    RB_Tree_Node<T>*father_Node = current_Node->Father_Node;
    current_Node->Left_child = Left_child->Right_child;
    Left_child->Father_Node = father_Node;
    if (father_Node == nullptr)
    {
        Root_Node = Left_child;
    }
    else if(current_Node == father_Node->Left_child)
    {
        father_Node->Left_child = Left_child;
    }
    else {
        father_Node->Right_child = Left_child;
    }

    Left_child->Right_child = current_Node;
    current_Node->Father_Node = Left_child;
}


//函数功能：寻找当前节点的中序后继节点
//入口参数：当前节点
//返回值：当前节点的后继节点
//后继节点在红黑树中定义为比给定节点的值大的最小节点
template <class T>			
RB_Tree_Node<T>* RB_Tree<T>::Find_Successor_Node(RB_Tree_Node<T>* current_Node)
{

    RB_Tree_Node<T>* temp_Node = current_Node;
    while (temp_Node->Left_child != NULL)
    {
        temp_Node = temp_Node->Left_child;
    }

    return temp_Node;
}


// 函数功能：清除该节点相关的所有信息                                   */
// 入口参数：当前节点
// 返回值：无
template <class T>
void RB_Tree<T>::erase_Node(RB_Tree_Node<T>* Node_del)
{
    if (Node_del->Father_Node != nullptr)
    {
        Node_del->Father_Node = nullptr;
    }
    Node_del->color_tag = nullptr;  //error
    Node_del->Left_child = nullptr;
    Node_del->Right_child = nullptr;
    Node_del->data = nullptr;
    delete Node_del;
}


/************************************************************************/
/* 函数功能：寻找值为data的节点                         */
// 入口参数：查找的值
// 返回值：无
/************************************************************************/
template <class T>
RB_Tree_Node<T>* RB_Tree<T>::find(T data) {
    RB_Tree_Node<T> *q = this->Root_Node;
    while (q != NULL && q->data != data) {      // 查询操作
        if (q->data > data) {      // 如果 q->value 小于 data ，查找左子树
            q = q->Left_child;
        }
        else {      // 否则查找右子树
            q = q->Right_child;
        }
    }
    return q;       // 返回结果
}


/************************************************************************/
/* 函数功能：将 v 移植到 u 的位置，仅改变 u 的父节点的子节点和 v 的父节点                        */
// 入口参数：被替换的节点 待移植的节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::transplant(RB_Tree_Node<T> *u, RB_Tree_Node<T> *v) {
    v->Father_Node = u->Father_Node;      // 更新 v 的父节点
    if (u->Father_Node == NULL) {     // 如果这棵红黑树的根节点为 u，更新根节点
        this->Root_Node = v;
    }
    else if (u->Father_Node->Left_child == u) {     // u 是左孩子
        u->Father_Node->Left_child = v;
    }
    else {      // u 是右孩子
        u->Father_Node->Right_child = v;
    }
}


/************************************************************************/
/* 函数功能：从红黑树中搜寻要删除的数据节点                             */
// 入口参数：删除的数据
// 返回值：true表示删除成功 false表示删除失败
/************************************************************************/
template<class T>
bool RB_Tree<T>::Delete_Node(T data)
{	
	RB_Tree_Node<T> *node = find(data);
	if (node == NULL) {      // 没有该元素，删除失败
        return false;
    }
    del_node(node);     // 删除该节点
    return true;
}


/************************************************************************/
/* 函数功能：删除指定节点                             */
// 入口参数：待删除的节点
// 返回值：无
/************************************************************************/
template <class T>
void RB_Tree<T>::del_node(RB_Tree_Node<T> *del) {
    RB_Tree_Node<T> *x , *f;        // x 为最终影响了红黑树的节点，即调整开始的位置（可能为 nullptr）， f 是调整位置的父节点
    int color = del->color_tag;        // 记录最终被删除的节点的颜色
    // 只有右子树
    if (del->Left_child == NULL && del->Right_child != NULL) {        
        x = del->Right_child;
        transplant(del, x);
        f = x->Father_Node;
    }

    // 只有左子树
    else if (del->Left_child != NULL && del->Right_child == NULL) {       
        x = del->Left_child;
        transplant(del, x);
        f = x->Father_Node;
    }
    
    // 左右子树均不为空，找个后继节点将del取而代之
    else if (del->Left_child != NULL && del->Right_child != NULL) {       
        RB_Tree_Node<T> *y = Find_Successor_Node(del->Right_child);       // 找到右子树中最小的节点，用来替换 del
        color = y->color_tag;       // 更新 color ， 因为这个时候要删除的节点是 y
        x = y->Right_child;       // 此时删除 del ，用 y 去替换 del 。所以就变成了删除 y ，所以 x 和 f 都要更新
        f = y->Father_Node;
        if (y->Father_Node != del) {     // y 不是 del 的右子节点
            if (y->Right_child != NULL) {      // y 的左子树必然为空，因为 y 是最左侧节点，所以此时判断 y 的右子节点是否为空
                transplant(y, y->Right_child);        // 移植 y 的右子树
            }
            else {
                y->Father_Node->Left_child = NULL;      // 此时将 y 的父节点的左子节点更新为 nullptr
            }
            y->Right_child = del->Right_child;      // 更新 y 的右子树
            y->Right_child->Father_Node = y;
        }
        else {      // 否则此时的父节点为 y
            f = y;
        }
        transplant(del, y);     // 将 y 移植到 del 处
        y->Left_child = del->Left_child;        // 更新 y 的左子树
        y->Left_child->Father_Node = y;
        y->color_tag = del->color_tag;      // 更新 y 的颜色
    }

    // del 的左右子树均为空
    else {      
        if (del->Father_Node == NULL) {       // 如果 del 是根节点，直接将根节点设置为 nullptr
            this->Root_Node = NULL;
            return;
        }
        else {      // 如果 del 不是根节点
            x = NULL;
            if  (del->Father_Node->Left_child == del) {        // 更新父节点的子节点
                del->Father_Node->Left_child = NULL;
            }
            else {
                del->Father_Node->Right_child = NULL;
            }
        }
        f = del->Father_Node;
    }

    // 如果被删除的节点的颜色为黑色
    if (color == 0) {       
        Fix_Tree_Delete(x, f);        // 调整红黑树
    }
}



/************************************************************************/
/* 函数功能：删除节点后修整红黑树，保证满足性质                              */
// 入口参数：删除后需要修正的结点和它的父节点
// 返回值: void
/************************************************************************/
/*		
				  P
				/	\
				R    S
					/ \
				  SL  SR   */
template <class T>
void RB_Tree<T>::Fix_Tree_Delete(RB_Tree_Node<T> *x, RB_Tree_Node<T> *f) {
    while (x != Root_Node && (x == NULL || x->color_tag == 0)) {      // 需要调整的情况

        // x 在 f 的左子树的情况
        if (x == f->Left_child) {     
            RB_Tree_Node<T> *bro = f->Right_child;     // 兄弟节点

            // 2.1.1兄弟节点为红色
            if (bro->color_tag == 1) {        
                f->color_tag = 1;
                bro->color_tag = 0;
                Left_Rotate(f);
                bro = f->Right_child;     // 兄弟节点发生改变   #
            }

            //2.1.2.3
            else if ((bro->Right_child == NULL && bro->Left_child == NULL) || (bro->Right_child->color_tag == 0 && bro->Left_child->color_tag == 0)) {        
                bro->color_tag = 1;       // bro 改为红色
                x = f;      // 以 f 为根的子树的黑色节点减少了 1 ，从 x 开始往上调整
                f = x->Father_Node;      // 更新 f
                continue;       // 也有可能此时 x 为红色，那么直接跳出循环，把 x 染成黑色即可
            }

            //2.1.2.2
            else if (bro->Left_child != NULL && bro->Left_child->color_tag == 1 && (bro->Right_child == NULL || bro->Right_child->color_tag == 0)) {       
                bro->color_tag = 1;
                bro->Left_child->color_tag = 0;      // 互换颜色
                Right_Rotate(bro);      // 旋转
                bro = bro->Father_Node;      // 更新兄弟节点
            }

                // 2.1.2.1
            bro->color_tag = f->color_tag ;        // 交换兄弟节点和父节点的有颜色
            f->color_tag = 0 ;
            bro->Right_child->color_tag = 0 ;     // 兄弟节点的右子节点改为黑色
            Left_Rotate(f) ;        // 旋转
            x = Root_Node ;       // 左右平衡了，直接跳出循环， x 设置为根节点，出循环后维护根节点为黑色，保持性质二
        }

        // x 在 f 的右子树的情况
        else {
            RB_Tree_Node<T> *bro = f->Left_child;     // 兄弟节点

            // 2.2.1兄弟节点为红色
            if (bro->color_tag == 1) {        
                f->color_tag = 1;
                bro->color_tag = 0;
                Right_Rotate(f);
                bro = f->Left_child;     // 兄弟节点发生改变
            }

            //2.2.2.3
            else if ((bro->Right_child == NULL && bro->Left_child == NULL) || ((bro->Right_child != NULL && bro->Left_child != NULL) && (bro->Right_child->color_tag == 0 && bro->Left_child->color_tag == 0))) {        
                bro->color_tag = 1;       // bro 改为红色
                x = f;      // 以 f 为根的子树的黑色节点减少了 1 ，从 x 开始往上调整
                f = x->Father_Node;      // 更新 f
                continue;       // 也有可能此时 x 为红色，那么直接跳出循环，把 x 染成黑色即可
            }

            //2.2.2.2
            else if (bro->Right_child != NULL && bro->Right_child->color_tag == 1 && (bro->Left_child == NULL || bro->Left_child->color_tag == 0)) {        
                bro->color_tag = 1;
                bro->Right_child->color_tag = 0;      // 互换颜色
                Left_Rotate(bro);      // 旋转
                bro = bro->Father_Node;      // 更新兄弟节点
            }

            //2.2.2.1    
            bro->color_tag = f->color_tag ;        // 交换兄弟节点和父节点的有颜色
            f->color_tag = 0 ;
            bro->Left_child->color_tag = 0 ;     // 兄弟节点的右子节点改为黑色
            Right_Rotate(f) ;        // 旋转
            x = Root_Node ;       // 左右平衡了，直接跳出循环， x 设置为根节点，出循环后维护根节点为黑色，保持性质二
        }
    }
    x->color_tag = 0;      // 如果此时 x 为根节点，将 x 染为黑色。也有可能 x 是情况二中跳出来的，直接将 x 染成黑色即可
}



//函数功能：中序遍历并输出
// 入口参数：中序遍历的root
// 返回值: void
template<class T>
void RB_Tree<T>::print_Inorder(RB_Tree_Node<T>* root)
{
	if (root == NULL) return;

	print_Inorder(root->Left_child);
	std::cout << root->data << std::endl;
	print_Inorder(root->Right_child);
}