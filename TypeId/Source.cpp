#include <iostream>


class advance {
public:
	virtual void test(int i = 10) {
		std::cout << i << std::endl;
	}
};

class advance_der : public advance {
public:

	void some_code() {
		std::cout << "Hello advance_der" << std::endl;
		this->i = 100;
	}
private:
	int i;
};

class advance_der_v2 : public advance {
public:

	void some_code2() {
		std::cout << "Hello advance_der_v2" << std::endl;
	}
};

void inter(advance* ad) {
	/*advance_der* der = dynamic_cast<advance_der*>(ad);  
														
	if (der != nullptr) {
		der->some_code();
		return;
	}

	advance_der_v2* der2 = dynamic_cast<advance_der_v2*>(ad); 
	der2->some_code2();*/

	std::cout << typeid(*ad).name() << std::endl;
	if (typeid(*ad) == typeid(advance_der)) { // typeid возвращает структуру type_info
		advance_der* der = static_cast<advance_der*>(ad);
		der->some_code();
	}

}

/*
	В начале таблицы vtable хранится строка RTTI. Так мы и получаем доступ к ней
*/

int main(int argc, const char* argv[]) {

	auto der = advance_der_v2{};

	inter(&der);


	system("pause");
	return 0;
}