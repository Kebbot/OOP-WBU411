#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <stdio.h>
//#include "List_cast2.h"
#include "Binary_Tree.h"
using namespace std;

struct Element
{
	//Данные
	char data;
	//Адрес следующего элемента списка
	Element* Next;
};
//Односвязный список
class List_cast
{
	//Адрес головного элемента списка
	Element* Head;
	//Адрес концевого элемента списка
	Element* Tail;
	//Количество элементов списка
	int Count;
public:
	//Конструктор
	List_cast();
	//Деструктор
	~List_cast();
	//Добавление элемента в список
	//(Новый элемент становится последним)
	void Add(char data);
	//Удаление элемента списка
	//(Удаляется головной элемент)
	void Del();
	//Удаление всего списка
	void DelAll();
	//Распечатка содержимого списка
	//(Распечатка начинается с головного элемента)
	void Print();
	//Получение количества элементов,
	//находящихся в списке
	int GetCount();
};
List_cast::List_cast()
{
	//Изначально список пуст
	Head = Tail = nullptr;
	Count = 0;
}
List_cast::~List_cast()
{
	//Вызов функции удаления
	DelAll();
}
int List_cast::GetCount()
{
	//Возвращаем количество элементов
	return Count;
}
void List_cast::Add(char data)
{
	//создание нового элемента
	Element* temp = new Element;
	//заполнение данными
	temp->data = data;
	//следующий элемент отсутствует
	temp->Next = nullptr;
	//новый элемент становится последним элементом списка
	//если он не первый добавленный
	if (Head != nullptr) {
		Tail->Next = temp;
		Tail = temp;
	}
	//новый элемент становится единственным
	//если он первый добавленный
	else {
		Head = Tail = temp;
	}
}
void List_cast::Del()
{
	//запоминаем адрес головного элемента
	Element* temp = Head;
	//перебрасываем голову на следующий элемент
	Head = Head->Next;
	//удаляем бывший головной элемент
	delete temp;
}
void List_cast::DelAll()
{
	//Пока еще есть элементы
	while (Head != 0)
		//Удаляем элементы по одному
		Del();
}
void List_cast::Print()
{
	//запоминаем адрес головного элемента
	Element* temp = Head;
	//Пока еще есть элементы
	while (temp != 0)
	{
		//Выводим данные
		cout << temp->data << " ";
		//Переходим на следующий элемент
		temp = temp->Next;
	}
	cout << "\n\n";
}

//турнирная таблица
Tree tournament;

void Game(char Commands[][20], int N)
{
	int i, j;
	int p1, p2; //Счет
	//Каждая команда играет с каждой по 2 раза -
	//дома и в гостях
	int k;
	Elem* temp;
	for (k = 0; k < 2; k++)
	{
		for (i = 0; i < N - 1; i++)
		{
			for (j = i + 1; j < N; j++)
			{
				temp = new Elem;
				if (k == 0)
				{
					//1 игра
					strcpy_s(temp->Name, Commands[i]);
					strcpy_s(temp->Opponent, Commands[j]);
				}
				else
				{
					//2 игра
					strcpy_s(temp->Name, Commands[j]);
					strcpy_s(temp->Opponent, Commands[i]);
				}
				p1 = rand() % 6;
				p2 = rand() % 6;
				if (p1 > p2)
				{
					temp->OwnerPoints = 3;
					temp->OppPoints = 0;
				}
				else if (p1 == p2)
				{
					temp->OwnerPoints = 1;
					temp->OppPoints = 1;
				}
				else
				{
					temp->OwnerPoints = 0;
					temp->OppPoints = 3;
				}
				//Запись счета
				sprintf_s(temp->Match, " %d : %d ", p1, p2);
				cout << temp->Match << " " << p1 << " : " << p2 << endl;
				//Добавление записи
				tournament.Insert(temp);
			}
		}
	}
}

int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	
	const int N = 4;
	char Commands[4][20] =
	{
	"Arsenal",
	"Liverpool",
	"Lids United",
	"Manchester United"
	};
	//Игра
	Game(Commands, N);
	//Вывод результатов
	tournament.Print(tournament.GetRoot());

	
	/*
	//Создаем объект класса List
	List_cast lst;
	//Тестовая строка
	char s[] = "Hello, World !!!\n";
	//Выводим строку
	cout << s << "\n\n";
	//Определяем длину строки
	int len = strlen(s);
	//Загоняем строку в список
	for (int i = 0; i < len; i++)
		lst.Add(s[i]);
	//Распечатываем содержимое списка
	lst.Print();
	//Удаляем три элемента списка
	lst.Del();
	lst.Del();
	lst.Del();
	//Распечатываем содержимое списка
	lst.Print();*/

	/*List_cast2 L;
	const int n = 10;
	int a[n] = { 0,1,2,3,4,5,6,7,8,9 };
	//Добавляем элементы, стоящие на четных
	//индексах, в голову,
	//на нечетных - в хвост
	for (int i = 0; i < n; i++)
		if (i % 2 == 0)
			L.AddHead(a[i]);
		else
			L.AddTail(a[i]);
	//Распечатка списка
	cout << "List L:\n";
	L.Print();
	cout << endl;
	//Вставка элемента в список
	L.Insert();
	//Распечатка списка
	cout << "List L:\n"; L.Print();
	//Распечатка 2-го и 8-го элементов списка
	L.Print(2);
	L.Print(8);
	List_cast2 T;
	//Копируем список
	T = L;
	//Распечатка копии
	cout << "List T:\n";
	T.Print();
	//Складываем два списка
	//(первый в перевернутом состоянии)
	cout << "List Sum:\n";
	List_cast2 Sum = -L + T;
	//Распечатка списка
	Sum.Print();*/

	return 0;
}

