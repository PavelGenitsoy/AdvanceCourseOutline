#include <iostream>


template <typename T>   //  T - является частью всего класса
class Test {
public:
	template <typename U>
	void test(U&& data) {   // шаблонизируем сам метод. U часть только этого метода и эта U&& сущность получается той же универсальной ссылкой
		std::cout << __FUNCSIG__ << std::endl;
	}
};

int main(int argc, const char *argv[]) {
	Test<int> t;
	int a;

	t.test(a);

	return 0;
}