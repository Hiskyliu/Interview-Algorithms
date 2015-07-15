#include <iostream>
#include <vector>

/*
BST: binary search tree is a sorted tree. For the key of each node:
1) is larger than the key in its left subtree, and 
2) is smaller than the key in its right subtree.

algorithms implemented in this for BST includes:
1) insert (both recursive and non-recursive insertion solution)
2) search
3) display (both display in order and printing by layer)
4) destory/delete
5) convert a binary search tree to a doubly linked list
6) get the height of a bt/bst
7) check whether the bst is height-balanced
8) get the diameter of a bt/bst
9) check whether the bt/bst is a unival tree (all nodes have the same value)
10) find/get the kth smallest element/value
11) Reverse/Invert a bunary search tree or invert a binary tree

Diameter: It is the number of nodes on the longest path between two leaves in 
          the tree. note that there may be more than one path in each tree.

The diameter of a tree T is the largest value of the following quantities:
* the diameter of T’s left subtree
* the diameter of T’s right subtree
* the longest path between leaves that goes through the root of T 
  (this can be computed from the heights of the subtrees of T) 

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

		//Interface get the height of the tree
		int getHeight()
		{
			if(nullptr == m_root)
				return 0;
			
			return getHeight(m_root);
		}

		//Interface check whether the bst is height-balanced
		bool isBalanced()
		{
			if(nullptr == m_root)  //null tree is balanced tree
				return true;

			if(-1 == getAndCheckHeight(m_root)) //-1 not balanced
				return false;   
			else                                //else balanced
				return true;  
		}

		//Interface get the diameter of a bst
		int getDiameter()
		{
			if(nullptr == m_root)
				return 0;

			return getDiameter(m_root);
		}

		//Interface check whether the tree is a unival tree
		bool isUnival()
		{
			if(nullptr == m_root)
				return true;
			
			return (isUnival(m_root->left, m_root) && isUnival(m_root->right, m_root));
		}

		//Interface get the kth smallest value
		bool getKthSmallest(int k, DATA &data /*output*/) //k=1: the smallest value
		{
			if(nullptr == m_root)
				return false;
			
			int count = 0;
			bool bFound = false;
			getKthSmallest(m_root, k, count, data, bFound); //count: number of nodes which has been visited (inorder)
			return bFound;
		}

		//Interface invert a bst
		void invert()
		{
			if(nullptr == m_root)
				return;

			std::vector<Node*> vec;
			vec.push_back(m_root);
			int index = 0;
			while(index < vec.size())
			{
				Node* p = vec[index++];
				if(p->left)
					vec.push_back(p->left);
				if(p->right)
					vec.push_back(p->right);

				Node* tmp = p->left;
				p->left = p->right;
				p->right = tmp;
			}
		}

		//Interface invert a bst -- recursive solution
		void invertRecursive()
		{
			if(nullptr == m_root)
				return;

			invert(m_root);
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

		int getHeight(Node* root)
		{
			if(root == nullptr) //base case
				return 0;

			return 1 + max(getHeight(root->left), getHeight(root->right));
		}

		int max(int v1, int v2)
		{
			return v1 > v2 ? v1 : v2;
		}

		int getAndCheckHeight(Node* root)
		{
			if(root == nullptr) //base case
				return 0;

			int l_height = 0;
			int r_height = 0;

			l_height = getAndCheckHeight(root->left); //get left subtree's height
			if(-1 == l_height) //left subtree is not balanced, return directly
				return -1;

			r_height = getAndCheckHeight(root->right); //get right subtree's height
			if(-1 == r_height) //right subtree is not balanced, return directly
				return -1;

			if(abs(l_height - r_height) > 1) //the difference between left and right is larger than 1, not balanced
				return -1;

			return 1 + max(l_height, r_height);
		}

		int getDiameter(Node* root)
		{
			if(root == nullptr)  //base case: leafe's null node -- diameter is 0
				return 0;

			int l_diameter, r_diameter;
			int l_height, r_height;
			
			l_height = getHeight(root->left);
			r_height = getHeight(root->right);

			l_diameter = getDiameter(root->left);
			r_diameter = getDiameter(root->right);

			return  max(l_diameter, r_diameter, 1 + l_height + r_height);
		}

		bool isUnival(Node* p, Node* root)
		{
			if(p == nullptr)   //base case
				return true;

			if(p->data != root->data)
				return false;

			return (isUnival(p->left, root) && isUnival(p->right, root));
		}		

		int max(int v1, int v2, int v3)
		{
			int v = max(v1, v2);
			return max(v, v3);
		}

		//inorder: left->root->right to get the kth smallest value
		void getKthSmallest(Node* root, int k, int &count,  DATA &data, bool &bFound)
		{
			if(root == nullptr)  //base case
				return;
			
			getKthSmallest(root->left, k, count, data, bFound);
			
			count += 1;
			if(count == k)
			{
				data = root->data; //find it
				bFound = true;
				return;
			}

			getKthSmallest(root->right, k, count, data, bFound);
		}

		//Postorder left->right->root
		void invert(Node* root)
		{
			if(root == nullptr)
				return;
			
			if(root->left)
				invert(root->left);
			if(root->right)
				invert(root->right);
	
			Node* p = root->left;
			root->left = root->right;
			root->right = p;
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
	BSTree::DATA ret = -1;
	bool b = t.getKthSmallest(1, ret);
	std::cout<<(b == true ? "1th smallest value exist: " : "1th smallest value does not exist: ")<<ret<<std::endl;
	ret = -1;
	b = t.getKthSmallest(15, ret);
	std::cout<<(b == true ? "15th smallest value exist: " : "15th smallest value does not exist: ")<<ret<<std::endl;
	ret = -1;
	b = t.getKthSmallest(6, ret);
	std::cout<<(b == true ? "6th smallest value exist: " : "6th smallest value does not exist: ")<<ret<<std::endl;
	std::cout<<"Display by layer:"<<std::endl;
	t.displayByLayer();
	std::cout<<"Invert -- Display by layer:"<<std::endl;
	t.invert();
	t.displayByLayer();
	t.invertRecursive();
	std::cout<<"Recursively Invert -- Display by layer:"<<std::endl;
	t.displayByLayer();
	std::cout<<(t.search(11) == nullptr ? "11 Not found!" : "11 found")<<std::endl;
	std::cout<<(t.search(2) == nullptr ? "2 Not found!" : "2 found")<<std::endl;

	std::cout <<"Height = "<<t.getHeight()<<std::endl;
	std::cout <<"Diameter = "<<t.getDiameter()<<std::endl;
	std::cout <<(t.isBalanced() == true ? "Balanced tree" : "Not Balanced tree")<<std::endl;
	std::cout <<(t.isUnival() == true ? "Unival tree" : "Not Unival tree")<<std::endl;
	BSTree::NODE *p = t.convertBST2DoublyList();
	std::cout<<"Head node: "<<p->data<<"; end node: "<<p->left->data<<std::endl; 
//	t.destory();
	return 0;
}
