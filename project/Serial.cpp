//
// Created by Mark Magdy on 1/5/2023.
//


#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

// Matrix multiplication function
vector<vector<int>> multiply(const vector<vector<int>> &A,
                             const vector<vector<int>> &B) {

    vector<vector<int>> result(A.size(), vector<int>(B[0].size()));

    // Multiply the matrices
    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[0].size(); j++) {
            for (size_t k = 0; k < A[0].size(); k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

int main() {
    // Initialize the random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-10, 10);

    int rows = 2;
    int cols = 2;
    // Create the matrices with random values
    vector<vector<int>> A(rows, vector<int>(cols));
    vector<vector<int>> B(cols, vector<int>(rows));
    for (auto &row: A) {
        for (auto &element: row) {
            element = dis(gen);
        }
    }
    for (auto &row: B) {
        for (auto &element: row) {
            element = dis(gen);
        }
    }

    // Record start time
    auto start = chrono::high_resolution_clock::now();

    // Multiply the matrices
    vector<vector<int>> result = multiply(A, B);

    // Stop the timer
    auto end = chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    elapsed_time *= 1e-9;

    cout << "Time taken by program is : " << fixed
         << elapsed_time << setprecision(9);
    cout << " sec" << endl;

    // Print the result matrix
    for (const auto &row: result) {
        for (const auto &element: row) {
            cout << element << " ";
        }
        cout << endl;
    }

    return 0;
}
