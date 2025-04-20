#pragma once
struct Elem
{
	int data; //������
	Elem* next, * prev;
};
class List_cast2
{
	//������, �����
	Elem* Head, * Tail;
	//���������� ���������
	int Count;
public:
	//�����������
	List_cast2();
	//����������� �����������
	List_cast2(const List_cast2&);
	//����������
	~List_cast2();
	//�������� ����������
	int GetCount();
	//�������� ������� ������
	Elem* GetElem(int);
	//������� ���� ������
	void DelAll();
	//�������� ��������, ���� ��������
	//�� �����������,
	//�� ������� ��� �����������
	void Del(int pos = 0);
	//������� ��������, ���� �������� �� �����������,
 //�� ������� ��� �����������
	void Insert(int pos = 0);
	//���������� � ����� ������
	void AddTail(int n);
	//���������� � ������ ������
	void AddHead(int n);
	//������ ������
	void Print();
	//������ ������������� ��������
	void Print(int pos);
	List_cast2& operator = (const List_cast2&);
	//�������� ���� ������� (�����������)
	List_cast2 operator + (const List_cast2&);
	//��������� �� ���������
	bool operator == (const List_cast2&);
	bool operator != (const List_cast2&);
	bool operator <= (const List_cast2&);
	bool operator >= (const List_cast2&);
	bool operator < (const List_cast2&);
	bool operator > (const List_cast2&);
	//��������������� ������
	List_cast2 operator - ();
};