#include <iostream>
#include <algorithm>
#include <map>
#include <string.h> //memset

/*
Array Questions
Sorted Array:
1. Given a sorted array which may contain repeated elements (e.g., 2,2,2,,4,5,5,6,7,7,7,8), get the number of occurrences for each elements.
2. Given a sorted array which may contain repeated elements (e.g., 2,2,2,,4,5,5,6,7,7,7,8), given a value v, output the number of occurences for v in this array.
3) Search for an element in a rotated sorted array, e.g, rotated sorted array: {5, 7, 8, 10, 1, 2, 3, 4}.

Unsorted Array:
1. array permutaion and remove duplicated .
2. find the kth largest value in an array -- use quick selection.
3. the best time to sell stock (get best profit) and the worst time to sell stock, say stock prices are stored in an array.
4. find the largest subarray with equal number of 0's and 1's from an array which contains 0 and 1, time constraint: O(). e.g., 001010101, output is 8
5. given a sequence of positive integers A and an integer T, return whether there is a continuous sequence of A that sums up to exactly T. e.g., [23, 5, 4, 7, 2, 11], T = 20. Return True because 7 + 2 + 11 = 20 (continuous sub sequence)
6. find the largest increasing sub sequence of integers in the integer array
7. find two numbers in an integer array whose sum is T. If there are multiple pairs with sum sum, just output any one of them
*/


class SortedArray
{
	public:
		//given a sorted array and a value v, find #occurences of v in this array if v exists
		static int getCount(int a[]/*input array*/, int len, int v) 
		{
			if(a == nullptr)
				return false; 

			auto num = 0;  //0 means v does not exist in a
			count(a, 0, len-1, v, num);
			return num;
		}
	
		//given a sorted array, find #occurences of each element in this array 
		static std::map<int, int> getCount(int a[], int len) 
		{
			if(a == nullptr)
				return std::map<int, int>();

			std::map<int, int> m;
			count(a, 0, len-1, m);

			for(auto &kv: m)
				std::cout<<"Element = "<<kv.first<<"; number of occurence: "<<kv.second<<std::endl;

			return m;
		}
		
		//Search for an element in a rotated sorted array 
		static int search(int a[]/*input rotated array*/, int len, int key)
		{
			if(a == nullptr)
				return -1;

			int index = -1;       //default, key does not exist
			int s = 0, e = len-1; //start/end index 
			if(a[s] == key)       //quick check 
				index = s;
			else if(a[e] == key)
				index = e;

			while(index == -1 && s >= 0 && e <= len-1 && s <= e)
			{
				int mid = (s+e)/2;

				if(a[mid] == key)      //find it
				{
					index  = mid;
				}			
				else if(a[mid] < a[s]) //[mid ... e] are sorted
				{
					if(key > a[mid] && key <= a[e]) //key can only eist in [mid+1, e]
						s = mid+1;
					else                            //key can only exist in [s, mid-1]
						e = mid-1;
				}
				else                  //[s ... mid] are sorted
				{
					if(key < a[mid] && key >= a[s])
						e = mid-1;
					else
						s = mid+1;
				}
			}
			return index;
		}
		
	private:
		//O(logn)
		static void count(int a[], int s/*start index*/, int e/*end index*/, int v, int &c)
		{
			if(a[s] == a[e] && a[s] == v) //base case, find v
			{
				c += e - s + 1;
				return;
			}

			if(s <= e)
			{
				auto mid = (s + e)/2;
				if(v < a[mid])      //v can only exist in [s, mid-1]
				{	
					if(mid > s)
						count(a, s, mid-1, v, c);
				}
				else if(v > a[mid]) //v can only exist in [mid+1, e]
				{
					if(mid < e)
						count(a, mid+1, e, v, c);
				}
				else                //v can exist in both [s, mid-1] and [mid, e]
				{
					count(a, s, mid, v, c);
					count(a, mid+1, e, v, c);
				}
			}
		}

		//O(mlogn) -- m: number of unique elements in array
		static void count(int a[], int s, int e, std::map<int, int>& m)
		{
			if(a[s] == a[e])   //base case
			{
				if(m.find(a[s]) != m.end())
					m[a[s]] += e-s+1;
				else
					m.insert(std::pair<int, int>(a[s], e-s+1));
			
				return;
			}

			if(s <= e)
			{
				int mid = (s+e)/2;
				count(a, s, mid, m);
				count(a, mid+1, e, m);
			}
		}
};

class UnsortedArray
{
	public:
		//array permutation and remove duplicated
		static void permutation(int a[], int len)
		{
			if(a == nullptr)
				return;

			perm(a, 0, len);
		}

		//find the kth largest value in an array
		static bool findKthLargest(int a[], int len, int k)
		{
				if(a == nullptr || k > len || k <= 0)
					return false;
			
				int kThLargest = quickSelect(a, 0, len-1, len, k);

				std::cout<<"The kth largest value: "<<kThLargest<<std::endl;
				return true;					
		}

		//sell stocks to get the best profit, stock prices are stored in an array
		static int getMaxDiff(int a[], int len)
		{
			int max = a[0];
			int max_diff = -65535;
			int buy = 0, sell = 0;

			for(int i = 0; i < len; i++)
			{
				if(a[i] > max)
					max = a[i];

				if(max - a[i] > max_diff)
				{
					buy = max;
					sell = a[i];
					max_diff = max - a[i];
				}
			}
			std::cout<<"Buy = "<<buy<<"; sell = "<<sell<<"; max profit = "<<max_diff<<std::endl;
		}

		//find the largest subarray with equal number of 0's and 1's from an array which contains 0 and 1
		//Time constraint is O(n) -- 0s are considered as -1, so sum(i) = sum(j), if 0s and 1s are equal from i to j 
		static int getLargestSubArray(int a[], int len)
		{
			if(nullptr == a)
				return -1;

			int hash_array[len*2 + 1]; //key = len + sum(0->i); value: index value (i) in a
			memset(hash_array, -1, sizeof(hash_array));
			int sum = 0;
			int max_len = 0;

			for(auto i = 0; i < len; i++)
			{
				sum = sum + (a[i] == 0 ? -1 : 1);
				if(hash_array[len + sum] == -1)   
				{
						hash_array[len + sum] = i;  
				}
				else  //key exists, means sum(0->j) = sum(0->i)
				{
						int pre_index = hash_array[len + sum];
						if(i - pre_index > max_len)
							max_len = i - pre_index;
				}
			}
			return max_len;
		}

		//Given a sequence of positive integers A and an integer T, return whether 
		//there is a continuous sub sequence of A that sums up to exactly T
		static bool findSequenceWithValue(int a[], int len, int v)
		{
			auto j = 0;
			auto sum = 0;
			for(auto i = 0; i < len; i++)
			{
				for(; j < len && sum < v; j++)
					sum += a[j];

				if(sum == v)
					return true;

				sum -= a[i];
			}

			return false;
		}

		//find the largest increasing sub sequence of integers in the array
		static int findLargestIncrSequence(int a[], int len, int &s, int &e)
		{
			if(nullptr == a)
				return -1;

			if(len == 1)
			{
				s = 0;
				e = 0;
				return 1;
			}

			int start = 0;
			int end = 0;
			int max_len = 1; //at least 1

			for(auto i = 1; i < len; i++)
			{
				if(a[i] > a[i-1])
				{
					end = i;
				}
				else
				{
					if(end - start + 1 > max_len)
					{
						max_len = end - start + 1;
						s = start;
						e = end;
					}
					start = i;
				}
			}

			if(end - start + 1 > max_len)
			{
				max_len = end - start + 1;
				s = start;
				e = end;
			}

			return max_len;
		}

		//find two numbers in an integer array whose sum is T.
		static bool findTwoNumWithSum(int a[], int len, int& num1, int& num2, int sum)
		{
			if(nullptr == a)
				return false;	
	
			std::sort(a, a+len); //sort the array first

			int start = 0, end = len - 1, s = 0;
			while(start < end)
			{
				s = a[start] + a[end];
				if(sum == s)
				{
					num1 = a[start];
					num2 = a[end];
					return true;
				}
				else if(sum < s)
				{
					end--;
				}
				else
				{
					start++;
				}
			}
			return false;
		}

	private:
		static void perm(int a[], int s/*start index*/, int len)
		{
			if(s == len-1)
			{
				print(a, len);
				return;
			}

			for(auto i = s; i < len; i++) //from the start index, swap the next element with the element in start index in turn
			{
				if(isWap(a, s, i))   //remove duplicated 
				{
					swap(a, s, i);
					perm(a, s+1, len); //permutate for the last elements
					swap(a, s, i);
				}
			}
		}

		static void print(int a[], int len)
		{
			for(auto i = 0; i < len; i++)
				std::cout<<a[i];
			std::cout<<std::endl;
		}

		static bool isWap(int a[], int s, int j)
		{
			for(auto i = s; i < j; i++)
				if(a[i] == a[j])
					return false;

			return true;
		}

		static void swap(int a[], int i, int j)
		{
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}

		//Average time complexity: O(n) -- if n is extremely large, consider using minheap
		static int quickSelect(int a[], int s, int e, int len, int k)
		{
			if(s <= e)
			{
				int m = partition(a, s, e);
				if(m == len - k)
					return a[m];
				else if(m < len - k)
					return quickSelect(a, m+1, e, len, k);
				else
					return quickSelect(a, s, m-1, len, k);
			}
		}

		static int partition(int a[], int s, int e)
		{
			int pivot = a[s];
			int i = s, j = e;
			while(i < j)
			{
				while(i<j && pivot <= a[j])
					j--;
				if(i<j)
					a[i] = a[j];

				while(i<j && pivot >= a[i])
					i++;
				if(i<j)
					a[j] = a[i];
	
			}
			a[i] = pivot;
			return i;
		}
};

int main(int argc, char* argv[])
{
	int a[] = {1,1,1,2,4,4,4,4,5,6,7,8,8,8,8};
	std::cout<<"the number of occurences of 8 in array: "<<SortedArray::getCount(a, 15, 8)<<std::endl;
	std::cout<<"the number of occurences of 1 in array: "<<SortedArray::getCount(a, 15, 1)<<std::endl;
	std::cout<<"the number of occurences of 2 in array: "<<SortedArray::getCount(a, 15, 2)<<std::endl;
	std::cout<<"the number of occurences of 4 in array: "<<SortedArray::getCount(a, 15, 4)<<std::endl;
	std::cout<<"the number of occurences of 9 in array: "<<SortedArray::getCount(a, 15, 9)<<std::endl;
	SortedArray::getCount(a, 15);
	int b[] = {1};
	std::cout<<"the number of occurences of 1 in array: "<<SortedArray::getCount(b, 1, 1)<<std::endl;
	SortedArray::getCount(b, 1);
	int c[] = {5, 7, 8, 10, 1, 2, 3, 4};
	std::cout<<"seach 5 in rotated array, index = "<<SortedArray::search(c, 8, 5)<<std::endl;
	std::cout<<"seach 4 in rotated array, index = "<<SortedArray::search(c, 8, 4)<<std::endl;
	std::cout<<"seach 10 in rotated array, index = "<<SortedArray::search(c, 8, 10)<<std::endl;
	std::cout<<"seach 7 in rotated array, index = "<<SortedArray::search(c, 8, 7)<<std::endl;
	std::cout<<"seach 1 in rotated array, index = "<<SortedArray::search(c, 8, 1)<<std::endl;
	std::cout<<"seach 9 in rotated array, index = "<<SortedArray::search(c, 8, 9)<<std::endl;
	int d[] = {1,2,3,3};
	UnsortedArray::permutation(d, 4);
	int e[] = {12,3,8,56,1,45};
	UnsortedArray::findKthLargest(e, 6, 1);
	UnsortedArray::findKthLargest(e, 6, 2);
	UnsortedArray::findKthLargest(e, 6, 3);
	UnsortedArray::findKthLargest(e, 6, 4);
	UnsortedArray::findKthLargest(e, 6, 5);
	UnsortedArray::findKthLargest(e, 6, 6);
	int ee[] = {12,3,8,56,1,45};
	UnsortedArray::getMaxDiff(ee, 6);
	std::cout<<"Sub sequence sum equal to 68: "<<(UnsortedArray::findSequenceWithValue(ee, 6, 68) == true ? "exist." : "not exist.")<<std::endl;
	std::cout<<"Sub sequence sum equal to 168: "<<(UnsortedArray::findSequenceWithValue(ee, 6, 168) == true ? "exist." : "not exist.")<<std::endl;
	int s = -1;
	int end = -1;
	int ret = UnsortedArray::findLargestIncrSequence(ee, 6, s, end);
	std::cout<<"Largest incr sequence: "<<ret<<"; start index = "<<s<<"; end index = "<<end<<std::endl;
	int f[] = {1,0,0,1,0,1,1,1,0};
	std::cout<<"Largest subarray with 0s and 1s: "<<UnsortedArray::getLargestSubArray(f, 9)<<std::endl;
	int num1= 0, num2 = 0;
	std::cout<<"Find two nums with sum 9: "<<(UnsortedArray::findTwoNumWithSum(ee, 6, num1, num2, 9) == true?"exist":"not exist")<<std::endl;
	std::cout<<"Find two nums with sum 9: "<<"num1 = "<<num1<<"; num2 = "<<num2<<std::endl;
	return 0;
}

