//Birthday Choclate (Hacker Rank)

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

void print_probability(const int& len, 
                       const vector<int>& dates,
                       const vector<int>& day_month)
{
    int count{0};
    
    //for (auto it = dates.begin(); it != dates.end(); ++it)
    for (int i=0;i<len;i++)
    {
        int sum = 0;
        //int sum = accumulate(it,(it+day_month[1]));//accumulate was not working not sure why
        //if(sum == day_month[0])
        //{
        //    count++;
        //}
        for(int j=i;j<(day_month[1]+i);j++)
        {
            sum += dates[j];
        }
        if(sum == day_month[0])
        {
            count++;
        }
    }
    cout << count << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int Num_Squ{0};
    cin >> Num_Squ;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    istringstream iss;    
        
    string numbers;
    getline(cin, numbers);
    iss.str(numbers);
    vector<int> dates{istream_iterator<int>(iss),
                     istream_iterator<int>()};
    //std::copy(dates.begin(), dates.end(), std::ostream_iterator<int>(std::cout, " "));
    
    
    //string dob;
    //getline(cin, dob);
    //iss.str(dob);//cout << iss.str()<<endl;
    vector<int> day_month{istream_iterator<int>(cin),//here istringstream was not working not sure why
                          istream_iterator<int>()};
    //int val{0};iss >> val;cout << val; 
    //while(iss >> val)
    //{cout<< "in loop" <<endl;
    //    day_month.push_back(val);
    //}
    
    //cout << day_month.size() <<endl;
    //std::copy(day_month.begin(), day_month.end(), std::ostream_iterator<int>(std::cout, " "));
    
    print_probability(Num_Squ,dates,day_month);
    return 0;
}

