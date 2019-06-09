#ifndef _SCHEDULER_
#define _SCHEDULER_

#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

class Scheduler
{
	private:
		
		static std::unique_ptr<Scheduler> sh_instance;
		
		std::multimap<std::chrono::system_clock::time_point, std::function<void()>> task_queue;
		std::mutex mutex;
		std::unique_ptr<std::thread> sh_thread;
		std::condition_variable sh_wait;
		bool start_run;
			
		Scheduler():start_run(true)
		{
			sh_thread.reset(new std::thread([this](){ this->ShThread();}));
		}
	
	public:
		//should not be copyable
		Scheduler(const Scheduler& rhs) = delete;
		Scheduler&  operator=(const Scheduler& rhs)	= delete;
		
		//should allow move
		Scheduler(Scheduler&& rhs);
		Scheduler&  operator=(Scheduler&& rhs);
		
		~Scheduler();
		void ShThread();
		void Schedule(std::chrono::system_clock::time_point time, std::function<void()> task);
		void SchedulePeriodic(std::chrono::system_clock::duration interval, std::function<void()> task);
		
		static Scheduler* getInstance();
};

std::unique_ptr<Scheduler> Scheduler::sh_instance = NULL;//std::nullptr; not supporting
	
Scheduler* Scheduler::getInstance()
{
	//need to add logic for mutex locking here to avoid simultaneious calls discripancies
	if(Scheduler::sh_instance.get() == NULL)
	{
		Scheduler::sh_instance.reset(new Scheduler());	
	}
	
	return 	Scheduler::sh_instance.get();
}
		
#endif //_SCHEDULER_
