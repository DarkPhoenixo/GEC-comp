public class MatrixDifference {
    public static void main(String[] args) {
        int[][] matrixA = {
            {10, 5, 2},
            {4, 1, 9}
        };

        int[][] matrixB = {
            {3, 2, 1},
            {1, 1, 1}
        };

        int[][] difference = subtractMatrices(matrixA, matrixB);

        if (difference != null) {
            System.out.println("Matrix Difference (A - B):");
            printMatrix(difference);
        }
    }

    public static int[][] subtractMatrices(int[][] A, int[][] B) {
        int rowsA = A.length;
        int colsA = A[0].length;
        
        if (B.length == 0 || B[0].length == 0) return null;
        
        int rowsB = B.length;
        int colsB = B[0].length;

        if (rowsA != rowsB || colsA != colsB) {
            System.out.println(" Error: Matrices must have the same number of rows and columns for subtraction.");
            return null;
        }

        int[][] C = new int[rowsA][colsA];

        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsA; j++) {
                C[i][j] = A[i][j] - B[i][j];
            }
        }
        return C;
    }

    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            System.out.print("| ");
            for (int element : row) {
                System.out.printf("%4d ", element);
            }
            System.out.println("|");
        }
    }
}