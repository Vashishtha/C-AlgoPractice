#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

class Node
{
	private:
		const string _name;
		const string _gender;
		unique_ptr<Node> _spouse_ptr;
		unordered_map<string,unique_ptr<Node> > _children;
		const Node* _parent;
		const bool _isRoot;
	public:
		Node(const string& name, const string& gender, bool isRoot = false):
		_name(name),
		_gender(gender),
		_parent(nullptr),
		_spouse_ptr(nullptr),
		_isRoot(isRoot)	
		{
			//cout << name << " Constructed " <<endl;
			//do nothing
		}
		
		~Node()
		{
			//cout << "distructor called for " << _name << endl;
			if(!_isRoot && _parent == nullptr)
				_spouse_ptr.release();
				//this is to avoid cycalic dependecy between spouce
				//release ownership of spouce when Node is not direct child hirarcy of head	
		}
		
		bool addSpouse(unique_ptr<Node>&& spouce)
		{
			bool retVal = false;
			if(_spouse_ptr == nullptr)
			{
				if(_gender != spouce->_gender)
				{
					spouce->_spouse_ptr.reset(this);
					_spouse_ptr = move(spouce);
					//cout << "Spouce " << _spouse_ptr->_name << " added to " << _name << endl;
					retVal = true;
				}
			}
			return retVal;
		}
		
		bool addChild(unique_ptr<Node>&& child)
		{
			bool retVal = false;
			
			if(_gender == "Female")
			{
				if(_children.find(child->_name) == _children.end())
				{
					child->_parent = this;
					//cout << "Child " << child->_name << " added to " << _name << endl;
					//emplace not working with geektrust
					//_children.emplace(make_pair(child->_name,move(child)));
					auto itr = _children.insert(make_pair(child->_name,move(child))).first;
					//cout << "Child " << itr->second->_name << " added to " << _name << endl;
					retVal = true;
				}
			}
			else if(_gender == "Male" && _spouse_ptr != nullptr)
			{
				retVal = _spouse_ptr->addChild(move(child));
			}
			
			return retVal;
		}

		string getGender() const 
		{
			return _gender;
		}
		
		//void setGender(string& gender)
		//{
		//	_gender = gender;
		//}
		
		string getName() const
		{
			return _name;
		}
		
		//void setName(string& name)
		//{
		//	_name = name;
		//}
		
		Node* getSpouse() const
		{
			return _spouse_ptr.get();
		}
		
		int getNoOfChild() const
		{
			return _children.size();
		}
		
		//geek trust not supporting c++14 so decltype used
		auto getChildrenBegin() const -> decltype(_children.begin())
		{
			return 	_children.begin();
		} 
		
		auto getChildrenEnd() const -> decltype(_children.end())
		{
			return 	_children.end();
		} 
		
		const Node* getParent() const
		{
			return _parent;
		}
		
};

class RelationShips
{
	protected:
		const string relation;
		bool _womens;
	public:
		RelationShips(string& relative):relation(relative)
		{
			
		}
		
		virtual const Node* getRelative(const Node* nodePtr) = 0;
		void printRelative(const Node* node)
		{  
		    int count = 0;
			if(node != nullptr && _womens)
			{
				for(auto itr = node->getChildrenBegin(); itr != node->getChildrenEnd(); itr++)
				{
					if(itr->second->getGender() == "Female")
					{
						count++;
						//cout << itr->first << " ";
					}
				}
			}
			else if(node != nullptr)
			{
				for(auto itr = node->getChildrenBegin(); itr != node->getChildrenEnd(); itr++)
				{
					if(itr->second->getGender() == "Male")
					{
						count++;
						//cout << itr->first << " ";
					}
				}
			}
			if(count == 0) cout << "NONE";
			cout << endl;
		}
};

class Parental : public RelationShips
{
	public:
		Parental(string& relative):RelationShips(relative)
		{
			if(relative.rfind("Aunt") != string::npos)
				_womens = true;
			else
				_womens = false;	
		}
		virtual const Node* getRelative(const Node* nodePtr)
		{
			return nodePtr->getParent();
		}
};

class Peternal : public Parental
{
	public:
		Peternal(string& relative):Parental(relative)
		{
			
		}
		const Node* getRelative(const Node* nodePtr)
		{
			auto node = Parental::getRelative(nodePtr);
			if(node != nullptr && node->getSpouse() != nullptr)
			{
				node = Parental::getRelative(node->getSpouse());
			    printRelative(node);	
				return node;
			}		
			return nullptr;	
		}	
};

class Meternal : public Parental
{
	public:
		Meternal(string& relative):Parental(relative)
		{
			
		}
		const Node* getRelative(const Node* nodePtr)
		{
			auto node = Parental::getRelative(nodePtr);
			if(node != nullptr)
			{
				node = Parental::getRelative(node->getSpouse());
			    Parental::printRelative(node);	
				return node;
			}
			return nullptr;	
		}	
};

class Child : public RelationShips
{
	public:
		Child(string& relative):RelationShips(relative)
		{
			if(relative == "Daughter")
				_womens = true;
			else
				_womens = false;	
		}	
		virtual const Node* getRelative(const Node* nodePtr)
		{
			if(nodePtr->getNoOfChild())
			{
				printRelative(nodePtr);
				return nodePtr;
			}
			return nullptr;
		}
};

class Sibling : public RelationShips
{
	public:
		Sibling(string& relative):RelationShips(relative)
		{
	
		}	
		virtual const Node* getRelative(const Node* nodePtr)
		{
			int count = 0;
			auto node = nodePtr->getParent();
			if(node != nullptr)
			{
				for(auto itr = node->getChildrenBegin(); itr != node->getChildrenEnd(); itr++)
				{
					count++;
					//cout << itr->first << " ";
				}
				if(count == 0) cout<<count;
				cout << endl;
				return node;
			}
			return nullptr;
		}
};

class InLaw : public RelationShips
{
	public:
		InLaw(string& relative):RelationShips(relative)
		{
			if(relative.find("Sister") != string::npos)
				_womens = true;
			else
				_womens = false;	
		}	
		virtual const Node* getRelative(const Node* nodePtr)
		{
			auto node = nodePtr->getSpouse() != nullptr ? nodePtr->getSpouse()->getParent() : nullptr;
			if(node != nullptr)
			{
				printRelative(node);
				return node;
			}
			return nullptr;
		}	
};

class RelationFactory
{
	public:
		static const Node* printRelationship(const Node* nPtr,string& relation)
		{
			RelationShips* relPtr = nullptr;

				if(relation == "Paternal-Uncle")
					relPtr = new Peternal(relation);
				else if(relation == "Maternal-Uncle")
					relPtr = new Meternal(relation);
				else if(relation == "Paternal-Aunt")
					relPtr = new Peternal(relation);
				else if(relation == "Maternal-Aunt")
					relPtr = new Meternal(relation);
				else if(relation == "Sister-In-Law")
					relPtr = new InLaw(relation);
				else if(relation == "Brother-In-Law")
					relPtr = new InLaw(relation);
				else if(relation == "Son")
					relPtr = new Child(relation);
				else if(relation == "Daughter")
					relPtr = new Child(relation);
				else if(relation == "Siblings")
					relPtr = new Sibling(relation);	
					
			auto nodePtr = relPtr->getRelative(nPtr);
			delete relPtr;
			return nodePtr;
		}
};

class FamilyTree
{
	unique_ptr<Node> _head;
	
	bool constructFamilyAsInput()
	{
		return add_child("Queen Anga","Chit","Male") &&
			add_spouse("Chit","Amba","Female") &&
				add_child("Amba","Dritha","Female") &&
					add_spouse("Dritha","Jaya","Male") &&
						add_child("Dritha","Yodhan","Male") &&
				add_child("Amba","Tritha","Female") &&
				add_child("Amba","Vritha","Male") &&
		add_child("Queen Anga","Ish","Male") &&
		add_child("Queen Anga","Vich","Male") &&
			add_spouse("Vich","Lika","Female") &&
				add_child("Lika","Vila","Female") &&
				add_child("Lika","Chika","Female") &&
		add_child("Queen Anga","Aras","Male") &&
			add_spouse("Aras","Chitra","Female") &&
				add_child("Chitra","Jnki","Female") &&
					add_spouse("Jnki","Arit","Male") &&
						add_child("Jnki","Laki","Male") &&
						add_child("Jnki","Lavanya","Female") &&
				add_child("Chitra","Ahit","Male") &&
		add_child("Queen Anga","Satya","Female") &&
			add_spouse("Satya","Vyan","Male") &&
				add_child("Satya","Asva","Male") &&
					add_spouse("Asva","Satvy","Female") &&
						add_child("Satvy","Vasa","Male") &&
				add_child("Satya","Vyas","Male") &&
					add_spouse("Vyas","Krpi","Female") &&
						add_child("Krpi","Kriya","Male") &&
						add_child("Krpi","Krithi","Female") &&
				add_child("Satya","Atya","Female");
	}
	
	Node* searchNode(Node* node,const string& name, bool addChild = false)
	{
		Node* resultPtr = nullptr;
		if(node == nullptr)
		{
			//cout << "searchNode nullptr passed" <<endl;
			return resultPtr;
		}
		else if(node->getName() == name)
		{
			if(addChild)
			{
				if(node->getGender() == "Female")
					resultPtr = node;
			}
			else
				resultPtr = node;
				
			//cout << "Nmae found in search Node for " << name << " gender " << 	node->getGender() << endl;
		}
		else if(node->getGender() == "Male")
		{
			//cout << "calling spouce because childs linked to womens for " << node->getName() << endl;
			resultPtr = searchNode(node->getSpouse(),name,addChild);
		}
		else
		{
			//cout << "total number of childs for women " << node->getNoOfChild() <<endl;
			auto childBeg = node->getChildrenBegin();
			while(childBeg != node->getChildrenEnd())
			{
				//cout << "calling searchNOde for child " << ((childBeg->second).get())->getName() << endl;
				resultPtr = searchNode((childBeg->second).get(),name,addChild);
				if(resultPtr != nullptr)
					break;
				childBeg++;
			}
		}
		
		return resultPtr;				
	}
	
	public:
		FamilyTree()
		{
			_head.reset(new Node("King Shan","Male",true));
			//make_unique is c++14 not supported by geektrust
			//if(_head->addSpouse(make_unique<Node>("Queen Anga","Female")))
			if(_head->addSpouse(unique_ptr<Node>(new Node("Queen Anga","Female"))))
			{
				if(constructFamilyAsInput()){
				}
					//cout << "----------Base family is prepared-------------" << endl;
				//else
					//cout << "----Got Error while constructing family1----" << endl;	
			}
			else
			{
				//cout << "----Got Error while constructing family----" << endl;
			}
		}
		
		bool add_child(const string& mother, const string& name, const string& gender)
		{
			Node* temp = searchNode(_head.get(),mother,true);
			if(temp == nullptr)
			{
				cout << "PERSON_NOT_FOUND" << endl;
			}
			//make_unique is c++14 not supported by geektrust
			//else if(temp != nullptr && temp->addChild(make_unique<Node>(name,gender)))
			else if(temp != nullptr && temp->addChild(unique_ptr<Node>(new Node(name,gender))))
			{
				cout << "CHILD_ADDITION_SUCCEEDED" << endl;
				return true;
			}
			else
			{
				cout << "CHILD_ADDITION_FAILED" << endl;
				return false;
			}
		}
		
		bool add_spouse(const string& spouse, const string& name, const string& gender)
		{
			Node* temp = searchNode(_head.get(),spouse);
			if(temp != nullptr && temp->addSpouse(unique_ptr<Node>(new Node(name,gender))))
			{
				//cout << "SPOUSE_ADDITION_SUCCEEDED" << endl;
				return true;
			}
			else
			{
				//cout << "SPOUSE_ADDITION_FAILED" << endl;	
				return false;
			}
		}

		void geRelationShip(const string& name, string& relation)
		{
			const Node* temp = searchNode(_head.get(),name);
			if(temp != nullptr)
			{
				if(RelationFactory::printRelationship(temp,relation) == nullptr)
					cout << "NONE" << endl;
			}
			else
			{
				cout << "PERSON_NOT_FOUND" << endl;
			}
		}
};

int main(int argc, char* argv[])
{
	std::ifstream infile;
	infile.open(argv[1],std::ifstream::in);
	string line;
	FamilyTree tree;
	//cout << string(argv[1]) <<endl;
	
	if(infile.is_open())
	{
		while (std::getline(infile, line))
		{
			//cout << line <<endl;
    		std::istringstream iss(line);
    		vector<string> command {istream_iterator<string>(iss), istream_iterator<string>()};
    		if(command[0] == "ADD_CHILD")
    		{
    			tree.add_child(command[1],command[2],command[3]);
			}
    		else if(command[0] == "GET_RELATIONSHIP")
    		{
    			tree.geRelationShip(command[1],command[2]);
			}
		}
		infile.close();
	}
	else
	{
		cout << "Error opening file"<<endl;
	}
	return 0;
}
