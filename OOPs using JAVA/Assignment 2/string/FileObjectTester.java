import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;

public class FileObjectTester {
    public static void main(String[] args) {
        String dirName = "test_directory";
        String fileName = dirName + File.separator + "test_file.txt";

        File dir = new File(dirName);
        File file = new File(fileName);

        System.out.println("--- File Object Methods Test ---");
        
        dir.mkdir();
        System.out.println("1. Directory '" + dirName + "' created: " + dir.exists());
        System.out.println("2. Is it a directory? " + dir.isDirectory());

        try {
            file.createNewFile();
            try (PrintWriter writer = new PrintWriter(file)) {
                writer.println("Content.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        System.out.println("3. Does the file exist? " + file.exists());
        System.out.println("4. Is it a file? " + file.isFile());
        System.out.println("5. Name: " + file.getName());
        System.out.println("6. Absolute Path: " + file.getAbsolutePath());
        System.out.println("7. Size (bytes): " + file.length());
        System.out.println("8. Last Modified: " + new Date(file.lastModified()));
        System.out.println("9. Can Read/Write? " + file.canRead() + "/" + file.canWrite());

        System.out.println("10. Deleting file: " + file.delete());
        System.out.println("11. Deleting directory: " + dir.delete());
    }
}