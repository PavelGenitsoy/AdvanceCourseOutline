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
// Test::Test(const char*) -> Test::Test(const std::string&); // �������� ������� � �++17 , �� ������-�� � ���� �� ��������������


int main(int argc, const char *argv[]) {
	
	Test t{ "const char" };
	std::vector v{1,2,3};  // � �++17 ����� ���� �� ��������� <int>

	return 0;
}