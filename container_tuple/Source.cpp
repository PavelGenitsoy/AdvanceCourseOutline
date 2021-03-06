#include <iostream>
#include <tuple>



int main(int argc, const char* argv[]) {

	//std::tuple<int, double, char> t {1, 1.f, 'c'};
	auto t = std::make_tuple(1, 1.111f, 'c');


	std::cout << std::get<2>(t) << std::endl; 


	// int a1;
	double a2;
	char a3;

	std::tie(std::ignore, a2, a3) = t; // tuple разбили.  Так делали до С++11, после стали юзать struct binding

	std::cout << a2 << std::endl;


	auto[b1, b2, b3] = t; // struct binding .  Раскручиваем и получаем значения
	std::cout << b1 << std::endl;




	system("pause");
	return 0;
}