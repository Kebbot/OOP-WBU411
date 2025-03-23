#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Point
{
	int x; 
	int y;
	int* mass;
public:
	Point() : x{ 0 }, y{ 0 }, mass{ nullptr }
	{
		std::cout << "Point default constructor" << std::endl;
	}
	Point(int pX, int pY) : x{ pX }, y{ pY },  mass { nullptr }
	{
		std::cout << "Point parameters constructor" << std::endl;
	}
	Point(int pX, int pY,int* mass1) : x{ pX }, y{ pY }, mass{ new int[pY] }
	{
		std::cout << "Point parameters2 constructor" << std::endl;
		for (int i = 0; i < pY; i++)
		{
			mass[i] = mass1[i];
		}
	}
};

class Human
{
	string name;
	int age;
	string worker;
	bool n;
	static int count;
	static const int maxHuman = 20;
public:
	Human() : Human{ "",0,"" } 
	{ count++; /*cout << "Human default constructor : " << endl;*/ }
	Human(string name, int age) : Human{ name,age,"" } 
	{
		//cout << "Human parameters constructor" << endl;
	}
	Human(string name, int age, string worker) :
		name{ name }, age{ age }, worker{ worker }, n{ age >= 18 ? true :false }
	{
		//cout << "Human parameters2 constructor" << endl;
	}
	static void Say()
	{
		cout << "Human is " << count << endl;
	}
};

int Human::count = 0;

class Date
{
	int day;
	int month;
	int year;
public:
	Date(int day, int month, int year) :
		day{ day }, month{ month }, year{ year }
	{
		cout << "Date constructed for " << this << endl;
	}

	Date():Date(1,1,1970){}

	Date(int year) : Date(1,1,year) {}

	~Date()
	{
		cout << "Date destructed for " << this << endl;
	}

	friend void displayDate(Date date);

	void Print() const
	{
		cout << this->day << ' '
			<< this->month << ' ' 
			<< this->year << endl;
	}

	//void setDay(int dayP) { day = dayP; }
	//void setMonth(int monthP) { month = monthP; }
	//void setYear(int yearP) { year = yearP; }

	Date& setDay(int dayP) { day = dayP;return *this; }
	Date& setMonth(int monthP){ month = monthP;return *this; }
	Date& setYear(int yearP){ year = yearP; return *this;}
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	
};

void displayDate(Date date)
{
	cout << date.day << "." << date.month << "."
		<< date.year << endl;
}
Date baseDate()
{
	return 2000;
}

class Fraction
{
	int numerator;
	int denominator;
public:
	Fraction(int numerator, int denominator) :
		numerator{ numerator }, denominator{ denominator }
	{
		cout << "Fraction constructed for " << this << endl;
	}
	Fraction():Fraction(1,1) {}

	//ClassName(const ClassName& object)
	Fraction(const Fraction& object) :
		numerator{ object.numerator}, denominator{object.denominator}
	{ 
		cout << "Fraction copy constructed for " << this << endl;
	}

	~Fraction() { cout << "Fraction destructed for " << this << endl; }
	void Print()
	{
		cout << '(' << numerator << '/' << denominator << ')' << endl;
	}
};

class DynArray
{
	int* arr;
	int size;
public:
	DynArray(int sizeP) :
		arr{ new int[sizeP] }, size{ sizeP }
	{
		cout << "DynArr constructed for "
			<< size << " elements, for "
			<< this << endl;
	}
	DynArray(const DynArray& object) :
		arr{new int[object.size]}, size{object.size}
	{
		cout << "DynArr copy constructed for "
			<< size << " elements, for "
			<< this << endl;
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = object.arr[i];
		}
	}
	int getElem(int idx) { return arr[idx]; }
	DynArray& setElem(int idx, int val) { arr[idx] = val;return *this; }
	DynArray& Print();
	DynArray& randomize();
	~DynArray()
	{
		delete[] arr;
		cout << "DynArr destructed for "
			<< size << " elements, for "
			<< this << endl;
	}
};
DynArray& DynArray::Print()
{
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	return *this;
}
DynArray& DynArray::randomize()
{
	for (size_t i = 0; i < size; i++)
		arr[i] = rand() % 10;
	return *this;
}

class ArrayP
{
	int size;
	int* array;
public:
	explicit ArrayP(int size = 10);
	~ArrayP();
	int getSize()const;
	int getValue(int index) const;
	void setValue(int index, int value);
	void display(int index) const;
};
ArrayP::ArrayP(int size)
{
	ArrayP::size = size;
	array = new int[size];
}
ArrayP::~ArrayP() { delete[] array; }
int ArrayP::getSize() const { return size; }
int ArrayP::getValue(int index) const { return array[index]; }
void ArrayP::setValue(int index, int value) { array[index] = value; }
void ArrayP::display(int index) const { cout << array[index] << ' '; }
void display(const ArrayP& array)
{
	for (size_t i = 0; i < array.getSize(); i++)
	{
		array.display(i);
	}
	cout << endl;
}

int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));

	

	return 0;
}