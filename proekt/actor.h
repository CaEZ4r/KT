#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//#include <time.h>
#include <errno.h>
#include <string.h>
#include<sys/wait.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

#define PERM 0666
using namespace std;

// Структура для записи и чтения в/из очереди сообщений
struct Mess{
  long type; // тип сообщения в структуре должен быть первым
  int number; // номер участника
  pid_t pid;  //pid процесса, пославшего сообщение
};

// Процесс, он же дейcтвующее лицо для других задач
class Actor{
   Mess mSend, mRead; // сообщения для посылки и чтения
   key_t key;  // ключ для создания очереди сообщений
   int mesid; // дескриптор очереди сообщений
   size_t smsg; // размер посылки
	 int lng,n;
public:
// Конструктор
// Создаем или получаем mesid
    Actor();
// Удалаяем очередь
	~Actor();
// что-то делаем
      void act(int);
};

