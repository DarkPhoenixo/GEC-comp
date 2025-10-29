import java.util.Scanner;

public class Stock {
    private String sym;
    private String nm;
    private double oldPrice;
    private double newPrice;
    
    public Stock(String sym, String nm) {
        this.sym = sym;
        this.nm = nm;
    }
    
    public String getSymbol() {
        return sym;
    }
    
    public String getName() {
        return nm;
    }
    
    public double getOldPrice() {
        return oldPrice;
    }
    
    public void setOldPrice(double old) {
        this.oldPrice = old;
    }
    
    public double getNewPrice() {
        return newPrice;
    }
    
    public void setNewPrice(double new1) {
        this.newPrice = new1;
    }
    
    public double getPercent() {
        return ((newPrice - oldPrice) / oldPrice) * 100;
    }
    
public String toString() {
    return sym + " - " + nm;
}

    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        
        Stock[] list = new Stock[10];
        list[0] = new Stock("AAPL", "Apple Inc");
        list[0].setOldPrice(15000.95);
        list[0].setNewPrice(15200.52);
        
        list[1] = new Stock("MSFT", "Microsoft Corporation");
        list[1].setOldPrice(28000.11);
        list[1].setNewPrice(28200.67);
        
        list[2] = new Stock("GOOGL", "Alphabet Inc");
        list[2].setOldPrice(10900.86);
        list[2].setNewPrice(11000.20);
        
        list[3] = new Stock("AMZN", "Amazon.com Inc");
        list[3].setOldPrice(10700.33);
        list[3].setNewPrice(10650.95);
        
        list[4] = new Stock("TSLA", "Tesla Inc");
        list[4].setOldPrice(17800.65);
        list[4].setNewPrice(17950.50);
        
        list[5] = new Stock("META", "Meta Platforms Inc");
        list[5].setOldPrice(25000.55);
        list[5].setNewPrice(25400.78);
        
        list[6] = new Stock("NVDA", "NVIDIA Corporation");
        list[6].setOldPrice(36000.20);
        list[6].setNewPrice(36600.35);
        
        list[7] = new Stock("JPM", "JPMorgan Chase & Co");
        list[7].setOldPrice(12100.43);
        list[7].setNewPrice(12200.10);
        
        list[8] = new Stock("V", "Visa Inc");
        list[8].setOldPrice(20050.10);
        list[8].setNewPrice(19950.82);
        
        list[9] = new Stock("WMT", "Walmart Inc");
        list[9].setOldPrice(4950.84);
        list[9].setNewPrice(4975.12);
        
        int opt;
        do {
            System.out.println("\n===== Stock Menu =====");
            System.out.println("1. Show All Stocks");
            System.out.println("2. Find Highest Stock");
            System.out.println("3. Find Lowest Stock");
            System.out.println("4. Check Price Change");
            System.out.println("5. Exit");
            System.out.print("Choose option: ");
            opt = scan.nextInt();
            
            if (opt == 1) {
                showAll(list);
            } else if (opt == 2) {
                findMax(list);
            } else if (opt == 3) {
                findMin(list);
            } else if (opt == 4) {
                checkChange(list, scan);
            } else if (opt == 5) {
                System.out.println("Bye!");
            } else {
                System.out.println("Wrong input!");
            }
        } while (opt != 5);
        
        scan.close();
    }
    
    private static void showAll(Stock[] list) {
        System.out.println("\n===== All Stocks =====");
        for (int i = 0; i < list.length; i++) {
            System.out.println(list[i] + " (Old: Rs" + list[i].getOldPrice() + 
                              ", New: Rs" + list[i].getNewPrice() + ")");
        }
    }
    
    private static void findMax(Stock[] list) {
        Stock max = list[0];
        for (int i = 1; i < list.length; i++) {
            if (list[i].getOldPrice() > max.getOldPrice()) {
                max = list[i];
            }
        }
        System.out.println("\nHighest Stock: " + max + " (Rs" + max.getOldPrice() + ")");
    }
    
    private static void findMin(Stock[] list) {
        Stock min = list[0];
        for (int i = 1; i < list.length; i++) {
            if (list[i].getOldPrice() < min.getOldPrice()) {
                min = list[i];
            }
        }
        System.out.println("\nLowest Stock: " + min + " (Rs" + min.getOldPrice() + ")");
    }
    
    private static void checkChange(Stock[] list, Scanner scan) {
        System.out.println("\n===== Stocks =====");
        for (int i = 0; i < list.length; i++) {
            System.out.println((i+1) + ". " + list[i]);
        }
        
        System.out.print("Pick a number (1-10): ");
        int num = scan.nextInt() - 1;
        
        if (num >= 0 && num < list.length) {
            Stock pick = list[num];
            double change = pick.getPercent();
            System.out.println("\nStock: " + pick);
            System.out.println("Old Price: Rs" + pick.getOldPrice());
            System.out.println("New Price: Rs" + pick.getNewPrice());
            System.out.println("Change: " + change + "%");
            
            if (change > 0) {
                System.out.println("Status: UP ");
            } else if (change < 0) {
                System.out.println("Status: DOWN ");
            } else {
                System.out.println("Status: SAME ");
            }
        } else {
            System.out.println("Wrong number!");
        }
    }
}
