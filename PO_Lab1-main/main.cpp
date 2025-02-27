#include <iostream>

const int n = 10000;
const int m = 10000;

int main() {
    int** matrix = new int*[n]; // Виділяємо пам'ять під покажчики на рядки
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m]; // Виділяємо пам'ять для кожного рядка
    }

    std::cout << "Memory allocated for matrix." << std::endl;

    return 0;
}
