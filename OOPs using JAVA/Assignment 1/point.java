public class point {
    private int x;
    private int y;

    public point() {
        this.x = 0;
        this.y = 0;
    }

    public point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void setXY(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int[] getXY() {
        return new int[]{x, y};
    }

    @Override
    public String toString() {
        return "(" + x + "," + y + ")";
    }

    public double distance(int x, int y) {
        int xDiff = this.x - x;
        int yDiff = this.y - y;
        return Math.sqrt(xDiff * xDiff + yDiff * yDiff);
    }

    public double distance(point another) {
        return distance(another.getX(), another.getY());
    }

    public double distance() {
        return distance(0, 0);
    }

    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        point p = new point(0, 0);
        int choice;
        
        do {
            System.out.println("\n---- Point Operations Menu ----");
            System.out.println("1. Set point coordinates (x,y)");
            System.out.println("2. Get point coordinates");
            System.out.println("3. Calculate distance to origin (0,0)");
            System.out.println("4. Calculate distance to specific point");
            System.out.println("5. Calculate distance to another Point object");
            System.out.println("0. Exit");
            System.out.print("Enter your choice: ");
            
            choice = scanner.nextInt();
            
            switch (choice) {
                case 1:
                    System.out.print("Enter x coordinate: ");
                    int x = scanner.nextInt();
                    System.out.print("Enter y coordinate: ");
                    int y = scanner.nextInt();
                    p.setXY(x, y);
                    System.out.println("Point set to " + p);
                    break;
                    
                case 2:
                    int[] coordinates = p.getXY();
                    System.out.println("Current coordinates: x = " + coordinates[0] + ", y = " + coordinates[1]);
                    break;
                    
                case 3:
                    System.out.println("Distance to origin (0,0): " + p.distance());
                    break;
                    
                case 4:
                    System.out.print("Enter x coordinate of target point: ");
                    x = scanner.nextInt();
                    System.out.print("Enter y coordinate of target point: ");
                    y = scanner.nextInt();
                    System.out.println("Distance to point (" + x + "," + y + "): " + p.distance(x, y));
                    break;
                    
                case 5:
                    System.out.print("Enter x coordinate of another point: ");
                    x = scanner.nextInt();
                    System.out.print("Enter y coordinate of another point: ");
                    y = scanner.nextInt();
                    point another = new point(x, y);
                    System.out.println("Distance to point " + another + ": " + p.distance(another));
                    break;
                    
                case 0:
                    System.out.println("Exiting program. Goodbye!");
                    break;
                    
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
            
        } while (choice != 0);
        
        scanner.close();
    }
}
