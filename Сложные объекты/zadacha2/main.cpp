#include <fstream>
#include "zadacha2_head.h"
#define N 6

int main()
{

	int arr[N];
	string path = "data.txt";
	ifstream fin;
	fin.open(path);

	if (!fin.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		exit(1);
	}
	else
	{
		cout << "Файл открыт" << endl;
	}

	for (int i = 0; i < N; i++)
	{
		fin >> arr[i];
	}

	fin.close();
	cout << "Файл закрыт" << endl;

	Drob a(arr[0],arr[1],arr[2]);
	Drob b(arr[3],arr[4],arr[5]);

	cout << "Дробь 1: ";
	a.print();
	cout << endl;
	cout << "Дробь 2: ";
	b.print();
	cout << "\n";

	Drob c;
	c = a + b;
	cout << "Сумма: ";
	c.print();
	cout << "\n";

	c = a -b;
	cout << "Разность: ";
	c.print();
	cout << "\n";

	c = a* b;
	cout << "Произведение: ";
	c.print();
	cout << "\n";

	c = a/b;
	cout << "Частное: ";
	c.print();
	cout << "\n";

	int flag;
	flag = (a > b);
	cout << "Больше: ";
	cout << flag << endl;

	flag = (a< b);
	cout << "Меньше: ";
	cout << flag << endl;

	flag = (a == b);
	cout << "Равно: ";
	cout << flag << endl;

	return 0;
}
