#include <iostream>
#include <type_traits>

/*
template <typename T1, typename T2>
bool compare1(T1 data1, T2 data2) {
	return data1 == data2;
}

template <typename T1, typename T2>
typename std::enable_if<std::is_floating_point<T1>::value>::type compare1(T1 data1, T2 data2) {
	return std::abs(data1 - data2) > 0.0001;
}

//template <typename T1, typename T2>
//std::enable_if_t<std::is_floating_point<T1>::value> compare1(T1 data1, T2 data2) {  // enable_if_t  более специализированная вещь
//	return std::abs(data1 - data2) > 0.0001;
//}

*/

template <typename T1, typename T2>
bool compare(T1 data1, T2 data2) {
	if constexpr (std::is_floating_point<T1>::value) {
		return std::abs(data1 - data2) > 0.0001;
	}
	else  {
		return data1 == data2;
	}
}

int main(int argc, const char *argv[]) {

	// compare1(10, 10);  // good
	 
	// compare1(10.1, 10.1f);  //  not correct , error

	compare(10.1, 10.1f);


	system("pause");
	return 0;
}