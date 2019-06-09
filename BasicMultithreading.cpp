#include <iostream>
#include <future>
#include <chrono>

void doSomeWork()
{
	for (int i=0; i< 5; i++)
	{
   		std::cout << "Thread Running is: "<<std::this_thread::get_id()<<std::endl;
   		std::this_thread::sleep_for (std::chrono::seconds(1));
	}
}

int main()
{
	for (int i=0; i < 10; i++)
	{
		std::cout << "Main Thread Running is: "<<std::this_thread::get_id()<<std::endl;
		std::async(std::launch::async,doSomeWork);
	}
}
