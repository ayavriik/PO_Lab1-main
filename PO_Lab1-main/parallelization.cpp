#include <iostream>
#include <thread>
#include <chrono>

const int n = 10000;
const int m = 10000;
const int numThreads = 48;

int main() {
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = j + 1;
        }
    }

    long* rowSums = new long[n]();
    std::thread* threads = new std::thread[numThreads]; 
    int chunkSize = n / numThreads;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? n : (i + 1) * chunkSize;

        threads[i] = std::thread([matrix, &rowSums, start, end]() {
            for (int i = start; i < end; ++i) {
                for (int j = 0; j < m; ++j) {
                    rowSums[i] += matrix[i][j];
                }
            }
        });
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    long long totalSum = 0;
    for (long i = 0; i < n; ++i) {
        totalSum += rowSums[i];
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Sum of elements in the array: " << totalSum << std::endl;
    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
