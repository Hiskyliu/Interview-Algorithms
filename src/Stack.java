/*
Stack: Last in first out (LIFO) 
Algorithms implemented for Stack include:
1) push an item into stack
2) pop an item from  stack
3) top get the top item
4) isEmpty() check
5) design a stack which, in addition to push and pop, also has a function min or max 
   which returns the minimum or maxinum element in O(1) time
*/

class StackWithMin<T extends Comparable<T>>
{
	private class Node
	{
		private T item = null;
		private Node next = null;
	}

	private int m_size = 0;     //size of stack
	private Node m_top = null;  //Normal stack
	private Node m_min = null;  //min stack store the minimum item of normal stack

	public void push(T it)
	{
		Node p = new Node();
		p.item = it;
		p.next = m_top;
		m_top = p;
		m_size++;

		if((m_min == null) || (it.compareTo(m_min.item) <= 0)) //if it <= top value of m_min, push into min stack
		{
			Node min_p = new Node();
			min_p.item = it;
			min_p.next = m_min;
			m_min = min_p;
		}
	}

	public T pop() throws Exception
	{
		if(isEmpty())
			throw new Exception("empty stack.");

		T item = m_top.item;
		m_top = m_top.next;
		m_size--;

		if(item == m_min.item) //if item == min.top(), pop it from min stack
		{
			if(m_min != null && item.compareTo(m_min.item) == 0)
			{
				m_min = m_min.next;
			}
		}

		return item;
	}

	public boolean isEmpty()
	{
		return m_top == null;
	}

	public T getMinimun()
	{
		return m_min.item;
	}

	public int size()
	{
		return m_size;
	}

	public T top()
	{
		return m_top.item;
	}
}


//Normal stack
public class Stack<T extends Comparable<T>> 
{
	private class Node
	{
		private T data = null;
		private Node next = null;
	}

	private Node m_top = null;

	public void push(T d)
	{
		Node p = new Node();
		p.data = d;
		p.next = m_top;
		m_top = p;
	}

	public T pop() throws Exception
	{
		if(isEmpty())
			throw new Exception("stack is empty.");

		T o = top();
		m_top = m_top.next;

		return o;
	}
	
	public T top()
	{
		return m_top.data;
	}

	public boolean isEmpty()
	{
		return m_top == null;
	}

	public static void main(String argv[])
	{
		StackWithMin s =  new StackWithMin<Integer>();

		int[] a = {8,4,5,4,2,7,10};
		for(int i = 0; i < a.length; i++)
		{
			s.push(a[i]);
			System.out.println("Top value = " + (Integer)(s.top()));
			System.out.println("Min value = " + (Integer)(s.getMinimun()));
		}
		System.out.println("Now begin to pop:");
		for(int i = 0; i < a.length; i++)
        {
        	try
			{ 
				s.pop();
            	System.out.println("Top value = " + (Integer)(s.top()));
				System.out.println("Min value = " + (Integer)(s.getMinimun()));
			}
			catch(Exception e)
			{
				System.out.println("error:" + e.getMessage());
			}
        }

	}
}
