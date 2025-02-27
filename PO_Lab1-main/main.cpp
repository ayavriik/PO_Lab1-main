#include <iostream>

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

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sum += matrix[i][j];
        }
    }

    std::cout << "Sum of matrix elements: " << sum << std::endl;

    return 0;
}
