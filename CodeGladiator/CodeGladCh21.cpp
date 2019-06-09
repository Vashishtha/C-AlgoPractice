/* Read input from STDIN. Print your output to STDOUT*/
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

void printWinList(int sum,vector<int>&& values)
{
	for_each(values.rbegin(),values.rend(),[=](int i){
		if (i != 0)
		{
			if (sum > 0 && i < 0);
			else
				cout << i; 
		}
	});
	cout << endl;
	
	return;
}

void findWinningList(vector<int>&& tickets)
{
	vector<int> Sums;
	vector<vector<int>> maxSubArray;
	//bool negative = *(max_element(std::begin(tickets), std::end(tickets)))<=0 ? true : false;
	
	for(int i=0; i<tickets.size(); i++)
	{
		//int value = (!negative && tickets[i] < 0) ? 0 : tickets[i];
		int value = tickets[i];
		vector<int> array;
		
		if(i == 0)
		{
			Sums.push_back(value);
			array.push_back(value);
			maxSubArray.push_back(array);
		}
		else if(i == 1)
		{
			Sums.push_back(max(Sums[0],value));
			array.push_back(max(Sums[0],value));
			maxSubArray.push_back(array);	
		}
		else
		{
			if(Sums[i-2]+value >= Sums[i-1])
			{
				Sums.push_back(Sums[i-2]+value);
				//if(maxSubArray.empty())
				//maxSubArray[maxSubArray.size()-1] = tickets[i-2];		
				//maxSubArray.push_back(value);	
				if(Sums[i-2]+value == Sums[i-1])
				{
					if(value > tickets[i-1])
					{
						array.push_back(value);
						maxSubArray.push_back(maxSubArray[i-2]);
						maxSubArray[maxSubArray.size()-1].push_back(value); 	
					}
					else
					{
						maxSubArray.push_back(maxSubArray[i-1]);
				}
				}
				else
				{
					array.push_back(value);
					maxSubArray.push_back(maxSubArray[i-2]);
					maxSubArray[maxSubArray.size()-1].push_back(value); 
				}
			}
			else
			{
				Sums.push_back(Sums[i-1]);
				//if(maxSubArray.empty())
				maxSubArray.push_back(maxSubArray[i-1]);
			}
		}
	}
	copy(Sums.begin(),Sums.end(),std::ostream_iterator<int>(std::cout, " "));
	cout << endl;
	copy(maxSubArray[maxSubArray.size()-1].begin(),maxSubArray[maxSubArray.size()-1].end(),std::ostream_iterator<int>(std::cout, " "));
	cout << endl;
	printWinList(Sums[tickets.size()-1],move(maxSubArray[maxSubArray.size()-1]));
	
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
        if(tktList.size() > N)
        	tktList.erase(tktList.begin()+N,tktList.end());
		
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

