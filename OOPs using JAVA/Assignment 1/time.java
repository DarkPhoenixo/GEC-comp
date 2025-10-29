public class time {
    private int hour;
    private int minute;
    private int second;

    public time() {
        this.hour = 0;
        this.minute = 0;
        this.second = 0;
    }

    public time(int hour, int minute, int second) {
        this.hour = hour;
        this.minute = minute;
        this.second = second;
    }

    public int getHour() {
        return hour;
    }

    public int getMinute() {
        return minute;
    }

    public int getSecond() {
        return second;
    }

    public void setHour(int hour) {
        this.hour = hour;
    }

    public void setMinute(int minute) {
        this.minute = minute;
    }

    public void setSecond(int second) {
        this.second = second;
    }

    public void setTime(int hour, int minute, int second) {
        this.hour = hour;
        this.minute = minute;
        this.second = second;
    }

    public time nextSecond() {
        second++;
        if (second >= 60) {
            second = 0;
            minute++;
            if (minute >= 60) {
                minute = 0;
                hour++;
                if (hour >= 24) {
                    hour = 0;
                }
            }
        }
        return this;
    }

    @Override
    public String toString() {
        return String.format("%02d:%02d:%02d", hour, minute, second);
    }

    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        time t = new time(12, 0, 0);
        int choice;

        do {
            System.out.println("\nCurrent Time: " + t);
            System.out.println("Menu:");
            System.out.println("1. Set Time (Hour, Minute, Second)");
            System.out.println("2. Next Second");
            System.out.println("3. Get Hour, Minute, Second");
            System.out.println("0. Exit");
            System.out.print("Enter your choice: ");
            
            choice = scanner.nextInt();
            
            switch (choice) {
                case 1:
                    System.out.print("Enter hour (0-23): ");
                    int h = scanner.nextInt();
                    System.out.print("Enter minute (0-59): ");
                    int m = scanner.nextInt();
                    System.out.print("Enter second (0-59): ");
                    int s = scanner.nextInt();
                    t.setTime(h, m, s);
                    break;
                case 2:
                    t.nextSecond();
                    System.out.println("Advanced to next second!");
                    break;
                case 3:
                    System.out.println("Hour: " + t.getHour());
                    System.out.println("Minute: " + t.getMinute());
                    System.out.println("Second: " + t.getSecond());
                    break;
                case 0:
                    System.out.println("Exiting program...");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        } while (choice != 0);
        
        scanner.close();
    }
}
