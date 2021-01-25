#include <iostream>
#include <type_traits>


template <typename T>
class Base {
public: 
	void test() {}
};

/*
template <typename T>
class Derived : Base<T> {
public:				// здесь проблема зависимости контекста.  Есть же компиляция шаблона и потом компиляция при инстанцировании,
	void calc() {	// тут первого рода ошибка. Компилятор не знает, что такое test(), ибо он не знает, что такое Base<T>, а будет
		test();		// знать только тогда, когда явно укажем ему этот тип
	}			  
};				  
*/

template <typename T>
class Derived : Base<T> {
public:
	void calc() {
		this->test();		 //  использование явного this
		// Base<T>::test();  //  либо так
	}
};

int main(int argc, const char *argv[]) {

	Derived<int> d;


	system("pause");
	return 0;
}