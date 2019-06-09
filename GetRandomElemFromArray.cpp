//To pic random number from a list of elements, by choosong diif index every time {1,2,3,4,5,6,7,8,9,0} 
//#include <stdlib>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
	int length = 10;
	srand(unsigned(time(0))); //initialise random  no generator
	
	vector<int> v = {1,2,3,4,5,6,7,8,9,0,11,23,100,234,45,69,78,88,12};
	
	//this loop will print random elements from vector but not sure uinque or not
	//because its choosing again-2 from same set
	for(int i=0; i<length; i++)
	{
		int idx = rand()%(v.size());
		cout << v[idx] << endl;		
	}	
	
	cout << endl;
	//but this loop will print unique 5 numbers from vector
	//becuase we are not considering element again once selected
	for(int i=0; i<length; i++)
	{	
		int idx = rand()%(v.size()-i);//generate random number skipping elements at last of vector which are already printed and swapped
		//cout << "index: " << idx << "value " << v[idx] << endl;
		cout << v[idx] << endl;
		
		//swap printed element from end elemnts of vector
		v[idx] += v[v.size()-i-1];
		v[v.size()-i-1] = v[idx] - v[v.size()-i-1];  
		v[idx] =  v[idx] - v[v.size()-i-1];
		//cout << "v.size()-i-1: " << v.size()-i-1 << "value " << v[v.size()-i-1] << endl;
	}
	return 0; 
} 
