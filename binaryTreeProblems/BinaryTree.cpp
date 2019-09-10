#include "BinaryTree.hpp"
#include <iostream>
#include <list>

//template<typename T>
bool Tree::insertValue(std::string key, Tree::NodeClass* leaf)
{
	if(key < leaf->val)
	{
		if(leaf->left != nullptr)
			return insertValue(key,(leaf->left).get());
		else
			{leaf->left.reset(new Tree::NodeClass(key,count));	count++;}
		return true;	
	}
	else if(key >= leaf->val)
	{
		if(leaf->right != nullptr)
			return insertValue(key,(leaf->right).get());
		else
			{leaf->right.reset(new Tree::NodeClass(key,count));  count++;}	
		return true;
	}
	else
		return false;	
}

//template<typename T>
Tree::NodeClass* Tree::copyTree(std::unique_ptr<Tree::NodeClass>&& dest, NodeClass* src)
{
	if(src == nullptr)
		return nullptr;
	else
	{
		dest.reset(new Tree::NodeClass(src->val,src->id));
		dest->left = nullptr;
		dest->right = nullptr;	
		dest->right.reset(copyTree(move(dest->right),src->right.get()));
		dest->left.reset(copyTree(move(dest->left),src->left.get()));
	}	
	
	return dest.release();//releasing because local unique_ptr will be deleted after func finished
}

//template<typename T>
Tree::Tree():root(nullptr),count(0)
{

}

//template<typename T>
Tree& Tree::operator=(const Tree& rtTree)
{
	this->root.reset(copyTree(move(this->root), rtTree.root.get()));
	return *this;
}

//template<typename T>
Tree::Tree(const Tree& rtTree)
{
	this->root.reset(copyTree(move(this->root), rtTree.root.get()));
}

//template<typename T>
bool Tree::insert(std::string key)
{
	if(root != nullptr)
		return insertValue(key,root.get());
	else	
	{
		root.reset(new Tree::NodeClass(key,count));
		count++;
		return true;
	}
}

void Tree::printTree()
{
	print.clear();
	printT(root.get());
	for(auto itr = print.begin(); itr != print.end(); itr++)
	{
		for(auto val : itr->second)
			std::cout << val << " ";
		std::cout <<std::endl;
	}
}

//print whole tree nodes in decreasing order
//template<typename T>
void Tree::printT(Tree::NodeClass* start,int count)
{
	if(start == nullptr)
		return;
	else
	{
		printT(start->left.get(),count+1);
		print[count].push_back(start->val);
		printT(start->right.get(),count+1);		
	}	
	return;
}

//update each node by sum of all elements greater than it
//right most child will be updated to empty as nothing bigger than that
//parent node will be = rt child node value
//left node will be = parentNode + parent's right child value
//return result of left child's traversal if not empty otherwise sum of parent and right child value
//left child's result required because it contain all the sum required for parent of parent node  
std::string Tree::updateNodeByGreaterSum(Tree::NodeClass* head)
{
	if(head == nullptr)
		return "";
	else
	{
		std::string rtVal = updateNodeByGreaterSum(head->right.get());
		std::string nodeVal = head->val;
		head->val = rtVal;
		std::string lftval = "";
		
		if(head->left != nullptr)
		{
			head->left->val += rtVal + nodeVal;
			lftval = updateNodeByGreaterSum(head->left.get());
			head->left->val += rtVal + nodeVal;
		}
		
		
		return lftval != "" ? lftval : rtVal + nodeVal;
	}	
}

void Tree::updateNodeByGreaterSum()
{
	updateNodeByGreaterSum(root.get());
}

//We are starting search from right most node here
//If right node is Null than check node for Id and return result if found something
//If not than it it means right and parent are searched already and check in left sub tree
//return whatever found at left sub tree, This value dosen't used to derive something
//Because we already looked at parent value
int Tree::iterate4Id(Tree::NodeClass* head)
{
	if(head == nullptr)
		return 0;
	else
	{
		int retVal = iterate4Id(head->right.get());
		
		if(retVal==0 && head->id == id1)
			return 1;
		else if(retVal ==0 && head->id == id2)
			return 2;
		else if(retVal == 0)
			return iterate4Id(head->left.get());	
		else
			return retVal;
	}	
}

//suppose each node in tree have one id assosiated with it,
//Tree's structure dosen't depend upon node id but node values
//given such 2 ids in tree find out, 
//If node value of left id is greater than node value of right id or not 
bool Tree::compareId(int id1, int id2)
{
	this->id1 = id1;
	this->id2 = id2;
	int retVal = iterate4Id(root.get());
	
	if(retVal == 1)
		return true;
	else
		return false;	
}

void Tree::prepareDeviationMap(std::unique_ptr<Tree::NodeClass>& head, int count, std::map<int,std::list<std::string>>& deviation)
{
	if(head == nullptr)
		return;
	else
	{
		deviation[count].push_back(head->val);
		prepareDeviationMap(head->left,count-1,deviation);
		prepareDeviationMap(head->right,count+1,deviation);
	}	
	return;	
}

//use map of deviation from center to vector to hold each node at perticular deviation
void Tree::printTopBottomView()
{
	std::map<int,std::list<std::string>> deviation;
	prepareDeviationMap(root,0,deviation);
	
	//print top
	std::cout << "top___: " <<std::endl;
	for(auto itr : deviation)
	{
		std::cout << *(itr.second.begin()) << " ";
	}
	std::cout << std::endl;
	
	//print bottom
	std::cout << "bottom___: " <<std::endl;
	for(auto itr : deviation)
	{
		std::cout << *(itr.second.rbegin()) << " ";
	}
	std::cout << std::endl;
}

void Tree::prepareLevelMap(std::unique_ptr<Tree::NodeClass>& head, int count, std::map<int,std::list<std::string>>& levels)
{
	if(head == nullptr)
		return;
	else
	{
		levels[count].push_back(head->val);
		prepareLevelMap(head->left,count+1,levels);
		prepareLevelMap(head->right,count+1,levels);
	}	
	return;	
}

//use map of each level of tree to all nodes at perticular level
void Tree::printLeftRightView()
{
	std::map<int,std::list<std::string>> levels;
	prepareLevelMap(root,0,levels);
	
	//print left
	std::cout << "left___: " <<std::endl;
	for(auto itr : levels)
	{
		std::cout << itr.first<<" " <<*(itr.second.begin()) << std::endl;
	}
	std::cout << std::endl;
	
	//print right
	std::cout << "right___: " <<std::endl;
	for(auto itr : levels)
	{
		std::cout << itr.first<<" " <<*(itr.second.rbegin()) << std::endl;
	}
	std::cout << std::endl;	
}

