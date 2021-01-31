#include <iostream>
#include <array>


template <typename T, typename T1>
T find_(T begin, T const end, T1 func) {
	while (begin != end + 1)
	{
		if (func(*begin)) {
			return begin;
		}
		++begin;
	}
	return end;
}


auto make_lambda() {  // вовзращаемое значение это лямбда
	int a{ 10 };
	return [&a](int value) { return a + value; };
}



int main(int argc, const char* argv[]) {

	std::array arr{ 3, 2, 7, 4 };

	int div{ 3 };

	auto it = find_(&arr[0], &arr[arr.size() - 1], [div](int value) {   // лямбда это сахар вокруг функтора. захват по значению
																		// div это то, что мы захватили до момента создания лямбда
																		// value этот аргумент будет передоватся, когда эту лямбду будем вызывать
		std::cout << "Value = " << value << std::endl;
		return value % div == 0;
	});

	std::cout << "//////////////////////\n";

	auto lmb = [div](int value) {	//  первый контекст, как лямбда можно использовать
		std::cout << "Value = " << value << std::endl;
		return value % div == 0;
	};
	lmb(10);

	[div](int value) {				//  второй контекст
		std::cout << "Value = " << value << std::endl;
		return value % div == 0;
	}(15);

	std::cout << "//////////////////////\n";

	std::cout << "div = " << div << std::endl; // output : div = 3
	[&div](int value) {				//  такой способ захвата лучше избегать
		std::cout << "Value = " << value << std::endl;
		div = 10;
		return value % div == 0;
	}(20);
	std::cout << "div = " << div << std::endl; // output : div = 10

	std::cout << "//////////////////////\n";

	// один из способов зачем не использовать захват по ссылке
	auto lmb_ = make_lambda();
	// lmb_(100);  // получим UB, ибо в make_lambda захватываем локальную копию объекта 'а', а соответственно, в момент создания 
				// лямбды мы захватили по ссылке аргумент, который будет выделен на стеке, а значит по завершению ф-ции make_lambda
				// этот ('а') аргумент будет уже not valid



	system("pause");
	return 0;
}