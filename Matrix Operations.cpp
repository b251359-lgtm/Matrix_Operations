#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to input matrix
void inputMatrix(vector<vector<int>>& matrix, int rows, int cols)
{
    cout << "\nEnter matrix elements:\n";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << "Element [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matrix[i][j];
        }
    }
}

// Function to display matrix
void displayMatrix(const vector<vector<int>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << setw(6) << matrix[i][j];
        }
        cout << endl;
    }
}

// Matrix Addition
void addMatrices()
{
    int rows, cols;

    cout << "\nEnter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<int>> A(rows, vector<int>(cols));
    vector<vector<int>> B(rows, vector<int>(cols));
    vector<vector<int>> result(rows, vector<int>(cols));

    cout << "\nEnter Matrix A";
    inputMatrix(A, rows, cols);

    cout << "\nEnter Matrix B";
    inputMatrix(B, rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    cout << "\nResultant Matrix:\n";
    displayMatrix(result);
}

// Matrix Multiplication
void multiplyMatrices()
{
    int r1, c1, r2, c2;

    cout << "\nEnter rows and columns of Matrix A: ";
    cin >> r1 >> c1;

    cout << "Enter rows and columns of Matrix B: ";
    cin >> r2 >> c2;

    if (c1 != r2)
    {
        cout << "\nMatrix multiplication not possible!\n";
        return;
    }

    vector<vector<int>> A(r1, vector<int>(c1));
    vector<vector<int>> B(r2, vector<int>(c2));
    vector<vector<int>> result(r1, vector<int>(c2, 0));

    cout << "\nEnter Matrix A";
    inputMatrix(A, r1, c1);

    cout << "\nEnter Matrix B";
    inputMatrix(B, r2, c2);

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "\nMultiplication Result:\n";
    displayMatrix(result);
}

// Matrix Transpose
void transposeMatrix()
{
    int rows, cols;

    cout << "\nEnter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));

    inputMatrix(matrix, rows, cols);

    cout << "\nTranspose Matrix:\n";

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            cout << setw(6) << matrix[j][i];
        }
        cout << endl;
    }
}

// Function to get cofactor matrix
vector<vector<int>> getCofactor(vector<vector<int>> matrix,
                                int p, int q, int n)
{
    vector<vector<int>> temp(n, vector<int>(n));

    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = matrix[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }

    return temp;
}

// Recursive function to calculate determinant
int determinant(vector<vector<int>> matrix, int n)
{
    // Base case for 1x1 matrix
    if (n == 1)
        return matrix[0][0];

    // Base case for 2x2 matrix
    if (n == 2)
    {
        return (matrix[0][0] * matrix[1][1]) -
               (matrix[0][1] * matrix[1][0]);
    }

    int det = 0;
    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        vector<vector<int>> temp =
            getCofactor(matrix, 0, f, n);

        det += sign *
               matrix[0][f] *
               determinant(temp, n - 1);

        sign = -sign;
    }

    return det;
}

// Determinant Function
void determinantMatrix()
{
    int n;

    cout << "\nEnter size of square matrix (n x n): ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid size!\n";
        return;
    }

    vector<vector<int>> matrix(n, vector<int>(n));

    inputMatrix(matrix, n, n);

    cout << "\nMatrix:\n";
    displayMatrix(matrix);

    int det = determinant(matrix, n);

    cout << "\nDeterminant = " << det << endl;
}

int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "      MATRIX OPERATIONS LIBRARY\n";
        cout << "=====================================\n";

        cout << "1. Matrix Addition\n";
        cout << "2. Matrix Multiplication\n";
        cout << "3. Matrix Transpose\n";
        cout << "4. Determinant of NxN Matrix\n";
        cout << "5. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addMatrices();
                break;

            case 2:
                multiplyMatrices();
                break;

            case 3:
                transposeMatrix();
                break;

            case 4:
                determinantMatrix();
                break;

            case 5:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}