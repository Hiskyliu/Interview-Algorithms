#include <iostream>
#include <string>

/*
Dynamic Programming: the key is to find the State Transition Function (STF).
1). Coins problem: Given a list/array of coins, and their values (V1, V2, ... , VN),find the minimum number of coins, the sum of which is S.
d[i]: the minimun number of coins the sum of which is i, so d[0] = 0;
coins[j]: the value of coin j.
STF: d[i] = min(d[i-coins[j]] + 1), a[j]<=i; d[i]: the minimun number of coins the sum of which is i;

2). Longest Increasing Subsequence (LIS) problem: The longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. For example, length of LIS for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}. 
d[i]: LIS for sequence a[0], a[1], ..., a[i] 
STF: d[i] = max(d[j] + 1, 1); 0<=j<i and a[j] < a[i]

3). Maximum sum of non consecutive elements: given an array, find the maximum sum of a subsequence with the constraint that no 2 numbers in the sequence should be adjacent in the array. So 3 2 7 10 should return 13 (sum of 3 and 10) or 3 2 5 10 7 should return 15 (sum of 3, 5 and 7).
d[i]: Maximum sum of subsequence end of a[i].
STF: d[i] = max(d[i-1], d[i-2] + 1), 2<=i<n

4). Maximum sum contiguous subsequence: find a contiguous subseqnence (A[i], A[i+1], …, A[j]) such that the sum of the elements in that subsequence is maximized. (Note that, in general, there may be more than one such optimal subsequence.).
d[i]:  Maximum sum contiguous subsequence a[0],a[1], ..., a[i]
d[i] = max(d[i-1], end[i]), 1<=i<n

end[i]: the maximun sum contiguous subsequence end of a[i]
end[i] = max(end[i-1] + a[i], a[i])

5). Longest common subsequence (LCS):  Given two sequences, find the length of longest subsequence present in both of them. A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are subsequences of “abcdefg”. So a string of length n has 2^n different possible subsequences.
LCS[i][j]: LCS of sequence Ai(a1, a2 ... ai) and Bj(b1, b2 ... bj)
               =0, i = 0 or j = 0
STF: LCS[i][j] = LCS[i-1][j-1] + 1, if a[i] = b[j]
			   max(LCS[i-1][j], LCS[i][j-1]), if a[i] != b[j]				
*/

class Dp
{
	private:
		static const int MAX = 65535353;
		static const int MIN = -65535;
	public:
		//coins: d[i] = min(d[i-coins[j]] + 1), coins[j] <= i
		static int getMinimumCoins(int coins[]/*input coins array*/, int len/*array len*/, int s/*input sum*/)
		{
			if(s < 0)
				return -1;

			int* min =  new int[s+1]; //min[i] is the d[i]
			min[0] = 0;

			for(int i = 1; i <=s; i++)
			{
				int min_coins = MAX;  //initial value for min_coins
				for(int j = 0; j < len; j++)
				{
					if((coins[j] <= i) && (min[i-coins[j]] + 1 < min_coins))
						min_coins = min[i-coins[j]] + 1;
				}

				min[i] = min_coins;
			}	

			int num = min[s];
			for(auto i = 0; i <= s; i++)
				std::cout<<"Sum: "<<i<<"; min number of coins: "<<min[i]<<std::endl;

			delete[] min;
			return num;
		}

		//Longest Increasing Sequence (LIS) d[i] = max(1, d[j] + 1), 0<=j<i and a[j] < a[i]
		static int getLIS(int a[], int len)
		{
			if(a == nullptr)
				return -1;
			if(len == 1)
				return 1;

			int max_len = MIN; // LIS
			int* lis = new int[len];
			for(int i = 0; i < len; i++)
			{
				lis[i] = 1;
				for(int j = 0; j < i; j++)
				{
					if(a[j] < a[i])
					{
						if(lis[j] + 1 > lis[i])
							lis[i] = lis[j] + 1;
					}
				}
				
				if(lis[i] > max_len)
					max_len = lis[i];
			}

			for(auto i = 0; i < len; i++)
				std::cout<<"LIS end of index "<<i<<" is: "<<lis[i]<<std::endl;

			delete[] lis;
			return max_len;
		}

		//Maximum sum of non consecutive elements d[i] = max(d[i-1], d[i-2] + a[i])
		static int getMaxSubSequence(int a[], int len)
		{
			if(len == 1)
				return a[0];
			if(len == 2)
				return a[0] > a[1] ? a[0] : a[1];

			int* mss =  new int[len];
			mss[0] = a[0];
			mss[1] = a[0] > a[1] ? a[0] : a[1];
			
			int max_sum = mss[0] > mss[1] ? mss[0] : mss[1];
			for(auto i = 2; i < len; i++)
			{
				if(mss[i-1] > mss[i-2] + a[i])
					mss[i] = mss[i-1];
				else
					mss[i] = mss[i-2] + a[i]; 

				if(mss[i] > max_sum)
					max_sum = mss[i];
			}

			for(auto i = 0; i < len; i++)
				std::cout<<"Maximum sum non-consective end of index "<<i<<" is: "<<mss[i]<<std::endl;
		
			delete[] mss;
			return max_sum;
		}
		
		//Maximum sum of continguous elements d[i] = max(d[i-1], end[i]), end[i] = max(end[i-1]+a[i], a[i]), 1<=i
		static int getMaxSumContinguousSequence(int a[], int len)
		{
			if(len == 1)
				return a[0];

			int* mcs =  new int[len];
			int* end = new int[len];

			mcs[0] = end[0] = a[0];
			int max_sum = mcs[0];
			for(auto i = 1; i < len; i++)
			{
				if(end[i-1] + a[i] > a[i])
					end[i] = end[i-1] + a[i];
				else
					end[i] = a[i];

				if(mcs[i-1] > end[i])
					mcs[i] = mcs[i-1];
				else
					mcs[i] = end[i];

				if(mcs[i] > max_sum)
					max_sum = mcs[i];
			}

			for(int i = 0; i < len; i++)
			{
				std::cout<<"Maximum sum consective end of index "<<i<<" is: "<<mcs[i]<<std::endl;
				std::cout<<"Maximum sum consective end of a["<<i<<"] is: "<<end[i]<<std::endl;
			}

			delete[] mcs;
			delete[] end;
			return max_sum;
		}

		//                                       0, i = 0 or j = 0
		//Longest Common Subsequence lcs[i][j] = lcs[i-1][j-1], if a[i] = b[j]
		//                                       max(lcs[i-1][j], lcs[i][j-1]), if a[i] != b[j]
		static int getLCS(std::string &str1, std::string &str2)
		{
			int len1 = str1.size();
			int len2 = str2.size();

			if(len1 == 0 || len2 == 0)
				return 0;

			int** lcs =  new int*[len1+1];
			for(auto i = 0; i <= len1; i++)
				lcs[i] = new int[len2+1];

			for(auto i = 0; i <= len2; i++)
				lcs[0][i] = 0;
			for(auto i = 0; i <= len1; i++)
				lcs[i][0] = 0;

			int max_len = 0;
			for(auto i = 1; i <= len1; i++)  //string str1
			{
				for(auto j = 1; j <= len2; j++) //string str2
				{
					if(str1[i-1] == str2[j-1])
						lcs[i][j] = lcs[i-1][j-1] + 1;
					else if(lcs[i-1][j] > lcs[i][j-1])
						lcs[i][j] = lcs[i-1][j];
					else
						lcs[i][j] = lcs[i][j-1];

					if(lcs[i][j] > max_len)
						max_len = lcs[i][j];
				}
			}
			
			for(auto i = 0; i <= len1; i++)
				delete[] lcs[i];
			delete lcs;
			return max_len;
		}
};

int main(int argc, char* argv[])
{
	int coins[3] = {1,3,5};
	std::cout<<"Sum 11 the number of coins needed: "<<Dp::getMinimumCoins(coins, 3, 11)<<std::endl;

	int seq[] = { 10, 22, 9, 330, 21, 50, 41, 60, 80 };
	std::cout<<"LIS is: "<<Dp::getLIS(seq, 9)<<std::endl;
	std::cout<<"Maximum sum is: "<<Dp::getMaxSubSequence(seq, 9)<<std::endl;
	int s[] = { 10, 22, 9, 33, 21, 10, 41, 60, -80 };
	std::cout<<"Maximum continguous sum is: "<<Dp::getMaxSumContinguousSequence(s, 9)<<std::endl;
	std::string s1 = "AGGTAB";
	std::string s2 = "GXTXAYB";
	std::cout<<"LCS: "<<Dp::getLCS(s1, s2)<<std::endl;
	return 0;
}


