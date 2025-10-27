#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 1. Обмен двух элементов,,,
void Swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 2. Создание матрицы расстояний
void Randmatr(int** matr, int strok, int stolb) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < strok; i++) {
        for (int j = 0; j < stolb; j++) {
            if (i == j)
                matr[i][j] = 0;
            else
                matr[i][j] = rand() % 15 + 1;
        }
    }
}

// 3. Вывод матрицы
void Outputmatr(int** matr, int strok, int stolb) {
    cout << "Matrix:\n";
    for (int i = 0; i < strok; i++) {
        for (int j = 0; j < stolb; j++) {
            cout << matr[i][j] << "\t";
        }
        cout << "\n";
    }
}

// 4. Создание первой перестановки
void Peres(int* arr, int size, int k) {
    arr[0] = k;
    arr[size] = k;
    for (int i = 1, t = 1; i < size; i++, t++) {
        if (t == k)
            t++;
        arr[i] = t;
    }
}

// 5. Вывод перестановки
void OutputPeres(int* P, int cities) {
    for (int i = 0; i < cities; i++) {
        cout << P[i] << " ";
    }
    cout << P[0];  // Показываем возврат в начальный город
}

// 6. Реверс хвоста перестановки
void Inversion(int* P, int cities, int imax) {
    for (int j = cities - 1, i = imax + 1; i < j; i++, j--) {
        Swap(&P[i], &P[j]);
    }
}

// 7. Генерация следующей перестановки
bool Permutation(int* P, int cities) {
    int imax = -1, jmax = -1;

    // Поиск индекса для обмена
    for (int i = 1; i < cities - 1; i++) {
        if (P[i] < P[i + 1])
            imax = i;
    }
    if (imax == -1) return false;

    // Поиск элемента для обмена
    for (int j = imax + 1; j < cities; j++) {
        if (P[imax] < P[j])
            jmax = j;
    }

    // Обмен и реверс
    Swap(&P[imax], &P[jmax]);
    Inversion(P, cities, imax);
    return true;
}

// 8. Вычисление длины маршрута
int PermutationSum(int** Matr, int* P, int cities) {
    int total = 0;
    for (int i = 0; i < cities - 1; i++) {
        int from = P[i] - 1;
        int to = P[i + 1] - 1;

        // Проверка выхода за границы (на всякий случай)
        if (from < 0 || from >= cities || to < 0 || to >= cities) {
            cout << "ERROR: Invalid city index!" << endl;
            return -1;
        }

        total += Matr[from][to];
    }
        return total;
}
