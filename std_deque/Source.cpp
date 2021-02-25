#include <iostream>
#include <deque>

/*
	API дэки такой же как у вектора за исключением capacity и с дополнением работы в начале.
*/

int main(int argc, const char* argv) {

	std::deque<int> d{ 1,2,3 };

	for (int i = 0; i < d.size(); ++i)
	{
		std::cout << d[i] << " ";
	}

	system("pause");
	return 0;
}