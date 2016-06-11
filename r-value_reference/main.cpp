#include <iostream>
using namespace std;

int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;

struct A{
	A(){
		cout << "construct: " << ++g_constructCount << endl;
	}
	
	A(A const& a){
		cout << "copy construct: " << ++g_copyConstructCount << endl;
	}
	
	~A(){
		cout << "destruct: " << ++g_destructCount << endl;
	}
};

A GetA(){
	return A();
}

void PrintValue(int& i){
	cout << "lvalue:" << i << endl;
}

void PrintValue(int&& i){
	cout << "rvalue:" << i << endl;
}

void Forward(int&& i){
	PrintValue(i);
}

int main(){
	A && a = GetA();
	int i = 0;
	PrintValue(i);
	PrintValue(1);
	Forward(2);
	return 0;
}
