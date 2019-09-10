# ifndef _BINARY_TREE_
#define _BINARY_TREE_

//Currently this binary tree only support primitive datatype and string
//To use it with user defined type override << operator
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <list>

//template<typename T>
class Tree
{
	private:
		
		using NodeClass = class Node
		{
			public:
				std::string val;
				int id;
				std::unique_ptr<Node> left;
				std::unique_ptr<Node> right;
		
				Node(std::string val1,int val2):val(val1),left(nullptr),right(nullptr),id(val2)
				{
					//do nothing now
				}
		};
		
		std::unique_ptr<NodeClass> root;
		int id1, id2, count;
		
		bool insertValue(std::string key, NodeClass* leaf);
		Tree::NodeClass* copyTree(std::unique_ptr<NodeClass>&& dest, NodeClass* src);
		std::map<int,std::vector<std::string>> print;
		void printT(NodeClass* start=nullptr, int count=0);
		std::string updateNodeByGreaterSum(NodeClass* head);
		int iterate4Id(NodeClass* head);
		void prepareDeviationMap(std::unique_ptr<Tree::NodeClass>& head, int count, std::map<int,std::list<std::string>>& deviation);
		void prepareLevelMap(std::unique_ptr<Tree::NodeClass>& head, int count, std::map<int,std::list<std::string>>& levels);
		
		void deleteTree(std::unique_ptr<NodeClass>&& head)
		{
			if(head == nullptr)
				return;
			else
			{
				deleteTree(std::move(head->right));
				deleteTree(std::move(head->left));
				head.reset();
			}	
			return;
		}
		
	
	public:
		Tree();
		Tree& operator=(const Tree& rtTree);
		Tree(const Tree& rtTree);
		bool insert(std::string key);
		void printTree();
		//update each node by sum of all elements greater than it
		void updateNodeByGreaterSum();
		bool compareId(int id1, int id2);
		void printTopBottomView();
		void printLeftRightView();	
	
		~Tree()
		{
			//nothing to delete anythin with unique_ptr
			//delete(root;
		}
};

#endif //_BINARY_TREE_
