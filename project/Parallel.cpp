//
// Created by Mark Magdy on 1/5/2023.
//

#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <iomanip>


// Matrix multiplication function
void multiply(const std::vector<std::vector<int>> &A,
              const std::vector<std::vector<int>> &B,
              std::vector<std::vector<int>> &C,
              int row, int col)
{
    int sum = 0;
    for (int i = 0; i < A[row].size(); i++) {
        sum += A[row][i] * B[i][col];
    }
    C[row][col] = sum;
}

int main()
{
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-10, 10);

    // Generate matrices A and B randomly
    int rows = 2;
    int cols = 2;
    std::vector<std::vector<int>> A(rows, std::vector<int>(cols));
    std::vector<std::vector<int>> B(cols, std::vector<int>(rows));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = dis(gen);
            B[j][i] = dis(gen);
        }
    }

    std::vector<std::vector<int>> C(A.size(), std::vector<int>(B[0].size(), 0));

    // Get number of rows and columns in matrix C
    rows = C.size();
    cols = C[0].size();

    // Set number of threads
    int p = 4;

    // Create a vector to store the threads
    std::vector<std::thread> threads;

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

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
    for (auto &t : threads) {
        t.join();
    }

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    elapsed_time *= 1e-9;

    std::cout << "Time taken by program is : " << std::fixed
              << elapsed_time << std::setprecision(9);
    std::cout << " sec" << std::endl;

    // Print the result matrix
    for (const auto &row : C) {
        for (const auto &elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
