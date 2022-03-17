#include "timedat2.h"

int main(int argc, char** argv){
  char ss[100];//="13 7:25:10.9876";
   FILE *fin;
   if(argc > 1){
      fin = fopen(argv[1],"r");
      if( errno ){
         perror("file open: ");
         exit(1);
      }
   }
// в файле две строки с описанием даты
// строго по фомату
   fgets(ss,99,fin);
   DataTime dt;
   dt.getData(ss);
   dt.print();
   fgets(ss,99,fin);
   DataTime dt1(ss);
   dt1.print();
   CTime res;
// получение результата вычитания
// здесь предполагается, что первое время больше
   res = dt - dt1;
   res.print();

 return 0;
}
