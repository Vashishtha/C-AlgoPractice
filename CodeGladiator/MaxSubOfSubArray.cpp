/* Read input from STDIN. Print your output to STDOUT*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <iterator>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>

//this soultion calculates sum of numers in input list
//and store them in a map with all digits of all numbers used to calculate that sum
//at last we return last index from map which is greatest sum.
//This code has flaw as we are not considering same sums created from diff set of digits,
//To resolve that when I started using multimap score get worse.
//Same solution when submitted with python using list of tuples as dictionary worked fine and I got 100.
//There we are maintaining a global variable maxSum.

using namespace std;

set<int> getDigits(int val)
{
	set<int> digits;
	
    while(0 != val)
    {
        int rem = val%10;
        val = val/10;
        digits.insert(rem);
    }	
	return digits;
}

bool canAdd(int val, set<int>& inSet, map<long,set<int>>& maxSumSet)
{
	bool retVal = false;
	map<long,set<int>> temp;
	
	for(auto itr = maxSumSet.begin(); itr != maxSumSet.end(); itr++)
	{
		//cout << "Map Sum " << itr->first << "Map digits ";
		//copy(itr->second.begin(), itr->second.end(), ostream_iterator<int>(cout, " ")); 
		//cout << endl;
		
		auto it = find_first_of(inSet.begin(), inSet.end(), itr->second.begin(), itr->second.end());
		if(it != inSet.end())
		{
			//cout << "intersecting value can't be added" << endl;
			continue;
		}
		else
		{
			//cout << "value added and new digits:";
			set<int> digits = itr->second;
			digits.insert(inSet.begin(), inSet.end());
			//copy(digits.begin(), digits.end(), ostream_iterator<int>(cout, " "));
			//cout << endl;
			
			temp.emplace(make_pair(itr->first+val,digits)); 
			//itr = maxSumSet.erase(itr);
			retVal = true;
			
		}
	}
	maxSumSet.insert(temp.begin(),temp.end());
	return retVal;
}

//sorted input with no dulicates
int maxSubStrSum(vector<int>&& boxList)
{
    int maxSum{0};
    map<long,set<int>> maxSumSet;//holds sum and its corresponding digits

    for(auto itr = boxList.rbegin(); itr != boxList.rend(); itr++)
    {
    	//cout << *itr <<endl;//  << "   Digits:  ";
    	set<int> digits = move(getDigits(*itr));
    	//copy(digits.begin(), digits.end(), ostream_iterator<int>(cout, " "));
    	//cout << endl;
    	
        canAdd(*itr,digits,maxSumSet);
		maxSumSet.emplace(make_pair(*itr,digits));
    }

	
    return maxSumSet.rbegin()->first;//(--maxSumSet.end())->first;
}

int main(int argc, char *a[])
{
    int testCases{0};
    int noOfBoxs{0};
    string numbers;

    cin >> testCases;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while(testCases != 0)
    {
        //vector<bool> visited(10,false);
        istringstream iss;
        cin >> noOfBoxs;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

		getline(cin, numbers);
        iss.str(numbers);

        vector<int> boxList{istream_iterator<int>(iss),
        istream_iterator<int>()};
        
        //copy(boxList.begin(), boxList.end(), ostream_iterator<int>(cout, " "));
        //cout << maxSubStrSum(move(boxList),move(visited));
        cout << maxSubStrSum(move(boxList));
        cout << endl;
        numbers.clear();
        testCases--;
    }

    return 0;
}

