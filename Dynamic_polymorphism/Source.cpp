#include <iostream>


/*
	Само по себе виртуальные ф-ции несут в себе понятия: vptr + vtable
*/


class Test {
public:
	void test() {}
};

// vtable содержит указатели на виртуальные ф-ции именно класса advance
class advance {
public:
	virtual void test() {}
	virtual void test1() {}
	//advance() : ptr{ arr_base } {}  // конструктор инициализирует этот (ptr) указатель на таблицу виртуальных ф-ций своего класса 
private:
	//static PtrToFunc arr_base[];  // PtrToFunc представим, что есть такой тип. arr этот массив инициализируется виртульными ф-циями (test())
									// таблица хранит в себе: advance::test,  advance::test1 
protected:
	//void* ptr;
};

// vtable содержит указатели на виртуальные ф-ции именно производного класса advance_der, если наш производный класс переопределяет 
// (test()) виртуальную ф-цию, иначе содержит указатель на виртуальную ф-цию базового класса 
class advance_der : public advance {
public:
	//advance_der() : ptr{ arr_der } {}
	void test() override {}
private:
	//static PtrToFunc arr_der[]; // таблица хранит в себе: advance_der::test,  advance::test1 
};

int main(int argc, const char* argv[]) {
	std::cout << sizeof(Test) << std::endl;  // размер пустого объекта 1 байт  (связано с тем, что любая сущность должна иметь адресуемость)
	std::cout << sizeof(advance) << std::endl;  // при добавлении virtual размер класса увеличился на размер указателя. на 32-разрядной размер указателя 4 байта
	
	advance* add{ new advance_der{} }; 

	/*
		как понять, что add должен ссылатся на vtable производного класса?  появляется в классе поле protected
	*/

	add->test(); // add -> (ptr + 0) ()
	add->test1(); // add -> (ptr + 1) ()

	system("pause");
	return 0;
}