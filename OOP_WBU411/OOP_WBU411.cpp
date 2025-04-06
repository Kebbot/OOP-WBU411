#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
using namespace std;

class RectangleP;
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
	//Point(Point& object) = delete;
	/*{
		this->x = object.x;
		this->y = object.y;
	}*/
	//Point(Point&& object) : x{ object.x }, y{ object.y }
	//{
	//	object.x = 0;
	//	object.y = 0;
	//	//cout << "Был вызван конструктор перемещения " << this << endl;
	//}
	Point& setX(int pX) { x = pX;return *this; }
	Point& setY(int pY) { y = pY;return *this; }
	int getX()const { return x; }
	int getY()const { return y; }
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
	Point& operator=(const Point& object)/* = delete;*/
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

	//Перегрузка оператора "Вывода"
	friend ostream& operator<<(ostream& out, const Point& point);
	//Перегрузка оператора "Ввода"
	friend istream& operator>>(istream& in, Point& point);
	
	//дружественный класс
	friend class RectangleP;
};
class RectangleP
{
	Point leftUpCorner;
	Point rightDownCorner;
public:
	RectangleP() = default;
	RectangleP(const Point& leftUpCornerP, int sideAP, int sideBP) :
		leftUpCorner{ leftUpCornerP }, rightDownCorner{
		leftUpCornerP.x + sideAP,leftUpCornerP.y + sideBP } {}
	RectangleP(const Point& leftUpCornerP, const Point& rightDownCornerP) :
		leftUpCorner{ leftUpCornerP }, rightDownCorner{ rightDownCornerP } {}

	int getSideA()const { return rightDownCorner.x - leftUpCorner.x; }
	int getSideB()const { return rightDownCorner.y - leftUpCorner.y; }

	friend ostream& operator<<(ostream& out, const RectangleP& rectangle);


};

//Перегрузка оператора "Вывода"
ostream& operator<<(ostream& out, const Point& point)
{
	out << "(" << point.x << "," << point.y << ")";
	return out;
}
//Перегрузка оператора "Ввода"
istream& operator>>(istream& in, Point& point)
{
	in >> point.x >> point.y;
	return in;
}
ostream& operator<<(ostream& out, const RectangleP& rectangle)
{
	out << "[ " << rectangle.leftUpCorner << ' '
		<< rectangle.getSideA() << " X "
		<< rectangle.getSideB() << " "
		<< rectangle.rightDownCorner << " ]";
	return out;
}
/*
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
	//определяем константы для удобного 
	//и однозначного доступа к элементам массива
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
		
		//* выделяем блок памяти для хранения всех элементов
		//* двумерного динамического массива.
		
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
		
		//* адрес начала большого блока dataElements
		//* в конструкторе совпадает с адресом первой
		//* строки нашего двумерного динамического массива.
		//* Сперва освобождаем память из-под элементов
		//* массива, затем — память контейнера строк.
		
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
}*/

template<class T>
T square(T number)
{
	T result = number * number;
	return result;
}
template<class T>
void sortP(T array[], size_t size)
{
	for (size_t k = size -1; k > 0; k--)
	{
		for (size_t j = 0; j < k; j++)
		{
			if (array[j] > array[j + 1])
				swap(array[j], array[j + 1]);
		}
	}
}
template<class T>
void display(T array[], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

template<class T>
class ArrayP
{
	T* array;
	size_t size;
public:
	ArrayP() = default;
	ArrayP(T num, size_t size) : size{ size },
		array{ new decltype(num)[size] }
	{
		if(sizeof(num) == 8)
			for (size_t i = 0; i < size; i++)
			{
				array[i] = 0.5 + rand() % 50;
			}
		else if(sizeof(num) == 4)
			for (size_t i = 0; i < size; i++)
			{
				array[i] = rand() % 50;
			}
		else
			for (size_t i = 0; i < size; i++)
			{
				array[i] = 0;
			}
	}
	~ArrayP()
	{
		delete[] array;
	}
	void display()
	{
		for (size_t i = 0; i < size; i++)
		{
			cout << array[i] << " ";
		}
		cout << endl << endl;
	}
};

class StackP
{
	//Нижняя и верхняя границы стека
	enum {EMPTY = -1, FULL = 20};

	//Массив для хранения данных
	char st[FULL + 1];

	//указатель на вершину стека
	int top;
public:
	//конструктор
	StackP();

	//Добавление элемента
	void Push(char c);

	//Извлечение элемента
	char Pop();

	//Очистка стека
	void Clear();

	//Проверка существования элементов в стеке
	bool IsEmpty();

	//проверка на переполнение стека
	bool IsFull();

	//Количество эелемнтов в стеке
	int GetCount();
};
StackP::StackP()
{
	//изначально стек пуст
	top = EMPTY;
}
void StackP::Clear()
{
	//Эффективная "очистка" стека
	//данные в массиве всё еще существуют,
	//НО функция класса, ориентированная на работу с вершиной стека
	//будет игнорировать их.
	top = EMPTY;
}
bool StackP::IsEmpty()
{
	//Пустой?
	return top == EMPTY;
}
bool StackP::IsFull()
{
	//Полный?
	return top == FULL;
}
int StackP::GetCount()
{
	//Количество присутствующих элементов в стеке
	return top + 1;
}
void StackP::Push(char c)
{
	//Если в стеке есть место, то увеличиваем показатель
	//на вершину стека и вставляем новый элемент
	if (!IsFull())
	{
		st[++top] = c;
	}
}
char StackP::Pop()
{
	//Если в стеке есть элементы, то возвращаем
	//верхний и уменьшаем указатель "на вершину" стека
	if (!IsEmpty())
		return st[top--];
	else //Если в стеке нет элементов
		return 0;
}


class Queue
{
	//очередь
	int* Wait;
	// Максимальный размер очереди
	int MaxQueueLength;
	//Текущий размер очереди
	int QueueLength;
public:
	//Конструктор
	Queue(int m);
	
	//Деструктор
	~Queue();
	
	//Добавление элемента
	void Add(int c);

	//Извлечение элемента
	int Extract();

	//Очистка очереди
	void Clear();

	//Проверка существования элементов в очереди
	bool IsEmpty();

	//Проверка на переполнение очереди
	bool IsFull();

	//Количество элементов в очереди
	int GetCount();

	//демонстрация очереди
	void Show();
};
void Queue::Show()
{
	cout << "\n---------------------------------------\n";
	for (int i = 0; i < QueueLength; i++)
	{
		cout << Wait[i] << ' ';
	}
	cout << "\n---------------------------------------\n";
}
Queue::~Queue()
{
	delete[] Wait;
}
Queue::Queue(int m)
{
	//получить размер
	MaxQueueLength = m;
	//создаем очередь
	Wait = new int[MaxQueueLength];
	QueueLength = 0;
}
void Queue::Clear()
{
	//Эффективная "Очистка" очереди
	QueueLength = 0;
}
bool Queue::IsEmpty()
{
	//пустой?
	return QueueLength == 0;
}
bool Queue::IsFull()
{
	//Полный?
	return QueueLength == MaxQueueLength;
}
int Queue::GetCount()
{
	//Количество присутствующих в стеке эелемнтов
	return QueueLength;
}
void Queue::Add(int c)
{
	//Если есть свободное место то увеличиваем кол-во значений
	// и вствавляем новый элемент
	if (!IsFull())
		Wait[QueueLength++] = c;
}
int Queue::Extract()
{
	//Если в очереди есть элементы, то возвращаем тот,
	//который вошел первым и сдвигаем очередь
	if (!IsEmpty())
	{
		//запомнить первый
		int temp = Wait[0];

		//сдвинуть все эелементы
		for (int i = 1; i < QueueLength; i++)
			Wait[i - 1] = Wait[i];
		// Уменьшить количество
		QueueLength--;

		//Вернуть первый(нулевой) элемент
		return temp;
	}
	else
		return -1; //Если в очереди нет элементов 
}

int main()
{
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "Rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	
	Queue QU(25);
	for (int i = 0; i < 5; i++)
	{
		QU.Add(rand() % 50);
	}
	QU.Show();
	cout << QU.Extract();
	QU.Show();

	//StackP ST;
	//char c;
	////Пока стек не заполниться
	//while (!ST.IsFull()) {
	//	//c = 30+rand() % (120-30);
	//	cin >> c;
	//	ST.Push(c);
	//}
	////Пока стек не освебодится
	//while (c = ST.Pop()) {
	//	cout << c << ' ';
	//}
	//cout << "\n\n";

	/*ArrayP arrP1{ 1,10 };
	ArrayP arrP2{ 1.1,10 };
	arrP1.display();
	arrP2.display();*/

	/*RectangleP rect1{ {0,0},10,5 };
	RectangleP rect2{ {0,0},{10,10} };

	cout << "Rectangle 1 " << rect1 <<
		"\n\n" << "Rectangle 2 " << rect2 << "\n\n";*/
	return 0;
}

