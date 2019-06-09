/* Read input from STDIN. Print your output to STDOUT*/
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

void printWinList(vector<int>&& winList)
{
	for_each(winList.rbegin(),winList.rend(),[](int i){
        if (i != 0)
		    cout << i;
	});
	cout << endl;
	
	return;
}

void populateSubList(const int& value,long long& sum,vector<int>& stk,bool neg)
{
	auto temp = sum;
	temp += value;
	if(!neg && temp > sum)
	{
		sum = temp;
	}
	else if(neg && temp < sum)
	{
		sum = temp;
	}	
    if(value == 0)
       stk.push_back(value); 
       
	return;
}

void findWinningList(vector<int>&& tickets)
{
	long long sum1{-1000};
	long long sum2{-1000};
	vector<int> stk1;
	vector<int> stk2;
	
	bool negative = *(max_element(std::begin(tickets), std::end(tickets)))<=0 ? true : false;
	
	for(int i=0; i<tickets.size();i++)
	{
		auto value = tickets[i];
		
		if(i%2 == 0)
		{
			populateSubList(value,sum1,stk1,negative);
		}
		else
		{	
			populateSubList(value,sum2,stk2,negative);
		}
		//copy(stk1.begin(),stk1.end(),std::ostream_iterator<int>(std::cout, " "));
		//cout << endl;
		//copy(stk2.begin(),stk2.end(),std::ostream_iterator<int>(std::cout, " "));
		//cout << endl;
	}
	
	if(sum1 > sum2)
	{
		printWinList(move(stk1));
	}
	else if(sum1 == sum2)
	{
		int size = ((stk1.size()<=stk2.size()) ? stk1.size() : stk2.size())-1;
		
		while(size >= 0)
		{
			//cout << "stk1[i] " << stk1[size] << " " << "stk2[i] " << stk2[size] << endl;
			
			if(stk1[size] == stk2[size])
			{
				size--;
				continue;
			}
			else if(stk1[size] > stk2[size])
			{
				printWinList(move(stk1));
				break;
			}
			else
			{
				printWinList(move(stk2));
				break;
			}
			
		}
		if(size < 0) printWinList(move(stk2));
		
	}
	else
	{
		printWinList(move(stk2));
	}
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

