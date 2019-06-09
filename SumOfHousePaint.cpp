//A builder is looking to build a row of N houses that can be of K different colors. 
//He has a goal of minimizing cost while ensuring that no two neighboring houses are of the same color.

//Given an N by K matrix where the nth row and kth column represents the cost to build the nth house with kth color, 
//return the minimum cost which achieves this goal.
#include <iostream>

using namespace std;

int main()
{
	int N,K;
	cout << "Enter number of house." <<endl;
	cin >> N;
	cout << "Enter no. of colours." <<endl;
	cin >> K;
	
	int sum = 0;
	for(int i=1; i<= N; i++)
	{
		sum += ((i%K)> 0 ? (i%K) : K);
	}
	cout << "Total cost of paint is: " << sum << endl; 
	
	return 0;
}
