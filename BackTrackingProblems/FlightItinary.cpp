//Given an unordered list of flights taken by someone, 
//each represented as (origin, destination) pairs, and a starting airport, 
//compute the person's itineary. If no such itinerary exists, return null. All flights must be used in the itinerary.
//For example, given the following list of flights:
//HNL>AKL
//YUL>ORD
//ORD>SFO
//SFO>HNL
//and starting airport YUL, you should return YUL ? ORD ? SFO ? HNL ? AKL.
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <ios>       
#include <limits>

std::pair<std::string,std::string> split(std::string& line, char&& delimiter)
{
	std::vector<std::string> tokens;
	std::string tok;
	//intialise string stream with input string
	std::istringstream stream(line);
	
	while(std::getline(stream,tok,delimiter))
	{
		//get string from stream based on delimiter
		tokens.push_back(tok);
	}
	
	//return pair of airports
	return std::make_pair(tokens[0],tokens[1]);
}

//in each iteration or nested call of this function we are inserting one port in path and removing one lag from itinary
//Here we are using backtracking just for fun, 
//Simple solution is to just traverse through map once using start point and get desitnation and use it for next lookp in map
//Here we are adding one port and if not fits in itinary thna we remove it with subsequent unfit ports and start again with correct position
//This is not a good use case of back tracking
std::vector<std::string> printItineary(std::unordered_multimap<std::string,std::string> itineary,std::vector<std::string>& path)
{
	if(itineary.empty())
	{
		//if all of legs are covered than processing is done
		std::copy(path.begin(),path.end(),std::ostream_iterator<std::string>(std::cout,"->"));
		return path;
	}
	
	//check which leg in given filght plan starts from last inserted port
	std::string last_stop = path.back();
	for(auto itr = itineary.begin(); itr != itineary.end(); itr++)
	{
		//creat a temporary map excluding current leg which is under process
		//so that in next nested call we will not consider this leg again
		std::unordered_multimap<std::string,std::string> new_itineary(itineary);
		new_itineary.erase(itr->first);
		
		//insert current leg's destination and if src is same as last entry in path than
		//check next port in itinary in nested call
		path.push_back(itr->second);
		if(last_stop == itr->first)
		{
			printItineary(new_itineary,path);
		}
		//otherwise remove inserted port and try with next one.
		path.pop_back();
	}
	return {};//nullptr;
	//here each nested call have is own copy of itineary
}

int main()
{
	std::unordered_multimap<std::string,std::string> itineary;
	
	std::string startPt;
	std::cout << "Enter starting airport:"<<std::endl;
	std::cin >> startPt;
	
	//this is to ignore and remove last '\n' from input buffer
	//ignore all characters uptill '\n'
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
	
	std::cout << "Enter Itineary details:"<<std::endl;
	std::string line;
	//get pair of airports line by line
	while (std::getline(std::cin, line)) 
	{
		//to stop add empty line
		if (line.empty())
        	break;
        
        //insert airport in map with start point as key and destination as value
        //split leg with delimiter '>'
		std::pair<std::string,std::string> leg = split(line,'>');
		//itineary.emplace(split(line,'>'));
		itineary.insert(leg);	
	}
	for(auto& x : itineary)
	{
		std::cout << x.first << " " <<x.second <<std::endl;
	}
	
	//add start point and deduce itineary
	std::vector<std::string> path{startPt};
	printItineary(itineary,path);
	
	return 0;
}

