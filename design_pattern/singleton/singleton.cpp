#include <iostream>
using namespace std;

class Singleton {
public :
	static Singleton* Instance();
	int returnData() { return 5; }
protected :
	Singleton();
private :
	static Singleton* _instance;
};

Singleton::Singleton() {}
Singleton* Singleton::_instance = nullptr;
Singleton* Singleton::Instance() {
	if (_instance == nullptr)
		_instance = new Singleton;
	return _instance;
}

int main(void) {
	Singleton *s = Singleton::Instance();
	cout << s->returnData() << endl;
}