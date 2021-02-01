#include <iostream>
#include <array>
#include <functional>


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

typedef void(Test::*Func) (int);
int main(int argc, const char* argv[]) {

	Func f = &Test::callback; // f являектся указателем на метод . Но как же обратится к методу?

	Test t;

	(t.*f)(10); // ugly способ
	t.print();

	std::invoke(f, t, 20); // good способ, но invoke также делает обвёртку(т.е. под капотом влечёт за собой что-то)
	t.print();

	auto bin_class = std::bind(f, &t, std::placeholders::_1); // better способ.  Метод привязали к объекту
	bin_class(30); // this -> t
	t.print();

	[&t](int value) { // the best способ. добавляет меньше всего генерируемого кода, чем способы выше
		t.callback(value);
	}(40);
	t.print();

	system("pause");
	return 0;
}