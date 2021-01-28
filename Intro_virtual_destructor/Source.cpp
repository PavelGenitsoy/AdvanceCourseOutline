#include <iostream>


class advance {
public:
	virtual void test(int i = 10) {
		std::cout << i << std::endl;
	}

	virtual ~advance() {
		std::cout << "advance dstr\n";   // �� ����������� ����������� ������� ��������� ����������������
	}
};

class advance_der : public advance {
public:
	advance_der() { i = new int{ 10 }; }

	void some_code() {
		std::cout << "Hello advance_der" << std::endl;
	}

	~advance_der() { 
		std::cout << "advance_der dstr\n";
		delete i; 
	}

private:
	int* i{nullptr};
};

class advance_der_v2 : public advance {
public:

	void some_code2() {
		std::cout << "Hello advance_der_v2" << std::endl;
	}
};



int main(int argc, const char* argv[]) {

	advance* ad = new advance_der{};

	ad->test();

	// delete ad; // ���������� ������ (����� � ������� ������ �� �������� ���������� virtual)

	delete ad;  // ���������� ����� �������� ���������� ������������ ������, ������� ����� ������� ���������� �������� ������


	system("pause");
	return 0;
}