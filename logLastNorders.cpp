//You run an e-commerce website and want to record the last N order ids in a log. Implement a data structure to accomplish this, with the following API:

//record(order_id): adds the order_id to the log
//get_last(i): gets the ith last element from the log. i is guaranteed to be smaller than or equal to N.
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

class Recorder
{
 private:
 	const int RecordLimit;
	unordered_map<int,string> _logRecord; //using list because removing first element from it is easy and not take much time unlike vector(move all element)	
	int start;//we will remove old records from here
	int end;// we will insert new recrods from here 
 public:
	Recorder(int N=10):RecordLimit(N)
	{
		start = end = 0;
	}
	
	bool record(string order_id)
	{
		if(_logRecord.size() >= RecordLimit)
		{
			_logRecord.erase(start);
			start = (start+1)%RecordLimit;			
		}	
		_logRecord.emplace(end,order_id);
		end = (end+1)%RecordLimit;
		return true;
	}
	
	const string& get_last(int i)
	{
		if (i > RecordLimit) return NULL;// i must be in recodrer capacity
		int pos = end-i>0 ? (end-i) : (RecordLimit+end-i);//to get circular index 	
		return _logRecord[pos];
	}

};

int main()
{
    Recorder recorder;
	
	recorder.record("AB");
	recorder.record("AB1");
	recorder.record("AB2");
	recorder.record("AB3");
	recorder.record("AB4");
	recorder.record("AB5");
	recorder.record("AB6");
	recorder.record("AB7");
	recorder.record("AB8");
	recorder.record("AB9");
	recorder.record("AB10");
	recorder.record("AB11");
	
	cout << "Third last record: " << recorder.get_last(3) <<endl;
	cout << "10th last record: " << recorder.get_last(10) <<endl;
	cout << "1st last record: " << recorder.get_last(1) <<endl;
	
	return 0; 
} 
