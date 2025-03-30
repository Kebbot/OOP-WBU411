#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
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
	Point(Point& object) = delete;
	/*{
		this->x = object.x;
		this->y = object.y;
	}*/
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
	// перегрузка оператора =
	Point& operator=(const Point& object) = delete;
	/*{
		if (this == &object)
		{
			cout << "Присвоение запрещено" << endl;
			return *this;
		}
		this->x = object.x;
		this->y = object.y;
		return *this;
	}*/
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

class Point1
{
	int x;
	int y;
	//Point1() = default;
public:
	Point1() = default;
	Point1(int pX, int pY) : x{ pX }, y{ pY } {}

	Point1& setY(int pY) { y = pY; return *this; }
	Point1& setX(int pX) { x = pX; return *this; }
	template<class T1>
	Point1& setY(T1 pY) = delete;
	template<class T1>
	Point1& setX(T1 pX) = delete;

	/*Point1& setY(double pY) = delete;
	Point1& setX(double pX) = delete;*/

	void showPoint1() const
	{
		cout << '(' << x << ',' << y << ')' << endl;
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
		arr{ new int[object.size] }, size{ object.size }
	{
		cout << "DynArr copy constructed for "
			<< size << " elements, for "
			<< this << endl;
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = object.arr[i];
		}
	}
	DynArray(DynArray&& object) :
		arr{ object.arr},size{ object.size}
	{
		object.arr = nullptr;
		object.size = 0;
		cout << "DynArr move constructed for "
			<< size << " elements, for "
			<< this << endl;
	}
	int getElem(int idx) { return arr[idx]; }
	DynArray& setElem(int idx, int val) { arr[idx] = val;return *this; }
	//константная перегрузка, возвращающая по значению
	int operator[](int idx) const
	{
		assert(idx >= 0 and idx < size and "Index is out of range!");
		return arr[idx];
	}
	//Не константная перегрузка, возвращающая по ссылке
	int& operator[](int idx)
	{
		assert(idx >= 0 and idx < size and "Index is out of range!");
		return arr[idx];
	}
	DynArray& operator=(DynArray&& object)
	{
		if (!(this == &object))
		{
			delete arr;
			arr = object.arr;
			size = object.size;
			object.arr = nullptr;
			object.size = 0;
		}
		cout << "DynArr move assigned for "
			<< size << " elements, for "
			<< this << endl;
		return *this;
	}
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

DynArray arrayFactory(int size)
{
	DynArray tmp{ size };
	tmp.randomize();
	return move(tmp);
}

class MedalRow
{
	char country[4];
	int medals[3];
public:
	/*определяем константы для удобного 
	и однозначного доступа к элементам массива*/
	static const int GOLD{ 0 };
	static const int SILVER{ 1 };
	static const int BRONZE{ 2 };
	MedalRow(const char* countryP, const int* medalsP)
	{
		strcpy_s(country, 4, countryP ? countryP : "NON");
		for (int i = 0; i < 3; i++)
		{
			medals[i] = medalsP ? medalsP[i] : 0;
		}
	}
	MedalRow() : MedalRow(nullptr, nullptr) {}
	MedalRow& setCountry(const char* countryP)
	{
		if (countryP)
		{
			strcpy_s(country, 4, countryP);
		}
		return *this;
	}
	const char* getCountry()const { return country; }
	int& operator[](int idx)
	{
		assert((idx >= 0 and idx < 3) and "Index is out of range!");
		return medals[idx];
	}
	int operator[](int idx)const
	{
		assert((idx >= 0 and idx < 3) and "Index is out of range!");
		return medals[idx];
	}
	void Print()const
	{
		cout << '[' << country << "]-( ";
		for (int i = 0; i < 3; i++)
		{
			cout << medals[i];
			if (i < 2) { cout << '\t'; }
		}
		cout << ")\n\n";
	}

	static void Poof()
	{
		cout << "Hello, static!" << endl;
	}
};

class MedalsTable
{
public:
	static const int maxSize{ 10 };
private:
	MedalRow medalRows[MedalsTable::maxSize];
	int size;
	int findCountry(const char* country) const
	{
		for (int i = 0; i < size; i++)
		{
			if (strcmp(medalRows[i].getCountry(), country) == 0)
				return i;
		}
		return -1;
	}
public:
	MedalsTable() : size{ 0 } {}
	MedalRow& operator[](const char* country)
	{
		int idx{ findCountry(country) };
		if (idx == -1)
		{
			assert(size < MedalsTable::maxSize and "Table is FULL!");
			idx = size++;
			medalRows[idx].setCountry(country);
		}
		return medalRows[idx];
	}
	MedalRow operator[](const char* country)const 
	{
		int idx{ findCountry(country) };
		if (idx == -1)
		{
			assert(idx !=-1 and "Country not found on const table");
		}
		return medalRows[idx];
	}
	void Print()const
	{
		for (int i = 0; i < size; i++)
		{
			medalRows[i].Print();
		}
	}
};

class Dyn2DArr
{
	int sizeY;
	int sizeX;
public:
	int** data;
	Dyn2DArr(int sizeYP, int sizeXP)
		: sizeY{ sizeYP }, sizeX{ sizeXP },
		data{ new int* [sizeYP] }
	{
		for (int y{ 0 }; y < sizeY; ++y)
		{
			data[y] = new int[sizeX];
		}
	}
	void print()const
	{
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				std::cout << data[y][x] << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	~Dyn2DArr()
	{
		for (int y{ 0 }; y < sizeY; ++y)
		{
			delete[] data[y];
		}
		delete[] data;
	}
};

class Dyn2DArrLinear
{
	int sizeY;
	int sizeX;
public:
	int** data;
	Dyn2DArrLinear(int sizeYP, int sizeXP)
		: sizeY{ sizeYP }, sizeX{ sizeXP },
		data{ new int* [sizeYP] }
	{
		/*
		* выделяем блок памяти для хранения всех элементов
		* двумерного динамического массива.
		*/
		int* dataElements{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			// "нарезаем" блок построчно
			data[y] = dataElements + y * sizeX;
		}
	}
	void print()const
	{
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				std::cout << data[y][x] << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	~Dyn2DArrLinear()
	{
		/*
		* адрес начала большого блока dataElements
		* в конструкторе совпадает с адресом первой
		* строки нашего двумерного динамического массива.
		* Сперва освобождаем память из-под элементов
		* массива, затем — память контейнера строк.
		*/
		delete[] data[0];
		delete[] data;
	}
};

class Matrix
{
	int sizeY;
	int sizeX;
	int* data;
	int index2D(int y, int x)
		const {
		return y * sizeX + x;
	}
	int index2D(int y, int x, int sizeXP)
		const {
		return y * sizeXP + x;
	}
public:
	Matrix(int sizeYP, int sizeXP)
		: sizeY{ sizeYP }, sizeX{ sizeXP },
		data{ new int[sizeYP * sizeXP] } {
	}
	int operator()(int y, int x)
		const {
		return *(data + index2D(y, x));
	}
	int& operator()(int y, int x)
	{
		return *(data + index2D(y, x));
	}
	void deleteColumn(int columnPos)
	{
		--sizeX;
		int* newData{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x)) =
					*(data + index2D(y, x + (x >=
						columnPos)));
			}
		}
		delete[] data;
		data = newData;
	}
	void addColumn(int columnPos, int* newCol = nullptr)
	{
		int* newData{ new int[sizeY * (sizeX + 1)] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x + (x >= columnPos),
					sizeX + 1)) = *(data + index2D(y, x));
			}
			*(newData + index2D(y, columnPos, sizeX + 1)) =
				newCol ? *(newCol + y) : 0;
		}
		delete[] data;
		data = newData;
		++sizeX;
	}
	void deleteRow(int rowPos)
	{
		--sizeY;
		int* newData{ new int[sizeY * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y, x)) =
					*(data + index2D(y + (y >= rowPos),
						x));
			}
		}
		delete[] data;
		data = newData;
	}
	void addRow(int rowPos, int* newRow = nullptr)
	{
		int* newData{ new int[(sizeY + 1) * sizeX] };
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				*(newData + index2D(y + (y >= rowPos), x)) =
					*(data + index2D(y, x));
			}
		}
		for (int x{ 0 }; x < sizeX; ++x)
		{
			*(newData + index2D(rowPos, x)) =
				newRow ? *(newRow + x) : 0;
		}
		delete[] data;
		data = newData;
		++sizeY;
	}
	void print()const
	{
		for (int y{ 0 }; y < sizeY; ++y)
		{
			for (int x{ 0 }; x < sizeX; ++x)
			{
				std::cout << (*this)(y, x) << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
	~Matrix() { delete[] data; }
};

class Counter
{
	int cnt;
public:
	Counter(int start) : cnt{ start } {}
	Counter() : Counter(0) {}
	int operator()() { return cnt++; }
	void resetTo(int start) { cnt = start; }

};

int cnt()
{
	static int counter{ 0 };
	return counter++;
}

int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));

	const int maxCnt{ 5 };
	Counter cnt1;
	Counter cnt2{ 100 };
	for (int i = 0; i < maxCnt; i++)
	{
		cout << "cnt1: " << cnt1() << endl;
		cout << "cnt2: " << cnt2() << endl;
	}
	cout << endl;




	//const int maxCnt{ 5 };
	//// cnt1;
	//for (int i = 0; i < maxCnt; i++)
	//{
	//	cout << cnt() << ' ';
	//}
	//cout << endl;

	/*cnt1.resetTo(10);
	for (int i = 0; i < maxCnt; i++)
	{
		cout << cnt1() << ' ';
	}
	cout << endl;*/

/*#define USER_INPUT 0;
	int rows{ 3 };
	int columns{ 3 };
	int counter{ 1 };
#if USER_INPUT == 1
	cout << "Enter matrix rows count\n";
	cin >> rows;
	cout << "Enter matrix columns count\n";
	cin >> columns;
#endif // USER_INPUT == 1
	Matrix matrix{ rows,columns };
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			matrix(y, x) = counter++;
		}
	}
	matrix.print();
	matrix.deleteColumn(2);
	matrix.print();

	int* newColumn{ new int[columns] {11,22,33} };
	matrix.addColumn(0, newColumn);
	matrix.print();

	matrix.deleteRow(2);
	matrix.print();

	int* newRow{ new int[rows] {111,222,333} };
	matrix.addRow(2, newRow);
	matrix.print();

	delete[] newRow;
	delete[] newColumn;*/

	/*int rows{ 3 };
	int columns{ 3 };
	int counter{ 1 };
	Dyn2DArrLinear arr2d{ rows, columns };
	for (int y{ 0 }; y < rows; ++y)
	{
		for (int x{ 0 }; x < columns; ++x)
		{
			arr2d.data[y][x] = counter++;
		}
	}
	arr2d.print();*/
	/*int rows{ 3 };
	int columns{ 3 };
	int counter{ 1 };
	Dyn2DArr arr2d{ rows, columns };
	for (int y{ 0 }; y < rows; ++y)
	{
		for (int x{ 0 }; x < columns; ++x)
		{
			arr2d.data[y][x] = counter++;
		}
	}
	arr2d.print();*/

	/*MedalsTable mt1;
	cout << "Medals table #1: \n";

	mt1["RUS"][MedalRow::GOLD] = 14;
	mt1["RUS"][MedalRow::SILVER] = 7;
	mt1["USA"][MedalRow::GOLD] = 3;
	mt1["USA"][MedalRow::BRONZE] = 5;
	mt1["POL"][MedalRow::SILVER] = 2;
	mt1["POL"][MedalRow::BRONZE] = 7;

	mt1.Print();*/

	/*const int size{10};
	DynArray ar1{ arrayFactory(size) };
	cout << "ar1 elements: ";
	ar1.Print();

	cout << "\nChange every ar1 element to it\'s square: " << endl;

	for (int i{0}; i < size; i++)
	{
		ar1[i] *= ar1[i];
		cout << "ar1[" << i << "] = " << ar1[i] << endl;
	}
	cout << "\n\n";
	const DynArray ar2{ arrayFactory(size) };
	cout << "ar2 elements: \n";
	for (int i{ 0 }; i < size; i++)
	{
		cout << "ar2[" << i << "] = " << ar2[i] << endl;
	}*/


	return 0;
}

/*
* ReturnType operator()(){} //1
* ReturnType operator()(ParamType_A param_A){} //2
* ReturnType operator()(ParamType_A param_A, ParamType_B param_B){} //3
*/