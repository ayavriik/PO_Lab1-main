#include <iostream>
#include <thread>
#include <chrono>

// задаємо розміри матриці
const int n = 10000;
const int m = 10000;

// вказуємо кількість потоків для паралельного обчислення
const int numThreads = 6;

int main() {
    // динамічне виділення памєяті для матриці
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m]; // для кожного рядка
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = j + 1; // ініціалізація значень (1, 2, ..., 10000)
        }
    }

    // масив для збереження сум кожного рядка
    long* rowSums = new long[n]();

    // масив потоків
    std::thread* threads = new std::thread[numThreads]; 
   
   // кількість рядків, що обробляє кожен потік
    int chunkSize = n / numThreads;

    auto start_time = std::chrono::high_resolution_clock::now();

    // запуск потоків для обчислення суми рядків
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize; // початковий рядок
        int end = (i == numThreads - 1) ? n : (i + 1) * chunkSize; // останній рядок

        // лямбда--функція для підрахунку суми в межах заданих рядків
        threads[i] = std::thread([matrix, &rowSums, start, end]() {
            for (int i = start; i < end; ++i) { // -> по рядках
                for (int j = 0; j < m; ++j) { // -> по стовпчиках
                    rowSums[i] += matrix[i][j]; // + значення до суми рядка
                }
            }
        });
    }

    // очікування завершення всіх потоків
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // обчислення загальної суми всіх елементів матриці
    long long totalSum = 0;
    for (long i = 0; i < n; ++i) {
        totalSum += rowSums[i]; // + суми всіх рядків
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Sum of elements in the array: " << totalSum << std::endl;
    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;

    // видалення виділеної пам'яті
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i]; // - кожного рядка
    }
    delete[] matrix;  // - головного масиву покажчиків
    delete[] rowSums; // - масиву сум
    delete[] threads; // - масиву потоків    

    return 0;
}
