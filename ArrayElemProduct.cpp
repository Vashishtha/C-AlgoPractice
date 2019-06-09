//Given an array of integers, return a new array such that 
//each element at index i of the new array is the product of all the numbers in the original array except the one at i.
//For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. 
//If our input was [3, 2, 1], the expected output would be [2, 3, 6].

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

template<typename T,typename c>
//T&& getMultiplication(T&& vec)
T getMultiplication(T&& vec)
{
	c product = 1;
	T vec1(vec.size(),0);
	
	vec1[0] = 1;
	for(auto i=1; i<vec.size(); ++i)
	{
		product = product*vec[i-1];
		vec1[i] = product;
		//std::cout<<i<<" " <<vec1[i]<<std::endl;
	}

	product = 1;
	vec1[vec.size()-1] = vec1[vec.size()-1]* product;
	for(int i=vec.size()-2; i>=0; --i)
	{
		product = product * vec[i+1];
		vec1[i] = product * vec1[i];
		//std::cout<<i<<" " <<vec1[i]<<std::endl;
	}

	return vec1;
//	return std::forward<T>(vec);
}

template<typename T>
void printContainer(const T& vec)
{
	auto print = [](const auto n) { std::cout << " " << n<<std::endl; };
    std::for_each(vec.begin(),vec.end(),print);
	   
    return;
}
     
    
int main()
{  
  	std::istringstream iss;    
        
    std::string numbers;
    std::getline(std::cin, numbers);
    iss.str(numbers);
    std::vector<int> vec{std::istream_iterator<int>(iss),
                     std::istream_iterator<int>()};
                     
    printContainer<std::vector<int>>(vec);            
	
	if(vec.size() > 0)
	{
		printContainer(getMultiplication<std::vector<int>,int>(std::move(vec)));
	}
	
	return 0;
}
