#include <iostream>
#include <set>


class Debug {
public:
	Debug() { std::cout << __FUNCSIG__ << std::endl; };
	Debug(int valu1, double value2) { std::cout << __FUNCSIG__ << std::endl; }
	explicit Debug(int value) : value_{ value } { std::cout << __FUNCSIG__ << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug&) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&&)noexcept { std::cout << __FUNCSIG__ << std::endl; }
	Debug& operator=(const Debug&) { return *this; }
	Debug& operator=(Debug&&) { return *this; }

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

	std::set<Debug> s;  // если компоратор по умолчанию (<) нас не устраивает, то можем явно его переопределить. В set каждая нода не повторяющаясь
	
	// auto comp{ [](const Debug& lhs, const Debug& rhs) {return lhs.value() > rhs.value(); } };
	// std::set<Debug, decltype(comp)> s{comp};

	s.emplace(10);
	s.emplace(2);
	s.emplace(11);
	s.emplace(5);

	if (auto[it, status] = s.emplace(2); !status) { // emplace возвращает 2 значения, поэтому можно так проверять находится ли такая же нода в дереве уже
		std::cout << "error\n";
	}

	if (auto[it, status] = s.emplace(20); !status) { 
		s.emplace_hint(it, 21); // вставка с подсказкой, это мы подсказываем куда можно сразу вставить, чтобы не было проверки с каждым значением в нодах
								// т.е. в данном случае мы добавили 20, и говорим что 21 можно добавить сразу после 20. Если же эта вставка даст fail, то
								// просто будет начата проверка с корня
	}

	for (const auto& var : s) {
		std::cout << var.value() << " ";
	}
	std::cout << std::endl;


	if (auto it{ s.find(Debug{2}) }; it != s.end()) { // если нашло, то вовзращает искомую ноду, если нет, то упрётся в конец дерева
		std::cout << "find\n";

		/*
		s.erase(it);
		s.emplace(100);

		// раньше таким способом изменяли значение ноды, но он плох. Происходит перебалансировка дерева когда удаляем ноду, а потом снова происходит
		// перебалансирвока когда добавляем.
		*/

		auto node{ s.extract(it) };  // c++17.   Получили ноду
		node.value().set_value(100);  // устанавливаем значение
		s.insert(std::move(node)); // вставляем эту ноду
	}

	for (const auto& var : s) {
		std::cout << var.value() << " ";
	}
	std::cout << std::endl;


	auto it{ s.lower_bound(Debug{12}) }; // возвращает указатель на ноду где значение не ниже 12, т.е. output: 20

	std::cout << it->value() << std::endl;



	return 0;
}