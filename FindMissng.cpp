//Given an array of integers, find the first missing positive integer in linear time and constant space. 
//In other words, find the lowest positive integer that does not exist in the array. 
//The array can contain duplicates and negative numbers as well.
//For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

template<typename T>
void printContainer(const T& vec)
{
	auto print = [](const auto n) { std::cout << " " << n<<std::endl; };
    std::for_each(vec.begin(),vec.end(),print);
	   
    return;
}

template<typename RandItr>
void swap(RandItr first, RandItr last)
{
	*first = *first + *last;
	*last = *first - *last;
	*first = *first - *last;
}

//Arrage each valid array value at proper index
//such that array index == array value
//if some index dosen't follow such rule it will be the missing number
int find_missing(std::vector<int>& vec)
{	
	for(int i=0; i<vec.size(); ++i)
	{
		if(0 < vec[i] 
		   && vec[i]-1 < vec.size()
		   && vec[i] != i+1
		   && vec[i] != vec[vec[i]-1])
		{
			swap<decltype(vec.begin())>(vec.begin()+i,vec.begin()+vec[i]-1);   
		}   
	}
	
	for(int i=0; i<vec.size(); ++i)
	{
		if(vec[i] >= 0 && vec[i] != i+1)
			return i+1;	
	}
	
	return vec.size()-1;
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
		std::cout << "Smallest missing +ve no is: "<<find_missing(vec) << std::endl;
	}
	
	return 0;
}
