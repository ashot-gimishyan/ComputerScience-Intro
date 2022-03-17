#include <iostream>
#include <cstdlib>
using namespace std;

int NOD(int, int);

class Drob{
 int cel, chisl,znam;

public:
  Drob(); // конструктор дроби по-умолчанию
// Инициализирующий конструктор
  Drob(int, int, int);

// Устанавливаем значение
  void setVol(int, int,int);
/*
Зарезервированное слово "operator" обозначает описание именно
оператора, а не какой-либо другой функции.
В С++ существуют два способа передачи адреса: указатель (*) и
ссылка (&).
  При передачи указателя синтаксис работы с этим объектом
как с указателем (разыменовывание - *point, обращение к
атрибутам и методам - point->metod()).

  При передачи ссылки сохраняется синтаксис как при работе с
самим объектом: разыменовывание не нужно.

Но объявить ссылку как отдельный объект нельзя. Она
используется только для передачи данных в функции и как
возвращаемые значения функций.

При передачи адреса есть опасность несанкционированно
изменить значение объекта. Чтобы этого не произошло,
объявляется const. Тогда такие попытки будут отловлены на
стадии компиляции.

*/
  Drob operator+(const Drob&);
  void prrrint();
/*
  Оператор ++ - постфиксный, то есть пишется после объекта.
Поэтому для соблюдений правил синтаксиса ему нужно указать
неиспользуемый параметр int

Так как этот оператор изменяет текущий объект, он возвращает
указатель на себя самого. Для того, чтобы иметь указатель на текущий
объект, имеется специальное слово this.
*/
  Drob& operator++(int);
  Drob operator*(const Drob& a);


/*
  Оператор ! - префиксный, то есть пишется перед объектом.
Ему не нужно указывать дополнительный параметр, так как сам
объект формально является его параметром.

  Для всех операторов существует строго определенное количество
параметров, а для некоторых параметров еще должен сохраняться его
тип. Переопределяя оператор, нельзя изменить количество параметров
для этого оператора (а для некоторых еще и тип). Переопределению
подлежит, в основном, функциональность.
*/

  Drob& operator!();

// Для отладки
  void print();
  void print(char);
  void print(int);
};

Drob::Drob(){
  cel = chisl = 0;
  znam = 1;
};


void Drob::print(){
  if (cel == 0)
  {
    if (znam == 0 && chisl == 0)
    {
      printf("%d\n", cel);
      exit(2);
    }

    if (znam == 0)
    {
      printf("%s\n", "Деление на ноль!!!");
    }
    else if (znam != 1)
    {
      if (chisl == 0)
      {
        printf("%d\n", 0);
      }
      else
      {
        cout<<chisl<<'/'<<znam;
      }
    }
    else
    {
      if (chisl == 0)
      {
        printf("%d\n", 0);
      }
      else
      {
        cout<<chisl;
      }
    }
  }
  else
  {
    if (znam == 0 && chisl == 0)
    {
      printf("%d\n", cel);
      exit(2);
    }
    if (znam == 0)
    {
      printf("%s\n", "Деление на ноль!!!");
    }
    else if (znam != 1)
    {
      if (chisl == 0)
      {
        cout << cel;
      }
      else
      {
        cout<<cel<<'('<<chisl<<'/'<<znam<<')';
      }
    }
    else
    {
      if (chisl == 0)
      {
        printf("%d\n", cel);
      }
      else
      {
        cout<<chisl + cel;
      }
    }
  }

};

void Drob::setVol(int a, int b, int c){
     cel = a;
     chisl = b;
     znam = c;
};

/*
 Это "заглушка" - то есть функциональность
реализована не полностью.
Этот метод  - только как пример написания подобных.

При использовании параметра, переданного "по-ссылке" синтаксис
использования такой же как и для параметров, переданных как копии
*/
Drob Drob::operator+(const Drob& a){
     Drob tmp;
     int multi_znam = znam * a.znam;
     int multi_chisl_1 = chisl * (multi_znam / znam);
     int multi_chisl_2 = a.chisl * (multi_znam / a.znam);
     int obshi_chisl = multi_chisl_1 + multi_chisl_2;

     int nodd = NOD(obshi_chisl, multi_znam);
     tmp.chisl = obshi_chisl / nodd;
     tmp.znam = multi_znam / nodd;
     return tmp;
};

/*
  Это также "заглушка".
Изменения произошли с текщим объектом, и
возвращается указатель на текущий объект.
  Указывается параметр int, который не используется.
*/

Drob& Drob::operator++(int){
   cel++;

   return *this;
};

/*
  Префиксный оператор.
Также возвращается ссылка на текущий объект.
*/
Drob& Drob::operator!(){
    int z = chisl + cel;
    chisl = znam;
    znam = z;
    cel=0;
    return *this;
};

// print() "с парамером" - n означает сколько знаков
// после запятой нужно напечатать.
void Drob::print(int n){
   int c = cel * znam + chisl;
   int b = znam;
  for(int i = 0; i < n + 1; i++){
   int pr = c / b;
   cout<<pr;
   if (i == 0)
    cout<<'.';
   int next = c % b;
   next *= 10;
   while(next < b){
     next *= 10;
     i++;
     if (next >= b || i>=n) break;
     cout<<'0';
   }
  c = next;
 }
  cout<<endl;
};

// Инициализирующий конструктор (с параметрами )
// По количеству и типам параметров С++ различает какую из
// какую из имеющихся функций нужно применять
Drob::Drob(int c, int ch, int z){
    int the_nod = 1;
    if (ch != 0 && z != 0)
    {
     the_nod = NOD(ch, z);
   }
     cel = c;
     chisl = ch / the_nod;
     znam = z / the_nod;
};

int NOD(int n1, int n2)
{
  int div;
  if (n1 == n2)   // если числа равны, НОД найден
    return n1;
  int d = n1 - n2; // Находим разность чисел
  if (d < 0)       // если разность отрицательная,
  {
    d = -d;     // меняем знак
    div = NOD(n1, d); // вызываем функцию NOD() для двух наименьших чисел
  }
  else      // если разность n1-n2 положительная
  {
    div = NOD(n2, d); // вызываем функцию NOD() для двух наименьших чисел
  }
  return div;
}


void Drob::print(char zvezda)
{
  int obshi_znam = znam * cel + chisl; // 1
  int isxod_cel_chast = obshi_znam / znam; // 0
  cout << isxod_cel_chast; // 0
  cout << "."; // .

  int ostalos_chisl = obshi_znam % znam; // 1
//  cout << ostalos_chisl;
  int arr[15] = {0};
  int n = 0; // количество элементов в массиве
  int flag = 0;

do {
    int net = 0;
    ostalos_chisl *= 10; // 30
    int x = ostalos_chisl / znam; // 4
    for (int i = 0; i < n; i++)
    {
      if (arr[i] != x)
        net++;
      else
      {
        for (int k = 0; k < i; k++)
        {
          cout << arr[k];
        }
        cout << '(';
        for (int j = i; j < n; j++)
          {
            cout << arr[j];
          }
        cout << ')';
          exit(1);
      }
      flag = i+1;
    }

    if (net == n)
    {
      arr[flag] = x;
      n++;
    }
    ostalos_chisl %= znam; // 2

} while(1);

};

Drob Drob::operator*(const Drob& a)
{
  Drob tmp;
  int tmp_znam = znam * a.znam;
  //  cout << tmp_znam;
  int tmp_chisl = chisl * a.chisl;
  //  cout << tmp_chisl;
  int my_nod = NOD(tmp_znam, tmp_chisl);
  tmp.chisl = tmp_chisl / my_nod;
  tmp.znam = tmp_znam / my_nod;

  return tmp;
};

void Drob::prrrint()
{
  int cel = chisl / znam;
  int new_chisl = chisl % znam;
  cout<<cel<<'('<<new_chisl<<'/'<<znam<<')';

};


int main(){
  int m, n, k;
  cin >> m >> n >> k;

  Drob sum;
  int hill = 0; // пока 0 метров

  Drob b(0, 1, n);
  Drob c(0, 1, k);
  Drob e(0, 1, 1); // чтобы в конце сложить 1 метр

   if (m % 2 == 0)
   {
       Drob a_1(0, m, 2);
       sum = b.operator+(c);
       Drob pr = sum.operator*(a_1);

       sum = pr.operator+(e);
       sum.prrrint();
   }
   else
   {
     Drob a_2(0, m+1, 2); // for n
     Drob a_3(0, m-1, 2); // for k

     Drob pr_k = a_3.operator*(c);
     Drob pr_n = a_2.operator*(b);
     sum = pr_k.operator+(pr_n);

     sum = sum.operator+(e);
     sum.prrrint();
   }

  return 0;
}
