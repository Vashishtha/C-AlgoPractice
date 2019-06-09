//Divisible Pair Count

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

void find_Pairs(const int& devisor, const vector<int>& numbers)
{
    int pair_count{0};
    
    for(vector<int>::size_type i =0; i < numbers.size(); i++)
    {
        for(vector<int>::size_type j = i+1; j < numbers.size(); j++)
        {
            if((numbers[i]+numbers[j])%devisor == 0)
            {
                pair_count++;
            }
        }
    }
    cout << pair_count;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string num_dev;
    getline(cin,num_dev);
    
    istringstream iss(num_dev);
    int len,devisor;
    iss >> len;iss >> devisor;
    
    //string values;
    //getline(cin,values);
    //iss.str(values);// why istringstream not able to intialise vector again in second time
    //cout<<iss.str();
    vector<int> numbers{istream_iterator<int>(cin),
                     istream_iterator<int>()};
    //copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
    numbers.resize(len);
    
    find_Pairs(devisor,numbers);
    return 0;
}
