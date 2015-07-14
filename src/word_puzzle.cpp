#include <iostream>
#include <string>

/*
Word Puzzle
Given a word dictionary, a method to do lookup in dictionary and a M x N board where every cell has one character. 
Find all possible words that can be formed by a sequence of adjacent characters. Note that we can move to any of 8 
adjacent characters, but a word should not have multiple instances of same cell.

Example:
Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
       boggle[][]   = {{'G','I','Z'},
                       {'U','E','K'},
                       {'Q','S','E'}};
isWord(str): returns true if str is present in dictionary, else false.
Output:  Following words of dictionary are present
         GEEKS
         QUIZ

DFS Recursive solutions: 
1）consider every character as a starting character and find all words starting with it. 
2）All words starting from a character can be found using Depth First Traversal (DFS). 
We do depth first traversal starting from every cell. We keep track of visited cells to make sure 
that a cell is considered only once in a word.
3) for word dictionary, we can choose trie tree to store the words
*/

//Trie tree is used to store the words
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
				DATA value;        //here value is used to count #times of this key/char occured in word
				Node* child[SIZE]; //child nodes
				bool isEnd;        //used to indicate whether this node/key/char is the end of a word
			
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
					auto index = word[i] - 'A';
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
					auto index = word[i] - 'A';
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
					auto index = prefix[i] - 'A';
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

class WordPuzzle
{
	private:
		TrieTree* m_tree; //used to store words dictionary
		char m_letter[3][3];

	public:
		WordPuzzle(char a[3][3])
		{
			m_tree =  new TrieTree();

			for(auto i = 0; i < 3; i++)
				for(auto j = 0; j < 3; j++)
					m_letter[i][j] = a[i][j];
		}

	public:
		void addWord(std::string word)
		{
			m_tree->insert(word);
		}

		void findWords()
		{
			//used to indicate whether this position has been visited
			bool bVisited[3][3] = {{false,false,false},{false,false,false},{false,false,false}};
			std::string str; //store the words

			for(auto i = 0; i < 3; i++)
				for(auto j = 0; j < 3; j++)
					recursive(m_letter, m_tree, i, j, bVisited, str);
		}

	private:
		void recursive(char letter[3][3], TrieTree* t, int r, int c, bool bVisited[3][3], std::string& res)
		{
			if(r < 0 || r >= 3 || c < 0 || c >= 3) //base case1: out of border
				return;

			res.push_back(letter[r][c]);    //want this letter
			bVisited[r][c] = true;          //label visiting flag  

			if(t->search(res))  //find a word, print it
			{
				std::cout<<res<<std::endl;
			}
			else if(t->getCommonPrefix(res) == 0) //not word prefix, return directly
			{
				res.erase(res.end()-1);
				bVisited[r][c] = false;
				return;
			}

			//try 8 different directions
			recursive(letter, t, r-1, c, bVisited, res);
			recursive(letter, t, r-1, c+1, bVisited, res);
			recursive(letter, t, r, c+1, bVisited, res);
			recursive(letter, t, r+1, c+1, bVisited, res);
			recursive(letter, t, r+1, c, bVisited, res);
			recursive(letter, t, r+1, c-1, bVisited, res);
			recursive(letter, t, r, c-1, bVisited, res);
			recursive(letter, t, r-1, c-1, bVisited, res);
				
			res.erase(res.end()-1); //back tracking
			bVisited[r][c] = false;		  
		}
};

int main(int argc, char* argv[])
{
	char boggle[3][3] = {{'G','I','Z'},{'U','E','K'},{'Q','S','E'}};
	WordPuzzle w(boggle);
	std::string dictionary[4] = {"GEEKS", "FOR", "QUIZ", "GO"};	
	for(auto i: dictionary)
		w.addWord(i);
	w.findWords();
	return 0;
}
