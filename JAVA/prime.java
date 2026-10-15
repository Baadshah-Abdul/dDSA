package JAVA;

import java.util.Scanner;

public class prime {
    public static int isPrim(int num)
    {
        if(num <= 1)
        {
            return 1;
        }
        for(int i= 2; i <= Math.sqrt(num);i++ )
        {
            if ((num % i) == 0){
                return 1;
            }
        }
        return 0;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a number: ");
        int p = sc.nextInt();
        if(isPrim(p) == 0)
        {
            System.out.println("Number is Prime");
        }
        else
        {
            System.out.println("Number not prime");
        }
        sc.close();
    }
}
