import java.util.Scanner;
import java.util.ArrayList;

public class Fan {
    public static final int SLOW = 1;
    public static final int MEDIUM = 2;
    public static final int FAST = 3;
    
    private int s = SLOW;
    private boolean o = false;
    private double r = 5;
    private String c = "blue";
    
    public Fan() {
    }
    
    public boolean isOn() {
        return o;
    }
    
    public void setOn(boolean o) {
        this.o = o;
    }
    
    public String toString() {
        if (o) {
            return "Fan speed: " + s + ", color: " + c + ", radius: " + r;
        } else {
            return "Fan color: " + c + ", radius: " + r + ", fan is off";
        }
    }
    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        ArrayList<Fan> fans = new ArrayList<>();
        fans.add(new Fan());
        int currentFan = 0;
        int ch = 0;
        
        while (ch != 4) {
            System.out.println("\n===== Fan Control Menu =====");
            System.out.println("1. Turn fan on/off");
            System.out.println("2. Create new fan");
            System.out.println("3. Display running fans");
            System.out.println("4. Exit");
            System.out.print("Enter your choice: ");
            
            ch = scan.nextInt();
            scan.nextLine();
            
            if (ch == 1) {
                fans.get(currentFan).setOn(!fans.get(currentFan).isOn());
                System.out.println("Fan is now " + (fans.get(currentFan).isOn() ? "on" : "off"));
                System.out.println(fans.get(currentFan));
            } else if (ch == 2) {
                fans.add(new Fan());
                currentFan = fans.size() - 1;
                System.out.println("New fan created with default settings (Fan #" + (currentFan + 1) + ")");
                System.out.println(fans.get(currentFan));
            } else if (ch == 3) {
                System.out.println("\n===== Running Fans =====");
                boolean anyRunning = false;
                for (int i = 0; i < fans.size(); i++) {
                    if (fans.get(i).isOn()) {
                        System.out.println("Fan #" + (i + 1) + ": " + fans.get(i));
                        anyRunning = true;
                    }
                }
                if (!anyRunning) {
                    System.out.println("No fans are currently running.");
                }
            } else if (ch == 4) {
                System.out.println("Exiting program");
            } else {
                System.out.println("Invalid choice! Please try again.");
            }
        }
        
        scan.close();
    }
}
