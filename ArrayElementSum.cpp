//Given a list of numbers and a number k, return whether any two numbers from the list add up to k.
//For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
//Bonus: Can you do this in one pass?

#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_set>

template<class T>
bool findSum(const std::vector<T>& vec,const T& exp_sum)
{
	std::unordered_set<T> set;
	
	for(auto val:vec)
	{
		if(exp_sum < val) continue;
		auto diff = exp_sum - val;
		
		if(set.find(diff) != set.end())
			return true;
		else
			set.insert(val);	
	}
	return false;
}

int main()
{  
  	std::istringstream iss;    
        
    std::string numbers;
    std::getline(std::cin, numbers);
    iss.str(numbers);
    std::vector<int> vec{std::istream_iterator<int>(iss),
                     std::istream_iterator<int>()};
                     
    //auto print = [](const auto n) { std::cout << " " << n<<std::endl; };
    //std::for_each(vec.begin(),vec.end(),print);                 

	int exp_sum{0};
	std::cin >> exp_sum;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//std::cout << exp_sum <<std::endl;
	
	std::cout<< "Sum Available is: " << findSum(vec,exp_sum)<<std::endl;
	
	return 0;
}
