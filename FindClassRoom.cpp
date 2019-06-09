//Given an array of time intervals (start, end) for classroom lectures (possibly overlapping), find the minimum number of rooms required.
//For example, given [(30, 75), (0, 50), (60, 150)], you should return 2.

#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

int getRoomCount(const map<int,string>& room_logger)
{
	int max_count = 0;
	int count = 0;
	for(auto val: room_logger)
	{
		cout << val.first << " " <<val.second << endl;
		if(val.second == "start") count++;
		else count--;
		
		if (count > max_count) max_count = count;
	}
	return max_count;
}

int main()
{
	vector<pair<int,int>> classes{make_pair(30,75),make_pair(0,50),make_pair(60,150)};
	map<int,string> room_logger;
	
	for(auto val: classes)
	{
		room_logger[val.first] = "start";
		room_logger[val.second] = "end";
	}
	
	cout << "No. of rooms required are: " << getRoomCount(room_logger) << endl;
	
	return 0;
}
