#include <cstdlib>
#include <iostream>


using namespace std;

//Класс Obj - элементы этого класса необходимо поместить в буфер
class Obj{
   int n;

public:
     Obj();
     Obj(int);
     void print();
      ostream& put(ostream&);
};
class Villager{
   string name;
   int status;
public:
      Villager(string, int);
      Villager();
      void set(string, int);
      ostream& put(ostream&);
};

// Класс-контейнер для элементов Obj
// Шаблон класса CBuff
template< class T>class CBuff{

/*
  Внутренний класс Elem,  описывающий каждый узел
  кольцевого буфера
*/
  class Elem{
  public:

// Объекты, помещаемые в буфер
    T obj;

// Указатель на следующий элемент буфера
    Elem *next;

// Количество элементов в буфере
    int nm;
  };

// Два указателя на кольцевой список: на первый элемент
// и  на последний
  Elem * frst;
   Elem * last;

// Общее количество элементов
  int kolvo;

 public:
       class Iterator;
// Конструктор буфера
        CBuff();

/*
  Добавление элемента в буфер.
  Добвление будем производить после последнего элемента
*/
       void add(T);

/*
  Получить указатель на первый элемент кольцевого списка.
  Заметим, что возвращаемый тип данных (указатель на Elem)
  может быть доступен только функциям или друзьям класса CBuff
*/
       Elem* begin();

// Получить указатель на последний элемент списка
       Elem* end();

// Печать всего списка (для отладки)
        void print();
         Elem * find(const T&);
      //   void delete(Elem*);
      void delElem(Iterator);
/*
  Класс Iterator - внутренний класс (НЕ ОБЪЕКТ!!) класса CBuff.
  Находится в области public, значит может быть доступен для
  конструирования объекта и доступа к его методам.
  Класс Iterator:
  1. получает указатель на конкретный элемент списка,
     состоящего из узлов типа Elem
  2. перемещается к следующему элементу в списке
  3. возвращает указатель на объект Obj, помещенный в буфер
  4. позволяет выполнить операцию "разыменовывания" для
     указателей на объект
  5. позволяет выпольнить сранение ("нет, это не он") для решения
     достигнут ли нужный элемент при просмотре списка
*/
        class Iterator{

 // Указатель на элемет списка
            CBuff<T>::Elem *point;
            int idx; // для проверки конца обхода

         public:

// Конструктор
            Iterator();

// Оператор присваивание. В качестве параметра указатель на Elem
            Iterator* operator=(Elem*);

// Перемещение к следующему элементу в списке
            Iterator* operator++(int);

// Возвращение указателя на объект, помещенный в список
            T* operator->();

// Получение доступа к самому объекту. Оператор "разыменовывания"
            T operator*();

// Сравнение двух элементов ("нет, это не он")
            int operator!=(Elem*);

        };

};

//______________________________________________________________________
// Реализация класса Obj
//______________________________________________________________________

Obj::Obj(){
  n=0;
};
Obj::Obj(int a){
    n = a;
cout<<"obj param:"<<n<<endl;
};

void Obj::print(){
    cout<<n<<endl;
};

ostream& Obj::put(ostream& s){
   return s<<n;
};

ostream& operator<<(ostream& s, Obj b){
      return b.put(s);
};
ostream& operator<<(ostream& s, Obj* b){
      return b->put(s);
};

//_______________________________________________
// Villager
//______________________________________________________________________

Villager::Villager(string z, int r){
      name = z;
      status = r;
};
Villager::Villager(){

};

void Villager::set(string z, int r){
      name = z;
      status = r;
};

ostream& Villager::put(ostream& s){
   return s<<name<<'('<<status<<") ";
};


ostream& operator<<(ostream& s, Villager vl){
   return vl.put(s);
};

ostream& operator<<(ostream& s, Villager* vl){
   return vl->put(s);
};
//______________________________________________________________________
// Реализация класса CBuff
//______________________________________________________________________

// Коструктор. Предполагаем, что вначале буфер пуст.
template< class T> CBuff<T>::CBuff(){
     frst = 0;
     kolvo = 0;
};
template< class T> void CBuff<T>::delElem(CBuff<T>::Iterator it){
      cout<<"delele:" << *it <<endl;
};

// Добавление элемента
template< class T> void CBuff<T>::add(T z){
    struct Elem *new_p;
    kolvo++;

// Выделяем память под новый элемент
    new_p = new Elem;

// Заполняем ее полезной информацией
    new_p->obj = z;
    new_p->nm = kolvo;

// Проверяем, пуст буфер или нет
    if (!frst){

//  Если пуст - это элемент становится первым
//  и последним (ссылка на него же)
        frst = new_p;
        frst->next = frst;
        last = frst;

    } else{

// Если не пуст
// ему присваивается ссылка на первый элемент
         new_p->next = last->next;

// последний элемент теперь ссылается на новый
         last->next = new_p;

//  новый становится последним
         last = new_p;
    }

};

// Получение указателя на первый элемент
template <class T> typename CBuff<T>::Elem* CBuff<T>::begin(){
    kolvo = 0;
   return frst;
};

// Получение указателя на последний элемент
template <class T> typename CBuff<T>::Elem* CBuff<T>::end(){
   return last;
};


// Печать всего буфера
template <class T> void CBuff<T>::print(){
  Elem *p = frst;
// Печатаем, если список не пуст
  if (frst != 0){
//      (frst->obj).print();
         cout<<frst->obj<<' ';
      p = frst->next;

     while (p != frst){
//         (p->obj).print();
            cout<<p->obj<<' ';
         p = p->next;
     };
  }
}

//______________________________________________________________________
// Реализация класса CBuff::Iterator
//______________________________________________________________________

// Конструктор. Указатель вначале 0
template <class T> CBuff<T>::Iterator::Iterator(){
    point = 0;
};

// Оператор присваивания.
template <class T> typename CBuff<T>::Iterator* CBuff<T>::Iterator::operator=(CBuff<T>::Elem* z){
     idx = 1;
     point = z;
     return this;
};

// Оператор ++
template <class T> typename CBuff<T>::Iterator* CBuff<T>::Iterator::operator++(int){

// Если список не пуст, перемщаем указатель по списку
        if(point)
        point = point->next;
        return this;
};



// Оператор "укаатель на объект"
template <class T> T* CBuff<T>::Iterator::operator->(){

       return &(point->n);
};

template <class T> T CBuff<T>::Iterator::operator*(){
     if(point)
      return point->obj;
     else
       exit(1);
};

// Оператор "неравенство"
/*
 Так как буфер - кольцевой, то начало и конец списка совпадают
 к тому же могут быть удалены некоторые элементы и начальный
 элемент может изменится
*/
template <class T> int CBuff<T>::Iterator::operator!=(CBuff<T>::Elem* check){
 //   cout<<"check:"<<kolvo<<endl;
    bool ret;
//    cout<<"ret:"<<ret<<endl;

// Проверка в первый ли раз указатель "смотрит"
// на головной элемент
    ret = (idx);

// kolvo=0, значит перехода на следующий элемент не будет
    if(point == check)
        idx--;
    return ret;
};

// Тестирование буфера
int main(int argc, char *argv[])
{
    char c;

    CBuff<Villager> a;
    CBuff<Obj> ab;//  список пуст

    ab.add(7); // добавление элементов
    ab.add(8);
    ab.add(5);
     CBuff<Obj>::Iterator tobj;
      std::cout << "Obj:\n";
      for(tobj = ab.begin(); tobj != ab.end(); tobj++){
//        t->print();
         cout<< *tobj <<' ';
    }

    Villager t1;
      t1.set("Зюзя", 0);
    a.add(t1);

      t1.set("Кузя", 1);
     a.add(t1);

      t1.set("СеменСеменыч", 0);
      a.add(t1);

//    cout<<t1;
// Создание итератора
    CBuff<Villager>::Iterator t;
    cout<<"итератор\n";

// связывание итератора (это другой объект!!!) с буфером
    t = a.begin();
// t-> - указывает на первый элемент списка и, далее, вызов print()
//    t->print();

     cout<< *t <<endl;
     t++;
     a.delElem(t);
// Пример использования итератора в цикле
    for(t = a.begin(); t != a.end(); t++){
//        t->print();
         cout<< *t <<' ';
    }


    return 0;
}
