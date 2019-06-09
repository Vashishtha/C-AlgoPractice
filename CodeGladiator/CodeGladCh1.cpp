#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

bool fightPlyVill(const vector<int>& plyEnergy,const vector<int>& vilStrength)
{
	int itr = 0;
	for(; itr<plyEnergy.size(); itr++)
	{		
		if(plyEnergy[itr] > vilStrength[itr])
			continue;
		else
			break;	
	}
	
	return (itr==plyEnergy.size())?true:false;
}

int main()
{
	int testCases{0};
	int length{0};
	
	string villans;
	string players;
	
	cin >> testCases;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	while(testCases != 0)
	{
		istringstream iss1,iss2;
		cin >> length;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		
    	getline(cin, villans);
    	iss1.str(villans);
    	vector<int> vilStrength{istream_iterator<int>(iss1),
                     istream_iterator<int>()};
        if(vilStrength.size() > length)
        	vilStrength.erase(vilStrength.begin()+length,vilStrength.end());
		sort(vilStrength.begin(), vilStrength.end(), greater<int>());		
        
		getline(cin, players);
    	iss2.str(players);
    	vector<int> plyEnergy{istream_iterator<int>(iss2),
                     istream_iterator<int>()};
        if(plyEnergy.size() > length)
        	plyEnergy.erase(plyEnergy.begin()+length,plyEnergy.end());    
		sort(plyEnergy.begin(), plyEnergy.end(), greater<int>());	         
		
		//cout << "length: " << length <<endl;

		//cout << "villan: " << villans;
		//copy(vilStrength.begin(),vilStrength.end(),std::ostream_iterator<int>(std::cout, " "));
		//cout << endl;
		//cout << "player: " << players;
		//copy(plyEnergy.begin(),plyEnergy.end(),std::ostream_iterator<int>(std::cout, " "));
		//cout << endl;
		string result = fightPlyVill(plyEnergy,vilStrength)?"WIN":"LOSE";
		cout << result << endl;
		
		villans.clear();
		players.clear();			              
		testCases--;
	}
	
	return 0;
}
