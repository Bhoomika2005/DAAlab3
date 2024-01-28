#include <bits/stdc++.h>
using namespace std;

// Function to perform matrix addition
vector<vector<int>> matrixAddition(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Function to perform matrix subtraction
vector<vector<int>> matrixSubtraction(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// Function to multiply two matrices using Strassen's algorithm
vector<vector<int>> strassenMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int n = A.size();

    // Base case: if the matrix size is 1x1
    if (n == 1)
    {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Divide matrices into submatrices
    int half = n / 2;
    vector<vector<int>> A11(half, vector<int>(half));
    vector<vector<int>> A12(half, vector<int>(half));
    vector<vector<int>> A21(half, vector<int>(half));
    vector<vector<int>> A22(half, vector<int>(half));

    vector<vector<int>> B11(half, vector<int>(half));
    vector<vector<int>> B12(half, vector<int>(half));
    vector<vector<int>> B21(half, vector<int>(half));
    vector<vector<int>> B22(half, vector<int>(half));

    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Compute intermediate matrices
    vector<vector<int>> S1 = matrixSubtraction(B12, B22);
    vector<vector<int>> S2 = matrixAddition(A11, A12);
    vector<vector<int>> S3 = matrixAddition(A21, A22);
    vector<vector<int>> S4 = matrixSubtraction(B21, B11);
    vector<vector<int>> S5 = matrixAddition(A11, A22);
    vector<vector<int>> S6 = matrixAddition(B11, B22);
    vector<vector<int>> S7 = matrixSubtraction(A12, A22);
    vector<vector<int>> S8 = matrixAddition(B21, B22);
    vector<vector<int>> S9 = matrixSubtraction(A11, A21);
    vector<vector<int>> S10 = matrixAddition(B11, B12);

    // Recursive calls for intermediate matrices multiplication
    vector<vector<int>> P1 = strassenMultiply(A11, S1);
    vector<vector<int>> P2 = strassenMultiply(S2, B22);
    vector<vector<int>> P3 = strassenMultiply(S3, B11);
    vector<vector<int>> P4 = strassenMultiply(A22, S4);
    vector<vector<int>> P5 = strassenMultiply(S5, S6);
    vector<vector<int>> P6 = strassenMultiply(S7, S8);
    vector<vector<int>> P7 = strassenMultiply(S9, S10);

    // Compute result matrices
    vector<vector<int>> C11 = matrixAddition(matrixSubtraction(matrixAddition(P5, P4), P2), P6);
    vector<vector<int>> C12 = matrixAddition(P1, P2);
    vector<vector<int>> C21 = matrixAddition(P3, P4);
    vector<vector<int>> C22 = matrixSubtraction(matrixSubtraction(matrixAddition(P5, P1), P3), P7);

    // Combine submatrices to form the result matrix
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    return C;
}

int main()
{
    ofstream inputfile("input1.txt");
    const int n = 4;
    inputfile << "The size of the square matrices: " << n << endl;
    inputfile << "elements of Matrix A:" << endl;
    vector<vector<int>> A;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int num = rand() % 100;
            inputfile << num << " ";
        }
        inputfile << endl;
    }
    inputfile << endl;
    inputfile << "elements of Matrix B:" << endl;
    vector<vector<int>> B;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int num = rand() % 100;
            inputfile << num << " ";
        }
        inputfile << endl;
    }
    inputfile << endl;
    inputfile.close();

    ifstream inputFile("input1.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inputFile >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inputFile >> B[i][j];
        }
    }
    inputFile.close();
    ofstream outputfile("output1.txt");
    vector<vector<int>> C = strassenMultiply(A, B);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            outputfile << C[i][j] << " ";
        }
        outputfile << endl;
    }
    outputfile.close();

    return 0;
}
