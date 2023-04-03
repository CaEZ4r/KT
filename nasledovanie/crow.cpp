#include <iostream>
#include <cstdlib>

using namespace std;

class Crow{
	int apple;
public:
	Crow();
	~Crow();
	void act();
	void print();
	static int basket;
};

int Crow::basket = 300;

Crow::Crow(){
	apple = rand() % 100;
	cout << "Crow: " << apple << " app per hour\n";
}

Crow::~Crow(){
	cout << "Crow flew\n";
}

void Crow::print() {
	cout << basket << " in basket\n";
} 

void Crow::act() {
	if (basket > apple)
		basket-=apple;
	else
		basket = 0;
}

int main() {
	Crow cr[6];
	
	for(int i = 0; i < 6; i ++) {
		cr[i].act();
		cr[i].print();
	}	
}
