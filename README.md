# 二叉树

每个结点最多有两个子树的树结构

# AVL树

> 又称平衡二叉树，这种左右子树的高度相差不超过 1 的树，二叉搜索树一定程度上可以提高效率

## 平衡二叉树的来由

![img](https://pic3.zhimg.com/80/v2-f8e97ce8bff6af406ca2e3399be7ad5e_720w.webp)

如果将此改造为平衡二叉树

![img](https://pic4.zhimg.com/80/v2-fd82c10388b933d1c09d1fbe297984ef_720w.webp)

效率从O(N)提高到O(logn)



## 平衡因子

> 定义：某节点的左子树与右子树的高度差，在一棵平衡二叉树中，节点的平衡因子只能取 0 、1 或者 -1 ，分别对应着左右子树等高，左子树比较高，右子树比较高。

![img](https://pic4.zhimg.com/80/v2-6f2e86b1231b5df131813dc45f8f98cb_720w.webp)

![img](https://pic2.zhimg.com/80/v2-7e5f77810ff2a3a0ae6ae0c0d9443ac1_720w.webp)

![img](https://pic2.zhimg.com/80/v2-ba3929eafa5c6a32b1db0402850a321d_720w.webp)



## 左旋

> 以某个结点作为支点(旋转结点 —— p)，其右子结点  v  变为 p 的父结点，右子结点的左子结点变为旋转结点的右子结点。

![img](https://upload-images.jianshu.io/upload_images/2392382-a95db442f1b47f8a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1000/format/webp)



## 右旋

> 以某个结点作为支点(旋转结点 —— p)，其左子结点 F 变为 p 的父结点，左子结点的右子结点变为旋转结点的左子结点。

![img](https://upload-images.jianshu.io/upload_images/2392382-0676a8e2a12e2a0b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1000/format/webp)



# 红黑树

[30张图带你彻底理解红黑树 - 简书 (jianshu.com)](https://www.jianshu.com/p/e136ec79235c/)

![在这里插入图片描述](https://img-blog.csdnimg.cn/688c3281a2734019832e12bf28643278.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAMjAyMWRyYWdvbg==,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

## 性质

1. 每个结点不是红色就是黑色
2. 根结点是黑色的
3. 如果一个结点是红色的，则它的两个孩子结点是黑色的
4. 对于每个结点，从该结点到其所有后代叶子结点的简单路径上，均包含相同数目的黑色结点
5. 每个叶子结点都是黑色的（此处的叶子结点指定是空结点）



## 最长路径不超过最短两倍

根据红黑树性质3知，红黑树不会出现连续的红色结点，根据性质4又可以得出，从某一结点到其后代叶子结点的所有路径上包含的黑色结点的数目是相同的。

我们假设在红黑树中，从根到叶子的所有路径上包含的黑色结点的个数都是N个，那么最短路径就是全部由黑色结点构成的路径，即长度为N。

![在这里插入图片描述](https://img-blog.csdnimg.cn/be20a16e9c8b4758a771ba366dbc256f.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAMjAyMWRyYWdvbg==,size_20,color_FFFFFF,t_70,g_se,x_16)

而最长可能路径就是由一黑一红结点构成的路径，该路径当中黑色结点与红色结点的数目相同，即长度为2N。

![在这里插入图片描述](https://img-blog.csdnimg.cn/69140de321164a74be9c1d787e8404f6.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAMjAyMWRyYWdvbg==,size_20,color_FFFFFF,t_70,g_se,x_16)



## 左旋

![image-20230626173116889](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230626173116889.png)

```c++
RB_Tree_Node<T>*Right_child = current_Node->Right_child;
					18号			  11号    的	右孩子	
RB_Tree_Node<T>*father_Node = current_Node->Father_Node;
					7号			  11号    的  父节点					
current_Node->Right_child = Right_child->Left_child;
		11号  的	右节点			    18号 的 左孩子为14
Right_child->Father_Node = father_Node;
	18号	  的  父节点		   7号
Right_child->Left_child = current_Node;
    18号   的  左节点           11号
current_Node->Father_Node = Right_child;
      11号  的 父节点           18号
```



```C++
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
```



三个语句分别对应三种情况

1. 第一个图没有7节点，即11没有父节点
2. 第一个图的左旋在7的左枝
3. 第一个图的左旋在7的右枝，即本图



## 右旋

To Do

## 插入

![img](https://upload-images.jianshu.io/upload_images/2392382-9ac3d6b69ef7ead3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/662/format/webp)

![image-20230628191146250](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230628191146250.png

![红黑树的插入](D:\桌面\面试准备\知识点\红黑树的插入.png)

> 插入操作属于一种自上而下，而它的修整操作属于自下而上的:每颗子树都能平衡，那么整棵树最终必能平衡



## 删除

- 情景1：若删除结点无子结点，直接删除

- 情景2：若删除结点只有一个子结点，用子结点替换删除结点

- 情景3：若删除结点有两个子结点，用后继结点（大于删除结点的最小结点）替换删除结点

  

![img](https://upload-images.jianshu.io/upload_images/2392382-db3468a5977ad998.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1000/format/webp)

![红黑树的删除](D:\桌面\面试准备\知识点\红黑树的删除.png)# yj
# 
