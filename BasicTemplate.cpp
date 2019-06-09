#include <iostream>
#include <vector>
#include <array>
#include <utility>

template<typename T,typename I>
decltype(auto) func_ret(T&& arg,I i)// -> decltype(arg[i])
{
	std::cout<<arg[i]<<std::endl;
	//return std::forward<decltype(arg[i])>(arg[i]);
	//return arg[i];
	return std::forward<T>(arg)[i];
}

template<typename T,std::size_t N>
constexpr decltype(auto) array_size(T (&) [N]) noexcept
{
	return N;
}


int main()
{
  int b =5;	
  //constexpr auto a = b;
  const auto a = b;
  std::cout << "Test +14 compiler" << a <<std::endl;

  std::vector<int> v(10,4);
  func_ret(v,2) = 5;
  
  //char* s = func_ret(v,2);  This to know return type from function by compilation error
  
  int values[] = {1,2,3,4,5,6,7,8,9};
  std::cout << array_size(values) << std::endl;
  //std::array<int,a> arr1;
  std::array<int,array_size(values)> arr2;
  
  auto x5{1,2,3};
  return 0;
}

