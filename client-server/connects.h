#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>

#include <iostream>
#include <cstdlib>

#define PORTNUM 15000

class Server{
    int ppid; // родительский pid
    int nport; // номер порта
    struct sockaddr_in serv_addr; // ip сервера
    // массив адресов клиентов
    struct sockaddr_in clnt_addr[2];
// для получения IP-адреса по имени хоста
    struct hostent *hp;
//  для сокета "слушать"
    int s;
// для сокетов клиентов
    int ns[2];
    char buf[80], hname[80];
// когда подключились два клиента
// запускаем дочерний процесс для
// обслуживания игры
// далее сервер продолжает слушать
   void new_act();
// проверка правильности хода
//   int check_turn(int x, int y);
public:
//создает порт чтобы слушать подключения
// заполняет информацию serv_addr
   Server(int port_num);
// Destructor
	 ~Server();
// запускает бесконечный цикл приема запросов
   void start();
// останавливает сервер
// для остановки запускается еще один процесс 
// сервера с ключом -stop
// и посылает ему сообщение terminate 
// сервер может получить сообщение terminate 
// также от клиента
   void stop();   
};

class Client{
    struct sockaddr_in serv_addr; // ip сервера
// для получения IP-адреса по имени хоста
    struct hostent *hp;
    char buf[80];    
    int nport;// номер порта
		int s;
public:
// запускает сервер и подключается к хосту
// с адресом addr
   Client(std::string addr, int port);
// сообщает серверу о выходе из игры
// закрывает соединение
   ~Client();
// предоставляет возможность делать ходы
// получает и обрабатывает сообщения от 
// сервера
   void act();
};

