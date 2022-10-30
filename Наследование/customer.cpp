#include <iostream>
#include <cstdlib>
#include <fstream>
#define APPLE_PRICE 10
using namespace std;
// Класс, в котором есть общие для работников и ворон
// атрибуты и функции

class Person{
  int apple; // яблоки "знают" и работники и вороны
public:
      Person(); // конструктор. Количество яблок - случайно
      Person(int app); // инициализирующий конструктор.
      int getApple(); // возвращает количество яблок
      void print(); // печать

  // теперь изменять basket могут только
  // объекты классов-наследников
     static int basket;
};
// Сначала в козине 0
int Person::basket=0;

// Реализация

Person::Person(){
    //srand(time(0));
    apple=rand() % 100;
//   cout<<"Появился кто-то. Хочет "<<apple<<" яблок в час"<<endl;
};

Person::Person( int app){
// Проверка. Сокращенная запись
// Если app < 0, то яблок - 0, если >=0, то не больше 100
    apple=(app < 0)? 0 : app % 100;
//   cout<<"Появился кто-то. Хочет "<<apple<<" яблок в час"<<endl;
};
// получить яблоки
int Person::getApple(){
     return apple;
};
// печать
void Person::print(){
  cout<<apple<<" яблок в час"<<endl;
// basket - статическая переменная - общая для всех
// сразу печататем сколько в ней яблок
};

class Worker:public Person{
public:
      Worker();
      Worker(int app);
      void act();
// Для денег за яблоки заведем  кошелек
      static int cache;

};

int Worker::cache = 0;

// Реализация

Worker::Worker(){
// в новом конструкторе можно добавить действий
   cout<<"Я работник, я собираю ";
// этот print() уже есть в классе - родителе Person
// его можно просто вызвать.
   print() ;
};

// Новый инициализирующий конструктор
// Когда создается объект класса-наследника, сначала всегда создается
// объект класса - родителя.
// apple - в закрытой области класса-родителя, значит
// не доступен Worker/
// Чтобы передать параметры объекьу классса Person,
// нужно ЯВНО вызвать инициализирующий конструктор класса Person

Worker::Worker(int app):Person(app){
   cout<<"Я работник, мне сказали собирать ";
   print() ;
};

// basket - в открытой области. Можно спокойно им пользоваться
void Worker::act(){
     basket += getApple(); // кладет яблоки в корзину
    // cout << basket << endl;
};

class Crow:public Person{
// про яблоки все уже написано в классе Person
   public:
       Crow(); // конструктор
       Crow(int app); // инициализирующий конструктор
       void steal(); // вороны воруют яблоки из корзины
};

Crow::Crow(){
// в новом конструкторе можно добавить действий
   cout<<"Я ворона, я ворую ";
// этот print() уже есть в классе - родителе Person
// его можно просто вызвать.
   print() ;
};

Crow::Crow(int app):Person(app){
   cout<<"Я ворона, я буду воровать ";
   print() ;
};

// basket - в открытой области. Можно спокойно им пользоваться
void Crow::steal(){
    int n = getApple();
    if (basket > n)
     basket -= n;
    else
      basket = 0;
};


// класс Покупатель. Он берет яблоки и оставляет в деньги в cache
// имеет доступ к cache
class Customer:public Person{
// про яблоки уже все известно
  int money;
  public:
    Customer();// конструктор только по-умолчанию, деньги случайно, но <= 20
// покупатель может и собирать яблоки - функция act() у него тоже есть
// берет яблоки и оставляет деньги в cache
    void buy();

    void print();
};

Customer::Customer(){
// в новом конструкторе можно добавить действий
   cout<<"Я покупатель, я покупаю ";
// этот print() уже есть в классе - родителе Person
// его можно просто вызвать.
   Person::print() ;
};

void Customer::buy()
{
  int buy_n_apples = getApple();
  if (basket >= buy_n_apples)
  {
    Worker::cache += APPLE_PRICE * buy_n_apples;
    basket -= buy_n_apples;
  }

  else
    printf("%s\n", "В корзине меньше яблок, чем хочет покупатель");
};


int main(int argc, char const *argv[]){
    int arr[4];
    if (argc < 2)
    {
      exit(1);
    }

    string path(argv[1]);
    ifstream fin;
    fin.open(path);

    if (!fin.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        exit(1);

    }
    else {
        cout << "Файл открыт" << endl;
    }

    for (int i = 0; i < 4; i++) {
        fin >> arr[i];
        //cout << arr[i];
    }


    fin.close();
    cout << "Файл закрыт" << endl;
    // arr[0] - hour arr[1]-количество работников arr[2]-количество ворон
    // arr[3] - количество покупательей

    Worker a[arr[1]];
    Crow cr[arr[2]];
    Customer biz[arr[3]];

    for(int h = 0; h < arr[0]; h++)
    {
      for(int i = 0; i < arr[1]; i++)
      {
        a[i].act();
      }

      for (int j = 0; j <arr[2]; j++)
      {
        cr[j].steal();
      }

      for (int k = 0; k < arr[3]; k++)
      {
        biz[k].buy();
      }
    }

    cout << "\nСобранных денег в конце дня: " << Worker::cache << endl;
    cout << "Собранных яблок в конце дня: " << Person::basket << endl;
   return 0;
}
