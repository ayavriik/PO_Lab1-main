#include <iostream>
#include <thread>

const int n = 10000;
const int m = 10000;
const int numThreads = 6;

int main() {
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = j + 1;
        }
    }

    long* rowSums = new long[n](); // Ініціалізація масиву нулями
    std::thread* threads = new std::thread[numThreads]; 
    int chunkSize = n / numThreads;

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

    // Очікування завершення всіх потоків
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    std::cout << "Threads joined successfully." << std::endl;
    return 0;
}
