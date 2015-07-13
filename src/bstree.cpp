#include <iostream>
#include <vector>

/*
BST: binary search tree is a sorted tree. For the key of each node:
1) is larger than the key in its left subtree, and
2) is smaller than the key in its right subtree.

General insert/search/ operations, time complexity: O(log(n))
*/

class BSTree
{
	public:
		typedef int DATA;
	protected:
		class Node //represent the ndde in tree
		{
			public:
				DATA data;
				Node* left;
				Node* right;
			public:
				Node(DATA d):data(d)
				{
					left = nullptr;
					right = nullptr;
				}
		};

	private:
		Node* m_root;  //root node

	public:
		typedef Node NODE;
		BSTree()
		{
			m_root = nullptr;
		}

	public: //public operation interfaces
		//Interface insert: recursive solution
		void insert(DATA key)
		{
			if(nullptr == m_root) //null tree
			{
				m_root =  new Node(key);
				return;
			}

			//non-null tree
			insert(m_root, key);
		}	
		
		//Interface search recursive solution
		Node* search(DATA key)
		{
			if(nullptr == m_root)
				return nullptr;

			return search(m_root, key);
		}

		//Interface display recursive solution -- inorder: left->root->right
		void display()
		{
			if(nullptr == m_root)
				return;

			display(m_root);
		}

		//Interface recursive destory solution -- inorder
		void destory()
		{
			if(nullptr == m_root)
				return ;

			destory(m_root);
		}

		//Interface insert non-recursive solution
		void insertNonRecursive(DATA key)
		{
			if(nullptr == m_root)
			{
				m_root = new Node(key);
				return;
			}

			Node* cur = m_root;
			Node* pre = nullptr;

			while(cur)
			{
				if(cur->data == key) //key already exists
				{
					return;
				}

				pre = cur;
				cur = cur->data > key ? cur->left : cur->right;
			}

			Node* p = new Node(key);
			if(pre->data > key)
				pre->left = p;
			else
				pre->right = p;
		}

		//Interface display nodes non-recursive solution
		void displayByLayer()
		{
			if(nullptr == m_root)
				return;

			std::vector<Node*> vec;
			vec.push_back(m_root);
			unsigned int index = 0;

			while(index < vec.size())
			{
				Node* p = vec[index++];
				std::cout<<p->data<<std::endl;

				if(p->left)
					vec.push_back(p->left);

				if(p->right)
					vec.push_back(p->right);
			}
		}

		//Interface convert bst to doubly linked list -- O(n)
		Node* convertBST2DoublyList()
		{
			if(nullptr == m_root)
				return nullptr;

			Node* head = nullptr; //head point to the head node of doubly list
			Node* pre = nullptr;; //pre pointer the previous node which is the previous smaller node

			convertBST2DoublyList(m_root, pre, head);
			return head;
		}	

	private:
		void insert(Node* root, DATA key)
		{
			if(root->data == key) //base case1: key exist, return directly
				return;

			if(root->data > key) //key should be inserted/existed in root's 
			{                    //left sub tree
				if(root->left == nullptr) //base case2: reach to leaf node, add it directly
				{
					root->left = new Node(key);
				}
				else
				{
					insert(root->left, key);
				}
			}
			else
			{
				if(root->right == nullptr)
				{
					root->right = new Node(key);
				}
				else
				{
					insert(root->right, key);
				}
			} 

		}

		Node* search(Node* root, DATA key)
		{
			if(root == nullptr) //base case1: key does not exist
				return nullptr;

			if(root->data == key) //base case2: key exist
				return root;
			else if(root->data > key)
				return search(root->left, key);
			else
				return search(root->right, key);
		}

		void display(Node* root)
		{
			if(root == nullptr) //base case: already reach to leaf's null sub node
				return;

			display(root->left);
			std::cout<<root->data<<std::endl;
			display(root->right);
		}

		void destory(Node* root)
		{
			if(root == nullptr) //base case
				return;

			destory(root->left);
			destory(root->right);

			delete root;
		}

		void convertBST2DoublyList(Node* root, Node* &pre, Node* &head) //reference to pointer
		{
			if(root == nullptr)  //base case: already reached to leaf
				return;

			convertBST2DoublyList(root->left, pre, head);

			root->left = pre; //current node's left point to previous node
			if(pre)
			{
				pre->right = root;  //previous node'right point to current node
			}
			else
			{
				head =  root;    //head point to the left-most leaf node
			}
 
			Node* right = root->right;
			head->left = root;   //head node'left always points to end node
			root->right = head;  //end node's right always points to head node
 
			pre = root;  //update pre which is the previous smaller node (not parent node)
			convertBST2DoublyList(right, pre, head);
		}
};


int main(int argc, char* argv[])
{
	BSTree t;
	int a[10] = {10, 6,4,8,7,15,16,11,14,35};
	for(auto v: a)
		t.insert(v);	

	std::cout<<"Display in order:"<<std::endl;
	t.display();
	std::cout<<"Display by layer:"<<std::endl;
	t.displayByLayer();
	std::cout<<(t.search(11) == nullptr ? "11 Not found!" : "11 found")<<std::endl;
	std::cout<<(t.search(2) == nullptr ? "2 Not found!" : "2 found")<<std::endl;

	BSTree::NODE *p = t.convertBST2DoublyList();
	std::cout<<"Head node: "<<p->data<<"; end node: "<<p->left->data<<std::endl; 
//	t.destory();
	return 0;
}
