public class ArrayReverser {
    public static void main(String[] args) {
        int[] originalArray = {10, 20, 30, 40, 50, 60};
        System.out.print("Original Array: ");
        printArray(originalArray);

        reverseArray(originalArray);

        System.out.print("Reversed Array: ");
        printArray(originalArray);
    }

    public static void reverseArray(int[] arr) {
        int left = 0;
        int right = arr.length - 1;

        while (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }

    public static void printArray(int[] arr) {
        System.out.print("[");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + (i < arr.length - 1 ? ", " : ""));
        }
        System.out.println("]");
    }
}