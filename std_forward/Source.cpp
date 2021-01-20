#include <iostream>


void test1(int& data) {
	std::cout << __FUNCSIG__ << std::endl;
}

void test1(int&& data) {
	std::cout << __FUNCSIG__ << std::endl;
}

template <typename T>
void test(T&& data) {
	std::cout << __FUNCSIG__ << std::endl;
	test1(std::forward<T>(data));  // forward говорит, что в зависимости какой пришёл Т, я буду вызывать правильную перегрузку метода test1
}


int main(int argc, const char *argv[]) {
	int a;

	test(10);
	test(a);
	test(std::move(a));

	system("pause");
	return 0;
}