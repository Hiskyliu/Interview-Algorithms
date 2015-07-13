/*
Queue: First in first out (FIFO)
Algorithms implemented for Queue include:
1) enqueue - add an item into the tail of the queue
2) dequeue - pop an item from the head of the queue
3) isEmpty check
4) top - get the head item of the queue
5) tail -  get the tail item of the queue
6  size - get the size of queue
*/

public class Queue<T>
{
	private class Node
	{
		private T item = null;
		private Node next = null;
	}

	private Node m_top = null;  //Dequeue
	private Node m_tail = null; //Eequeue
	private int m_size = 0;

	public void enqueue(T it)
	{
		Node p = new Node();
		p.item = it;

		if(isEmpty())
		{
			m_top = p;
			m_tail = p;
		}
		else
		{
			m_tail.next = p;
			m_tail = p;
		}
		m_size++;
	}

	public T dequeue() throws Exception
	{
		if(isEmpty())
			throw new Exception("null");

		T it = m_top.item;
		m_top = m_top.next;

		if(m_top == null)
			m_tail = null;

		m_size--;
		return it;
	}

	public T top()
	{
		return m_top.item;
	}
	
	public T tail()
	{
		return m_tail.item;
	}

	public boolean isEmpty()
	{
		return m_top == null;
	}

	public int size()
	{
		return m_size;
	}

	public static void main(String argv[])
	{
		Queue q = new Queue<Integer>();
		int[] a = {1,2,3,4,5,6,7,8};
		try{
			for(int  i = 0; i<a.length; i++)
			{
				q.enqueue(a[i]);
				System.out.println("Enqueue, tail = " + q.tail());
				System.out.println("Enqueue, top = " + q.top());
			}

			for(int  i = 0; i<a.length; i++)
       	 	{
            	System.out.println("Dequeue, top = " + q.dequeue());
				System.out.println("Dequeue, tail = " + q.tail());
        	}	
	
        	System.out.println("Dequeue, top = " + q.dequeue());
		}
		catch(Exception e)
		{
        	System.out.println("error:  " + e.getMessage());
		}	
	}	
}
