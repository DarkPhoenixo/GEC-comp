import java.io.File;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class SortFileNames {
    private static final String FILE_NAME = "names.txt";

    public static void main(String[] args) {
        createDummyFile(); 
        
        ArrayList<String> names = new ArrayList<>();

        try (Scanner fileScanner = new Scanner(new File(FILE_NAME))) {
            while (fileScanner.hasNextLine()) {
                String name = fileScanner.nextLine().trim();
                if (!name.isEmpty()) {
                    names.add(name);
                }
            }
            System.out.println(" Successfully read " + names.size() + " names from the file.");
        } catch (FileNotFoundException e) {
            System.out.println(" Error: File not found: " + FILE_NAME);
            return;
        }

        Collections.sort(names);
        System.out.println(" Names sorted.");

        try (PrintWriter writer = new PrintWriter(FILE_NAME)) {
            for (String name : names) {
                writer.println(name);
            }
            System.out.println(" Sorted names written back to the file.");
        } catch (FileNotFoundException e) {
            System.out.println(" Error writing to file: " + e.getMessage());
        }
    }
    
    private static void createDummyFile() {
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            try (PrintWriter writer = new PrintWriter(FILE_NAME)) {
                writer.println("Chinmay");
                writer.println("Chirag");
                writer.println("Audumber");
            } catch (FileNotFoundException e) {
            }
        }
    }
}