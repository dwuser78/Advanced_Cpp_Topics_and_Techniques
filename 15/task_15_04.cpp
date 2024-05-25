#include <iostream>
#include <cmath>

#define ARRAY_SIZE 8

using namespace std;

template <typename T>
void inputArray(T *array, size_t size) {
    cout << "Fill the array (" << size << "): " << endl;
    for (size_t i = 0; i < size; ++i) {
        cin >> array[i];
    }
}

template <typename T>
double calculateAverage(const T *array, size_t size) {
    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum / static_cast<double>(size);
}

int main() {
    int intArray[ARRAY_SIZE];
    double doubleArray[ARRAY_SIZE];

    cout << "Integer array" << endl;
    inputArray(intArray, ARRAY_SIZE);

    double averageInt = calculateAverage(intArray, ARRAY_SIZE);
    cout << "Average of integer array: " << averageInt << endl;

    cout << endl << "Double array" << endl;
    inputArray(doubleArray, ARRAY_SIZE);

    double averageDouble = calculateAverage(doubleArray, ARRAY_SIZE);
    cout << "Average of double array: " << averageDouble << endl;

    return 0;
}