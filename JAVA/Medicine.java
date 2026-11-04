import java.util.ArrayList;
import java.util.Scanner;

public class Medicine {
    private String name;
    private double price;
    private int quantity;

    Medicine(String name, double price, int quantity) {
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }

    public int getQuantity() {
        return quantity;
    }

    public double value() {
        return price * quantity;
    }

    public void show() {
        System.out.println(name + " | Rs." + price + " x " + quantity + " = " + value());
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        ArrayList<Medicine> medicines = new ArrayList<>();

        System.out.println("Enter medine no: ");
        int num = sc.nextInt();
        sc.nextLine();
        for (int i = 0; i < num; i++) {
            System.out.println("Enter Medicine name: ");
            String Mname = sc.nextLine();
            System.out.println("Enter Price: ");
            double Mprice = sc.nextDouble();
            System.out.println("Enter Quantity: ");
            int Mquantity = sc.nextInt();
            sc.nextLine();
            medicines.add(new Medicine(Mname, Mprice, Mquantity));
        }
        System.out.println("Full stock ");
        double total = 0, maxVal = 0;
        String highest = "";
        for (Medicine m : medicines) {
            m.show();
            total = total + m.value();
            if (m.value() > maxVal) {
                maxVal = m.value();
                highest = m.getName();
            }
        }
        System.out
                .println("Total Stock value: " + total + "\nHighest value item: " + highest + "\nLow stock(below 20):");
        for (Medicine m : medicines) {
            if (m.getQuantity() < 20)
                m.show();
        }

        boolean medFound = false;
        System.out.println("Medicine to remove: ");
        String toRemove = sc.nextLine();
        for (int i = 0; i < medicines.size(); i++) {
            if (medicines.get(i).getName().equals(toRemove)) {
                medicines.remove(i);
                medFound = true;
                break;
            }
        }
        System.out.println((medFound ? "Removed " : "Not found ") + "\nitems left: " + medicines.size());
        sc.close();
    }
}
