#include <iostream>
#include <chrono>

const int n = 10000;
const int m = 10000;

int main() {
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = j + 1;
        }
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sum += matrix[i][j];
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Sum of matrix elements: " << sum << std::endl;
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
