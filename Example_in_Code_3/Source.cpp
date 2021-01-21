#include <iostream>


template <typename T>
void Log(T value) {	
	std::cout << "Value is " << value << std::endl;
	std::cout << "End" << std::endl;
}

template <typename T, typename ...Args>  
void Log(T head, Args ...args) {  // ...args - (сами точки) говорит как pack values (упаковка типов).  можем передавать n - количество параметров причём разного типа
	std::cout << "Cont args " << sizeof...(args) << std::endl;
	std::cout << "Value is " << head << std::endl;
	Log(args...); // args... - (сами точки) говорит как unpack values (распаковка типов)
				  // Log(args...) - это как рекурсивное инстанцирование Log	
				  // всё выражение это compile time инстацирование, которое говорит, что я просто генерирую просто набор каких-то ф-ций
}

int main(int argc, const char *argv[]) {
	Log(1, "Hello", 10.45);  // в compile time просто генерируем 

	system("pause");
	return 0;
}