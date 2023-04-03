#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

// Абстрактный класс
class Anybody{
protected:
int apple;
  static int basket;
public:
    Anybody();
    Anybody(int);
    int getApple();
// не виртуальная функция 
    void put();
// виртуальная функция, которая не реализуется в этом классе
 virtual void act() = 0;
};


class Worker:public Anybody{
public:
     Worker(int);
// будет работать как обычная функция
    void put();
// обязательно нужно реализовать
// будет работать как виртуальная
    void act();
};

class Crow:public Anybody{
public:
    Crow(int);
// будет работать как обычная функция
    void put(); 
// обязательно нужно реализовать
// будет работать как виртуальная
    void act(); 
};

int Anybody::basket = 0;


Anybody::Anybody(int a){
   apple = a;
};

int Anybody::getApple(){
    return apple;
};

// просто печатает что в корзине
void Anybody::put(){
   cout<<"basket: "<<basket<<endl;
};

Worker::Worker(int a):Anybody(a){
	
};

// функция в наследнике просто так же называется как и у
// родителя.
void Worker::put(){
    cout<<"Рабочий: я собираю по "<<getApple()<<" яблок"<<endl;
};

// реализация виртуальной функции
void Worker::act(){
    basket += getApple();
};

Crow::Crow(int a):Anybody(a){};


// функция в наследнике просто так же называется как и у
// родителя.
void Crow::put(){
   cout<<"Ворона: я ворую по "<<getApple()<<" яблок"<<endl;
};

// реализация виртуальной функции
void Crow::act(){
   basket += getApple();
   if(basket < 0) basket = 0;
};


int main(){
	ifstream file("test.txt");
	int N;
	file >> N;
	int a;
	int i;
	 Anybody **p;

	for(i = 0; i < N; i ++){
	file >> a;
		if (a > 0){
			*(p+i) = new Worker(a); 
			
		}
		else {
		 	*(p+i) = new Crow(a);
		}
		
	}
   for(int  h = 0; h<4;h++){
     cout<<endl<<h<<" час:"<<endl;
	
// обращаемя к каждому Anybody из массива 
// по-очереди
    for(i = 0; i< N; i++){
    
// что-то делает
     p[i]->act();
// печать
     p[i]->put();
    }
  }
}
