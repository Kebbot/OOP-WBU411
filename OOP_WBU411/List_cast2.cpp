#include <iostream>
#include "List_cast2.h"
using namespace std;
List_cast2::List_cast2()
{
	//���������� ������ ����
	Head = Tail = NULL;
	Count = 0;
}
List_cast2::List_cast2(const List_cast2& L)
{
	Head = Tail = NULL;
	Count = 0;
	//������ ������, �� �������� ��������
	Elem* temp = L.Head;
	//���� �� ����� ������
	while (temp != 0)
	{
		//���������� ������
		AddTail(temp->data);
		temp = temp->next;
	}
}
List_cast2::~List_cast2()
{
	//������� ��� ��������
	DelAll();
}
void List_cast2::AddHead(int n)
{
	//����� �������
	Elem* temp = new Elem;
	//����������� ���
	temp->prev = nullptr;
	//��������� ������
	temp->data = n;
	//��������� - ������ ������
	temp->next = Head;
	//���� �������� ����?
	if (Head != nullptr)
		Head->prev = temp;
	//���� ������� ������, �� �� ������������
 //� ������ � �����
	if (Count == 0)
		Head = Tail = temp;
	else
		//����� ����� ������� - ��������
		Head = temp;
	Count++;
}
void List_cast2::AddTail(int n)
{
	//������� ����� �������
	Elem* temp = new Elem;
	//���������� ���
	temp->next = nullptr;
	//��������� ������
	temp->data = n;
	//���������� - ������ �����
	temp->prev = Tail;
	//���� �������� ����?
	if (Tail != nullptr)
		Tail->next = temp;
	//���� ������� ������, �� �� ������������
	//� ������ � �����
	if (Count == 0)
		Head = Tail = temp;
	else
		//����� ����� ������� - ���������
		Tail = temp;
	Count++;
}
void List_cast2::Insert(int pos)
{
	//���� �������� ����������� ��� ����� 0,
 //�� ����������� ���
	if (pos == 0)
	{
		cout << "Input position: ";
		cin >> pos;
	}
	//������� �� 1 �� Count?
	if (pos < 1 || pos > Count + 1)
	{
		//�������� �������
		cout << "Incorrect position !!!\n";
		return;
	}
	//���� ������� � ����� ������
	if (pos == Count + 1)
	{
		//����������� ������
		int data;
		cout << "Input new number: ";
		cin >> data;
		//���������� � ����� ������
		AddTail(data);
		return;
	}
	else if (pos == 1)
	{
		//����������� ������
		int data;
		cout << "Input new number: ";
		cin >> data;
		//���������� � ������ ������
		AddHead(data);
		return;
	}
	//�������
	int i = 1;
	//����������� �� ������ n - 1 ���������
	Elem* Ins = Head;
	while (i < pos)
	{
		//������� �� ��������,
		//����� ������� �����������
		Ins = Ins->next;
		i++;
	}
	//������� �� ��������,
	//������� ������������
	Elem* PrevIns = Ins->prev;
	//������� ����� �������
	Elem* temp = new Elem;
	//������ ������
	cout << "Input new number: ";
	cin >> temp->data;
	//��������� ������
	if (PrevIns != nullptr && Count != 1)
		PrevIns->next = temp;
	temp->next = Ins;
	temp->prev = PrevIns;
	Ins->prev = temp;
	Count++;
}
void List_cast2::Del(int pos)
{
	//���� �������� ����������� ��� ����� 0,
 //�� ����������� ���
	if (pos == 0)
	{
		cout << "Input position: ";
		cin >> pos;
	}
	//������� �� 1 �� Count?
	if (pos < 1 || pos > Count)
	{
		//�������� �������
		cout << "Incorrect position !!!\n";
		return;
	}
	//�������
	int i = 1;
	Elem* Del = Head;
	while (i < pos)
	{
		//������� �� ��������,
		//������� ���������
		Del = Del->next;
		i++;
	}
	//������� �� ��������,
	//������� ������������ ����������
	Elem* PrevDel = Del->prev;
	//������� �� ��������, ������� ������� �� ���������
	Elem* AfterDel = Del->next;
	//���� ������� �� ������
	if (PrevDel != nullptr && Count != 1)
		PrevDel->next = AfterDel;
	//���� ������� �� �����
	if (AfterDel != nullptr && Count != 1)
		AfterDel->prev = PrevDel;
	//��������� �������?
	if (pos == 1)
		Head = AfterDel;
	if (pos == Count)
		Tail = PrevDel;
	//�������� ��������
	delete Del;
	Count--;
}
void List_cast2::Print(int pos)
{
	//������� �� 1 �� Count?
	if (pos < 1 || pos > Count)
	{
		//�������� �������
		cout << "Incorrect position !!!\n";
		return;
	}
	Elem* temp;
	//���������� � ����� �������
	//������� ���������
	if (pos <= Count / 2)
	{
		//������ � ������
		temp = Head;
		int i = 1;
		while (i < pos)
		{
			//��������� �� ������� ��������
			temp = temp->next;
			i++;
		}
	}
	else
	{
		//������ � ������
		temp = Tail;
		int i = 1;
		while (i <= Count - pos)
		{
			//��������� �� ������� ��������
			temp = temp->prev;
			i++;
		}
	}
	//����� ��������
	cout << pos << " element: ";
	cout << temp->data << endl;
}
void List_cast2::Print()
{
	//���� � ������ ������������ ��������,
	//�� ��������� �� ����
	//� �������� ��������, ������� � ���������
	if (Count != 0)
	{
		Elem* temp = Head;
		cout << "( ";
		while (temp->next != 0)
		{
			cout << temp->data << ", ";
			temp = temp->next;
		}
		cout << temp->data << " )\n";
	}
}
void List_cast2::DelAll()
{
	//���� �������� ��������, ������� �� ������ � ������
	while (Count != 0)
		Del(1);
}
int List_cast2::GetCount()
{
	return Count;
}
Elem* List_cast2::GetElem(int pos)
{
	Elem* temp = Head;
	//������� �� 1 �� Count?
	if (pos < 1 || pos > Count)
	{
		//�������� �������
		cout << "Incorrect position !!!\n";
		return 0;
	}
	int i = 1;
	//���� ������ ��� �������
	while (i < pos && temp != nullptr)
	{
		temp = temp->next;
		i++;
	}
	if (temp == nullptr)
		return 0;
	else
		return temp;
}
List_cast2& List_cast2::operator = (const List_cast2& L)
{
	//�������� ������������ �������� "������ ����"
	if (this == &L)
		return *this;
	//�������� ������� ������
	this->~List_cast2(); // DelAll();
	Elem* temp = L.Head;
	//�������� ��������
	while (temp != 0)
	{
		AddTail(temp->data);
		temp = temp->next;
	}
	return *this;
}
//�������� ���� �������
List_cast2 List_cast2::operator + (const List_cast2& L)
{
	//������� �� ��������� ������ �������� �������
	//������
	List_cast2 Result(*this);
	//List Result = *this;
	Elem* temp = L.Head;
	//��������� �� ��������� ������ ��������
	//������� ������
	while (temp != 0)
	{
		Result.AddTail(temp->data);
		temp = temp->next;
	}
	return Result;
}
bool List_cast2::operator == (const List_cast2& L)
{
	//��������� �� ����������
	if (Count != L.Count)
		return false;
	Elem* t1, * t2;
	t1 = Head;
	t2 = L.Head;
	//��������� �� ����������
	while (t1 != 0)
	{
		//������� ������, �������
		//��������� �� ���������� ��������
		if (t1->data != t2->data)
			return false;
		t1 = t1->next;
		t2 = t2->next;
	}
	return true;
}
bool List_cast2::operator != (const List_cast2& L)
{
	//���������� ���������� ������� ���������
	return !(*this == L);
}
bool List_cast2::operator >= (const List_cast2& L)
{
	//��������� �� ����������
	if (Count > L.Count)
		return true;
	//��������� �� ����������
	if (*this == L)
		return true;
	return false;
}
bool List_cast2::operator <= (const List_cast2& L)
{
	//��������� �� ����������
	if (Count < L.Count)
		return true;
	//��������� �� ����������
	if (*this == L)
		return true;
	return false;
}
bool List_cast2::operator > (const List_cast2& L)
{
	if (Count > L.Count)
		return true;
	return false;
}
bool List_cast2::operator < (const List_cast2& L)
{
	if (Count < L.Count)
		return true;
	return false;
}
//���������
List_cast2 List_cast2::operator - ()
{
	List_cast2 Result;
	Elem* temp = Head;
	//�������� �������� ������, ������� � ���������,
	//� ���� ����� ���������� ��������� � ������, �����
	//������� ��������� ������ Result ����� ���������
	//�������� � �������� �������
	while (temp != 0)
	{
		Result.AddHead(temp->data);
		temp = temp->next;
	}
	return Result;
}