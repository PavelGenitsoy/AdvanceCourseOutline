#include <iostream>


class Test {
public:
	constexpr Test() = default;

	constexpr int getCompileTimeValue() {
		return 10;
	}
	int getRuntimeValue() {
		return 10;
	}

};

int main(int argc, char const *argv[]) {

	Test t; // объект создался в compile time (в данном случае)

	constexpr int data = t.getCompileTimeValue();
	// constexpr int data_ = t.getRuntimeValue();  // ошибка компиляции, ибо data_ должна быть инициализирована как константное выражение 
	
	// t.getRuntimeValue();  // при таком виде вызова ф-ции, объект t мог быть создан и в runtime 

	auto test = t.getRuntimeValue();


	return 0;
}