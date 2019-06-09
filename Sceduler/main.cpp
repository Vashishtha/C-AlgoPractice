#include <iostream>
#include "Scheduler.hpp"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void Task1()
{
	std::cout <<"Task 1 run after 5 sec from scheduled" << std::endl;
}

void Task2()
{
	std::cout <<"Task 2 run after 10 sec from scheduled" << std::endl;
}

void Task3()
{
	std::cout <<"Task 3 run every 5 sec from scheduled" << std::endl;
}

int main(int argc, char** argv) {
	auto now = std::chrono::system_clock::now();
	
	Scheduler::getInstance()->Schedule(now + std::chrono::seconds(5),Task1);
	Scheduler::getInstance()->Schedule(now + std::chrono::seconds(10),Task2);
	
	Scheduler::getInstance()->SchedulePeriodic(std::chrono::seconds(5),Task3);
	return 0;
}
