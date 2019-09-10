#include "BinaryTree.hpp"
#include <iostream>

using namespace std;

int main()
{
	Tree tree1;
	tree1.insert("a");
	tree1.insert("b");
	tree1.insert("a2");
	tree1.insert("a1");
	tree1.insert("b1");
	tree1.insert("A");
	Tree tree2 = tree1;
	tree2.printTree();
	tree1.updateNodeByGreaterSum();
	tree1.printTree();
	if(tree2.compareId(2,5))
		cout <<"a2 is greater than A chk1" << endl;
	if(!tree2.compareId(5,2))
		cout <<"a2 is greater than A chk2" << endl;	
	if(tree2.compareId(4,2))
		cout <<"a2 is less than b1 chk2" << endl;	
		
	tree2.printLeftRightView();
	tree2.printTopBottomView();	
///////////////////////////////////////////////////////////////////
	std::unique_ptr<std::string> s_p = std::make_unique<std::string>("abc");//nullptr;
    std::string *s = s_p.get();
    *s = "Abhinab";
    cout << *s << *s_p << '\n';
	return 0;
}
