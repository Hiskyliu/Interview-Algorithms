/*
Large Number Operation
Algorithms implemented for large number operations include:
1. Large number addition
	e.g., 123456799 + 9876543221  = 10000000020
		997654321  (reverse operand1)
	+   1223456789 (reverse operand2)
	---------------
	    02000000001 ==> reverse ==> 10000000020 (final result)

2. Large number subtration
e.g.,   807 - 9382 = -8575 (if the result is negative, don't forget the minus sign -- '-') 
if a > b, a-b = a-b; if a < b, a-b=-(b-a) ==> always larger value - smaller value; 
	  2839 (reverse operand1)
  -   708  (reverse operand2) 
  ---------------------------
      5758 ==> append minus sign "-" ==> "5758-" ==> reverse ==> -8575 (final result) 
*/

public class LargeNumberOper
{
	//large number is stored as String (e.g., "1234567890987654321")
	public static String addition(String v1, String v2) //v1,v2: operands
	{
		if(v1 == null && v2 == null)
			return null;

		int v1_len = v1.length();
		int v2_len = v2.length();

		if(v1_len == 0) //quick check
			return v2;
		if(v2_len == 0)
			return v1;	

		//reverse two operands
		String v1_reverse = new StringBuffer(v1).reverse().toString(); //reverse v1
		String v2_reverse = new StringBuffer(v2).reverse().toString(); //reverse v2

		StringBuffer res = new StringBuffer();  //store the addition result
		int c = 0; //carry number
		int len = v1_len > v2_len ? v1_len : v2_len;

		for(int i = 0; i < len; i++)
		{
			int v1_number = (i < v1_len ? (v1_reverse.charAt(i) - '0') : 0);
			int v2_number = (i < v2_len ? (v2_reverse.charAt(i) - '0') : 0);

			int sum = v1_number + v2_number + c;
			if(sum >= 10)
			{
				sum -= 10;
				c = 1;   //set carry number to 1
			}
			else
			{
				c = 0;   //carry number is 0
			}
		
			res.append(sum);
		}

		if(c == 1) //do not forget to check the final carry number
			res.append(1);

		return res.reverse().toString();
	}

	//Use String to represent large number
	public static String subtraction(String v1, String v2)
	{
		if(v1 == null && v2 == null)
			return null;

		int v1_len = v1.length();
		int v2_len = v2.length();
		
		if(v1_len == 0)  //quick check
			return new StringBuffer("-").append(v2).toString();
		if(v2_len == 0)
			return v1;

		//reverse two operands
		String v1_reverse = new StringBuffer(v1).reverse().toString();
		String v2_reverse = new StringBuffer(v2).reverse().toString();

		StringBuffer res =  new StringBuffer(); //store subtraction result
		int borrow = 0;  //borrow number
		boolean bMinus = false; //if v1 < v2 => v1 - v2 = -(v2 - v1)

	  //compare v1 and v2
		if(v1_len < v2_len)
		{
			bMinus =  true;
		}
		else if(v1_len == v2_len)
		{
			for(int i = 0; i < v1_len; i++)
			{
				if(v1.charAt(i) < v2.charAt(i))
				{
					bMinus = true;
					break;
				}
			}
		}
	
		int len =  v1_len > v2_len ? v1_len : v2_len;
		for(int i = 0; i < len; i++)
		{
			int v1_number = i < v1_len ? v1_reverse.charAt(i) - '0' : 0;
			int v2_number = i < v2_len ? v2_reverse.charAt(i) - '0' : 0;

			int sum = 0;
			if(bMinus) //v1 - v2 = -(v2 - v1)
				sum = v2_number - v1_number - borrow;
			else
				sum = v1_number - v2_number - borrow;

			if(sum < 0)
			{
				sum += 10;
				borrow = 1;
			}
			else
			{
				borrow = 0;
			}
		
			res.append(sum);
		}

		//remove "0" (e.g., 000000001 = > 1)
		for(int i = res.length()-1; i >= 1; i--)
		{
			if(res.charAt(i) != '0')
				break;
			res.deleteCharAt(i);
		}

		if(bMinus)
			res.append('-');

		return res.reverse().toString();
	}

	public static void main(String argv[])
	{
		System.out.println("Addition: " + addition("123456799", "9876543221"));
		System.out.println("Subtraction: " + subtraction("9382", "807"));
		System.out.println("Subtraction: " + subtraction("807", "9382"));
		System.out.println("Subtraction: " + subtraction("123456807", "123456808"));
	}
}
