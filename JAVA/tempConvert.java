package JAVA;

import java.util.Scanner;

public class tempConvert {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("ENter in Celcius: ");
        double Celcius = sc.nextDouble();
        double fahrenhiet = (Celcius * 1.8) + 32;
        System.out.println("Celcius->Fahrenhiet = "+ fahrenhiet);
        System.out.println("ENter in Fahrenhiet: ");
        fahrenhiet = sc.nextDouble();
        Celcius = (fahrenhiet - 32)/1.8;
        System.out.println("Farenhiet->Celcius = "+ Celcius);
        sc.close();

    }
}
