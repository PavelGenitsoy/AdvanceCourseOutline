#include <iostream>


/*
fold expression использует такие операции:
	unary  -  подразумевает, что есть какае-то операция   op ...args
	binary  -  подразумевает, что есть какой-то   init ...  и есть какае-то операция  op ...args   (args может находится как в начале так и в конце) 
*/


template <typename ...Args>
void Log(Args ...args) {
	(std::cout << ... << args) << '\n';  // все параметры(args) в 1 строчку вывели.    
}										 //  unary	

template <typename ...Args>
auto Sum(Args ...args) {
	return (args + ... + 10);   //  binary
}

int main(int argc, const char* argv[]) {
	Log(1, "Hello", 10.45);
	
	Log(1, ", ", "Hello", ", ", 10.45);

	std::cout << Sum(1, 2, 3) << std::endl;

	system("pause");
	return 0;
}