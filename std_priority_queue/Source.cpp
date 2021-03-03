#include <iostream>
#include <queue>


int main(int argc, const char* argv) {

	std::priority_queue<int> q;

	q.push(2);
	q.push(1);
	q.push(100);
	q.push(6);
	q.push(5);

	std::cout << q.top() << std::endl;

	q.pop();

	std::cout << q.top() << std::endl;


	system("pause");
	return 0;
}