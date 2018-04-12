package de.informatikBonn.Sheet1;

import java.util.Scanner;

public class Task3 {

    static class Maybe<T> {
        T value = null;

        public void setValue(T value){
            this.value = value;
        }

        public T getValue(){
            return value;
        }

        public boolean isPresent(){
            return value!=null;
        }

    }

    public static void main(String[] args) {
	// write your code here
        try(Scanner scanner = new Scanner(System.console().reader())){
            int persons = scanner.nextInt();
            int budget = scanner.nextInt();
            int accommodations = scanner.nextInt();
            int dates = scanner.nextInt();

            Maybe<Integer> bestPrize = new Maybe<>();

            for(int i=0; i<accommodations;i++){
                //the price for each person for this accommodation
                int price = scanner.nextInt()*persons;
                if(price>budget){
                    //skip this and the next line since we are already out of budget
                    scanner.nextLine();
                    scanner.nextLine();
                }
                else{
                    //we are in the budget
                    for (int j = 0; j<dates; j++){
                        //check if the current date has enough free beds
                        if(scanner.nextInt()>=persons){
                            //check if the current prize is really cheaper
                            if(!bestPrize.isPresent() || (bestPrize.isPresent() && price < bestPrize.getValue())){
                                bestPrize.setValue(price);
                            }
                            break;
                        }
                    }
                }
            }

            if (bestPrize.isPresent()){
                System.out.printf(bestPrize.getValue().toString());
            }
            else {
                System.out.printf("impossible");
            }
        }

    }
}
