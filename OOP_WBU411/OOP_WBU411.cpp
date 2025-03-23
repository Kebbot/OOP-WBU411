#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Перегрузка операторов +, -, *, /
class Point
{
	int x;
	int y;
public:
	Point() 
	{ 
		x = 1; 
		y = 1;
		//cout << "Был вызван конструктор по умолчанию " << this << endl;
	} // конструктор по умолчанию
	Point(int x, int y) : x{x}, y{y}
	{
		//cout << "Был вызван конструктор с параметрами " << this << endl;
	} // конструктор с параметрами
	Point(Point&& object) : x{ object.x }, y{ object.y }
	{
		object.x = 0;
		object.y = 0;
		//cout << "Был вызван конструктор перемещения " << this << endl;
	}
	// перегрузка оператора +
	Point operator+(const Point& object1)
	{
		return Point(object1.x + x, object1.y + y);
	}
	friend Point operator+(const Point& object1, const Point& object2)
	{
		return Point(object1.x + object2.x, object1.y + object2.y);
	}
	// перегрузка оператора -
	Point operator-(const Point& object1)
	{
		return Point(x - object1.x, y - object1.y);
	}
	friend Point operator-(const Point& object1, const Point& object2)
	{
		return Point(object1.x - object2.x, object1.y - object2.y);
	}
	// перегрузка оператора *
	Point operator*(const Point& object1)
	{
		return Point(x * object1.x, y * object1.y);
	}
	friend Point operator*(const Point& object1, const Point& object2)
	{
		return Point(object1.x * object2.x, object1.y * object2.y);
	}
	// перегрузка оператора /
	Point operator/(const Point& object1)
	{
		if(object1.x == 0 && object1.y != 0)
			return Point(x / 1, y / object1.y);
		else if(object1.y == 0 && object1.x != 0)
			return Point(x / object1.x, y / 1);
		else if(object1.y == 0 && object1.x == 0)
			return Point(x / 1, y / 1);

		return Point(x / object1.x, y / object1.y);
	}
	friend Point operator/(const Point& object1, const Point& object2)
	{
		if (object2.x == 0 && object2.y != 0)
			return Point(object1.x / 1, object1.y / object2.y);
		else if (object2.y == 0 && object2.x != 0)
			return Point(object1.x / object2.x, object1.y / 1);
		else if (object2.y == 0 && object2.x == 0)
			return Point(object1.x / 1, object1.y / 1);

		return Point(object1.x / object2.x, object1.y / object2.y);
	}
	// перегрузка оператора *
	Point& operator=(const Point& object)
	{
		if (this == &object)
		{
			cout << "Присвоение запрещено" << endl;
			return *this;
		}
		this->x = object.x;
		this->y = object.y;
		return *this;
	}
	void Print()
	{
		cout << "x = " << x << ' ' << "y = " << y << endl;
	}
	~Point()
	{
		//cout << "Был вызван деструктор " << this << endl;
	}
};

Point PointFactory()
{
	int x = rand() % 10;
	int y = rand() % 10;
	Point tmp{x,y};
	return move(tmp);
}

int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));

	/*Point p{ PointFactory()};
	p.Print();*/

	/*int&& rValueRef{ 2 + 3 };
	int x{42};
	int& lValueRef{ x };
	int&& RvalueRef{ x + lValueRef };*/

	vector<Point> arr;
	for (size_t i = 0; i < 20; i++)
	{
		arr.push_back(PointFactory());
		arr[i].Print();
	}
	return 0;
}
// след. тема = Заданные по умолчанию и удаленные методы.