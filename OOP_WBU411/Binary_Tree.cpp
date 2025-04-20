#include <iostream>
#include "Binary_Tree.h"
using namespace std;

Tree::Tree()
{
	root = nullptr;
}
Tree::~Tree()
{
	Del();
}

//������ �� ���������� ����
void Tree::Print(Elem* Node)
{
	//����������� ����� ������
	if (Node != nullptr)
	{
		//Print(Node->left);
		cout << Node->Name << ' ' <<
			Node->Match << ' ' <<
			Node->Opponent <<
			endl;
		Print(Node->left);
	}
}

//����� �� ���������� ����
Elem* Tree::Search(Elem* Node, char* key)
{
	//���� ���� ���� � ����� �� ���������
	while (Node != nullptr && strcmp(key, Node->Name) != 0)
	{
		if (strcmp(key, Node->Name) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	return Node;
}

//min �� ���������� ����
Elem* Tree::Min(Elem* Node)
{
	//����� ������ "������" ����
	if (Node != nullptr)
		while (Node->left != nullptr)
			Node = Node->left;
	return Node;
}

//max �� ���������� ����
Elem* Tree::Tree::Max(Elem* Node)
{
	//����� ������ "�������" ����
	if (Node != nullptr)
		while (Node->right != nullptr)
			Node = Node->right;
	return Node;
}

//"���������" ��� ���������� ����
Elem* Tree::Next(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		//���� ���� ������ �������
		if (Node->right != nullptr)
			return Min(Node->right);

		//�������� ����
		y = Node->parent;
		//���� Node �� ������ � Node ������
		while (y != nullptr && Node == y->right)
		{
			//�������� �����
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

//"����������" ��� ���������� ����
Elem* Tree::Previous(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		//���� ���� ����� �������
		if (Node->left != nullptr)
			return Max(Node->left);

		//�������� ����
		y = Node->parent;
		//���� Node �� ������ � Node �����
		while (y != nullptr && Node == y->left)
		{
			//�������� ����
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

//������� ����
void Tree::Insert(Elem* z)
{
	//�������� ���
	z->left = nullptr;
	z->right = nullptr;

	Elem* y = nullptr;
	Elem* Node = z;

	//����� �����
	while (Node != nullptr)
	{
		// ������� �������� 
		y = Node;
		if (strcmp(z->Name, Node->Name) < 0)
			Node = Node->left;
		else
			Node = Node->right;
		//��������� ��������
		z->parent = y;

		if (y == nullptr) //������� ������ (������������)
			root = z;
		//��� ���� ������?
		else if (strcmp(z->Name, y->Name) < 0)
			y->left = z;
		else
			y->right = z;
	}
}

//�������� ����� ��� ���������� ����
//0 - �������� ����� ������
void Tree::Del(Elem* z)
{
	//�������� �����
	if (z != nullptr)
	{
		Elem* Node, * y;

		//�� 2 �������
		if (z->left == nullptr || z->right == nullptr)
			y = z;
		else
			y = Next(z);

		if (y->left != nullptr)
			Node = y->left;
		else
			Node = y->right;

		if (Node != nullptr)
			root = Node;
		else if (y == y->parent->left)
			//����� �� ��������?
			y->parent->left = Node;
		else
			//������ �� ��������
			y->parent->right = Node;
		if (y != z)
		{
			//�������� ������ ����
			strcpy_s(z->Name, y->Name);
			strcpy_s(z->Opponent, y->Opponent);
			strcpy_s(z->Match, y->Match);
			z->OppPoints = y->OppPoints;
			z->OwnerPoints = y->OwnerPoints;
		}
		delete y;
	}
	else
		while (root != nullptr)
			Del(root);
}

//�������� ������
Elem* Tree::GetRoot()
{
	return root;
}