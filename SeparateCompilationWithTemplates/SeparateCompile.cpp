#include <iostream>
#include "Header.h"


template <typename T>
void test(T data) {

}

template <typename T>
void test1(T&& data) {  // эта T&& сущность(как хамелеон.  Ещё в ДАННОМ КОНТЕКСТЕ это универсальная ссылка) будет распозноваться как rvalue или lvalue 
	std::cout << __FUNCSIG__ << std::endl;
}

int main(int argc, const char *argv[]) {
	Test  t{ 100 };
	int a;

	// test(10);  // чтобы тест выводился по значению, то передаю 10.      Т --> int
	test1(10); // T --> int&&

	// test<int&>(a);  // чтобы тест выводился как lvalue, то явно скажу такой-то тип и передаю а.    T --> int&
				    // но так неудобно, поэтому исправим немного сигнатуру ф-ции тест
	test1(a);  // так выйдет удобнее

	test(std::move(a));  // чтобы тест выводился как rvalue, то сделаем move, т.е. закастим элемент а.     T --> int&&
	test1(std::move(a));

	system("pause");
	return 0;
}