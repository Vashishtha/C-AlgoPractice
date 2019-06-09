/* Read input from STDIN. Print your output to STDOUT*/
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <tuple>

using namespace std;

void printWinList(vector<int>&& validTickets,int maxSum)
{
	for(auto val : validTickets)
	{
		if(val == 0)
			continue;
		//else if(maxSum > 0)
		//{
		//	if(val > 0)
		//	{
		//		cout << val;
		//	}
		//}
		else
		//{
			cout << val;
		//}
	}
	
	cout << endl;	
	return;
}

vector<int> populateList(int startPt, const vector<int>& tickets, const vector<int>& positions)
{
	vector<int> finalList;
	
	while(startPt != -1)
	{
		finalList.push_back(tickets[startPt]);
		//cout << tickets[startPt];
		startPt = positions[startPt];
	}
	//cout << endl;
	return finalList;
}

void findWinningList(vector<int>&& tickets)
{
	vector<int> Sums(tickets.size(),-1001);
	vector<int> Positions(tickets.size(),-1);
	
	Sums[0] = tickets[0];// == 0 ? -1001 : tickets[0];
	Sums[1] = tickets[1];// == 0 ? -1001 : tickets[1];
	
	//bool consider_Neg = false;
	//std::max_element(tickets.begin(), tickets.end());
	//if(*() < 0)
	//	consider_Neg = true;
	
	for(int i=2; i<tickets.size(); i++)
	{
		//if(!consider_Neg && tickets[i] < 0)
		//	continue;
			
		auto itr = std::max_element(Sums.begin(), Sums.begin()+i-1);
		if(itr != tickets.begin()+i-1)
		{
			//if(tickets[i] == 0)
			//{
			//	continue;
			//}
			if(tickets[i]+(*itr) > tickets[i])
			{
				Sums[i] = tickets[i]+(*itr);
				Positions[i] = distance(Sums.begin(),itr);
			}
			else if((*itr) > tickets[i])
			{
				//Sums[i] = (*itr);
				//Positions[i] = distance(Sums.begin(),itr);	
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
	std::vector<int> finalList = populateList(startPt,tickets,Positions);
	
	int maxSum = *itr;
	Sums[startPt] = -1001;
	
	itr = find(Sums.begin(), Sums.end(),maxSum);
	while(itr != Sums.end())
	{
		startPt = distance(Sums.begin(),itr);
		std::vector<int> poss = populateList(startPt,tickets,Positions);
		
		int len = poss.size()>finalList.size() ? finalList.size() : poss.size();
		
		if(poss > finalList) finalList = poss;
		/*for(int i=0; i< len; i++)
		{
			if(poss[i] > finalList[i])
			{
				finalList = poss;
				break;
			}
			else if(finalList[i] > poss[i])
				break;
			else
				continue;	
		}*/
		
		Sums[startPt] = -1001;
		itr = find(Sums.begin(), Sums.end(),maxSum);
	}
	
	printWinList(move(finalList),maxSum);
	
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

