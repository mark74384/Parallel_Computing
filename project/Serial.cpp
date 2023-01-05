//
// Created by Mark Magdy on 1/5/2023.
//


#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

// Matrix multiplication function
std::vector<std::vector<int>> multiply(const std::vector<std::vector<int>>& A,
                                       const std::vector<std::vector<int>>& B) {

    std::vector<std::vector<int>> result(A.size(), std::vector<int>(B[0].size()));

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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-10, 10);

    int rows = 2;
    int cols = 2;
    // Create the matrices with random values
    std::vector<std::vector<int>> A(rows, std::vector<int>(cols));
    std::vector<std::vector<int>> B(cols, std::vector<int>(rows));
    for (auto& row : A) {
        for (auto& element : row) {
            element = dis(gen);
        }
    }
    for (auto& row : B) {
        for (auto& element : row) {
            element = dis(gen);
        }
    }

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    // Multiply the matrices
    std::vector<std::vector<int>> result = multiply(A, B);

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    elapsed_time *= 1e-9;

    std::cout << "Time taken by program is : " << std::fixed
              << elapsed_time << std::setprecision(9);
    std::cout << " sec" << std::endl;

    // Print the result matrix
    for (const auto& row : result) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
