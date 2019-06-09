// __________________
// _______________  |
//|_____   _________|
//|	  ______________|
//|______	  ______|
//|_______________  |	
//Find path from start to end in puzzle
#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <unordered_set>

using namespace std;

class Maze
{
	private:
		const int START;
		const int END;
		vector<list<int>> maze;
	
	protected:	
		virtual void define_maze()
		{
			maze.resize(9);
			//prepare maze with each vector entry as position in maze
			//each vector entry is list of adjecent positions
			maze[0].push_back(1);
			maze[0].push_back(3);
			maze[1].push_back(0);
			maze[1].push_back(2);
			maze[2].push_back(1);
			maze[3].push_back(0);
			maze[3].push_back(4);
			maze[3].push_back(6);
			maze[4].push_back(3);
			maze[4].push_back(5);
			maze[4].push_back(7);
			maze[5].push_back(4);
			maze[6].push_back(3);
			maze[7].push_back(4);
			maze[7].push_back(8);
			maze[8].push_back(7);
			
			return;
		}
		
		//we are using backtracking here, add entry and keep track if visted
		//remove entry if not leading to right direction based on visited set
		virtual vector<int> traverse_maze(vector<int> path, unordered_set<int>& visited)
		{
			if(END == path.back())// || visited.size() == maze.size())
			{
				//if reached at end than we are done print path
				//cout<< "visited size " << visited.size() << "end :" <<END<< "path.back :" <<path.back()<< endl;
				copy(path.begin(),path.end(),ostream_iterator<int>(cout,"->"));
				return path;
		    }
			
			//take last entry added in path and check all adjesent positions	
			int current = path.back();
			for(auto itr = maze[current].begin(); itr != maze[current].end(); itr++)
			{
					//cout << "path: " <<endl;
					//copy(path.begin(),path.end(),ostream_iterator<int>(cout,"->"));
					//cout << endl;
					//cout << "visted: " <<endl;
					//copy(visited.begin(),visited.end(),ostream_iterator<int>(cout,"->"));
					//cout << endl;
					//cout << "value: " << *itr << endl;
				
				//if position is not yet visited than add in path and add next entry in path in next nested call
				path.push_back(*itr);
				if(visited.find(*itr) == visited.end())
				{
					//cout <<"recrsive call " <<endl;
					//mark position as visited to not consider it again
					visited.insert(*itr);
					traverse_maze(path,visited);
				}
				//if position is already visited or entry is wrong as not leading to destination based on nested call than remove it.
				path.pop_back();
			} 
			
			return {};	
		}
		
	public:
		//by deault 3*3 map
		Maze():START(0),END(8)
		{
			define_maze();	
		}
		
		virtual vector<int> find_path()
		{
			vector<int> path;//path to deduce
			unordered_set<int> visited;//visited positions to never consider same position again
			path.push_back(START);
			visited.insert(START);

			return traverse_maze(path,visited);
		}	
};

int main()
{
	Maze maze1;
	maze1.find_path();
	
	return 0;
}
