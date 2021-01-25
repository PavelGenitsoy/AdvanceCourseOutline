#include <iostream>


class A {

};

/*
class B {

};
*/

class B {
public:
	B(A a) {}

};

int main(int argc, const char *argv[]) {
	
	int a{ 10 };
	float b{ 10.1f };
	a = static_cast<int>(b);

	/*
	int* a;
	float* b;
	a = static_cast<int*>(b);  // указатели нельзя кастить, очевидно
	*/

	A c;
	// B d{static_cast<B>(c)}; // нельзя пользовательский тип одного вида в пользовательский другого  (в случае класса В, что закоменчен)
	
	B d{ static_cast<B>(c) };  // в этом случае сработает конструктор


	system("pause");
	return 0;
}