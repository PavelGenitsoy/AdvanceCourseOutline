#include <iostream>
#include <memory>


class Base {
public: 
	virtual ~Base() { std::cout << __FUNCSIG__ << std::endl; }  
}; // virtual можем убрать если в коде используем shared_ptr (например такая строка std::shared_ptr<Base> ptr{ std::make_shared<Derived>() }) 
   // ибо они понимают правильный порядок


class Derived : public Base {
public:
	~Derived () { std::cout << __FUNCSIG__ << std::endl; }
};


int main(int args, const char* argv[]) {

	std::shared_ptr<Base> ptr{ std::make_shared<Derived>() }; // создали указатель на базовый класс, хотя по факут ссылаемся на производный, тут всё норм
															  
	// и к примеру мы хотим сделать down_cast . от Base получить Derived

	// std::shared_ptr<Base> ptr1{ dynamic_cast<Derived*>(ptr.get()) }; // core dumped error   (получился некий double free)
	/*
		(ptr.get()) это мы берём указатель с ptr, т.е. тот ресурс, что там есть. у нас не копирование самого ptr!! Мы берём ресурс 
		создаём shared_ptr и туда запихиваем этот ресурс

		на самом деле ref counter не увеличился, ибо мы ptr1 присвоили тот указатель (ptr) который находился в shared_ptr.

		У нас по факту существует 2 shared_ptr со своим счётчиком ссылок, и у нас ПРОБЛЕМА: что два shared_ptr ссылаються на один и тот 
		же ресурс, но у каждого свой control block
	*/

	std::shared_ptr<Base> ptr1{ std::dynamic_pointer_cast<Derived>(ptr) }; // РЕШЕНИЕ проблемы!!



	system("pause");
	return 0;
}