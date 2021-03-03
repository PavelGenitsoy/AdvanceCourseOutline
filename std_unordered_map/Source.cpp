#include <iostream>
#include <unordered_map>



int main(int argc, const char* argv) {

	std::unordered_map<int, int> cnt{
		{12, 4}, {5, 6}, {8,5}, {3, 11}, {2, 23}, {10, 3}, {7, 7}
	};


	cnt.max_load_factor(0.7);

	std::cout << cnt.size() << std::endl;
	std::cout << cnt.bucket_count() << std::endl;  // колическтво бакетов (эти ячейки мапятся на хеш значения)
	std::cout << cnt.load_factor() << std::endl;   // насколько загружены бакеты
	std::cout << cnt.max_load_factor() << std::endl; // если дойдём до макс, то будет перехэширование

	cnt.insert({ 15,1 }); // перехэширование будет
	cnt.insert({ 14,13 });


	for (size_t i = 0; i < cnt.bucket_count(); i++) {
		std::cout << "b[" << i << "]:";
		for (auto pos{ cnt.begin(i) }; pos != cnt.end(); ++pos) {
			std::cout << pos->second << " ";
		}
		std::cout << "\n";
	}


	std::cout << "///////////////////////////////////\n";

	cnt.erase(15);  // не приведёт к перехэшированию
	cnt.erase(14);

	

	for (size_t i = 0; i < cnt.bucket_count(); i++) {
		std::cout << "b[" << i << "]:";
		for (auto pos{ cnt.begin(i) }; pos != cnt.end(); ++pos) {
			std::cout << pos->second << " ";
		}
		std::cout << "\n";
	}


	system("pause");
	return 0;
}