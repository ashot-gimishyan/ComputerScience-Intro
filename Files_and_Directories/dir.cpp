// Реализация функции
#include "sysdir.h"

// конструктор класса
Catalog::Catalog()
{
    dirrec = 0;
    numbersf = 0;
    dir = 0;
};

// деструктор класса
Catalog::~Catalog()
{
    if (dir) {
        closedir(dir);
    }
};

// открыть каталог
unsigned char Catalog::dopen(char* dirnm)
{
    dir = opendir(dirnm);
    unsigned char er = errno;
    if (errno) {
        perror("dir!!");
        return er;
    }

    int sdir = open(dirnm, O_RDONLY);
    er = errno;
    struct stat sb;

    if (errno) {
        perror("Error!");
        return er;
    }

    fstat(sdir, &sb);
    return 0;
};

// закрыть каталог
bool Catalog::dclose()
{
    int res_dir;
    res_dir = closedir(dir);

    // closedir returns 0 if everything is OK
    if (res_dir != 0) {
        printf("%s\n", "Ошибка при закрытии каталога!");
        exit(1);
    }
    else {
        // Set pointer to NULL after free
        dir = 0;
        return true;
    }
};

// Напечать список файлов с указание их атрибутов, размера и владельца
// ls -l
void Catalog::list()
{
    char * c;
    int i;
    struct passwd* pw;
    /*
    #include <pwd.h>

    struct passwd {
    	char *pw_name;
    	char *pw_passwd;
    	uid_t pw_uid;
    	gid_t pw_gid;
    	time_t pw_change;
    	char *pw_class;
    	char *pw_gecos;
    	char *pw_dir;
    	char *pw_shell;
    	time_t pw_expire;
    };
    */

    // системные структуры
    struct dirent* myfile;
    struct stat fileStat;
    /*
    #include <sys/types.h>
    #include <sys/stat.h>

    struct stat {
    	dev_t st_dev;
    	ino_t st_ino;
    	mode_t st_mode;
    	nlink_t st_nlink;
    	uid_t st_uid;  // User ID of file owner.
    	gid_t st_gid;
    	dev_t st_rdev;
    	off_t st_size;
    	time_t st_atime;  // access
    	time_t st_mtime; // Time of last data modification.
    	time_t st_ctime;  // change
    	blksize_t st_blksize;
    	blkcnt_t st_blocks;
    	mode_t st_attr;
    };
    */

    // заполнение системной структуры начальними значениями
    stat(".", &fileStat);

    while ((myfile = readdir(dir)) != NULL) {
        stat(myfile->d_name, &fileStat);

        pw = getpwuid(fileStat.st_uid);
        printf("%s ", pw->pw_name);
        printf("%4ld ", fileStat.st_size);
        c = ctime(&fileStat.st_mtime);
        for (i = 0; i <= 15; i++)
            printf("%c", c[i]);
        printf(" ");
        printf("%s\n", myfile->d_name);
    }

};

// получить количество файлов
int Catalog::getNumbers()
{
  int n = 0;
  struct dirent* d;

  while ((d = readdir(dir)) != NULL) {
    n++;
  }
  printf("Всего %d файлов.\n", n);
  return n;
};

// удалить файл
int Catalog::delF(char * name)
{
  // system("rm name")
  if (remove(name) == 0)
  {
    cout << "Файл успешно удален" << endl;
    return 1;
  }

  perror("Ошибка при удалении файла");
  return 0;
};

// содержимое файла
int Catalog::catF(char * name)
{
  FILE *fp;
  char buffer[1000];

  fp = fopen(name, "r");
  if (fp != NULL)
  {
    while (fgets(buffer, 1000, fp) != NULL)
        printf("%s", buffer);
    fclose(fp);
    return 1;
  }

return 0;
};


// получить атрибуты доступа к файлу
int Catalog::getMode()
{
printf("\n");
struct dirent *myfile;
struct stat fileStat;

stat(".",&fileStat);
printf("Атрибуты доступа\tИмя файла\n");
while((myfile=readdir(dir))!=NULL)
{
  stat(myfile->d_name, &fileStat);
  printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
  printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
  printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
  printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
  printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
  printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
  printf("\t\t%s", myfile->d_name);
  printf("\n");
}
printf("\n");
return 0;
};

// проверка файла на существование
int Catalog::isExFile( char * name)
{
  struct stat buffer;
  // Функция stat возвращает значение 0,
  // если получена информация о статусе файла
  // имя файла или path-имя не найдено при0значении -1
  return (stat (name, &buffer) == 0);
};
