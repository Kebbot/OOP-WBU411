#pragma once
struct Elem
{
	int data; //данные
	Elem* next, * prev;
};
class List_cast2
{
	//Голова, хвост
	Elem* Head, * Tail;
	//Количество элементов
	int Count;
public:
	//Конструктор
	List_cast2();
	//Конструктор копирования
	List_cast2(const List_cast2&);
	//Деструктор
	~List_cast2();
	//Получить количество
	int GetCount();
	//Получить элемент списка
	Elem* GetElem(int);
	//Удалить весь список
	void DelAll();
	//Удаление элемента, если параметр
	//не указывается,
	//то функция его запрашивает
	void Del(int pos = 0);
	//Вставка элемента, если параметр не указывается,
 //то функция его запрашивает
	void Insert(int pos = 0);
	//Добавление в конец списка
	void AddTail(int n);
	//Добавление в начало списка
	void AddHead(int n);
	//Печать списка
	void Print();
	//Печать определенного элемента
	void Print(int pos);
	List_cast2& operator = (const List_cast2&);
	//сложение двух списков (дописывание)
	List_cast2 operator + (const List_cast2&);
	//сравнение по элементам
	bool operator == (const List_cast2&);
	bool operator != (const List_cast2&);
	bool operator <= (const List_cast2&);
	bool operator >= (const List_cast2&);
	bool operator < (const List_cast2&);
	bool operator > (const List_cast2&);
	//переворачивание списка
	List_cast2 operator - ();
};