//A lot of frogs want to cross a river. 
//A river is w units width, but frogs can only jump l units long, where l<w. 
//Frogs can also jump on lengths shorter than l. but can't jump longer. 
//Hopefully, there are some stones in the river to help them.

//The stones are located at integer distances from the banks. 
//There are ai stones at the distance of i units from the bank the frogs are currently at. 
//Each stone can only be used once by one frog, after that it drowns in the water.

//What is the maximum number of frogs that can cross the river, given that then can only jump on the stones?

//Input
//The first line contains two integers w and l (1=l<w=105) — the width of the river and the maximum length of a frog's jump.

//The second line contains w-1 integers a1,a2,…,aw-1 (0=ai=104), where ai is the number of stones at the distance i from the bank the frogs are currently at.

//Output
//Print a single integer — the maximum number of frogs that can cross the river.
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

int calculateFrogs(const int width, const int jumpLen, const vector<int>& stones)
{
	int sum = 0;
	for(int i=0; i<jumpLen;i++)
	{
		sum += stones[i];
	}
	
	int minVal = sum;
	for(int i=jumpLen; i< width-1; i++)
	{
		sum = sum - stones[i-jumpLen] + stones[i];
		minVal = min(minVal,sum);
	}
	
	return minVal;
}

int main()
{
	istringstream iss1,iss2;       
    string widthNjump;
    getline(cin, widthNjump);
    iss1.str(widthNjump);
    vector<int> in1{istream_iterator<int>(iss1),
                     istream_iterator<int>()};
    int width = in1[0];
	int jumpLen = in1[1];
	
	string stones;
	getline(cin,stones);
	iss2.str(stones);
	vector<int> stoneArr{istream_iterator<int>(iss2),
                     istream_iterator<int>()};                 
    
    cout << "width: " << width <<endl;
    cout << "jump max length: " << jumpLen <<endl;
    copy(stoneArr.begin(),stoneArr.end(),ostream_iterator<int>(cout, " "));
    cout << endl;
    
	cout << "Count of frogs crossed river is: " << calculateFrogs(width,jumpLen,stoneArr) << endl;
	return 0;
}
