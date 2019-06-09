#include "Scheduler.hpp"

Scheduler::~Scheduler()
{
	start_run = false;
	sh_thread->join();
}

void Scheduler::ShThread()
{
	while(start_run) //infinite loop of scehduler until object distructed
	{
		std::function<void()> todo;
		{
			std::unique_lock<std::mutex> lock(mutex); //unique_lock require a block for locking unlocking automation of mutex
													  //+ its also release lock in case of exception which we may need to do manually in catch block otherwise.	
			auto now = std::chrono::system_clock::now();
			if (!task_queue.empty() && task_queue.begin()->first <= now)	//if queue have any task registered for now or time before that schedule it.
			{
				todo = task_queue.begin()->second;
				task_queue.erase(task_queue.begin());
				
			}
		}
		
		if(todo)
			todo(); //scedule task if found in queue
			
		{
			//if schedule queue is empty block thread until new task is registered.
			//else block till schedule time of next task in queue
			std::unique_lock<std::mutex> lock(mutex);	
			if (task_queue.empty())
				sh_wait.wait(lock);
			else
				sh_wait.wait_until(lock, task_queue.begin()->first);	
		}	
	}//end of while
}

void Scheduler::Schedule(std::chrono::system_clock::time_point time, std::function<void()> task)
{
	std::unique_lock<std::mutex> lock(mutex);
	
	auto itr = task_queue.emplace(time,task);
	if (itr == task_queue.begin())
		sh_wait.notify_one();
}

void Scheduler::SchedulePeriodic(std::chrono::system_clock::duration interval, std::function<void()> task)
{
	//make a functor which call passed task and make periodic registery call to add periodic task to queue
	auto periodic = [this,interval,task]()
			{
				task();
				this->SchedulePeriodic(interval,task);
			};
			
	//scehdule functor with inerval+ current time		
	Schedule(std::chrono::system_clock::now() + interval, periodic);		
}

