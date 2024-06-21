#include <iostream>

int main() {
    int* array = new int[10];
    delete[] array; // 释放内存

    array[0] = 1; // 释放后使用，错误
    std::cout << array[0] << std::endl; // 释放后使用，错误

    return 0;
}
