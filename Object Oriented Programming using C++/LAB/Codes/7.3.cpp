#include <iostream>
#include <vector>

using namespace std;

class MAT {
private:
    int m, n;
    vector<vector<int>> matrix;

public:
    MAT(int rows, int cols) {
        m = rows;
        n = cols;
        matrix.resize(m, vector<int>(n, 0));
    }

    void inputMatrix() {
        cout << "Enter the elements of the matrix:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matrix[i][j];
            }
        }
    }

    void displayMatrix() {
        cout << "Matrix:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    MAT addMatrix(const MAT& other) {
        MAT result(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    MAT multiplyMatrix(const MAT& other) {
        MAT result(m, other.n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < other.n; j++) {
                for (int k = 0; k < n; k++) {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    MAT transposeMatrix() {
        MAT result(n, m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result.matrix[j][i] = matrix[i][j];
            }
        }
        return result;
    }
};

int main() {
    int m, n;
    cout << "Enter the number of rows and columns for the matrix: ";
    cin >> m >> n;

    MAT matrix1(m, n);
    matrix1.inputMatrix();

    MAT matrix2(m, n);
    matrix2.inputMatrix();

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add matrices\n";
        cout << "2. Multiply matrices\n";
        cout << "3. Transpose matrix\n";
        cout << "4. Display matrices\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                MAT sum = matrix1.addMatrix(matrix2);
                sum.displayMatrix();
                break;
            }
            case 2: {
                MAT product = matrix1.multiplyMatrix(matrix2);
                product.displayMatrix();
                break;
            }
            case 3: {
                MAT transpose = matrix1.transposeMatrix();
                transpose.displayMatrix();
                break;
            }
            case 4: {
                cout << "Matrix 1:" << endl;
                matrix1.displayMatrix();
                cout << "Matrix 2:" << endl;
                matrix2.displayMatrix();
                break;
            }
            case 5: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
    } while (choice != 5);

    return 0;
}