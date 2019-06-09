//You have an N by N board. 
//Write a function that returns the number of possible arrangements of the board where,
//N queens can be placed on the board without threatening each other, i.e. no two queens share the same row, column, or diagonal.
//for 1x1 its 1
//for 2x2 its 0
//for 3x3 its 0
//for 4x4 its 2
//for 5x5 its 10
//for 6x6 its 4
//for 7x7 its 40
//for 8x8 its 92
//for 9x9 its 352
//for 10x10 its 754
//____________________
//|  |. |  |  |  |  |
//--------------------
//|  |  |  |. |  |  |
//--------------------
//|. |  |  |  |  |  |
//--------------------
//|  |  |. |  |  |  |
//--------------------
//|  |  |  |  |  |  |
//--------------------
//|  |  |  |  |  |  |
//-------------------

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

//To check if newly inserted position is valid or not
//2 points(x1,y1) and (x2,y2) are in same line if x1 = x2 or y1 = y2
//or are digonally on same line if x1-x2 = y1-y2
bool isValid_position(const vector<int>& positions)
{
	//get current row and column
	int pos_col = positions[positions.size()-1];
	int pos_row = positions.size()-1;
	
	//loop through all positions of queen in board except last one
	for(int i=0; i<positions.size()-1; i++)
	{
		int col_diff  = abs(pos_col-positions[i]);
		int row_diff = abs(pos_row-i);
		if(col_diff == 0 || row_diff == 0 || (col_diff == row_diff))
		{
			//cout << "pos_row:" <<pos_row << " pos_col:" <<pos_col << " i"<<i<<" positions[i]"<<positions[i]<<endl;
			//queens intercepting each other so position not valid
			return false;
		}
		
	}
	return true;
}

//determine number of ways of position of N queens on NxN board.
//considering postions as an array with index as rows and entries as columns
//so that postions[1]=5 determines 5th coulmn in 1st row.
int n_queens(int n, vector<int>& positions)
{
	//base case when poistions found equal to dimenssion
	if (n == positions.size())
	{
		//print positions 
		copy(positions.begin(), positions.end(), ostream_iterator<int>(cout, " "));
		cout<<endl;
		return 1;//this is one of permutation so increase count by 1
	}
		
	int count = 0;
	
	//for each column
	for(int i=0; i < n; i++)
	{
		//insert column
		positions.push_back(i);
		//cout << "added column: " << positions[positions.size()-1] << "at row: " << positions.size()-1 <<endl;
		//If inserted position is valid as per exsisting queens position on board
		if(isValid_position(positions))	
		{
			//cout<< "position is valid"<<endl;
			//nested call with queen placed on board, Now try with remaining queens
			//count will start incrementing when all nested calls are resolved fo ever permutation by 1
			count +=n_queens(n,positions);
		}
		//cout << "removing column: " << positions[positions.size()-1] << "at row: " << positions.size()-1 <<endl;
		//remove above inserted column in 2 cases:
		//1. If inserted position is not valid as per last inserted poisitions
		//2. One permutation of position is done now this steps is a unwinding of nested call,
		//Now we will see next permutation as per loop.
		positions.pop_back();
				
	}	
	
	return count;
	//in this function every nested call have ist own copy of count and 
	//same copy of postions vector passed by refrence
 } 
 
 int main()
 {
 	//Here we are using backtracking instead of brut force 
 	//As we are inserting queens on board and if at some point we found combination is not valid
 	//we start removing them from last inserted postions till the point we started mistake and start again with new position
 	//This will take less time than brute force where time complexity is n^n.
 	for(int i=1; i<=10; i++)
 	{
 		vector<int> v;		cout << n_queens(i,v) <<endl;
		cout << "-----------------------"<<endl;	 
	}
 	return 0;
 }
