#include <iostream>
#include <algorithm>
#include <windows.h>
#include <time.h>
using namespace std;

bool compare(const int* a, const int* b) {
    HANDLE heap = GetProcessHeap();
    SIZE_T A = HeapSize(heap, 0, (LPVOID)a);
    SIZE_T B = HeapSize(heap, 0, (LPVOID)b);

    return A < B;
}

int main() {
    // Инициализация генератора случайных чисел
    srand(time(nullptr));

    // Создание двумерного массива
    int** nums = 0;
    int num_lines;
    cout << "enter the number of rows:";
    cin >> num_lines;
    while (num_lines < 5){
        cout << "the number of lines must be greater than 5:";
        cin >> num_lines;
    }

    // Выделение памяти для строк массива
    nums = (int**)HeapAlloc(GetProcessHeap(), 0, num_lines * sizeof(int*));
    if (!nums) {
        cerr << "Memory allocation error" << endl;
        return 1;
    }

    // Выделение памяти для каждой строки и заполнение случайными данными
    for (int i = 0; i < num_lines; i++) {
        int num_elements = rand() % 10 + 1;

        nums[i] = (int*)HeapAlloc(GetProcessHeap(), 0, num_elements * sizeof(int) + sizeof(int));
        if (!nums[i]) {
            cerr << "Memory allocation error" << endl;
            return 1;
        }

        *(nums[i]) = num_elements;
        for (int j = 0; j < num_elements; j++) {
            nums[i][j + 1] = rand() % 10 + 1;
        }
    }
    cout << "array: " << endl;
    for (int i = 0; i < num_lines; i++) {
        int num_elements = *(nums[i]);

        for (int j = 1; j <= num_elements; j++) {
            cout << nums[i][j] << " ";
        }
        cout << "\n";
    }
    // Сортировка массива по длине строк
    sort(nums, nums + num_lines, compare);

    // Вывод отсортированного массива
    cout << "Sorted array: " << endl;
    for (int i = 0; i < num_lines; i++) {
        int num_elements = *(nums[i]);

        for (int j = 1; j <= num_elements; j++) {
            cout << nums[i][j] << " ";
        }
        cout << "\n";
    }

    // Освобождение памяти
    for (int i = 0; i < num_lines; i++) {
        HeapFree(GetProcessHeap(), 0, nums[i]);
    }
    HeapFree(GetProcessHeap(), 0, nums);

    return 0;
}
