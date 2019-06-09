//Given: A string of peranthesis and number digits etc.
//To Do: Remove mini number of brackets to get valid bracket sequence.
//Example: (a)())() should return [(a)()(), (a())()]
#include <set>
#include <queue>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

bool isBalanced(const string& str)
{
	int count=0;
	
	for(auto ch: str)
	{
		if(ch == '(')
			count++;
		else if(ch == ')')
			count--;
		
		if(count < 0) 
			return false;		
	}
	
	return count==0;
}

void getBalanced(const string& in, set<string>& out)
{
	int count = 0;
	int size = 0;//this is to check if we need to look into subStrings with more brackets removed or not.
	//If we got valid string with less brackets removed than don't look for combination with brackets removed further.
	queue<string> que;
	que.push(in);
	
	while(!que.empty())
	{
		string s = que.front();
		que.pop();

		if(size > s.size())
			return;
		
		if(out.find(s) != out.end()) 
			continue;
		
		if(isBalanced(s))
		{
			out.insert(s);
			count++;
			size = s.size();	
		}	
		else
		{
			for(int i=0; i < s.size(); i++)
			{
				if(s[i] == ')' || s[i] == '(')
				{
					string sub = s.substr(0,i) + s.substr(i+1,s.size());
					que.push(sub);
				}
				 
			}
		}
	}
	
	return;
}

int main()
{
	string input{"(a)())()"};
	set<string>	output;
	getBalanced(input,output);
	
	copy(output.begin(),output.end(),ostream_iterator<string>(cout, ","));
}
