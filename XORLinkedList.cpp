//Implement XOR Linked List
//Its more memory efficient than normal doubly linked list.
//It hold a field named both, Which is XOR of nxt and prev node.
//implement add(element) --> To add element at end
//implement get(index) --> returns node at index
#include <memory>

class XORLList
{
	private:
		
		class Node
		{
			public:
				int val;
				Node* npXor;
		};	
		
		Node* head;
	public:
		XORLList():head(NULL)
		{}
		
		bool add(int val)
		{
			if(head == NULL)
			{
				head = new Node();//reset address pointed by unique_ptr delete old object
				head->val = val;
				head->npXor = (NULL ^ NULL);
			}
			else
			{
				auto ptr = head;//return raw pointer to managed object
				auto prev = NULL;
				auto nxt = (reinterpret_cast<long long int>(ptr->npXor) ^ prev);
				while(nxt != NULL)
				{
					prev = reinterpret_cast<long long int>(ptr);
					ptr = reinterpret_cast<Node>(nxt);
					nxt = (reinterpret_cast<long long int>(ptr->npXor) ^ prev);
				}
				
			}	
		}	
};
