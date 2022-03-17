#include <fstream>
#include "long.h"
#define N 2

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
    else {
        cout << "Файл открыт" << endl;
    }

    for (int i = 0; i < N; i++) {
        fin >> arr[i];
        //cout << arr[i];
    }

    fin.close();
    cout << "Файл закрыт" << endl;


    Arithmetic a(arr[0]);
    cout << "a = ";
    a.print();
    Arithmetic b(arr[1]);
    cout << "b = ";
    b.print();
    cout << endl;


    cout << "Конструктор по умолчанию, число - 0, размер 1\n";
    Arithmetic c; // Arithmetic() - конструктор по умолчанию
    c.print();
    cout << endl;
    

    cout << "Инициализирующий строкой конструктор\n";
    c = Arithmetic("212124512124542856533356");
    c.print();
    cout << endl;

    cout << "operator= т.е. Arithmetic = Arithmetic, (c = a, c.print())\n";
    c=(a);
    c.print();
    cout << endl;

    cout << "оператор копирования: Arithmetic = int\n";
    c=("999999");
    c.print();
    cout << endl;

    cout << "operator- без аргумента\n";
    -c;
    c.print();
    -c;
    c.print();
    cout << endl;

    cout << "operator+ (сложение длинных чисел)\n";
    c = a + b;
    c.print();
    cout << endl;

    cout << "operator+=\n";
    a += a;
    a.print();
    cout << endl;

    cout << "operator-=\n";
    Arithmetic x("9999999999999");
    Arithmetic y("8888888888888");
    x -= y;
    x.print();
    cout << endl;

    cout << "operator++\n";
    ++c;
    c.print();
    ++c;
    c.print();
    ++c;
    c.print();
    cout << endl;

    cout << "operator--\n";
    --c;
    c.print();
    --c;
    c.print();
    cout << endl;

    cout << "operator+ (int)\n";
    c = b + (777);
    c.print();
    cout << endl;

    cout << "operator- (int)\n";
    Arithmetic n("123456789123456789");
    c = n - (7);
    c.print();
    cout << endl;

    cout << "operator- (Arithmetic)\n";
    //Arithmetic n("123456789123456789");
    Arithmetic m_1("999999999999999999999999");
    Arithmetic m_2("1");
    c = m_1 - m_2;
    c.print();
    cout << endl;

    return 0;
}
