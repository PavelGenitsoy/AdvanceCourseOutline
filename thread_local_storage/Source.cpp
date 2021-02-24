#include <iostream>
#include <thread>


// thread_local добавляет так называемый storage duration. Есть разные storage duration: avtomatic, global, heap, thread. 
thread_local int test{}; // делаем переменную, которая будет глобальная между потоками, по сути каждый поток (что будет стучатся к ней) будет иметь свою копию


int main(int argc, const char* argv) {




	return 0;
}