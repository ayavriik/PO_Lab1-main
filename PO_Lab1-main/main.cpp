#include <iostream>
#include <chrono>
using namespace std;


// оголошення та динамічне виділення пам’яті для двовимірного масиву
const int n = 10000;
const int m = 10000;


int main() {
    int** matrix = new int*[n]; //  пам'ять для масиву покажчиків на рядки
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m]; // пам'ять для кожного рядка
    }


    // заповнення матриці
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = j + 1; // присвоєнняя значень (від 1 до 10000 у кожному рядку)
        }
    }


    auto start_time = std::chrono::high_resolution_clock::now();


    long long sum = 0; // збереження суми всіх елементів матриці

    //  обчислення суми всіх елементів матриці
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sum += matrix[i][j];  // + значення поточного елемента до суми
        }
    }


    auto end_time = std::chrono::high_resolution_clock::now();


    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);


    // виведення результатів
    std::cout << "Sum of array elements: " << sum << std::endl;
    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;


    // Звільнення пам’яті
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i]; // - кожен рядок
    }
    delete[] matrix; // - головний масив покажчиків

    return 0;
}
