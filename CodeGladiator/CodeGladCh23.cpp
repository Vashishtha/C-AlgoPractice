/* Read input from STDIN. Print your output to STDOUT*/
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

void printWinList(int sum, int startPt, vector<int>&& positions, vector<int>&& tickets)
{
	do{
		if(tickets[startPt] == 0)
		{
			startPt = positions[startPt];
			continue;
		}
		else if(sum > 0)
		{
			if(tickets[startPt] > 0)
			{
				cout << tickets[startPt];
			}
		}
		else
		{
			cout << tickets[startPt];
		}
		startPt = positions[startPt];
	}while(startPt != -1);
	
	cout << endl;
	
	return;
}

void findWinningList(vector<int>&& tickets)
{
	vector<int> Sums(tickets.size(),-1000);
	vector<int> Positions(tickets.size(),-1);
	
	Sums[0] = tickets[0] == 0 ? -1000 : tickets[0];
	Sums[1] = tickets[1] == 0 ? -1000 : tickets[1];
	
	for(int i=2; i<tickets.size(); i++)
	{
		auto itr = std::max_element(Sums.begin(), Sums.begin()+i-1);
		if(itr != tickets.begin()+i-1)
		{
			if(tickets[i] == 0)
			{
				continue;
			}
			else if(tickets[i]+(*itr) > tickets[i])
			{
				Sums[i] = tickets[i]+(*itr);
				Positions[i] = distance(Sums.begin(),itr);
			}
			else if((*itr) > tickets[i])
			{
				Sums[i] = (*itr);
				Positions[i] = distance(Sums.begin(),itr);	
			}
			else
			{
				Sums[i] = tickets[i];
				//Positions[i] = i;
			}
		}
	}
	//copy(Sums.begin(),Sums.end(),std::ostream_iterator<int>(std::cout, " "));
	//cout << endl;
	//copy(Positions.begin(),Positions.end(),std::ostream_iterator<int>(std::cout, " "));
	//cout << endl;
	
	auto itr = std::max_element(Sums.begin(), Sums.end());
	int startPt = distance(Sums.begin(),itr);
	
	printWinList(*itr,startPt,move(Positions),move(tickets));
	
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

