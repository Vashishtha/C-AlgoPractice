//Given an integer k and a string s, find the length of the longest substring that contains at most k distinct characters.
//For example, given s = "abcba" and k = 2, the longest substring with k distinct characters is "bcb".

#include <algorithm>
#include <map>
#include <iostream>
#include <string>

using namespace std;

//make a window on string and get largest sub-string with k diff caracters
int longestSubString(const string& s, const int k)
{
	int start = 0;//start of window
	int end = 0;//end of window
	map<char,int> charSet;//map to track diffrent caracters in window not exceed k
	charSet[s[start]]++;//start with first character
	
	for(int i=1; i < s.length(); i++)
	{
		end++;//increase end window
		charSet[s[i]]++;//add next character in array
		
		cout << "size of map is : " << charSet.size() << endl;
		if(charSet.size() > k) //check size of different characters in window 
		{
			charSet[s[start]]--;//remove first character from window if size of window increased limit
			if(charSet[s[start]] == 0)
				charSet.erase(s[start]);//if count of start char in map is 0 than remove it
			start++;//increase start of window	
			for_each(charSet.begin(),charSet.end(),[](auto pair){cout << pair.first << " " << pair.second << endl;});
		}
		cout << "start : " << start << " value : " << s[start] << endl;
		cout << "end : " << end << " value : " << s[end] << endl; 
	}
	
	if (charSet.size() >= k)
		return (end-start+1);//return window size if it covers all characters
	else
		return 0;	
}

int main()
{
	cout << "Enter a string:" << endl;
	string value = "";
	cin >> value;
	cout << "Enter size of substring:" << endl;
	int k = 0;
	cin >> k;
	
	cout << "Longest SubString length is: " << longestSubString(value,k);
	return 0;
}

