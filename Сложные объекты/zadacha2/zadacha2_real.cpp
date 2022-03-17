#include <string>
#include "zadacha2_head.h"

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
      exit(1);
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
  int tmp_chisl_1 = znam*cel + chisl; // 5
  int tmp_chisl_2 = a.znam * a.cel + a.chisl; // 5
  Drob tmp;
  tmp.znam = a.znam * znam; // 4
  //  printf("%s\n", "------------------------");
  tmp.chisl = (a.znam * tmp_chisl_1 + znam * tmp_chisl_2)% tmp.znam;
  //  printf("%s\n", "------------------------");
  tmp.cel = (a.znam * tmp_chisl_1 + znam * tmp_chisl_2)/ tmp.znam;
  //  printf("%s\n", "------------------------");

  int n_1;
  if (tmp.chisl != 0)
    n_1 = NOD(tmp.znam, tmp.chisl);

  if(n_1 > 1)
  {
    tmp.chisl /= n_1;
    tmp.znam /= n_1;

  }
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

int Drob::NOD(int n1, int n2)
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


// вычитание дробей
Drob Drob::operator-(const Drob& a){
  int tmp_chisl_1 = znam*cel + chisl; // 5
  int tmp_chisl_2 = a.znam * a.cel + a.chisl; // 5
  Drob tmp;
  tmp.znam = a.znam * znam; // 4
  //  printf("%s\n", "------------------------");
  tmp.chisl = (a.znam * tmp_chisl_1 - znam * tmp_chisl_2)% tmp.znam;
  tmp.cel = (a.znam * tmp_chisl_1 - znam * tmp_chisl_2)/ tmp.znam;

  int n_1;
  if (tmp.chisl != 0)
    n_1 = NOD(tmp.znam, tmp.chisl);

  if(n_1 > 1)
  {
    tmp.chisl /= n_1;
    tmp.znam /= n_1;

  }

  return tmp;

};

// умножение
Drob Drob::operator*(const Drob& a){
  int tmp_chisl_1 = znam*cel + chisl; // 5
  int tmp_chisl_2 = a.znam * a.cel + a.chisl; // 5
  Drob tmp;
  tmp.znam = a.znam * znam; // 4
  //  printf("%s\n", "------------------------");
  tmp.chisl = (tmp_chisl_1 * tmp_chisl_2)% tmp.znam;
  //  printf("%s\n", "------------------------");
  tmp.cel = (tmp_chisl_1 * tmp_chisl_2)/ tmp.znam;
  //  printf("%s\n", "------------------------");

  int n_1;
  if (tmp.chisl != 0)
    n_1 = NOD(tmp.znam, tmp.chisl);

  if(n_1 > 1)
  {
    tmp.chisl /= n_1;
    tmp.znam /= n_1;

  }
  return tmp;
};


// Деление
Drob Drob::operator/(const Drob& a){
  int tmp_chisl_1 = znam*cel + chisl; // 9
  int tmp_chisl_2 = a.znam; // 7
  Drob tmp;
  tmp.znam = znam * (a.znam * a.cel + a.chisl); // 4
  //  printf("%s\n", "------------------------");
  tmp.chisl = (tmp_chisl_1 * tmp_chisl_2)% tmp.znam;
  //  printf("%s\n", "------------------------");
  tmp.cel = (tmp_chisl_1 * tmp_chisl_2)/ tmp.znam;
  //  printf("%s\n", "------------------------");

  int n_1;
  if (tmp.chisl != 0)
    n_1 = NOD(tmp.znam, tmp.chisl);

  if(n_1 > 1)
  {
    tmp.chisl /= n_1;
    tmp.znam /= n_1;

  }

  return tmp;
};


// инвертирование
Drob& Drob::operator!(){
    int z = chisl + cel*znam;
    chisl = znam;
    znam = z;
    cel=0;

    int n_1;
    if (chisl != 0 && znam != 0)
      n_1 = NOD(znam, chisl);

    if(n_1 > 1)
    {
      chisl /= n_1;
      znam /= n_1;
    }

    return *this;
};

// операторы сравнения
int Drob::operator>(const Drob& a)
{
  return ((znam * cel + chisl)*a.znam) > (znam * (a.znam * a.cel + a.chisl));
};


int Drob::operator<(const Drob& a)
{
  return ((znam * cel + chisl)*a.znam) < (znam * (a.znam * a.cel + a.chisl));
};


int Drob::operator==(const Drob& a)
{
  return ((znam * cel + chisl)*a.znam) == (znam * (a.znam * a.cel + a.chisl));
};
