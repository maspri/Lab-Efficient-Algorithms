
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


/*
Idea: save the longest sequence in an array.
for every new number do a binary search on the array to find the smallest value which is >= the number to 
overwrite this value with the new number.
If no >= value exists the sequence will be extendend. while this is done the lenght of the longest sequence is always safed.
After iterating through all numbers and building all increasing sequences, the value of the longest sequence is returned.

Run time O(n * logn) 
*/

class main
{

	static int LIS(List<Integer> numbers)
	{
		int n = numbers.size();
		Integer [] seq_ends = new Integer[n];
		Arrays.fill(seq_ends, 0);
		int len = 0;

		for (int i = 0; i < n; i++)
		{
			int number_i = numbers.get(i);

			//binary search
			int l = 0;
			int r = len;
			while(l != r)
			{
				int m = (l + r) / 2;
				if(seq_ends[m] < number_i)
					l = m + 1;
				else
					r = m;
			}
			//build new sequence
			seq_ends[l] = number_i;
			//update longest
			len = Math.max(l+1, len);
		}
		return len;
	}

	
	public static void main(String[] args)  throws IOException


	{
		//input code segment
		List<Integer> numbers_list = new ArrayList<Integer>();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while(true) {
			String input = br.readLine();
		  
			if(input == null || input.equals("")) {
			  break;
			}
			numbers_list.add(Integer.valueOf(input));
		}
		System.out.println(LIS(numbers_list));
		
		
		
      }
      
}