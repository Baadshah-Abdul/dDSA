import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class StudentIterator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<String> studentNames = new ArrayList<>();

        System.out.println("Enter the names of 5 students:");
        for (int i = 0; i < 5; i++) {
            System.out.print("Student " + (i + 1) + ": ");
            studentNames.add(scanner.nextLine());
        }

        Iterator<String> itr = studentNames.iterator();
        while (itr.hasNext()) {
            System.out.println(itr.next().toLowerCase());
        }

        scanner.close();
    }
}