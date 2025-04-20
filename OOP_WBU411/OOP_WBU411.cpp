#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>0
#include <stdio.h>
using namespace std;

/*//самостоятельный (глобавльный) класс А
class A
{
public:
	int init(int);
private:
	class B
	{
	public:
		friend class A; // объявление друга
		B(int val = 0); // конструктор
		int value; //поле класса
		void mf( A&);
		static int memb;
		B* next; //указатель на собственный класс
	};
	B* object;
	class Ref {
		//pli имеет тип A::B*
		B* pli;
	};
	class C
	{
		//pref имеет тип A::Ref*
		Ref* pref;
	};
};
int A::B::memb = 0;
A::B::B(int val)
{
	//value = init(val);
}
void A::B::mf(A& i1)
{
	memb = i1.init(6);
}
*/

class A
{
	// класс
};
class B
{
	A a1; // агрегация
};
class Agregate
{
	B B1; //композиция
};

//Наследование
class Point //класс "точка"
{
protected:
	int x;
	int y;
public:
	Point() { x = 0; y = 0; };
	int& getX() { return x; }
	int& getY() { return y; }

};
class MyWindow : public Point
{
	int width;
	int height;
public:
	MyWindow(int W,int H) : width{W}, height{H} {}
	int& getWidth() { return width; }
	int& getHeight() { return height; }
	void MoveX(int DX) { x += DX; }
	void MoveY(int DY) { y += DY; }
	void Show()
	{
		cout << "______________________\n\n";
		cout << "X = " << x << endl;
		cout << "Y = " << y << endl;
		cout << "W = " << width << endl;
		cout << "H = " << height << endl;
		cout << "______________________\n\n";
	}
};

// Множественное наследование
class Roga
{
protected:
	string color;
	int wes;
public:
	Roga() { color = "Dirty"; wes = 20; }
	Roga(string c, int w) : color{c}, wes{w} {}
};
class Kopyta
{
protected:
	string forma;
	int razmer;
public:
	Kopyta() { forma = "Big"; razmer = 10; }
	Kopyta(string f,int r) : forma{f}, razmer{r} {}
};

class Los : public Roga, public Kopyta
{
public: 
	string name;
	Los(string name) : name{ name } {}
	void DispalayInfo()
	{
		cout << "Name: " << name << endl;
		cout << "Forma: " << forma << endl;
		cout << "Color: " << color << endl;
		cout << "Wes rogov: " << wes << endl;
		cout << "Razmer kopyt: " << razmer << endl;
	}
};

class Trnsport
{
protected:
	string vid;
	string sposob;
	int countH;
public:
	Trnsport() : vid{ "NON" }, sposob{ "NON" }, countH{0} {}
	Trnsport(string vid, string sposob, int countH) : 
		vid{ vid }, sposob{ sposob }, countH{ countH } { }
	void MoveT()
	{
		cout << "Транспорт движется: ";
	}
};
class Auto : public Trnsport
{
	string color;
	string mark;
public: 
	Auto() : color{ "NON" }, mark{"NON"} {}
	Auto(string color, string mark) : color{ color }, mark{ mark } {}
	Auto(string vid, string sposob, int countH, string color, string mark) : 
		Trnsport(vid, sposob, countH), color{ color }, mark{ mark } { }
	void Print()
	{
		MoveT();
		cout << "по земле" << endl;
	}
};
class Plane : public Trnsport
{
	string color;
	string mark;
public:
	Plane() : color{ "NON" }, mark{ "NON" } {}
	Plane(string color, string mark) : color{ color }, mark{ mark } {}
	Plane(string vid, string sposob, int countH, string color, string mark) :
		Trnsport(vid, sposob, countH), color{ color }, mark{ mark } {
	}
	void Print()
	{
		MoveT();
		cout << "по земле и потом по воздуху" << endl;
		cout << "Вид трансопрта: " << vid << endl;
		cout << "Способ передвижения: " << sposob << endl;
		cout << "Кол-во пассажиров: " << countH << endl;
		cout << "Цвет: " << color << endl;
		cout << "Модель: " << mark << endl;
	}
};

int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	
	Plane P{ "Летательный", "Летает",10, "Красно-белый", "Кукурузник" };
	P.Print();


	/*Los l{ "Radoon" };
	l.DispalayInfo();*/


	/*// Создание объектов
	MyWindow a{ 10,10 };
	a.Show();

	// Изменение параметров
	a.getX() = 15;
	a.getY() = 7;
	a.getWidth() = 40;
	a.getHeight() = 50;
	a.Show();

	// Сдвиг "окна"
	a.MoveX(2);
	a.MoveY(7);
	a.Show();*/

	
	/*ofstream out{"Hello.txt", ios::out}; //поток для записи
	if (!out.is_open())
	{
		//Проверка на открытый поток
		cout << "Ошибка открытия!" << endl;
	}
	//запись в поток и передача в файл
	out << "Привет потоки C++!" << endl << "Новая строка" << endl;
	out.close(); //закрытие потока


	out.open("Hello.txt", ios::app); //открытие для дозаписи
	if (!out.is_open())
	{
		//Проверка на открытый поток
		cout << "Ошибка открытия!" << endl;
	}
	//запись в поток и передача в файл
	out << "Дозапись с модификатором ios::app" << endl;
	out.close(); //закрытие потока

	ifstream in{ "Hello.txt", ios::in };
	string str;
	if (!in.is_open())
	{
		//Проверка на открытый поток
		cout << "Ошибка открытия!" << endl;
	}
	while (getline(in, str))
	{
		cout << str << endl;
	}*/
	

	return 0;
}
/* сначала ios::флаг_открытия
* 
* in - открыть только для чтения
* out - открыть только для записи
* ate - устанвоить указатель на конец файла
* app - дозаписывает данные в конец файла
* trunc - усечь файл до нулевой единицы
* _Nocreate - если файл не существует, ошибка открытия
* _Noreplace - если файл существует ошибка открытия
* binary - открыть файл для двоичного обмена
*/
