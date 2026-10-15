package JAVA;

import java.util.Scanner;

public class sum {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("ENter 1st Num: ");
        int num1 = sc.nextInt();
        System.out.println("ENter 2st Num: ");
        int num2 = sc.nextInt();
        int sum = num1 + num2;
        System.out.println("The Sum is: "+ sum);
        sc.close();
    }
}
