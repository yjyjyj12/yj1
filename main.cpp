// RB_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RB_Tree.h"
#include "RB_Tree.cpp"
int main(int argc, _TCHAR* argv[])
{
	RB_Tree<int>* m_RB_Tree = new RB_Tree<int>(1);
	for (int i = 2; i < 10;i++)
	{
		int a = i;
		m_RB_Tree->Insert_Node(a);
	}

	m_RB_Tree->Delete_Node(1);

    m_RB_Tree->print_Inorder(m_RB_Tree->Root_Node);	
	return 0;

}

