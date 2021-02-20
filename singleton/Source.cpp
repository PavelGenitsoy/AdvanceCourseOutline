#include <iostream>
#include <thread>


class singleton {  // singleton Майерса
private:
	singleton() = default;
	~singleton() = default;
public:
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;
	static singleton& getSingleton() {
		static singleton inst; // тут подход lazy initialisation, т.е. конструктор будет вызван для глобального объекта inst только тогда, когда я
							   // первый раз вызову ф-цию getSingleton. И потом буду просто возвращать ссылку уже на созданный instance.
							   // Все статические переменные, которые имеют подход lazy initialisation (объявленные в данном методе) являться потокобезопасными
		return inst;
	}
	/*
		определили конструктор копирования и оператор копирования, теперь не будет генерироваться ни одна перемещающая операция.

		Но как же создавать этот объект? Создавая методом. Есть 2 подхода:
		1) Классический синглтон  -  его лучше забыть.  И это всё работает когда однопоточный код. А в многопоточном будет проблема race condition.
		2) Синглтон Майерса. Тут в многопоточном коде будет всё хорошо.
	*/
};



class singleton_сlassic {  // singleton классический
private:
	singleton_сlassic() = default;
	~singleton_сlassic() {
		delete inst;
	}
	static inline singleton_сlassic* inst{ nullptr };
public:
	singleton_сlassic(const singleton_сlassic&) = delete;
	singleton_сlassic& operator=(const singleton_сlassic&) = delete;
	static singleton_сlassic* getSingleton() {
		if (inst == nullptr) {   // собственно здесь будет проблема при многопоточном коде
			inst = new singleton_сlassic{};
		}
		return inst;
	}
};

/*
// потокобезопасный вариант классического singleton
std::once_flag flag;

class singleton_сlassic {
private:
	singleton_сlassic() = default;
	~singleton_сlassic() {
		delete inst;
	}
	static inline singleton_сlassic* inst{ nullptr };
public:
	singleton_сlassic(const singleton_сlassic&) = delete;
	singleton_сlassic& operator=(const singleton_сlassic&) = delete;
	static singleton_сlassic* getSingleton() {
		std::call_once(flag, [inst]() {  // call_once говорит, что если 2 потока паралельно вызывают getSingleton, то часть std::call_once будет исполнено
										 // только 1 раз и она будет thread safe сразу между несколькими потоками
			if (inst == nullptr) {
				inst = new singleton_сlassic{};
			}
		});
		return inst;
	}
};
*/


int main(int args, const char* argv[]) {

	singleton& instance = singleton::getSingleton();

	return 0;
}