//Segment Tree is used in cases where there are multiple range queries on array and modifications of elements of the same array. 
//For example, finding the sum of all the elements in an array from indices  to , or 
//finding the minimum (famously known as Range Minumum Query problem) of all the elements in an array from indices  to . 
//These problems can be easily solved with one of the most versatile data structures, Segment Tree.

//What is Segment Tree ?
//Segment Tree is a basically a binary tree used for storing the intervals or segments. 
//Each node in the Segment Tree represents an interval. Consider an array  of size  and a corresponding Segment Tree :

//The root of  will represent the whole array .
//Each leaf in the Segment Tree  will represent a single element  such that A[i] 0 <= i <= N-1.
//The internal nodes in the Segment Tree  represents the union of elementary intervals  where .

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

template<class T>
class SegmentTree
{
	private:
		vector<T> tree;
		vector<T> Array;
		
		void prepareTree(int node, int start, int end)
		{
			if(start==end)
			{
				tree[node] = Array[start];
				cout << "array node: " << node << "val: " << tree[node] << endl;
			}
			
			else
			{
				int new_node = node*2;
				int middle = (start+end)/2;
				
				prepareTree(new_node+1,start,middle);
				prepareTree(new_node+2,middle+1,end);
				
				tree[node] = tree[new_node+1] + tree[new_node+2];
				cout << "tree node: " << node << "val: " << tree[node] << endl;
			}	
		}
		
		void updateTree(int tNode, int aIdx, const T& val, int aStart, int aEnd)
		{
			if(aStart == aEnd)
			{
				Array[aIdx] += val;
				tree[tNode] += val;
			}
			else
			{
				int new_node = tNode*2;
				int middle = (aStart+aEnd)/2;
				
				if(aIdx <= middle && aIdx >= aStart)
				{
					updateTree(new_node+1,aIdx,val,aStart,middle);
				}
				else if(aIdx >= middle+1 && aIdx <= aEnd)
				{
					updateTree(new_node+2,aIdx,val,middle+1,aEnd);
				}
				tree[tNode] = tree[new_node+1] + tree[new_node+2];
			}
		}
		
		int findSum(int tNode, int rLeft, int rRight, int aStart, int aEnd)
		{
			if(rRight < aStart || rLeft > aEnd)
				return 0;
			else if(rRight >= aEnd && rLeft <= aStart)
				return tree[tNode];
			else
			{
				int new_node = tNode*2;
				int middle = (aStart+aEnd)/2;
				
				int p1 = findSum(new_node+1,rLeft,rRight,aStart,middle);
				int p2 = findSum(new_node+2,rLeft,rRight,middle+1,aEnd);
				
				return p1+p2;
			}		
		}
		
	public:
		SegmentTree(const vector<T>& array):Array(array)
		{
			tree.resize(2*Array.size()+1);
			prepareTree(0,0,Array.size()-1);
			copy(tree.begin(),tree.end(),ostream_iterator<T>(cout, " "));	
		}	
		
		void updateTree(int arrayIdx,const T& val)
		{
			updateTree(0,arrayIdx,val,0,Array.size()-1);
			copy(tree.begin(),tree.end(),ostream_iterator<T>(cout, " "));
		}
		
		int findSum(int left, int right)
		{
			return findSum(0,left,right,0,Array.size()-1);
		}
};

int main()
{
	vector<int> A1{0,1,0,0,1,1,0};
	vector<int> A2{2,10,56,-1,0,100};
	
    SegmentTree<int> seg1(A1);
    cout << endl;
	SegmentTree<int> seg2(A2);
	cout << endl;
	seg1.updateTree(0,1);
	cout << endl;
	seg2.updateTree(2,30);	
	cout << endl;
	cout << "seg1 seg sum is: " << seg1.findSum(1,4);
	cout << endl;
	cout << "seg2 seg sum is: " << seg2.findSum(1,4);
	
	return 0;
}
