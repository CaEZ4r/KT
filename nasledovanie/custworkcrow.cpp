#include <iostream>
#include <cstdlib>

using namespace std;

class Person{
public:
	int apple;
	static void print();
	static int basket;
};

int Person::basket=0;

void Person::print(){
	cout << basket << endl;
	cout << endl;
}

class Worker:public Person{
public:
	Worker();
	~Worker();
	void job();
};

Worker::Worker(){
	apple = rand() % 100;
	cout << "Worker: " << apple << endl;
}

Worker::~Worker(){
	cout << "Worker out\n";
}

void Worker::job(){
	basket+=apple;
	cout << "Worker put " << apple << " apples\n";
}

class Crow:public Person {
public:
	Crow();
	~Crow();
	void theft();
};

Crow::Crow() {
	apple = rand() % 70;
	cout << "Crow: " << apple << endl;
}

Crow::~Crow() {
	cout << "Crow flew\n";
}

void Crow::theft() {
	basket-=apple;
	cout << "Crow stole " << apple << " apples\n"; 
}

class Customer:public Person {
public:
	Customer();
	~Customer();
	void buy();
};

Customer::Customer(){
	apple = rand() % 10;
	cout << "Customer: " << apple << endl;
}

Customer::~Customer(){
	cout << "Customer out\n";
}

void Customer::buy(){
	cout << "Customer bought " << apple << " apples\n";
	if(basket>apple)
		basket-=apple;
	else
		basket=0;
}

int main(){
	Worker w[5];
	Crow cr[3];
	Customer c[5];
	for (int i =0; i < 8; i ++){
		cout << i+1 << " hour\n";
		for (int j =0; j < 5; j++){
			w[j].job();
			cr[j % 3].theft();
			c[j].buy();
			Person::print();
		}
	}

}
