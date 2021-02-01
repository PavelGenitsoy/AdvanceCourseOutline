#include <iostream>
#include <array>


class Test {
public:
	auto callback(int value) {
		sensetive_data = value;
	}
	void print() const {
		std::cout << sensetive_data << std::endl;
	}
private:
	int sensetive_data{};
};


int main(int argc, const char* argv[]) {

	Test t;
	t.callback(100);
	t.print();

	auto lmb = [t](int value) { // ��� ������� ������� �������������, ������ ������ ��������� const
		// t.callback(value);		// error
		t.print();				// good 
	};

	auto lmb_ = [t](int value) mutable { // ����� ����� ������������ � ������� ���������� mutable. �� � ���� ������ ���
		t.callback(value);		// good
		t.print();				// good 
	};

	lmb_(10);  // ������ ������ �������� sensetive_data, �� �������� ��� ��� ���������� ������� � ������
	t.print(); // �� �� ������������ ������ �� ��������


	system("pause");
	return 0;
}