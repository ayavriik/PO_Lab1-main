#include <iostream>

const int n = 10000;
const int m = 10000;

int main() {
    int** matrix = new int*[n]; 
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m]; 
    }

    std::cout << "Memory allocated for matrix." << std::endl;

    return 0;
}
