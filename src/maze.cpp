#include <iostream>
#include <vector>

/*
Maze: find a path from src to des, 0 indicates you can go through this point, 1 indicates wall, can not go through.
Algorithms implemented for Maze include:
1. find a path from one one point to another point
2. find all paths from one point to another point

DFS : Depth-first search (DFS) is an algorithm for searching/traversing along a path 
      from the start point as far as possible before backtracking.

For tree or graph data structures. DFS starts at the root (selecting some arbitrary node as the root in the case of a graph) and explores as far as possible along each branch before backtracking.
*/

class Maze
{
	public:
		struct Step
		{
			int x;
			int y;
				
			Step(int x, int y):x(x), y(y)
			{}
		};

	private:
		int m_maze[8][10];
		std::vector<Step> m_path; //store the paths from src to des

	public:
		//Maze(int a[8][10]):m_maze(a)
		Maze():m_maze {{1,1,1,1,1,1,1,1,1,1},{1,0,1,1,1,0,1,1,1,1},{1,0,0,1,0,1,1,1,1,1},{1,0,0,0,0,0,0,0,1,1},{1,0,1,0,0,0,1,1,1,1},{1,0,0,0,0,0,0,0,0,1},{1,    0,1,1,0,0,1,1,0,1},{1,1,1,1,1,1,1,1,1,1}}
		{
			for(auto i = 0; i < 8; i++)
			{
				std::cout<<"[ ";
				for(auto j = 0; j < 10; j++)
					std::cout<<m_maze[i][j]<<" ";
				std::cout<<"]"<<std::endl;	
			}
		}
	
	public:
		//public interfae: whether exist a path from [srcx, srcy] to [desx, desy]
		bool findPath(const Step src, const Step des)
		{
			if(!outOfBorder(src.x, src.y) || !outOfBorder(des.x, des.y))
				return false;

			m_path.push_back(src);     
			m_maze[src.x][src.y] = -1;  //-1 indicates this point has already been visited
			while(m_path.size()> 0)
			{	
				Step cur = m_path[m_path.size() - 1]; //get the top point from path stack
				if(cur.x == des.x && cur.y == des.y)  //already reach to the destination 
				{
					output();
					return true;
				}

				if(outOfBorder(cur.x, cur.y-1) && m_maze[cur.x][cur.y-1] == 0)
				{   
					m_path.push_back(Step(cur.x, cur.y-1));
					m_maze[cur.x][cur.y-1] = -1;
				}
				else  if(outOfBorder(cur.x+1, cur.y) && m_maze[cur.x+1][cur.y] == 0)
				{
					m_path.push_back(Step(cur.x+1, cur.y));
					m_maze[cur.x+1][cur.y] = -1;
				}
				else  if(outOfBorder(cur.x, cur.y+1) && m_maze[cur.x][cur.y+1] == 0)
				{
					m_path.push_back(Step(cur.x, cur.y+1));
					m_maze[cur.x][cur.y+1] = -1;
				}
				else  if(outOfBorder(cur.x-1, cur.y) && m_maze[cur.x-1][cur.y] == 0)
				{
					m_path.push_back(Step(cur.x-1, cur.y));
					m_maze[cur.x-1][cur.y] = -1;
				}
				else
				{
					m_path.erase(m_path.end() - 1); 
				}
			}

			return false;
		}	

		//Public Interface -- find all paths from des to des
		void findAllPath(Step cur, Step des)
		{
			if(!outOfBorder(cur.x, cur.y) || !outOfBorder(des.x, des.y))
				return;

			m_path.push_back(cur);
			m_maze[cur.x][cur.y] = -1;
			if(cur.x == des.x && cur.y == des.y) //find a path
			{
				output();
				m_path.erase(m_path.end() - 1); //backtraking 
				m_maze[cur.x][cur.y] = 0;     
				return;
			}

			//Try four different directions
			if(m_maze[cur.x][cur.y-1] == 0)
				findAllPath(Step(cur.x, cur.y-1), des);
	
			if(m_maze[cur.x+1][cur.y] == 0)
				findAllPath(Step(cur.x+1, cur.y), des);

			if(m_maze[cur.x][cur.y+1] == 0)
				findAllPath(Step(cur.x, cur.y+1), des);

			if(m_maze[cur.x-1][cur.y] == 0)
				findAllPath(Step(cur.x-1, cur.y), des);

			m_path.erase(m_path.end() - 1);
			m_maze[cur.x][cur.y] = 0;
		}

	protected:
		bool outOfBorder(const int x, const int y)
		{
			return (x>=0 && x<8 && y>=0 && y<10);
		}
		
		void output()
		{
			for(auto v: m_path)
				std::cout<<"["<<v.x<<", "<<v.y<<"]"<<std::endl;
		}
};

/*
Given an array of strings where "L" indicates land and "W" indicates water, and a coordinate marking a starting point in the middle of the ocean.

The Challenge:
Find and mark the ocean in the map by changing appropriate W's to O's. An ocean coordinate is defined to be any coordinate directly adjacent to any other ocean coordinate. 

Input: 10 x 20
 LLLLLLLWWLLLLLLLLLLL
 LLLLLLLLWWLLLLLLLLLL
 LLLLLLLLLWWWLLLLLLLL
 LLLLLLLLLLWWWWWWLLLL
 LLLLLLLLLLWWWWWWLLLL
 LLLLLLLLLLWWWWWWLLLL
 LLLLWWLLLLWWWWWWLLLL
 LLLLWWWLLLWWWWWWWWWW
 LLLLLWWWWWWWWWWWLLLL
 LLLLLLLLLLLLLLWWWWLL
*/
#define L 'L'
#define W 'W'

class Matrix
{
	private:
		const static int M = 12; //#row
		const static int N = 20; //#columns
		
		char m_matrix[M][N];    //2D array -- store the input 

	public:
		Matrix(char a[M][N])
		{
			for(auto i = 0; i < M; i++)
			{
				for(auto j = 0; j < N; j++)
				{
					m_matrix[i][j] = a[i][j];
				}
			}

			output();
		}

		void changeW2O(int x, int y)
		{
			if(x < 0 || x >= M || y < 0 || y >= N) //base case1: out of border
				return;

			if(m_matrix[x][y] == 'L' || m_matrix[x][y] == 'O') //base case2: land or ocean already
				return;

			m_matrix[x][y] = 'O'; //change W to O


			//Try 4 different directions
			changeW2O(x, y-1);
			changeW2O(x+1, y);
			changeW2O(x, y+1);
			changeW2O(x-1, y);
		}

		void output()
		{
			for(auto i = 0; i < M; i++)
			{
				for(auto j = 0; j < N; j++)
				{
					std::cout<<m_matrix[i][j]<<" ";
				}
				std::cout<<std::endl;
			}
		}
};

int main(int argc, char* argv[])
{
	Maze m;
	Maze::Step src(1, 1), des(6, 5);
	std::cout<<(m.findPath(src, des) == true ? "find a path" : "No path") <<std::endl;
	Maze m1;
	m1.findAllPath(src, des);

	char a[12][20] = {
	    {L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L},
   	 	{L,L,L,L,L,L,L,L,L,L,L,L,L,L,W,L,L,L,L,L},
    	{L,L,W,W,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L},
    	{L,L,W,W,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L},
    	{L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L,L},
    	{L,L,L,L,L,L,L,W,W,L,L,L,L,L,L,L,L,L,L,L},
    	{L,L,L,L,L,L,L,L,W,W,L,L,L,L,L,L,L,L,L,L},
    	{L,L,L,L,L,L,L,L,L,W,W,W,L,L,L,L,L,L,L,L},
    	{L,L,L,L,L,L,L,L,L,L,W,W,W,W,W,W,L,L,L,L},
    	{L,L,L,L,L,L,L,L,L,L,W,W,W,W,W,W,L,L,L,L},
   	 	{L,L,L,L,L,L,L,L,L,L,W,W,W,W,W,W,L,L,L,L},
    	{L,L,L,L,W,W,L,L,L,L,W,W,W,W,W,W,L,L,L,L}
  	};
	Matrix ma(a);
	ma.changeW2O(5,8);
	std::cout<<"After change W to O"<<std::endl;
	ma.output();
	return 0;
}

