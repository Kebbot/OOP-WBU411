#pragma once
struct Elem
{
	int OwnerPoints; //���� ������
	int OppPoints; //���� ���������
	char Match[10]; //����
	char Name[20]; //�������
	char Opponent[20]; //��������
	

	Elem* left, * right, * parent;
};
class Tree
{
	Elem* root;
public:
	Tree();
	~Tree();

	//������ �� ���������� ����
	void Print(Elem* Node);

	//����� �� ���������� ����
	Elem* Search(Elem* Node, char* key);
	
	//min �� ���������� ����
	Elem* Min(Elem* Node);

	//max �� ���������� ����
	Elem* Max(Elem* Node);

	//"���������" ��� ���������� ����
	Elem* Next(Elem* Node);

	//"����������" ��� ���������� ����
	Elem* Previous(Elem* Node);

	//������� ����
	void Insert(Elem* z);

	//�������� ����� ��� ���������� ����
	//0 - �������� ����� ������
	void Del(Elem* z = nullptr);

	//�������� ������
	Elem* GetRoot();
};