#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
void sortCount(T arr[], int size, T min, T max) {
    int range = max - min + 1;

    int* count = new int[range]();

    for (int i = 0; i < size; i++) {
        count[arr[i] - min]++;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[index++] = i + min;
            count[i]--;
        }
    }

    delete[] count;
}

template<typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    int arr[] = { 4, 2, 2, 8, 3, 3, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    printArray(arr, size);

    int minVal = *min_element(arr, arr + size);
    int maxVal = *max_element(arr, arr + size);

    sortCount(arr, size, minVal, maxVal);

    cout << "Отсортированный массив: ";
    printArray(arr, size);

    return 0;
}
