//
// Created by Mark Magdy on 1/5/2023.
//

#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

// Matrix multiplication function
void multiply(const vector<vector<int>> &A,
              const vector<vector<int>> &B,
              vector<vector<int>> &C,
              int row, int col) {
    int sum = 0;
    for (int i = 0; i < A[row].size(); i++) {
        sum += A[row][i] * B[i][col];
    }
    C[row][col] = sum;
}

int main() {
    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(-10, 10);

    // Generate matrices A and B randomly
    int rows = 2;
    int cols = 2;
    vector<vector<int>> A(rows, vector<int>(cols));
    vector<vector<int>> B(cols, vector<int>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = dis(gen);
            B[j][i] = dis(gen);
        }
    }

    vector<vector<int>> C(A.size(), vector<int>(B[0].size(), 0));

    // Get number of rows and columns in matrix C
    rows = C.size();
    cols = C[0].size();

    // Set number of threads
    int p = 4;

    // Create a vector to store the threads
    vector<thread> threads;

    // Record start time
    auto start = chrono::high_resolution_clock::now();

    // Spawn p threads to perform matrix multiplication
    for (int i = 0; i < p; i++) {
        threads.emplace_back([&]() {
            // Calculate the start and end indices for this thread
            int start = (i * rows) / p;
            int end = ((i + 1) * rows) / p;

            // Multiply the matrices for the rows assigned to this thread
            for (int row = start; row < end; row++) {
                for (int col = 0; col < cols; col++) {
                    multiply(A, B, C, row, col);
                }
            }
        });
    }

    // Wait for all threads to finish
    for (auto &t: threads) {
        t.join();
    }

    // Stop the timer
    auto end = chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    elapsed_time *= 1e-9;

    cout << "Time taken by program is : " << fixed
         << elapsed_time << setprecision(9);
    cout << " sec" << endl;

    // Print the result matrix
    for (const auto &row: C) {
        for (const auto &elem: row) {
            cout << elem << ' ';
        }
        cout << endl;
    }

    return 0;
}
