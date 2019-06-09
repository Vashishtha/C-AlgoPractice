//Given two singly linked lists that intersect at some point, find the intersecting node. The lists are non-cyclical.
//For example, given A = 3 -> 7 -> 8 -> 10 and B = 99 -> 1 -> 8 -> 10, return the node with value 8.
//Do this in O(M + N) time
#include <list>
#include <map>
#include <iostream>

using namespace std;

int find_intersection(const list<int>& first, const list<int>& second)
{
	map<int,bool> present;
	
	for(auto val : first)
	{
		if(present.find(val) == present.end())
		{
			present[val] = true;
		}
	}
	
	for(auto val : second)
	{
		if(present.find(val) == present.end())
		{
			present[val] = true;
		}
		else
		{
			return val;
		}
	}
}

int main()
{
	list<int> first,second;
	
	first.push_back(3);
	first.push_back(7);
	first.push_back(8);
	first.push_back(10);
	
	second.push_back(99);
	second.push_back(1);
	second.push_back(8);
	second.push_back(10);
	
	cout << "Intersection point is: " << find_intersection(first,second) <<endl;
	
	return 0;
}
