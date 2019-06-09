//Suppose we represent our file system by a string in the following manner:
//The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:
//dir
//    subdir1
//    subdir2
//        file.ext
//The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

//The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:
//dir
//    subdir1
//        file1.ext
//        subsubdir1
//    subdir2
//        subsubdir2
//            file2.ext
//The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

//We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, 
//the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).
//Given a string representing the file system in the above format, return the length of the longest absolute path to a file in the abstracted file system. 
//If there is no file in the system, return 0.
//Note:
//The name of a file contains at least a period and an extension.
//The name of a directory or sub-directory will not contain a period.

#include <string>
#include <map>
#include <iostream>

std::map<std::string,int> fileLevel;

auto tabCount = [](const std::string& fileName){ 
				int count = 0;
				for(auto c : fileName)
				{
					if(c == '\t')	
					count++;
				}
				return count;	
			};

void addLevel(std::string path)
{
	if(path.empty())
		return;
	
	std::string fileName = path.substr(0,path.find("\n"));
	if(fileName.find("."))
	{
		int count = tabCount(fileName);
		fileName = fileName.substr(count);
		std::cout << "File: "<< fileName << " Count: " << count << std::endl;					
		fileLevel[fileName] = count;	
	}
	
	if(path.find("\n") != std::string::npos)
	{
		path = path.substr(path.find("\n")+1);			
		addLevel(path);
	}
	
}
		
int main()
{
	addLevel("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
	std::cout << "----------------------------------------" << std::endl;
	addLevel("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
	std::cout << "----------------------------------------" << std::endl;
	addLevel("file.ext");
	
	return 0;	
}	
			

/*
//Program Note: Input string is in PreOrderFormate --> Root,Left,Right
class Node
{
	public:
		string _val;
		std::vector<std::unique_ptr<Node>> childs;
		
		Node(string val):_val(val)
		{}
};

class Tree
{
	private:
		std::unique_ptr<Node> root;
		
		void createTree(string val, std::unique_ptr<Node>& position)
		{
			std::vector<char> delimeter{'\n','\t'};
			
			if(!val.empty())
			{
				auto pos = val.find("\n");
				string subStr = val.substr(0,pos+1);
				
				if(position == nullptr)
				{
					position.reset(Node(subStr));
					val = val.substr(pos);
				}
					
			}			
		}
	public:

		Tree(string val):root(nullptr)
		{
			createTree(val,root);
		}
		~Tree()
		{}	
		
};
*/


