#include <iostream>

int main() {
    int* array = new int[10];
    array[10] = 0; // 越界访问
    delete[] array;
    return 0;
}
