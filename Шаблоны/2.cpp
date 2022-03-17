#include <iostream>
#include <cstdlib> 


using namespace std;

//Класс Obj - элементы этого класса необходимо поместить в буфер
class Obj{
    int n;
    
public:
    Obj();
    Obj(int);
    void print();
    bool operator ==(const Obj&) const;
    ostream& put(ostream&);
};
class Villager
{
    string name;
    int status;
    
public:
    Villager(string, int);
    Villager();
    void set(string, int);
    bool operator ==(const Villager&);
    Villager& operator+= (int);
    int get_money();
    void put(int);
    ostream& put(ostream&);
};

// Класс-контейнер для элементов Obj
template< class T>class CBuff{
    
    /*
     Внутренний класс Elem,  описывающий каждый узел
     кольцевого буфера
     */
    class Elem
    {
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
    
    // Деструктор буфера
    ~CBuff();
    
    /*
     Добавление элемента в буфер.
     Добвление будем производить после последнего элемента
     */
    void add(T);
    
    
    CBuff* operator()();
    /*
     Получить указатель на первый элемент кольцевого списка.
     Заметим, что возвращаемый тип данных (указатель на Elem)
     может быть доступен только функциям или друзьям класса CBuff
     */
    
    int size_ ();
    Elem* begin();

    void free(CBuff<T>&);
    
    // Получить указатель на последний элемент списка
    Elem* end();
    
    // Печать всего списка (для отладки)
    void print();
    Elem * find(const Obj&);
    void deletE(Elem*);
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
        Iterator* operator++();
        
        // Возвращение указателя на объект, помещенный в список
        T* operator->();
        
        // Получение доступа к самому объекту. Оператор "разыменовывания"
        T& operator*();
        
        // Сравнение двух элементов ("нет, это не он")
        int operator !=(Elem*);
        
        bool operator== (CBuff<T>::Iterator&);

    };
    
};

//______________________________________________________________________
// Реализация класса Obj
//______________________________________________________________________

Obj::Obj(){
    n=0;
};
Obj::Obj(int a)
{
    n = a;
    cout<<"obj param: " << n << '\n';
};

void Obj::print(){
    cout<< n << '\n';
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
Villager::Villager()
{
    
};


bool Villager::operator ==(const Villager& a)
{
    return status == a.status;
}

Villager& Villager::operator+= (int a)
{
    status += a;
    return (*this);
}

void Villager::set(string z, int r){
    name = z;
    status = r;
};

void Villager::put (int a)
{
    status = a;
}

ostream& Villager::put(ostream& s)
{
    return s << "The name of villager: " << name << ", amount of money: " << status;
};

int Villager::get_money()
{
    return status;
}


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
template<class T> CBuff<T>::CBuff(){
    frst = 0;
    kolvo = 0;
};

template<class T> CBuff<T>* CBuff<T>::operator() ()
{
    return this;
}

template <class T> CBuff<T>::~CBuff()
{
    Elem* p = frst;
    
    if (kolvo == 1)
    {
        delete p;
        std::cout << "Destructor\n";
        --kolvo;
    }
    
    else
    {
        while (kolvo-- && kolvo >= 0)
        {
            Elem* p1 = p -> next;
            delete p;
            std::cout << "Destructor\n";
            p = p1;
        }
    }
    
    last = frst = nullptr;
    kolvo = 0;
}

template <class T> void CBuff<T>::free(CBuff<T>& cbuf)
{
    
}

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
template <class T> typename CBuff<T>::Elem* CBuff<T>::begin()
{
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
template <class T> CBuff<T>::Iterator::Iterator()
{
    point = 0;
};


// Оператор присваивания.
template <class T> typename CBuff<T>::Iterator* CBuff<T>::Iterator::operator=(CBuff<T>::Elem* z){
    idx = 1;
    point = z;
    return this;
};

// Оператор префиксного инкрементирования
template <class T> typename CBuff<T>::Iterator* CBuff<T>::Iterator::operator++()
{
    
    // Если список не пуст, перемщаем указатель по списку
    if (point)
        point = point->next;
    
    return this;
};



// Оператор "укаатель на объект"
template <class T> T* CBuff<T>::Iterator::operator->()
{
    return &(point -> obj);
};

template <class T> T& CBuff<T>::Iterator::operator*()
{
    if (point)
        return point -> obj;
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

template <class T> bool CBuff<T>::Iterator::operator==  (CBuff<T>::Iterator& a)
{
    return (*(*this)) == (*a);
}

bool Obj::operator== (const Obj& a) const
{
    return n == a.n;
}

template <class T> typename CBuff<T>::Elem* CBuff<T>::find(const Obj& a)
{
    Elem* prev = frst;
    
    if (kolvo == 1)
        return prev;
    
    bool check = false;
    while (!((prev -> next) -> obj == a) && (prev -> next) != frst)
    {
        prev = prev -> next;
        if ((prev -> next) -> obj == a)
            check = true;
    }
    
    if (!check)
    {
        cout << "There is no such element in the ring buffer." << '\n';
        return nullptr;
    }
    cout << "Previos element before deleted: ";
    
    (prev -> obj).print();
    
    return prev;
}

template <class T> void CBuff<T>::deletE (Elem* p)
{
    if (!p)
        return;
    
    Elem* del = p -> next;
    if (kolvo == 1)
    {
        std::cout << "Deleted element: ";
        (del -> obj).print();
        delete del;
        frst = last  = nullptr;
        kolvo = 0;
    }
    
    else
    {
        p -> next = del -> next;
        if (del == last)
            last = p;
        
        std::cout << "Deleted element: ";
        (del -> obj).print();
        
        delete del;
        --kolvo;
        
    }
}

template <class T> int CBuff<T>::size_()
{
    return kolvo;
}


bool all_is_equal (CBuff<Villager>& workers)
{
    if (workers.size_() == 1)
        return true;
        
    CBuff<Villager>::Iterator cur;
    CBuff<Villager>::Iterator checker;
    cur = workers.begin();

    checker = workers.begin();
    for (; cur != workers.end(); ++cur)
    {
        for (; checker != workers.end(); ++checker)
        {
            if (cur == checker)
                continue;
            
            else if (cur -> get_money() != checker -> get_money())
                return false;
            
        }
    }
    
    return true;
}

void show (CBuff<Villager>& workers)
{
    CBuff<Villager>::Iterator prev;
    prev = workers.begin();
    for (; prev != workers.end(); ++prev)
        cout << *prev << '\n';
}


void money_distribution (CBuff<Villager>& workers, Villager& merchant)
{
    while (!all_is_equal(workers))
    {
        CBuff<Villager>::Iterator prev;
        CBuff<Villager>::Iterator next;
        prev = workers.begin();
        next = workers.begin();
        ++next;
        for (; next != workers.end(); ++next)
        {
            int middle = ((prev -> get_money()) + (next -> get_money())) / 2;
            if (2*middle != (prev -> get_money() + next -> get_money()))
                merchant += ((prev -> get_money() + next -> get_money()) - 2*middle);
            
            (*next).put(middle);
            (*prev).put(middle);
        }
    }
    cout << "After: " << '\n';
    cout << merchant << '\n';
    show(workers);
    
    // Явный вызов деструктора
    workers() -> ~CBuff();
    
}

int main()
{
    /*
    Villager merchant;
    CBuff<Villager> workers;
    Villager worker;
    int t;
    cout << "How many requests do you want to process: ";
    cin >> t;
    for (int i(0); i < t; ++i)
    {
        string name;
        int n;
        int num;
        cout << "The name of merchant: ";
        cin >> name;
        cout << "How much money will he have: ";
        cin >> n;
        merchant.set(name, n);
        cout << "Number of workers: ";
        cin >> num;
        for (int j(0); j < num; ++j)
        {
            cout << "The name of " << j + 1 << " worker: ";
            cin >> name;
            cout << "How much money will he have: ";
            cin >> n;
            worker.set(name, n);
            workers.add(worker);
        }
        cout << "Before: " << '\n';
        cout << merchant << '\n';
        show (workers);
        money_distribution(workers, merchant);
    }
   
   */
    
    
    /*
    cout << "merchant: " << merchant << '\n';
    cout << '\n';
    cout << (all_is_equal(workers) ? "They are all equal" : "No, they all have different amounts of money") << '\n';
    cout << '\n';
    show(workers);

    cout << '\n';
    
    int var = 1000;
    CBuff<Villager>::Iterator cur;
    cur = workers.begin();
    for (; cur != workers.end(); ++cur)
    {
        cur -> put(var);
    }
    
    merchant += 1500;
    cout << merchant << '\n';
    show(workers);
    
    cout << (all_is_equal(workers) ? "They are all equal" : "No, they all have different amounts of money") << '\n';
    
    cout << '\n';
    
     */
    
    
    
    
    
    CBuff<Obj>::Iterator tobj;
    cout << "Objects:\n";
    CBuff<Villager> a;
    CBuff<Obj> ab;//  список пуст
    int cases;
    cin >> cases;
    cout << cases << " objects" << '\n';
    for (int i(0); i < cases; ++i)
    {
        int temp;
        cin >> temp;
        Obj a = temp;
        ab.add(a);
    }
    int del;
    cin >> del;
    cout << "Number of objects to be removed " << del << '\n';
    for (int i(0); i < del; ++i)
    {
        int temp;
        cin >> temp;
        Obj elem = temp;
        for(tobj = ab.begin(); tobj != ab.end(); ++tobj)
            cout << *tobj <<' ';
        
        cout << '\n';
        ab.deletE(ab.find(elem));
        
        cout << "Objects after deleting:\n";
        for(tobj = ab.begin(); tobj != ab.end(); ++tobj)
            cout << *tobj <<' ';
        cout << '\n';
        
    }
    
    return 0;
}

