import java.util.Collections;
import java.util.LinkedList;
import java.util.Scanner;

public class CricketSquad {

    static LinkedList<String> squad = new LinkedList<>();
    static Scanner sc = new Scanner(System.in);

    static void getInput() {
        System.out.print("Enter number of players: ");
        int n = sc.nextInt();
        sc.nextLine();
        for (int i = 0; i < n; i++) {
            System.out.print("Enter player " + (i + 1) + " name: ");
            squad.add(sc.nextLine());
        }
    }

    static void display() {
        System.out.println("Squad : " + squad);
        System.out.println("Team size : " + squad.size());
    }

    static void search() {
        System.out.print("Player to search for: ");
        String name = sc.nextLine();
        int pos = squad.indexOf(name);
        if (pos != -1)
            System.out.println(name + " is in the squad at position " + pos);
        else
            System.out.println(name + " is not in the squad");
    }

    static void removePlayer() {
        System.out.print("Player to remove: ");
        String name = sc.nextLine();
        if (squad.remove(name))
            System.out.println("Removed. Squad: " + squad);
        else
            System.out.println("Player not found. Removal failed. Squad: " + squad);
    }

    static void insertPlayer() {
        System.out.print("New player and position: ");
        String name = sc.next();
        int pos = sc.nextInt();
        sc.nextLine();
        squad.add(pos, name);
        System.out.println("Squad: " + squad);
    }

    static void displaySorted() {
        Collections.sort(squad);
        System.out.println("Sorted squad: " + squad);
    }

    static void displayFinal() {
        System.out.println("Final squad:");
        for (String p : squad)
            System.out.println(p);
        System.out.println("Team size : " + squad.size());
    }

    public static void main(String[] args) {
        getInput();

        while (true) {
            System.out.println("1. Display squad");
            System.out.println("2. Search player");
            System.out.println("3. Remove player");
            System.out.println("4. Insert player");
            System.out.println("5. Sort squad");
            System.out.println("0. Exit");
            System.out.print("Enter choice: ");
            int choice = sc.nextInt();
            sc.nextLine();

            switch (choice) {
                case 1:
                    display();
                    break;
                case 2:
                    search();
                    break;
                case 3:
                    removePlayer();
                    break;
                case 4:
                    insertPlayer();
                    break;
                case 5:
                    displaySorted();
                    break;
                case 0:
                    sc.close();
                    return;
                default:
                    System.out.println("Invalid choice");
            }
        }
    }
}