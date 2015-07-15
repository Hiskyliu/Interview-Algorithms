#include <iostream>
#include <algorithm>
#include <map>

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
	return 0;
}

