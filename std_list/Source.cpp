#include <iostream>
#include <vector>
#include <list>


class Debug {
public:
	Debug() { std::cout << __FUNCSIG__ << std::endl; };
	Debug(int valu1, double value2) { std::cout << __FUNCSIG__ << std::endl; }
	explicit Debug(int value) : value_{value} { std::cout << __FUNCSIG__ << std::endl; }
	~Debug() { std::cout << __FUNCSIG__ << std::endl; }
	Debug(const Debug&) { std::cout << __FUNCSIG__ << std::endl; }
	Debug(Debug&&)noexcept { std::cout << __FUNCSIG__ << std::endl; }
	Debug& operator=(const Debug&) { return *this; }
	Debug& operator=(Debug&&) { return *this; }
	int value() const {
		return value_;
	}
private:
	int value_;
};


bool operator < (const Debug& d1, const Debug& d2) {
	return d1.value() < d2.value();
}

bool operator == (const Debug& d1, const Debug& d2) {
	return d1.value() == d2.value();
}


int main(int argc, const char* argv) {

	std::list<Debug> l;
	l.emplace_back(1);
	l.emplace_back(10);
	l.emplace_back(2);
	l.emplace_back(10);

	std::list<Debug> l1;
	l1.emplace_back(7);
	l1.emplace_back(5);
	l1.emplace_back(7);

	for (const auto& var : l) {
		std::cout << var.value() << std::endl;
	}

	std::cout << "///////////////////////\n";
	l.sort();

	for (const auto& var : l) {
		std::cout << var.value() << std::endl;
	}

	std::cout << "///////////////////////\n";
	l.unique(); // удаляет дублирующиеся элементы в списке которые находятся рядом!
	l1.unique();

	for (const auto& var : l) {
		std::cout << var.value() << std::endl;
	}

	std::cout << "///////////////////////\n";
	for (const auto& var : l1) {
		std::cout << var.value() << std::endl;
	}

	std::cout << "///////////////////////\n";
	l1.sort();
	l.merge(l1); // мерджим 2 (заранее отсортированных так принято в основном) списка. В результирующем списке мердж тоже делает некую досортировку

	for (const auto& var : l) {
		std::cout << var.value() << std::endl;
	}

	std::cout << "///////////////////////\n";
	std::list<Debug> l2;
	l2.emplace_back(0);
	l2.emplace_back(8);
	l2.emplace_back(5);

	// l.splice(l.begin(), l2); // в список l в начало ставит список l2

	auto it{ std::next(l2.begin(), 2) }; // вместо сдвига итератора в виде (2 раз ++it), ибо арифметика как с указателями здесь не совсем работает
	// l.splice(l.begin(), l2, l2.begin(), it); // вставили 2 первых элемента из l2 в начало l

	l.splice(std::next(l.begin(), 2), l2, l2.begin(), it); // вставили 2 элемента из l2 в l после второго элемента

	for (const auto& var : l) {
		std::cout << var.value() << std::endl;
	}
	return 0;
}