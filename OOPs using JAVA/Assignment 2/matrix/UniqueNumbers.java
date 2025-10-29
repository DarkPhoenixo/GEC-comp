import java.util.ArrayList;
import java.util.Scanner;

public class UniqueNumbers {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Integer> uniqueNumbers = new ArrayList<>();
        final int MAX_UNIQUE = 11;

        System.out.println("Enter " + MAX_UNIQUE + " unique numbers:");

        while (uniqueNumbers.size() < MAX_UNIQUE) {
            System.out.print("Enter number " + (uniqueNumbers.size() + 1) + ": ");
            if (scanner.hasNextInt()) {
                int number = scanner.nextInt();
                if (uniqueNumbers.contains(number)) {
                    System.out.println("  " + number + " is already existing. It was not stored.");
                } else {
                    uniqueNumbers.add(number);
                    System.out.println("Stored: " + number);
                }
            } else {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.next();
            }
        }
        System.out.println("\nAll " + MAX_UNIQUE + " unique numbers stored: " + uniqueNumbers);
        scanner.close();
    }
}