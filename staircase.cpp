//There exists a staircase with N steps, 
//and you can climb up either 1 or 2 steps at a time. 
//Given N, write a function that returns the number of unique ways you can climb the staircase. The order of the steps matters.

//For example, if N is 4, then there are 5 unique ways:

//1, 1, 1, 1
//2, 1, 1
//1, 2, 1
//1, 1, 2
//2, 2
//What if, instead of being able to climb 1 or 2 steps at a time,
//you could climb any number from a set of positive integers X? 
//For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time.
#include<vector>
#include<iostream>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

unordered_map<int,long long> memo;
long long getWays(const std::vector<int> stepSizes, int N)
{
	cout << "stairs remaing: " << N << endl;
	if (N == 0)
	{
		cout << "stairs finished." << endl;
		return 1;
	}
	
	long long total = 0;
	if(memo.find(N) != memo.end())
	{
		total = memo[N];
		cout << "result found in map." << endl;
	}	
	else
	{
		cout << "calculate ways" << endl;
		for(int i : stepSizes)
		{
			if (N-i >= 0)
			{
				total +=  getWays(stepSizes,N-i);
			}
		}
		memo[N] = total;
	}
	return total;
}

void waysTOClimb(const std::vector<int>&& _steps, int N)
{
	std::cout << "TotalNumber of ways to climb staircase is: " << getWays(_steps,N) << std::endl;
	return; 
}

std::vector<std::string> split_string(std::string input_string) {
	
	//This will remove duplicate ' ' delimeter(actually moves them to the end of string)
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

	//erase duplicate delimeters
    input_string.erase(new_end, input_string.end());

	//not sure why we need it after erase need to check looks like redundant code for erase
    //while (input_string[input_string.length() - 1] == ' ') {
    //    input_string.pop_back();
    //}

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

int main()
{
	int stairSize;
	std::cout << "Get size of staircase: " << std::endl;
    std::cin >> stairSize;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Get step sizes: " << std::endl;
    std::string ar_stepSizes;
    std::getline(std::cin, ar_stepSizes);

    std::vector<std::string> ar_steps = split_string(ar_stepSizes);
    std::vector<int> stepSizes;

    for (int ar_itr = 0; ar_itr < ar_steps.size(); ar_itr++) {
        int ar_item = stoi(ar_steps[ar_itr]);
        stepSizes.push_back(ar_item);
        std::cout << stepSizes[stepSizes.size()-1] << std::endl;
    }
    
    waysTOClimb(std::move(stepSizes),stairSize);
    
    return 0;
}
