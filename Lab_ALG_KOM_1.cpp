#include <iostream>
#include "MyLib.h"
using namespace std;

int main() {
    cout << "Traveling Salesman Problem \n";

    int** matrix = nullptr;
    int Cities = 0;

    // 1. Ввод количества городов
    cout << "How many cities: ";
    cin >> Cities;

    if (Cities <= 0) {
        cout << "Error: Number of cities must be positive!" << endl;
        return 1;
    }

    // Создаем матрицу
    matrix = new int* [Cities];
    for (int i = 0; i < Cities; i++) {
        matrix[i] = new int[Cities]();
    }

    Randmatr(matrix, Cities, Cities);
    Outputmatr(matrix, Cities, Cities);

    // 2. Ввод количества стартовых городов
    int num_k = 0;
    cout << "How many starting cities (k): ";
    cin >> num_k;

    if (num_k <= 0 || num_k > Cities) {
        cout << "Error: Number of k must be between 1 and " << Cities << endl;
        return 1;
    }

    // 3. Ввод конкретных номеров k
    int* k_values = new int[num_k];
    cout << "Enter " << num_k << " starting city numbers (1 to " << Cities << "):" << endl;

    for (int i = 0; i < num_k; i++) {
        cout << "k" << (i + 1) << ": ";
        cin >> k_values[i];

        // Проверка корректности
        while (k_values[i] <= 0 || k_values[i] > Cities) {
            cout << "Invalid city! Enter 1 to " << Cities << ": ";
            cin >> k_values[i];
        }
    }

    // 4. Вычисление для каждого k
    for (int idx = 0; idx < num_k; idx++) {
        int k = k_values[idx];

        cout << "\nCALCULATING FOR STARTING CITY " << k  << endl;

        int total = 1;
        for (int i = 1; i < Cities; i++)
            total *= i;
        cout << "Number of permutations: " << total << endl;

        int* perest = new int[Cities + 1]();
        int* PerestMin = new int[Cities + 1]();

        Peres(perest, Cities, k);

        int minSumPermut = PermutationSum(matrix, perest, Cities);
        cout << " - ";
        OutputPeres(perest, Cities);
        cout << " - Route length number 1: " << minSumPermut << endl;

        PerestMin[Cities] = k;
        for (int i = 0; i < Cities; i++)
            PerestMin[i] = perest[i];

        int a = 2;
        while (Permutation(perest, Cities) != 0) {
            int flag = PermutationSum(matrix, perest, Cities);
            if (flag < minSumPermut) {
                minSumPermut = flag;
                PerestMin[Cities] = k;
                for (int i = 0; i < Cities; i++)
                    PerestMin[i] = perest[i];
            }
            cout << " - ";
            OutputPeres(perest, Cities);
            cout << " - Route length number " << a++ << ": " << flag << endl;
        }

        cout << "OPTIMAL ROUTE for city " << k << ": ";
        OutputPeres(PerestMin, Cities);
        cout << endl << "Minimum length: " << minSumPermut << endl;

        delete[] perest;
        delete[] PerestMin;
    }

    // Освобождение памяти
    delete[] k_values;
    for (int i = 0; i < Cities; i++)
        delete[] matrix[i];
    delete[] matrix;

    cout << "\nAll calculations completed!" << endl;
    return 0;
}