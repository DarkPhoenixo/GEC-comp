public class GCDCalculator {
    public static void main(String[] args) {
        System.out.println("GCD(12, 18) = " + gcd(12, 18));
        System.out.println("GCD(10, 15, 25) = " + gcd(10, 15, 25));
        System.out.println("GCD(7, 13) = " + gcd(7, 13));
    }

    private static int findTwoGCD(int a, int b) {
        a = Math.abs(a);
        b = Math.abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public static int gcd(int... numbers) {
        if (numbers == null || numbers.length == 0) {
            return 0;
        }
        if (numbers.length == 1) {
            return Math.abs(numbers[0]);
        }
        int result = findTwoGCD(numbers[0], numbers[1]);
        for (int i = 2; i < numbers.length; i++) {
            result = findTwoGCD(result, numbers[i]);
        }
        return result;
    }
}