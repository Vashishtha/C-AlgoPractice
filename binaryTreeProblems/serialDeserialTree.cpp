//Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, 
//and deserialize(s), which deserializes the string back into the tree.
//For example, given the following Node class
//class Node:
//    def __init__(self, val, left=None, right=None):
//        self.val = val
//        self.left = left
//        self.right = right
#include <string>
#include <memory>


class Node
{
	public:
		string val;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		
		Node(string val)
		{
			*this.val = val;
			left = nullptr;
			right = nullptr;
		}
};


class Tree
{
	private:
		std::unique_ptr<Node> root;
		
		bool insert(string key, Node* leaf)
		{
			if (key < leaf->val)
			{
				if (leaf->left != nullptr)
					insert (key,leaf->left);
				else
					leaf->left = new Node(key);
				return true;	
			}
			else if(key >= leaf->val)
			{
				if(leaf->right != nullptr)
					insert(key,leaf->right);
				else
					leaf->right = new Node(key);	
				return true;	
			}
			
			return false;
		}
		
		//Here I am choosing pre-order because it will be easy to deserialize
		bool serialize(string& treeStr, Node* leaf)
		{
			if(leaf == nullptr)
			{
				//treeStr += ")";
				return true;
			}
			
			treeStr += (Node->val+")");
			serialize(treeStr,Node->left);
			serialize(treeStr,Node->right);
		}
				
	public:
		Tree():root(nullptr)
		{}
		Tree(string val)
		{
			root = new Node(val);
		}
		~Tree()
		{}
		
		bool insert(string key)
		{
			if(root != nullptr)
				return insert(key,root);
			else	
			{
				root = new Node(key);
				return true;
			}
		}
		

		//Fiel is better than string here
		//leaving in middle
		bool serialize(string& treeStr)
		{
			if(root == nullptr)
				return false;
			else
			{
				return serialize(treeStr,root);			
			}			
		}
		
		//root)left)left.left)right)
		void deSerialize(string& treeStr)
		{
			if(treeStr.empty())
				return;
				
			insert(treeStr.substr(0,treeStr.find(")")));	
			string subStr = treeStr.substr(find(")")+1,treeStr.size()-1);

			return;
		}			
};

