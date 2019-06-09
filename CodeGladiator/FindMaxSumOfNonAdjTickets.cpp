/* Read input from STDIN. Print your output to STDOUT*/
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>

using namespace std;

void findWinningList(vector<int>&& tickets)
{
	int sum_p,sum_pp;
	map<int,set<int>> SumsMap;
	sum_pp = tickets[0];
	sum_p = tickets[1];
	set<int> positionValue0{tickets[0]};
	set<int> positionValue1{tickets[1]};
	SumsMap.emplace(make_pair(tickets[0],positionValue0));
	SumsMap.emplace(make_pair(tickets[1],positionValue1));
	
	for(int i=2; i<tickets.size(); i++)
	{
			set<int> positionValue;
			int temp_sum;	
			
			if(tickets[i]+sum_pp > tickets[i])
			{
				temp_sum = sum_pp;
				sum_pp = sum_pp > sum_p ? sum_pp : sum_p;
				sum_p = tickets[i]+temp_sum;
				auto itr = SumsMap.find(sum_p);
				if(itr != SumsMap.end())
				{
					positionValue = itr->second;
				}
				positionValue.insert(tickets[i]);
				SumsMap[sum_p] = move(positionValue);
			}
			else if(sum_pp > tickets[i])
			{
				temp_sum = sum_pp;
				sum_pp = sum_pp > sum_p ? sum_pp : sum_p;
				sum_p = temp_sum;
			}
			else
			{
				temp_sum = sum_pp;
				sum_pp = sum_pp > sum_p ? sum_pp : sum_p;
				sum_p = tickets[i];
				auto itr = SumsMap.find(sum_p);
				if(itr != SumsMap.end())
				{
					positionValue = itr->second;
				}
				positionValue.insert(tickets[i]);
				SumsMap[sum_p] = move(positionValue);
			}
	}
	//copy(Sums.begin(),Sums.end(),std::ostream_iterator<int>(std::cout, " "));
	//cout << endl;
	//for_each(SumsMap.begin(),SumsMap.end(),[](const pair<int,set<int>> &p){
	//			std::cout << "{" << p.first << ": ";
	//			for_each(p.second.begin(),p.second.end(),[](const int &i){
	//				std::cout << i << ", ";	
	//			});
	//			std::cout << "}\n";
	//});
	
	int maxSum = SumsMap.rbegin()->first;
	while(maxSum != 0)
	{
		auto itr1 = SumsMap.find(maxSum);
		if(itr1 == SumsMap.end())
			break;
			
		int value = *((itr1->second).rbegin());
		if(value != 0)
			cout << value;
		
		maxSum -= value;	
	}
	cout << endl;
	
	return;
}

int main()
{
	int testCases{0};
	int N{0};
	string tickets;

	cin >> testCases;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	while(testCases != 0)
	{
		istringstream iss1;
		cin >> N;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
		getline(cin, tickets);
    	iss1.str(tickets);
    	vector<int> tktList{istream_iterator<int>(iss1),
                     istream_iterator<int>()};
        //if(tktList.size() > N)
        //	tktList.erase(tktList.begin()+N,tktList.end());
		
		//cout << "N: " << N <<endl;      
		//cout << "tickets: " << tickets;   
		//copy(tktList.begin(),tktList.end(),std::ostream_iterator<int>(std::cout, " "));
		//cout << endl;    
    	findWinningList(move(tktList));
    	
    	tickets.clear();
		testCases--;	
	}
	return 0;	
}

