package JAVA;

import java.util.Scanner;

public class fibonaci {
    public static int fibo(int num){
        if(num <= 1)
        {
            return num;
        }
        return fibo(num - 1) + fibo(num - 2);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a number: ");
        int fib = sc.nextInt();
       for(int i = 0; i < fib; i++)
        {
            System.out.println(fibo(i));
        } 
        sc.close();
    }
}
