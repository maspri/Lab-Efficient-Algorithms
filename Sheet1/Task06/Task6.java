package de.informatikBonn.Sheet1;

import java.math.BigInteger;
import java.util.Scanner;

public class Task6 {

    public static void main(String [] args){
        try(Scanner scanner = new Scanner(System.console().reader())) {
            while (scanner.hasNext()){
                int n = scanner.nextInt();
                BigInteger k = new BigInteger(scanner.next(),10);
                BigInteger sum = BigInteger.ZERO;
                BigInteger k_j = k.abs();
                BigInteger j = BigInteger.ONE;

                for(int i=1; i<=n;i++){
                    sum = sum.add(k_j.multiply(j));
                    k_j = k_j.multiply(k);
                    j = j.add(BigInteger.ONE);
                }

                System.out.println(sum.toString(10));
            }

        }
    }
}
