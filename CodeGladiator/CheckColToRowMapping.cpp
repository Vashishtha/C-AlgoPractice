/* Read input from STDIN. Print your output to STDOUT*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <numeric>
#include <sstream>
#include <regex>

//This is my efforts for optimum performance solution from my side.
//Here I am reading phases and storing them as map key and no of phase val repitation by that key count.
//States are stored in vector which was presized.
//Both state and phase sum calculated during readin input.
//results contain a vector of states size, which actually holds derived state data from given phase data
//for example: phase 3 1 3have derived sate data as:
// 1 1 1
// 1
// 1 1 1 add to 3 2 2which is than compared with given sates by taking sum at each column level.
//If at any column level sum of input state values is > derived column sum than distribution not possible (o/p NO)
//els eits YES.
//some addon checks are also in place that if both state and phase overall sum is not equal than its anyway NO.
//if both sum 0 than YES
//if both sum >= Totalrow*Totalcoulmn YES
	
using namespace std;

std::string ltrim(const std::string& s) {
	return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(const std::string& s) {
	return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string& s) {
	return ltrim(rtrim(s));
}

bool doesBJPWins(vector<long int>& states, vector<long int>& results)
{
	long long int stateSum = 0;
	long long int resultSum = 0;
	
	for(int i=0; i < states.size(); i++)
	{
		stateSum += states[i];
		resultSum += results[i];
		
		if(stateSum > resultSum)
			return false;
	}

	return true;
}

int main(int argc, char *a[])
{
    int testCases{0};
    string phaseNstate;
    string phases;
	    string states;
	    
    cin >> testCases;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while(testCases != 0)
    {
        istringstream iss1,iss2,iss3;
        
		getline(cin, phaseNstate);
		trim(phaseNstate);
        iss1.str(phaseNstate);

        vector<long int> phs_st{istream_iterator<int>(iss1),
        istream_iterator<int>()};
        
        if(phs_st[0] == 0 && phs_st[1] == 0)
    	{
    		cout << "YES" << endl;
    		testCases--;
    		continue;
		}
		else if((phs_st[0] == 0 && phs_st[1] != 0) ||
				(phs_st[1] == 0 && phs_st[10] != 0))
		{
			cout << "NO" << endl;
			testCases--;
    		continue;		
		}		
        
        getline(cin, phases);
        trim(phases);
        iss2.str(phases);
        map<int,int,greater<int>> phaseVec;
        vector<long int> results(phs_st[1],0);
        
        getline(cin, states);
        trim(states);
        iss3.str(states);
        vector<long int> stateVec(phs_st[1],0);
        
		int val1,val2;
		long int id0 = 0;
		long int id1 = 0;
		long long int phSum = 0;
		long long int stSum = 0;
		
    	
    	do{	
    		if(id0 < phs_st[0])
    		{
    			iss2 >> val1;
    			phaseVec[val1]++;
    			phSum += val1;
        		id0++;
			}
			if(id1 < phs_st[1])
			{
				iss3 >> val2;
				stateVec[id1] = val2;
				stSum += val2;
        		id1++;
			}
			if(id0 == phs_st[0] && id1 == phs_st[1])
			{
				break;
			}
		}while(1);
        
        sort(stateVec.begin(),stateVec.end(),greater<int>());
        for(auto itr = phaseVec.begin(); itr != phaseVec.end(); itr++)
        {
        	long int value = itr->first*itr->second;
        	auto endItr = results.begin()+value <= results.end() ?  results.begin()+value : results.end();
        	for_each(results.begin(), endItr, [](long int& val){
				val++;
			});
		}
        
        long long int mtrxSize = phs_st[0] * phs_st[1];
        
        if(phSum == stSum)
        {
        	if(phSum == 0)
        		cout << "YES";
        	else if((phSum >= mtrxSize))	
        		cout << "YES";
        	else
        	{
        		cout << (doesBJPWins(stateVec,results) ? "YES" : "NO");
			}
		}
        else
        	cout << "NO";	
    			       
        cout << endl;
        phaseNstate.clear();
        phases.clear();
        states.clear();
        testCases--;
    }

    return 0;
}
