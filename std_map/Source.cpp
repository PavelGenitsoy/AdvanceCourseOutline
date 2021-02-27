#include <iostream>
#include <map>


class Debug {
public:
	Debug() { std::cout << __FUNCSIG__ << std::endl; };
	Debug(int valu1, double value2) { std::cout << __FUNCSIG__ << std::endl; }
	explicit Debug(int value) : value_{ value } { std::cout << __FUNCSIG__ << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug&) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&& rhs)noexcept { // делали перегрузку для insert_or_assign
		value_ = rhs.value_;
		std::cout << __FUNCSIG__ << std::endl; 
	}
	Debug& operator=(const Debug&) { return *this; }
	Debug& operator=(Debug&& rhs) { // делали перегрузку для insert_or_assign
		value_ = rhs.value_;
		return *this; 
	}

	int value() const {
		return value_;
	}

	void set_value(int new_value) {
		value_ = new_value;
	}
private:
	int value_;
};


bool operator < (const Debug& lhs, const Debug& rhs) {
	return lhs.value() < rhs.value();
}


int main(int argc, const char* argv) {

	std::map<int, Debug> m;  // если ключ представляет собой какой-то пользовательский тип, то нужно перегружать компоратор и по сути вручную добавлять
	
	m.emplace(1, 10);  // добавляем ключ, и значение
	m.emplace(12, 5);
	m.emplace(3, 20);

	for (const auto& var : m) {
		std::cout << "key: " << var.first << " " << "value: " << var.second.value() << std::endl;
	}

	std::cout << "//////////////////////////////\n";

	if (auto it{ m.find(3) }; it != m.end()) {  // в find передаём ключ
		it->second.set_value(100); // теперь мы можем спокойно модифицировать value ибо оно не есть константой, оно не являеться частью упорядочивания дерева
								   // это преимущество мапы над сэтами. А если хотим менять ключ, то делаем как в set
	}

	m.insert_or_assign(12, Debug{ 15 }); // данный метод позволяет вставлять ноду, если ключ уникальный, либо если ключ повторяется, то переназначает его значение
	m.insert_or_assign(13, Debug{ 15 });

	for (const auto& var : m) {
		std::cout << "key: " << var.first << " " << "value: " << var.second.value() << std::endl;
	}

	return 0;
}