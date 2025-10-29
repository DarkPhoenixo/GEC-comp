public class date {
    private int day;
    private int month;
    private int year;
    
    public date() {
        this.day = 1;
        this.month = 1;
        this.year = 2023;
    }
    
    public date(int day, int month, int year) {
        this.day = day;
        this.month = month;
        this.year = year;
    }
    
    public int getDay() {
        return day;
    }
    
    public int getMonth() {
        return month;
    }
    
    public int getYear() {
        return year;
    }
    
    public void setDay(int day) {
        this.day = day;
    }
    
    public void setMonth(int month) {
        this.month = month;
    }
    
    public void setYear(int year) {
        this.year = year;
    }
    
    public void setDate(int day, int month, int year) {
        this.day = day;
        this.month = month;
        this.year = year;
    }
    
    @Override
    public String toString() {
        return String.format("%02d/%02d/%04d", day, month, year);
    }
    
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        date myDate = new date();
        int choice;
        
        do {
            System.out.println("\n----- Date Operations Menu -----");
            System.out.println("1. Create a new date");
            System.out.println("2. Display date");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");
            
            choice = scanner.nextInt();
            
            switch (choice) {
                case 1:
                    System.out.print("Enter day: ");
                    int day = scanner.nextInt();
                    System.out.print("Enter month: ");
                    int month = scanner.nextInt();
                    System.out.print("Enter year: ");
                    int year = scanner.nextInt();
                    myDate = new date(day, month, year);
                    System.out.println("New date created: " + myDate);
                    break;
                    
                case 2:
                    System.out.println("Current date: " + myDate);
                    break;
                    
                case 3:
                    System.out.println("Exiting program. Goodbye!");
                    break;
                    
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
            
        } while (choice != 3);
        
        scanner.close();
    }
}
