#include <iostream>
#include <vector>


int main(int argc, const char* argv) {

	std::vector<int> v{ 1,2,3 };  // и например мы знаем позицию числа 2, и мы хотим удалить это число
	

	auto it = v.begin() + 1;
	//v.erase(it); // сложность будет O(n), ибо удалим элемент и остальные элементы надо сдвинуть.  НО можно схитрить и сделать swap, если порядок не важен

	*it = std::move(v.back());  // меняем местами с последним элементом
	v.pop_back(); // O(1)



	return 0;
}