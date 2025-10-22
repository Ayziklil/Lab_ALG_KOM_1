#include <iostream> 
#include "MyLib.h"
using namespace std;

int main() {
    cout << "Traveling Salesman Problem \n";
    int** matrix = nullptr;  
    int Cities = 0, k = 0;

    cout << "How many cities: ";
    cin >> Cities;

    // Проверка корректности ввода
    if (Cities <= 0) {
        cout << "Error: Number of cities must be positive!" << endl;
        return 1;
    }

    // Выделение памяти для матрицы
    matrix = new int* [Cities];
    for (int i = 0; i < Cities; i++) {
        matrix[i] = new int[Cities]();
    }

    Randmatr(matrix, Cities, Cities);
    Outputmatr(matrix, Cities, Cities);

    cout << endl << "Enter city number: ";
    cin >> k;

    // Проверка корректности номера города
    while (k <= 0 || k > Cities) {
        cout << "\nWe have only " << Cities << " cities (1 to " << Cities << ")\nEnter city number: ";
        cin >> k;
    }

    int total = 1;  // Подсчет количества перестановок
    for (int i = 1; i < Cities; i++)
        total *= i;
    cout << endl << "Number of permutations: " << total << endl;

    int* perest = new int[Cities + 1]();
    int* PerestMin = new int[Cities + 1](); 

    Peres(perest, Cities, k);
    OutputPeres(perest, Cities);

    /*cout << "Permutation: ";
    for (int i = 0; i <= Cities; i++) {
        cout << perest[i] << " ";
    }
    cout << endl;*/

    int minSumPermut = PermutationSum(matrix, perest, Cities);  // Минимальная сумма маршрута

    cout << " - Route length number 1: " << minSumPermut << endl;
    PerestMin[Cities] = k;
    for (int i = 0; i < Cities; i++)
        PerestMin[i] = perest[i];  // Сохраняем первую перестановку как минимальная

    int a = 2;
    while (Permutation(perest, Cities) != 0) {
        int flag = PermutationSum(matrix, perest, Cities);
        if (flag < minSumPermut) {
            minSumPermut = flag;  // Сохраняем минимальную сумму перестановки
            PerestMin[Cities] = k;  // Последний элемент - начальный город
            for (int i = 0; i < Cities; i++)  // Сохраняем мин перестановку
                PerestMin[i] = perest[i];
        }
        cout << " - Route length number " << a++ << ": " << flag << endl;
    }

    cout << endl;
    OutputPeres(PerestMin, Cities);
    cout << endl << "Length of the minimum rout: " << minSumPermut;

    // Освобождение памяти
    delete[] perest;
    delete[] PerestMin;
    for (int i = 0; i < Cities; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}