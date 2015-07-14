#include <iostream>

/*
Trie Tree: a trie tree, also called prefix tree (as they can be searched by prefixes) or radix tree, 
           it is an ordered tree data structure that is used to store a dynamic set or associative array 
		   where the keys are usually strings.

Typical scenarios : 
1) words frequency statistics; 
2) Prefix matching; 
			 
In Trie, root node is associated with the empty string. All the child nodes/descendants 
of a node have a common prefix.Values are normally not associated with every node, only 
with leaves and some inner nodes that correspond to keys of interest.

Algorithms implemented for trie tree include:
1) insert a word into trie tree
2) search whether a word exists
3) get the count of common prefix
4) get the total number of words
*/


//Simple implementation
class TrieTree
{
	public:
		typedef int DATA;
		static const int SIZE = 26; 

	protected:
		class Node //represent a node in trie tree 
		{
			public:
				char nodeChar;     //the char for this node (a character)
				DATA value;        //here value is used to count #times of this key/char occured in words
				Node* child[SIZE]; //child nodes
				bool isEnd;             //used to indicate whether this node/key/char is the end of a word 
			public:
				Node()
				{
					value = 1;
					isEnd = false;
					for(auto i = 0; i < SIZE; i++)
						child[i] = nullptr;
				}      
		};

	private:
		Node* m_root;  //root node
		int m_count;   //record the total number of words in this tree

	public:
		TrieTree()
		{
			m_root =  new Node(); //root node is associated with an empty string
			m_count = 0;
		}

	public: //publc interface
		void insert(std::string word)
		{
			if(word.size() == 0)
				return;

			Node* cur = m_root;
			for(auto i = 0; i < word.size(); i++)
			{
				auto index = word[i] - 'a';
				if(cur->child[index] == nullptr)
				{
					Node* p = new Node();
					p->nodeChar = word[i];
					cur->child[index] = p;
				}
				else
				{
					cur->child[index]->value += 1;
				}

				cur = cur->child[index];
			}

			m_count++;
			cur->isEnd = true; 
		}

		bool search(std::string word)
		{
			if(word.size() == 0)
				return false;
			
			Node* cur = m_root;
			for(auto i = 0; i < word.size(); i++)
			{
				auto index = word[i] - 'a';
				if(cur->child[index] == nullptr)
					return false;
				
				cur = cur->child[index]; 
			}

			return cur->isEnd;
		}

		int getCommonPrefix(std::string prefix)
		{
			if(prefix.size() == 0)
				return -1;

			Node* cur = m_root;
			for(auto i = 0; i < prefix.size(); i++)
			{
				auto index = prefix[i] - 'a';
				if(cur->child[index] == nullptr)
					return 0;

				cur = cur->child[index];
			}

			return cur->value;
		}

		int count()
		{
			return m_count;
		}
};

int main(int argc, char* argv[])
{
	TrieTree* t = new TrieTree();
	std::string words[] = {"are", "what", "where", "which", "what", "who", "how", "a", "an", "arrest", "arrange", "ear"};
	for(auto i: words)
		t->insert(i);

	std::cout<<(t->search("what") == true ? "what exists" : "what does not exist")<<std::endl;
	std::cout<<(t->search("go") == true ? "go exists" : "go does not exist")<<std::endl;
	std::cout<<"Common Prefix a: "<<t->getCommonPrefix("a")<<std::endl;
	std::cout<<"Common Prefix an: "<<t->getCommonPrefix("an")<<std::endl;
	std::cout<<"Common Prefix wh: "<<t->getCommonPrefix("wh")<<std::endl;
	std::cout<<"Common Prefix w: "<<t->getCommonPrefix("w")<<std::endl;
	std::cout<<"Common Prefix you: "<<t->getCommonPrefix("you")<<std::endl;
	std::cout<<"Total words: "<<t->count()<<std::endl;

	delete t;
	return 0;
}
