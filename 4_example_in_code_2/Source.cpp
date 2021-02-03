#include <iostream>
#include <memory>


class Callback {
public:
	auto createCallback() { // async (способ асинхронных вызовов)
		return [this](int new_data) { // через лямбда создали неименованный метод, который через список захвата принимает this
			data = new_data; // (когда this не передавали)ошибка (рассматривали раньше в лямбда). Мы внутри лямбда обращаемся к приватному 
		};					 // полю класса (а доступа не имеем)
	}
	auto createCallback_upd() {
		std::shared_ptr<Callback> sv{ this };
		std::weak_ptr<Callback> weak_{ sv };

		return [weak_](int new_data) {
			if (auto sv = weak_.lock()) {
				sv->change(new_data);
			}
		};
	}

	void change(int new_data) {
		data = new_data;
	}
private:
	int data{};
};



class Callback_upd  : public std::enable_shared_from_this<Callback_upd>{
public:
	auto createCallback() {
		// shared_from_this()
		auto weak = weak_from_this();
		return [weak](int new_data) {
			if (auto sh = weak.lock()) {
				sh->change(new_data);
			}
		};
	}

	void change(int new_data) {
		data = new_data;
	}
private:
	int data{};
};



auto getCallback() {
	Callback cl;
	return cl.createCallback_upd();
}


auto getCallback_upd2() {
	std::shared_ptr<Callback_upd> cl;
	return cl->createCallback();
}


int main(int args, const char* argv) {

	Callback cl;

	auto lmb_callback = cl.createCallback();
	lmb_callback(10); // вроде всё найс, но есть 1 проблема

	{
		// ПРОБЛЕМА:
		Callback cl_;

		auto lmb_callback_ = cl_.createCallback();
	}
	// lmb_callback_(100); // UB.  при вызове этой лямбды, я обращаюсь к полю data объекта this которого уже не существует. 
	
	/*
		Как пофиксить эту проблему?

		1) вариант: изменить синтаксис метода createCallback как в createCallback_upd. НО по итогу это нам снова не поможет, и будет 
		UB. Потому что мы будем в любом случае обращатся в weak, а он будет обращатся к shared_ptr, который заэкспарен(expired) ибо сам
		shared_ptr будет разрушатся когда закончится выполнятся метод createCallback_upd.

		2) вариант: создавать класс, который является наследником от std::enable_shared_from_this  
		по сути правильно, но не работает...
	*/

	//auto lmb_callback_upd = getCallback();
	//lmb_callback_upd(20);   //  UB

	//auto lmb_callback_upd_2 = getCallback_upd2();
	//lmb_callback_upd_2(50); // тоже ошибка, но логика правильная




	system("pause");
	return 0;
}