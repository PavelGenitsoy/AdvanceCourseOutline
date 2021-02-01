#include <iostream>
#include <array>


class Test {
public:
	auto callback(int value) {
		sensetive_data = value;
	}
	void print() const {
		std::cout << sensetive_data << std::endl;
	}
private:
	int sensetive_data{};
};


int main(int argc, const char* argv[]) {

	Test t;
	t.callback(100);
	t.print();

	auto lmb = [t](int value) { // все объекты которые захватываются, внутри лямбда являються const
		// t.callback(value);		// error
		t.print();				// good 
	};

	auto lmb_ = [t](int value) mutable { // чтобы снять констатность с объекта дописываем mutable. Но в этом смысла нет
		t.callback(value);		// good
		t.print();				// good 
	};

	lmb_(10);  // внутри лямбда изменили sensetive_data, мы изменили это для временного объекта в лямбда
	t.print(); // но на оригинлаьный объект не повлияло


	system("pause");
	return 0;
}