/* Read input from STDIN. Print your output to STDOUT*/
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stack>

using namespace std;

void printWinList(int sum,stack<int>&& values,vector<int>&& tickets)
{
	int prev = values.top();

	do
	{
		//if (values.top() != 0)
		//{
		//	if (sum > 0 && values.top() < 0);
		//	else
			if(prev+1 != values.top() || prev-1 != values.top())
				cout << tickets[values.top()]; 
		//}
		values.pop();
	}while(!values.empty());
	
	cout << endl;
	
	return;
}

void findWinningList(vector<int>&& tickets)
{
	//store max sum till i-2
	int pp_sum = tickets[0];
	//store max sum till i-1
	int p_sum = max(tickets[0],tickets[1]);
	
	stack<int> maxSubArray;
	if(p_sum == tickets[1]) maxSubArray.push(1);
	else maxSubArray.push(0);
	
	for(int i=2; i<tickets.size(); i++)
	{
		int curr = max(tickets[i], max(p_sum, pp_sum+tickets[i]));
		
		if(pp_sum+tickets[i] > p_sum)
		{
			//maxSubArray.pop();
			maxSubArray.push(i);
		}
		else if (tickets[i] > p_sum)
		{
			while(!maxSubArray.empty())
				maxSubArray.pop();

			maxSubArray.push(i);
		}
		
		pp_sum = p_sum;
		p_sum = curr;
	}
	
	cout << "pp_sum: " << pp_sum << " " << "p_sum: " << p_sum;
	cout << endl;

	printWinList(p_sum,move(maxSubArray),move(tickets));
	
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
		if(!tktList.empty()) 
    		findWinningList(move(tktList));
    	
    	tickets.clear();
		testCases--;	
	}
	return 0;	
}

