import java.util.Date;
import java.util.Scanner;
import java.text.SimpleDateFormat;
import java.text.ParseException;

public class Account {
    private int id;
    private double money;
    private static double rate; // Static rate for all accounts
    private Date date;

    public Account() {
        id = 0;
        money = 0;
        date = new Date();
    }

    public Account(int a, double b, Date d) {
        id = a;
        money = b;
        date = d;
    }

    public int getId() {
        return id;
    }

    public void setId(int a) {
        id = a;
    }

    public double getBalance() {
        return money;
    }

    public void setBalance(double a) {
        money = a;
    }

    public static double getAnnualInterestRate() {
        return rate;
    }

    public static void setAnnualInterestRate(double a) {
        rate = a;
    }

    public Date getDateCreated() {
        return date;
    }

    public double getMonthlyInterestRate() {
        return rate / 12;
    }

    public double getMonthlyInterest() {
        return money * getMonthlyInterestRate() / 100;
    }

    public void withdraw(double a) {
        if (a <= money) {
            money = money - a;
        } else {
            System.out.println("Not enough money");
        }
    }

    public void deposit(double a) {
        if (a > 0) {
            money = money + a;
        }
    }

    public String toString() {
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        return "Account [id=" + id + ", balance=Rs." + money + ", annualInterestRate=" + rate + "%, dateCreated=" + sdf.format(date) + "]";
    }

    public static Account getHighestBalanceAccount(Account[] a) {
        if (a == null || a.length == 0) {
            return null;
        }
        
        Account max = a[0];
        for (int i = 1; i < a.length; i++) {
            if (a[i].getBalance() > max.getBalance()) {
                max = a[i];
            }
        }
        return max;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        Account[] accs = new Account[10];
        int count = 0;
        
        System.out.print("Enter annual interest rate (%) for all accounts: ");
        double globalRate = scan.nextDouble();
        Account.setAnnualInterestRate(globalRate);
        
        int choice = 0;
        while (choice != 7) {
            System.out.println("\n===== BANKING SYSTEM MENU =====");
            System.out.println("1. Create New Account");
            System.out.println("2. Display All Accounts");
            System.out.println("3. Deposit");
            System.out.println("4. Withdraw");
            System.out.println("5. Check Monthly Interest");
            System.out.println("6. Find Account with Highest Balance");
            System.out.println("7. Exit");
            System.out.print("Enter your choice: ");
            
            choice = scan.nextInt();
            
            if (choice == 1) {
                if (count < accs.length) {
                    System.out.print("Enter account ID: ");
                    int id = scan.nextInt();
                    System.out.print("Enter initial balance: Rs.");
                    double bal = scan.nextDouble();
                    
                    scan.nextLine(); // Clear buffer
                    System.out.print("Enter creation date (DD/MM/YYYY): ");
                    String dateStr = scan.nextLine();
                    
                    Date creationDate = new Date(); // Default to current date
                    try {
                        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
                        creationDate = sdf.parse(dateStr);
                    } catch (ParseException e) {
                        System.out.println("Invalid date format! Using current date.");
                    }
                    
                    accs[count] = new Account(id, bal, creationDate);
                    System.out.println("Account created successfully!");
                    count++;
                } else {
                    System.out.println("Maximum account limit reached!");
                }
            } else if (choice == 2) {
                if (count == 0) {
                    System.out.println("No accounts exist yet.");
                } else {
                    System.out.println("All Account Details:");
                    for (int i = 0; i < count; i++) {
                        System.out.println(accs[i]);
                    }
                }
            } else if (choice == 3) {
                if (count == 0) {
                    System.out.println("No accounts exist yet.");
                } else {
                    System.out.print("Enter account ID: ");
                    int id = scan.nextInt();
                    boolean found = false;
                    
                    for (int i = 0; i < count; i++) {
                        if (accs[i].getId() == id) {
                            System.out.print("Enter deposit amount: Rs.");
                            double amt = scan.nextDouble();
                            accs[i].deposit(amt);
                            System.out.println("Deposit successful! New balance: Rs." + accs[i].getBalance());
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) {
                        System.out.println("Account not found!");
                    }
                }
            } else if (choice == 4) {
                if (count == 0) {
                    System.out.println("No accounts exist yet.");
                } else {
                    System.out.print("Enter account ID: ");
                    int id = scan.nextInt();
                    boolean found = false;
                    
                    for (int i = 0; i < count; i++) {
                        if (accs[i].getId() == id) {
                            System.out.print("Enter withdrawal amount: Rs.");
                            double amt = scan.nextDouble();
                            accs[i].withdraw(amt);
                            System.out.println("New balance: Rs." + accs[i].getBalance());
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) {
                        System.out.println("Account not found!");
                    }
                }
            } else if (choice == 5) {
                if (count == 0) {
                    System.out.println("No accounts exist yet.");
                } else {
                    System.out.print("Enter account ID: ");
                    int id = scan.nextInt();
                    boolean found = false;
                    
                    for (int i = 0; i < count; i++) {
                        if (accs[i].getId() == id) {
                            System.out.println("Monthly interest: Rs." + accs[i].getMonthlyInterest());
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) {
                        System.out.println("Account not found!");
                    }
                }
            } else if (choice == 6) {
                if (count == 0) {
                    System.out.println("No accounts exist yet.");
                } else {
                    Account[] active = new Account[count];
                    for (int i = 0; i < count; i++) {
                        active[i] = accs[i];
                    }
                    Account highest = getHighestBalanceAccount(active);
                    System.out.println("Account with highest balance: " + highest);
                }
            } else if (choice == 7) {
                System.out.println("Exiting the system. Goodbye!");
            } else {
                System.out.println("Invalid choice! Please try again.");
            }
        }
        
        scan.close();
    }
}
