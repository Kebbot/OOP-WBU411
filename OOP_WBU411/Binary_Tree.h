#pragma once
struct Elem
{
	int OwnerPoints; //Очки хояина
	int OppPoints; //Очки соперника
	char Match[10]; //Счёт
	char Name[20]; //Команда
	char Opponent[20]; //Соперник
	

	Elem* left, * right, * parent;
};
class Tree
{
	Elem* root;
public:
	Tree();
	~Tree();

	//печать от указанного узла
	void Print(Elem* Node);

	//Поиск от указанного узла
	Elem* Search(Elem* Node, char* key);
	
	//min от указанного узла
	Elem* Min(Elem* Node);

	//max от указанного узла
	Elem* Max(Elem* Node);

	//"Следующий" для указанного узла
	Elem* Next(Elem* Node);

	//"Предыдущий" для указанного узла
	Elem* Previous(Elem* Node);

	//Вставка узла
	void Insert(Elem* z);

	//Удаление ветки для указанного узла
	//0 - Удаление всего дерева
	void Del(Elem* z = nullptr);

	//Получеть корень
	Elem* GetRoot();
};