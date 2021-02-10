#include <iostream>
#include <thread>
#include <future>


/*
	Что если я хочу с потока вернуть значение? То возникает вопрос..., а как я через объект потока могу получить это вовзращаемое значение?
*/

int th_func() {
	return 20;
}

int th_func1(int & ret) { // неправильный код
	ret = 20;
	return 20;
}

void th_func2(std::promise<int> p) {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	p.set_value(20);
	//p.set_value(10); // мы не можем несколько раз переиспользовать тот же самый promise или future
}


class Debug {
public:
	Debug() = default;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = default;
};


int main(int args, const char* argv[]) {

	/*
		Объект потока (это врапер раишный) высокоуровневая абстракция, которая внутри себя реализовывает кроссплотформенный механизм вызова каких-то
		низкоуровневых ф-ций той или иной ОС для создания потока. Объект потока ничего не знает о возвращаемом значение ф-ции (в данный момент th_func),
		т.е. его задача взять что-то, что ведёт себя как ф-ция и исполнить его в отдельном потоке.
	*/

	std::thread tr{ th_func }; 

	tr.join();

	
	/*
	int ret{};  // но тут снова проблемка (возможно UB). Время жизни этого объекта потока tr1 может превышать время жизни объекта ret
	std::thread tr1{ th_func1, std::ref(ret) };

	tr1.join();

	std::cout << ret << std::endl;
	*/


	/*
		Чтобы решить проблему будем использовать механизм коммуникации (т.е. я что-то передаю в поток и что-то есть внешнее, которое мне позволит 
		проверять жизненный цикл моего потока). Т.е. будем использовать понятие promise future (promise - то что устанавливает\сообщает, а future - ожидает)
	*/

	std::promise<int> p;
	auto fut = p.get_future();

	std::thread tr2{ th_func2, std::move(p) }; 
	tr2.detach();

	std::cout << "after run thead tr2" << std::endl;

	if (fut.wait_for(std::chrono::seconds(3)) == std::future_status::timeout) {  // так называемая блокировка с таймоутом
		std::cout << "timeout\n"; // timeout возвращается если promise ещё ничего не установил. ready если уже было б установлено (std::future_status::ready)
	}

	std::cout << "waited 3 seconds\n";

	fut.wait(); // т.е. равносильно, что мы делали join для потоков. Т.е. мы блокируемся до того момента пока promise не установит своё значение.

	std::cout << "and still waited 2 seconds\n";

	std::cout << "our return value: " << fut.get() << std::endl;


	return 0;
}