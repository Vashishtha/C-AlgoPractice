//Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. Numbers can be 0 or negative.
//For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.
//include -- maximum sum including current element
//exclude -- maximum sum excluding current element
#include <vector>
#include <iostream>

int LargestSum(const std::vector<int>& vec)
{
	if (vec.empty() || (vec.size() < 3))
		return 0;
		
	int include = vec[0];
	int exclude = 0;
	int exc_new = 0;
	std::cout << "include = " << include << " exclude = " << exclude << std::endl;
	
	for(int i=1; i<vec.size(); i++)
	{
		exc_new = (include > exclude) ? include : exclude;
		include = exclude + vec[i];
		exclude = exc_new;
		std::cout << "include = prev_exc+curr value = " << include << " exclude = max(prev_inc,prev_exc) = " << exclude << std::endl;
	}
	std::cout << "final include = " << include << " final exclude = " << exclude << std::endl;
	
	return include > exclude ? include : exclude;
}

int main()
{
	std::vector<int> vec1{2,4,6,2,5};
	LargestSum(vec1);
	
	std::vector<int> vec2{5,1,1,5};
	LargestSum(vec2);
	
	std::vector<int> vec3{5,5,10,40,50,35};
	LargestSum(vec3);
	
	return 0;
}
