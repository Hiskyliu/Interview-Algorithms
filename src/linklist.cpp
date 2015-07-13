#include <iostream>
#include <map>

/*
Linked list: general operation time complexity is O(n)
algorithms implemented for linked list include:
1) insert/add a node
2) reverse a linked list (1->2->3 => 3->2->1)
3) copy the linked list with a random pointer without changing original list
4) reverse pair/two (1->2->3->4->5 => 2->1->4->3->5) 
5) find the Nth node from the end of the list
6) print
7) merge two sorted list into one sorted list 
*/

class LinkedList
{
	public:
		typedef int DATA;

	protected:
		class Node   //represent a node
		{	
			public:
				DATA data;
				Node* next;    //point to the next node
				Node* random;  //random pointer, point to random node
			public:
				Node(DATA d):data(d)
				{
					next = nullptr;
					random = nullptr;
				}
		};

	private:
		Node* m_head;   //Head node of the linked list
	
	public:
		LinkedList()
		{
			m_head = nullptr;
		}

	public: //Public Interface
		//Interface insert -- add a node to the end of the list	
		void insert(DATA value)
		{
			if(nullptr == m_head)
			{
				m_head = new Node(value);
				return;	
			}

			insert(m_head, value);
		}

		//Interface reverse a linked list
		void reverse()
		{
			m_head = reverse(m_head);
		}

		//Interface copy -- copy the Linked list with a random pointer and without changing original list
		Node* copy()
		{
			if(nullptr == m_head) //empty list
				return nullptr;

			return copy(m_head);
		}

		//Interface reverse pair -- 1->2->3->4->null => 2->1->4->3->null
		void reversePair()
		{
			m_head = reversePair(m_head);
		}

		//Interface find Nth node from the end of list -- 1 is the last node
		Node* findNth(int n)
		{
			if(nullptr == m_head)
				return nullptr;

			return findNth(m_head, n);
		}

		//Interface merge -- merge two sorted list to one sorted list
		void merge(Node* list)
		{
			m_head = merge(m_head, list);  //assume m_head and list are sorted lists
		}
	
		//Interface print
		void print()
		{
			if(nullptr == m_head)
				return;

			print(m_head);
		}

	private:
		void insert(Node* head, DATA value)
		{
			Node* cur = head;
			Node* pre = nullptr;

			while(cur)
			{
				pre = cur;
				cur = cur->next;
			}

			pre->next = new Node(value);
		}
		
		Node* reverse(Node* head)
		{
			//empty list or only one head node
			if(head == nullptr || head->next == nullptr)
				return head;

			Node* p1 = head;
			Node* p2 = head->next;
			Node* p3 = nullptr;

			while(p2)
			{
				p3 = p2->next;
				p2->next = p1;
				p1 = p2;
				p2 =p3;
			}

			head->next = nullptr;
			return p1;
		}

		Node* copy(Node* head)
		{
			std::map<Node*, Node*> m;  //key: ori list; value: new list	
			Node* cur = head; //head of original list
			while(cur) //generate a new list accrording to the oririnal list
			{
				Node* p = new Node(cur->data);
				m.insert(std::pair<Node*, Node*>(cur, p));
				cur = cur->next;
			}

			Node* new_head = m[head]; //key: ori head; value: new head 
			Node* new_cur = new_head; 
			cur = head;               
			while(cur)
			{
				new_cur->next = m[cur->next];
				new_cur->random = m[cur->random];
				
				cur = cur->next;
				new_cur = new_cur->next;
			}

			return new_head;
		}
		
		Node* reversePair(Node* head)
		{
			if(head == nullptr || head->next == nullptr)
				return head;

			Node* cur =  head;  //cur
			Node* next =  cur->next;  //cur->next
			Node* tmp = next->next;   //cur->next->next

			Node* new_head = reverseTwo(cur, next); //cur->next => next->cur and return next
			Node* p1 =  new_head->next;  

			while(nullptr != (cur = tmp)) //cur = cur->next->next || nullptr
			{
				next = cur->next; //cur->next
				if(next)
				{
					tmp = next->next;  //cur->next->next
					Node* p2 = reverseTwo(cur, next);
					p1->next = p2;
					p1 = p2->next;
				}
				else
				{
					tmp = nullptr;
					p1->next = cur;
				}
			}
		
			return new_head;
		}

		Node* reverseTwo(Node* first, Node* second)
		{
			second->next = first;
			first->next = nullptr;
			return second;
		}

		Node* findNth(Node* head, int n) //n = 1 is the last node
		{
			Node* first = head;
			Node* second = head;
			int count = 0;

			while(count < n)
			{
				second = second->next;
				count++;

				if(second == nullptr)
					break;
			}

			if(count != n) //n > list.length()
				return nullptr;

			while(second)
			{
				first = first->next;
				second = second->next;
			}

			return first;
		}

		Node* merge(Node* l1, Node* l2)
		{
			Node* fakeHead =  new Node(0); //fake head
			Node* cur = fakeHead->next;
			Node* first = l1;
			Node* second = l2;

			while(first && second)
			{
				if(first->data < second->data)
				{
					cur->data = first->data;
					first = first->next;
				}
				else
				{
					cur->data = second->data;
					second = second->next;
				}

				cur = cur->next;
			}
			
			if(first)
				cur->next = first;
		
			if(second)
				cur->next = second;

			cur = fakeHead->next;
			if(fakeHead)
				delete fakeHead;

			return cur;
		}

		void print(Node* head)
		{
			Node* cur = head;
			while(cur)
			{
				std::cout<<cur->data<<std::endl;
				cur = cur->next;
			}
		}
};


int main(int argc, char* argv[])
{
	int a[5] = {1,2,3,4,5};
	LinkedList l;

	for(auto i: a)
		l.insert(i);

	std::cout<<"Original list:"<<std::endl;
	l.print();
	l.reverse();
	std::cout<<"Reverse list:"<<std::endl;
	l.print();
	l.reverse();
	l.reversePair();
	std::cout<<"Reverse Pair list:"<<std::endl;
	l.print();
	std::cout<<"3th: "<<(l.findNth(3))->data<<std::endl;	
		
	return 0;
}
