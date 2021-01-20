#include <iostream>


class Test {
public:
	constexpr Test() = default;

	constexpr int getCompileTimeValue() {
		return 10;
	}
	int getRuntimeValue() {
		return 10;
	}

};

int main(int argc, char const *argv[]) {

	Test t; // ������ �������� � compile time (� ������ ������)

	constexpr int data = t.getCompileTimeValue();
	// constexpr int data_ = t.getRuntimeValue();  // ������ ����������, ��� data_ ������ ���� ���������������� ��� ����������� ��������� 
	
	// t.getRuntimeValue();  // ��� ����� ���� ������ �-���, ������ t ��� ���� ������ � � runtime 

	auto test = t.getRuntimeValue();


	return 0;
}