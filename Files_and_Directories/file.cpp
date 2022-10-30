#include "sysfile.h"
// Конструктор. Инициализируем атрибуты.
SystemFile::SystemFile()
{
    result = 0; //указатель на структуру 0
    id = -1; // если файл не открыт, дескриптор -1
};

// Деструктор. При удаленни объкта типа SystemFile
// файл должен быть закрыт.
SystemFile::~SystemFile()
{
    if (id > -1) {
        close(id);
        id = -1;
    }
};

//функция класса для открытия файла
unsigned char SystemFile::openf(char* name)
{
    unsigned char er;
    // Связывание дескриптора id с именем файла
    id = open(name, O_RDWR | O_CREAT | O_EXCL, 0775);
    er = errno;
    //Проверка открылся ли файл
    if (errno) {
        if (errno == EEXIST) {
            id = open(name, O_RDWR);
            er = 0;
        }
        else {
            return er;
        }
    }
    // заполнение структуры stat информацией о файле
    fstat(id, &sb);
    // получение имени пользователя по uid
    result = getpwuid(sb.st_uid);
    return er;
};
// запись в файл всего что есть в буфере (побайтно)
bool SystemFile::writef(void* buf, long size)
{
    long skolko = 0;
    // системный вызов
    skolko = write(id, buf, size);
    if (skolko == size)
        return 1;
    else
        return 0;
};

// закрыть файл
bool SystemFile::closef()
{
    if (id > -1) {
        close(id);
        id = -1;
        return 1;
    }
    return 0;
};

// печать информации о файле
void SystemFile::about()
{
    printf("user: %s\n", result->pw_name);
    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case S_IFLNK:
        printf("symlink\n");
        break;
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
    }

    // Для получения той же информации можно воспользоваться макросами:
    // S_ISREG(m) -обычный файл?, S_ISDIR(m) -  каталог? и др.

    printf("I-node number:  %ld\n", (long)sb.st_ino);

    printf("Mode:           %lo (octal)\n", (unsigned long)sb.st_mode);

    printf("Link count:    %ld\n", (long)sb.st_nlink);
    printf("Ownership:  UID=%ld   GID=%ld\n", (long)sb.st_uid, (long)sb.st_gid);
    printf("File size:  %lld bytes\n", (long long)sb.st_size);
    printf("Last status change:  %s", ctime(&sb.st_ctime));
    printf("Last file access: %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));
};

// получить имя владельца
string SystemFile::getUser()
{
    //printf("%s\n", result -> pw_passwd);
    string res = result->pw_name;
    return res;
};

// атрибуты на права доступа
mode_t SystemFile::getMode()
{
    // cout << sb.st_mode;
    return sb.st_mode;
};

// получить размер файла
long SystemFile::getSize()
{
    // полный размер в байтах
    return sb.st_size;
};

// прочитать из файла
bool SystemFile::readf(char* name, long ll)
{
    char buffer[10000];
    int fh;
    unsigned int nbytes = ll, bytesread;

    if ((fh = open(name, O_RDONLY)) == -1) {
        perror("open failed on input file");
        exit(1);
    }

    if ((bytesread = read(fh, buffer, nbytes)) == -1) {
        perror("");
        return 0;
    }
    else {
        printf("Read %u bytes", bytesread);
        return 1;
    }
};

// количество записей
long SystemFile::numbersOfRecord(char* FNAME, long num)
{
    FILE* f = fopen(FNAME, "rb");

    long len;
    // переместить внутренний указатель в конец файла
    fseek(f, 0, SEEK_END);

    // вернуть текущее положение внутреннего указателя
    len = ftell(f);
    fclose(f);

    long n, m;
    m = sizeof(num);
    n = (len - sizeof(num)) / m;
    // printf("\n%ld\n", n);
    return n;
};

// копировать файл откуда - куда
void SystemFile::copy(char* source_eee, char* dest_ttt)
{
    int dest; // дескриптор
    unsigned char er;
    // Связывание дескриптора id с именем файла
    dest = open(dest_ttt, O_WRONLY | O_CREAT, 0775);
    er = errno;
    //Проверка открылся ли файл
    if (errno) {
        if (errno == EEXIST) {
            dest = open(dest_ttt, O_TRUNC | O_WRONLY);
            er = 0;
        }
        else {
            perror("");
            exit(1);
        }
    }

    int source = open(source_eee, O_RDONLY, 0);

    struct stat stat_source;
    fstat(source, &stat_source);

    // используем системный вызов sendfile
    //ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count)
    sendfile(dest, source, 0, stat_source.st_size);

    close(source);
    close(dest);
};

// функция для удаления файла
void SystemFile::deletef(char* f1)
{
  /*
  int truncate(const char *path, off_t length);
  int ftruncate(int fd, off_t length);
  */

  FILE * fp = fopen(f1, "r");
  truncate(f1, 0);

  fclose(fp);
};
