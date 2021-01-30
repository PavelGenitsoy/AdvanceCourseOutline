#include <iostream>
#include <array>


bool is_even(int value) {
	return value % 2 == 0;  // НО что если бы мы хотели передавать не 2, а другое что-то???
}


class Functor {
public:
	Functor(int data) : data{data} {}

	bool operator() (int value) {  //  перегруженный оператор вызова ф-ции
		std::cout << "hello" << std::endl;
		return value % data == 0;
	} 

private:
	int data{};  // собственно это преимущество функторов в отличии от указателя на ф-ции, ибо при создании обьекта мы инициализируем  
};				 // его числом, которое будет отвечать за модуль по какому числу берём


template <typename T, typename T1>
T find_(T begin, T const end, T1 func) {
	while (begin != end + 1)
	{	
		if (func(*begin)) {  //  func здесь это унарный предикат, т.е. принимает 1 аргумент
			return begin;
		}
		++begin;
	}
	return end;
}


int main(int argc, const char* argv[]) {

	// Functor f; 

	// f(10);

	std::array arr{ 1, 5, 1, 4 };

	auto it = find_(&arr[0], &arr[arr.size() - 1], Functor{2}); // передаём объект f, и т.е. когда вызываем find для каждого func будет вызывать 
															    // перегруженный оператор вызова ф-ций

	system("pause");
	return 0;
}