#include <iostream>
#include <string>
#include <type_traits>


/*
	to_string1(class A) , то будет вызыватся соответствующая другая перегрузка enable_if у которой нету type
	и соответственно при попытки вызвать type, то компилятор не ругнётся, а уберёт эту вещь std::string в (std::string to_string1(А data))
	т.е. просто не будет возвращаемого значения. Компилятор пока ошибку не будет выдавать, а просто считает, что просто не сработало 
	инстанцирование этой ф-ции, и он пошёл искать дальше лучшего кандидата
*/

template <typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type to_string1(T data) { // to_string1(int) -> std::string to_string1(int)
	return std::to_string(data);
}

template <typename T>
typename std::enable_if<std::is_pointer<T>::value, std::string>::type to_string1(T data) {
	return std::string(data);
}

/*
// это альтернатива такая

template <typename T, typename Ret = typename std::enable_if<std::is_pointer<T>::value, std::string>::type>
std::string to_string1(T data) {
	// static_assert(not std::is_same<T, const char*>::value, "const char*!!!!");
	return std::string(data);
}
*/


/*
	Но всё же как можно упростить сам вид и записать проще и компактнее? Можно всё записать в 1 ф-ции!
*/


/*
template <typename T>
std::string to_string2(T data) {   
	if (std::is_integral<T>::value) {   // if это runtime оператор, а это выражение (std::is_integral<T>::value) compile time
		return std::to_string(data);	// надо сделать так чтобы если например первая ветка сработала, то остальные ветки компилятор не брал во внимание
	}
	else if (std::is_same<T, const char*>::value) {
		return std::string(data);
	}
	return data;  //  data == std::string      (объект std::string )
}
*/

template <typename T>
std::string to_string(T data) {
	if constexpr (std::is_integral<T>::value) {    // теперь мы говорим что эти if есть compile time, т.е. будет выбран 
		return std::to_string(data);			  // один из них на уровне компиляции, а другие ветки не будут рассматриваться
	}
	else if constexpr (std::is_same<T, const char*>::value) {
		return std::string(data);
	}
	else if constexpr (std::is_same<T, std::string>::value) {
		return data;
	}
}

int main(int argc, const char *argv[]) {

	to_string1("Hello World");

	// auto str{ to_string2(10) };  // error

	auto str{ to_string(10) };


	system("pause");
	return 0;
}