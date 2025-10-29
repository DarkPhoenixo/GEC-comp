public class ArrayResizer {
    public static void main(String[] args) {
        double[] originalList = {1.1, 2.2, 3.3};
        System.out.print("Original Array (size " + originalList.length + "): ");
        printArray(originalList);

        double[] doubledList = doubleCapacity(originalList);

        System.out.print("Doubled Array (size " + doubledList.length + "): ");
        printArray(doubledList);
    }

    public static double[] doubleCapacity(double[] list) {
        double[] newList = new double[list.length * 2];
        System.arraycopy(list, 0, newList, 0, list.length);
        return newList;
    }

    public static void printArray(double[] arr) {
        System.out.print("[");
        for (int i = 0; i < arr.length; i++) {
            System.out.printf("%.1f%s", arr[i], (i < arr.length - 1 ? ", " : ""));
        }
        System.out.println("]");
    }
}