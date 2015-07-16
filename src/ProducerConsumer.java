import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

/*
ConcurrentLinkedQueue: an unbounded thread-safe queue based on linked nodes.	
	       It is not a blocking queue, it does not implement the BlockingQueue 
				 interface, and therefore doen not provide the blocking method put()
				 and take().

LinkedBlockingQueue: an optionally-bounded blocking queue based on linked nodes
				 It implements the BlockingQueue interface and provides the blocking 
         methods put() and take().
*/

class Producer<T extends Comparable<T>> implements Runnable
{
	private LinkedBlockingQueue<T> queue = null;

	Producer(LinkedBlockingQueue<T> queue)
	{
		this.queue = queue;
	}

	@Override
	public void run()
	{
		System.out.println("Producer started...");
		try
		{
			//put product into queue
			for(Integer i = 0; i < 10; i++)
			{
				System.out.println("produce product into queue: "+i);
				queue.put((T)i);
				Thread.currentThread().sleep(200);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}

class Consumer<T extends Comparable<T>> implements Runnable
{
	private LinkedBlockingQueue<T> queue = null;

	Consumer(LinkedBlockingQueue<T> queue)
	{
		this.queue = queue;
	}

	@Override
	public void run()
	{
		System.out.println("Consumer started...");
		T product = null;
		try
		{
			while((product = queue.take())!=null)
			{
				System.out.println("consume product from queue: "+product);
				Thread.currentThread().sleep(300);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}

public class ProducerConsumer<T extends Comparable<T>>
{
	private LinkedBlockingQueue<T> queue = null;

	public ProducerConsumer()
	{
		queue = new LinkedBlockingQueue<T>();
	}	

	public LinkedBlockingQueue<T> getQueue()
	{
		return queue;
	}

	public static void main(String argv[])
	{
		ProducerConsumer obj = new ProducerConsumer<Integer>();
		Thread producer = new Thread(new Producer<Integer>(obj.getQueue()));
		Thread consumer = new Thread(new Consumer<Integer>(obj.getQueue()));

		producer.start();
		consumer.start();
	}
}
















