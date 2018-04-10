import java.util.Scanner;

public class main {

    public static void main(String[] args) {
    
        Scanner in = new Scanner(System.in);
        
        int t = in.nextInt();


        for(int i = 0; i < t; ++i) {
        
            int a = in.nextInt();
            int b = in.nextInt();
            
            if( a < b ){
                System.out.println("less than");
            } else if (a > b) {
                System.out.println("greater than");
            } else {
                System.out.println("equal to");
            }
        }

        return;
    }

}
