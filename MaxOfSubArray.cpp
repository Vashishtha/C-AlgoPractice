//Given an array of integers and a number k, where 1 <= k <= length of the array, compute the maximum values of each subarray of length k.
//For example, given array = [10, 5, 2, 7, 8, 7] and k = 3, we should get: [10, 7, 8, 8], since:
//10 = max(10, 5, 2)
//7 = max(5, 2, 7)
//8 = max(2, 7, 8)
//8 = max(7, 8, 7)

#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void subStrMaxValue(vector<int>&& numbers, int subStrLen)
{
	vector<int> max_values;

	for(int i=0; (i+subStrLen) <= numbers.size(); i++)
	{
		//std::max_element return iterator to greates element in range
		auto result = max_element(numbers.begin()+i, numbers.begin()+i+subStrLen);
		max_values.push_back(*result);
	}

	cout << "Max values of all substrings are: " << endl;
	//std::copy copies from range defined by first and second perameter to output or 3rd perameter some other range 
	//variation std::copy_if checks some coondition on each value before copying
	copy(max_values.begin(), max_values.end(), ostream_iterator<int>(cout, " "));
}

int main()
{
	string line;
	vector<int> numbers;
	int subStrLen;

	cout<< "Get Input: " << endl;
	getline(cin, line);//get whole line from input stream cin
	istringstream stream(line);//input string stream object
	
	
	copy(istream_iterator<int> (stream),//iterator to the start of stream
	     istream_iterator<int> (),//this represents iterator to the end of stream
         back_inserter(numbers));//std::back_inserter gives a iterator to insert into target vector works like push_back

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << "Input Length of SubString: " << endl;
	cin >> subStrLen;

	subStrMaxValue(move(numbers), subStrLen);

	return 0;
}
