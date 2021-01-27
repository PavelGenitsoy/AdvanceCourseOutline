#include <iostream>


class advance {
public:
	virtual void test(int i = 10) {
		std::cout << i << std::endl;
	}
};


// test можно занести и в private. и спокойно вызывать его через интерфейс базового класса
class advance_der : public advance {
public:
	void test(int i = 20) override {  // дефолтные аргументы не учавствуют в переопределении виртуальной ф-ции
		std::cout << i << std::endl;
	}
};


int main(int argc, const char* argv[]) {

	advance* add{ new advance_der{} };

	add->test();  // ожидали 20, а вывело 10.   Тут 2 этапа компиляции: статическая и динамическая. Статическая: компилятор смотрит
				  // add является типом advance и для него я вызываю метод test(), а этот метод является public. Значит этот (add->test())
				  // вызов валидный. Но потом срабатывает runtime вызов. Когда мы в runtime вызываем этот (test), то сработает vptr, 
				  // который пробежится и вызовет нужную таблицу.

	advance_der{}.test();  // 20. так как напрямую через объект класса


	system("pause");
	return 0;
}