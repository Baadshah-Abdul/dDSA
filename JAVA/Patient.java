import java.util.*;

public class Patient {
    static String hospitalName = "Crib's Hospital";
    private static int patientCounter = 0;
    private int patientId, age;
    private String name;

    Patient(String name, int age) {
        this.patientId = patientCounter + 1;
        patientCounter++;
        this.name = name;
        this.age = age;
    }

    static void getTotalPatients() {
        System.out.println("Total no of patients: " + patientCounter);
    }

    void show() {
        System.out.println("ID " + (patientId) + " | " + name + " | age " + age + " |" + hospitalName);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Patients before any object: " + patientCounter);

        int age[] = new int[3];
        String name[] = new String[3];
        int i = 0;
        while (i < 3) {
            System.out.println("Enter the name of the patient: ");
            name[i] = sc.nextLine();
            System.out.println("Enter the age: ");
            age[i] = sc.nextInt();
            sc.nextLine();
            i++;
        }
        Patient p1 = new Patient(name[0], age[0]);
        Patient p2 = new Patient(name[1], age[1]);
        Patient p3 = new Patient(name[2], age[2]);

        p1.show();
        p2.show();
        p3.show();
        getTotalPatients();
    }
}
