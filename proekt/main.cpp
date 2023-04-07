#include "actor.h"

int main(int argc, char **argv){
  int t;
  time_t start, current;
  time(&start);
  if (argc == 1)
  	printf("arg: %s\n", argv[0]);
// параметр - время работы (ожидания) 
// Внимание!! При использовании этого же файла для
// запуска в теле дочернего процесса с парамерами,
// нужно использовать argv[0]
  t = atoi(argv[0]);
  cout << t << endl;
// создаем объект
  Actor a;
// действие   
  a.act(t);
// деструктор отработает когда main завершает работу   
  return 0;
}
