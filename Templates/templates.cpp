#include <iostream>
#include <vector>


template <typename T>
class Test {
public:
	Test(T t) : data{t} {}
private:
	T data;
};

// deduction guide
// Test::Test(const char*) -> Test::Test(const std::string&); // работает начиная с С++17 , но почему-то у меня не поддерживается


int main(int argc, const char *argv[]) {
	
	Test t{ "const char" };
	std::vector v{1,2,3};  // в С++17 можно явно не указывать <int>

	return 0;
}