#include <iostream>
#include <array>
#include <functional>


class A {
public:
	void change_element_array_by_index(size_t index, int value) { array[index] = value; }
	int get_element_array_by_index(size_t index) const { return array[index]; }
private:
	int array[1000]{};
};


void call_function_use_function(std::function<long long(int, int)> f) { 
	f(300, 100);
}


template <typename T>
void call_function_use_function_(T f) {  // better
	f(300, 100);
}


void* operator new(size_t byt) {
	std::cout << "alloc\n";
	return malloc(byt);
}


int main(int argc, const char* argv[]) {

	A a;

	size_t index{};

	auto l_new = [a, &index](int a_, int b_) mutable {
		long long res = a_ + b_;
		a.change_element_array_by_index(index++, res);
		return res;
	};

	call_function_use_function(l_new); // так как есть std::function, то произошло выделение памяти из-за передоваемого объекта лямбда(функтора)
									   // (изза большого объёма данных)

	call_function_use_function_(l_new); // нет аллокаиции памяти


	system("pause");
	return 0;
}