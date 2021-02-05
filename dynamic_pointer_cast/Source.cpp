#include <iostream>
#include <memory>


class Base {
public: 
	virtual ~Base() { std::cout << __FUNCSIG__ << std::endl; }  
}; // virtual ����� ������ ���� � ���� ���������� shared_ptr (�������� ����� ������ std::shared_ptr<Base> ptr{ std::make_shared<Derived>() }) 
   // ��� ��� �������� ���������� �������


class Derived : public Base {
public:
	~Derived () { std::cout << __FUNCSIG__ << std::endl; }
};


int main(int args, const char* argv[]) {

	std::shared_ptr<Base> ptr{ std::make_shared<Derived>() }; // ������� ��������� �� ������� �����, ���� �� ����� ��������� �� �����������, ��� �� ����
															  
	// � � ������� �� ����� ������� down_cast . �� Base �������� Derived

	// std::shared_ptr<Base> ptr1{ dynamic_cast<Derived*>(ptr.get()) }; // core dumped error   (��������� ����� double free)
	/*
		(ptr.get()) ��� �� ���� ��������� � ptr, �.�. ��� ������, ��� ��� ����. � ��� �� ����������� ������ ptr!! �� ���� ������ 
		������ shared_ptr � ���� ���������� ���� ������

		�� ����� ���� ref counter �� ����������, ��� �� ptr1 ��������� ��� ��������� (ptr) ������� ��������� � shared_ptr.

		� ��� �� ����� ���������� 2 shared_ptr �� ����� ��������� ������, � � ��� ��������: ��� ��� shared_ptr ���������� �� ���� � ��� 
		�� ������, �� � ������� ���� control block
	*/

	std::shared_ptr<Base> ptr1{ std::dynamic_pointer_cast<Derived>(ptr) }; // ������� ��������!!



	system("pause");
	return 0;
}