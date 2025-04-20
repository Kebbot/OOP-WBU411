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

//печать от указанного узла
void Tree::Print(Elem* Node)
{
	//рекурсивный обход дерева
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

//Поиск от указанного узла
Elem* Tree::Search(Elem* Node, char* key)
{
	//пока есть узлы и ключи не совпадают
	while (Node != nullptr && strcmp(key, Node->Name) != 0)
	{
		if (strcmp(key, Node->Name) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	return Node;
}

//min от указанного узла
Elem* Tree::Min(Elem* Node)
{
	//Поиск самого "Левого" узла
	if (Node != nullptr)
		while (Node->left != nullptr)
			Node = Node->left;
	return Node;
}

//max от указанного узла
Elem* Tree::Tree::Max(Elem* Node)
{
	//Поиск самого "Правого" узла
	if (Node != nullptr)
		while (Node->right != nullptr)
			Node = Node->right;
	return Node;
}

//"Следующий" для указанного узла
Elem* Tree::Next(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		//Если есть правый потомок
		if (Node->right != nullptr)
			return Min(Node->right);

		//родитель узла
		y = Node->parent;
		//Если Node не корень и Node справа
		while (y != nullptr && Node == y->right)
		{
			//Движемся вверх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

//"Предыдущий" для указанного узла
Elem* Tree::Previous(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		//если есть левый потомок
		if (Node->left != nullptr)
			return Max(Node->left);

		//Родитель узла
		y = Node->parent;
		//Если Node Не корень и Node слева
		while (y != nullptr && Node == y->left)
		{
			//Движемся верх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

//Вставка узла
void Tree::Insert(Elem* z)
{
	//Потомков нет
	z->left = nullptr;
	z->right = nullptr;

	Elem* y = nullptr;
	Elem* Node = z;

	//Поиск места
	while (Node != nullptr)
	{
		// Будущий родитель 
		y = Node;
		if (strcmp(z->Name, Node->Name) < 0)
			Node = Node->left;
		else
			Node = Node->right;
		//заполнить родителя
		z->parent = y;

		if (y == nullptr) //элемент первый (единственный)
			root = z;
		//чей ключ больше?
		else if (strcmp(z->Name, y->Name) < 0)
			y->left = z;
		else
			y->right = z;
	}
}

//Удаление ветки для указанного узла
//0 - Удаление всего дерева
void Tree::Del(Elem* z)
{
	//удаление куста
	if (z != nullptr)
	{
		Elem* Node, * y;

		//не 2 потомка
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
			//слева от родителя?
			y->parent->left = Node;
		else
			//Справа от родителя
			y->parent->right = Node;
		if (y != z)
		{
			//Копируем данные узла
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

//Получеть корень
Elem* Tree::GetRoot()
{
	return root;
}