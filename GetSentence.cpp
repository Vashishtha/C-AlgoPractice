//Given a dictionary of words and a string made up of those words (no spaces), 
//return the original sentence in a list. 
//If there is more than one possible reconstruction, return any of them. 
//If there is no possible reconstruction, then return null.

//For example, given the set of words 'quick', 'brown', 'the', 'fox', 
//and the string "thequickbrownfox", 
//you should return ['the', 'quick', 'brown', 'fox'].

//Given the set of words 'bed', 'bath', 'bedbath', 'and', 'beyond', 
//and the string "bedbathandbeyond", 
//return either ['bed', 'bath', 'and', 'beyond] or ['bedbath', 'and', 'beyond'].

#include <unordered_map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

bool isValidSentence(string sentence, const unordered_map<string,int>& word_map, vector<string>& result)
{
	if(sentence.empty())
	{
		return true;
	}
	
	for(auto itr = word_map.begin(); itr != word_map.end(); itr++)
	{
		auto strSize = itr->second;
		auto substr = sentence.substr(0,strSize);
		
		if(substr.compare(itr->first) == 0)
		{
			result.push_back(substr);
			sentence.erase(0,strSize);
			return isValidSentence(sentence,word_map,result);
		}
	}
	
	return false;
}


int main()
{
	vector<string> sentence = {"thequickbrownfox","bedbathandbeyond"};
	vector<vector<string>> word_set = {{"quick", "brown", "the", "fox"},{"bed", "bath", "bedbath", "and", "beyond"}};
	
	for(int i=0; i<sentence.size(); i++)
	{
		vector<string> result{};
		unordered_map<string,int> word_map;
		for(auto word : word_set[i])
		{
			word_map[word] = word.size();
		}
		
		if(isValidSentence(sentence[i],word_map,result))
		{
			copy(result.begin(), result.end(), ostream_iterator<string>(cout, " "));
			cout << endl;
		}
	}
	return 0;
}
