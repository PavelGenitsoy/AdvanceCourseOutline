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
	advance_der* der = static_cast<advance_der*>(ad);  // unsafe

	der->some_code();
}

void inter1(advance* ad) {
	advance_der* der = dynamic_cast<advance_der*>(ad);  // safe.   не только кастит, но компилятор ещё как-бы смотрит куда объект указывает
														// если на advance_der, то объект валидный
	if (der != nullptr) {
		der->some_code();
		return;
	}

	advance_der_v2* der2 = dynamic_cast<advance_der_v2*>(ad); // RTTI
	der2->some_code2();
}

int main(int argc, const char* argv[]) {

	inter(new advance_der{});		//  так всё хорошо
	// inter(new advance_der_v2{}); //  тут будет UB

	/*
		Поэтому static_cast в данном контексте (от базового к производному классу) является не безопасным преобразованием.

		Чтобы обезопасить, то используем dynamic_cast - это преобразование на уровне runtime, т.е. компилятор не просто говорит, что
		это (advance_der* der = dynamic_cast<advance_der*>(ad)) преобразование возможно, а ещё и говорит, что это преобразование будет
		проверятся на уровне выполнения
	*/

	inter1(new advance_der_v2{});

	system("pause");
	return 0;
}