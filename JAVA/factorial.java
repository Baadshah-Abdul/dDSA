package JAVA;

import java.util.Scanner;

public class factorial {

    public static long factorialRecursive(long n) {
        if (n == 0 || n == 1) {
            return 1;
        }
        return n * factorialRecursive(n - 1);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("ENter a number: ");
        long fact = sc.nextLong();
        System.out.print(factorialRecursive(fact));
        sc.close();
    }
}
