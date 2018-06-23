
import java.io.*;
import java.util.Arrays;
import java.io.BufferedReader;
import java.io.IOException;



class main
{
	public static int lcs(int[]a, int[] b, int n){

		int f[][] = new int[2][n+1];

		int idx = 1;

		for (int i = 0; i <= n; i++){
			idx = 1 - idx;

			for (int j = 0; j <= n; j++){
				if (i == 0 || j == 0)
					f[idx][j] = 0;

				else if (a[i - 1] == (b[j - 1]))
					f[idx][j] = f[1 - idx][j - 1] + 1;

				else
					f[idx][j] = Math.max(f[1 - idx][j], f[idx][j - 1]);
			}
		}
		return f[idx][n];
		

	}
	public static void main(String[] args)  throws IOException
	{

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String input = br.readLine();
		int tests = Integer.valueOf(input);
		String[] a;
		String[] b;
		int n;
		
		
		for( int i = 1; i <= tests; i++ ){
			input = br.readLine();
			n = Integer.valueOf(input);
			a = br.readLine().split(" ");
			b = br.readLine().split(" ");
			int [] x = new int[n];
			int [] y = new int[n];
			for ( int  j = 0; j < n; j++){
				x[j] = Integer.valueOf(a[j]);
				y[j] = Integer.valueOf(b[j]);
 			}
			System.out.println(lcs(x, y, n));

		}
	}
}
