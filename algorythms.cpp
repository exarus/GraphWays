// algorythms.cpp - програмний код функцій для пошуку найкоротших шляхів
// у орієнтованому графі

#include "algorythms.h"
#ifdef MAX_DISTANCE
#undef MAX_DISTANCE
#endif

#ifndef MIN_DISTANCE
#undef MIN_DISTANCE
#endif

#define MAX_DISTANCE 2147483647
#define MIN_DISTANCE -2147483648

// =========================== РЕАЛІЗАЦІЯ ===================================

int **shortestPathsByFloyd(int **D0, int n, int **&renewMatrix)
{
    // Знаходимо матрицю найкоротших відстаней за алгоритмом Флойда-Уоршелла
    // та заповнюємо матрицю відновлення шляху
    int **D = shortestPathsByFloydWithoutNegativeLoopCheck(D0, n,
                                                           renewMatrix);

    // Модифікуємо матрицю, враховуючи цикли з від'ємними вагами
    int **C = negativeLoopCheck(D, n);

    // Очищуємо стару матрицю
    for (int i = 0; i < n; ++i) {
        delete[] D[i];
    }
    delete D;

    return C;   // Повертаємо модифіковану матрицю
}

int **shortestPathsByDantzig(int **D0, int n, int **&renewMatrix)
{
    // Знаходимо матрицю найкоротших відстаней за алгоритмом Данцига
    // та заповнюємо матрицю відновлення шляху
    int **D = shortestPathsByDantzigWithoutNegativeLoopCheck(D0, n,
                                                             renewMatrix);

    // Модифікуємо матрицю, враховуючи цикли з від'ємними вагами
    int **C = negativeLoopCheck(D, n);

    // Очищуємо стару матрицю
    for (int i = 0; i < n; ++i) {
        delete[] D[i];
    }
    delete D;

    return C;  // Повертаємо модифіковану матрицю
}

int **shortestPathsByFloydWithoutNegativeLoopCheck(int **D0, int n,
                                                   int **&renewMatrix)
{
    // підготока матриці попередніх вершин для заповнення
    prepareRenewMatrix(renewMatrix, n);

    // для початку роботи алгоритму ініціалізуємо матрицю відстаней
    int **D = copyOf(D0, n);

    // Цикл спроб скоротити шляхи через перші k вершин
    for (int k = 0; k < n; ++k) {

        // Оновлення матриці відстаней для кожного k
        for (int i = 0; i < n; ++i) {

            // Якщо одне із нових ребер не існує,
            // то шлях не може пролягати через нього
            if (D[i][k] < MAX_DISTANCE) {
                for (int j = 0; j < n; ++j) {

                    // Якщо одне із нових ребер не існує,
                    // то шлях не може пролягати через нього
                    if (D[k][j] < MAX_DISTANCE) {

                        // Якщо шлях через вершину k менший, то виконати
                        // релаксацію шляху
                        if (D[i][j] > sum(D[i][k], D[k][j])) {

                            // оновлюємо вагу
                            D[i][j] = sum(D[i][k], D[k][j]);

                            // оновлюємо матрицю відновлення
                            renewMatrix[i][j] = renewMatrix[k][j];
                        }
                    }
                }
            }
        }
    }

    // Повертаємо матрицю найкоротших відстаней
    return D;
}

int **shortestPathsByDantzigWithoutNegativeLoopCheck(int **D0, int n,
                                                     int **&renewMatrix)
{
    prepareRenewMatrix(renewMatrix, n);// підготока матриці відновлення
    int **D = copyOf(D0, n);           // спочатку потрібна матриця відстаней

    // У циклі поступово збільшуємо порядок нових матриць
    for (int m = 0; m < n; ++m) {

        // оновлюємо значення у новій матриці порядку m
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < m; ++i) {

                // Заповнення нового рядку m. Перебирання кожної
                // з вершин попередньої матриці як проміжної
                relaxPath(m, j, i, D, renewMatrix);

                // Заповнення нового стовпця. Перебирання кожної з
                // вершин попередньої матриці як проміжної
                relaxPath(i, j, m, D, renewMatrix);

                // Релаксування старої матриці, базуючись на даних
                // нового стовпця та рядку
                relaxPath(i, m, j, D, renewMatrix);
            }
        }
    }

    // повертаємо матрицю найкоротших відстаней
    return D;
}

void relaxPath(int from, int through, int to, int **D, int **&P)
{
    // Якщо шлях через проміжну вершину існує
    if (D[from][through] != MAX_DISTANCE &&
            D[through][to] != MAX_DISTANCE) {

        // вага шляху через проміжну вершину
        int newWeight = sum(D[from][through], D[through][to]);

        // Якщо нова вага менша за стару
        if (newWeight < D[from][to]) {

            // оновлюємо нову матрицю найкоротших відстаней
            D[from][to] = newWeight;

            // Оновлюємо матрицю відновлення
            P[from][to] = P[through][to];
        }
    }
}

int **negativeLoopCheck(int **D, int n)
{
    int **C = copyOf(D, n); // ініціалізуємо матрицю для перевірки

    // Цикл перебору вершин, що можуть лежати в негативному циклі
    for (int k = 0; k < n; ++k) {

        // Якщо виявилось, що вершина k лежить у від'ємному циклі
        if (C[k][k] < 0) {

            // перебираємо усі вершини, шлях між якими пролягає через цикл
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {

                    // Якщо шлях існує, то найменша вага E(i, j)
                    if ((C[i][k] < MAX_DISTANCE) &&
                            (C[k][j] < MAX_DISTANCE)) {
                        C[i][j] = MIN_DISTANCE;
                    }
                }
            }
        }
    }

    return C; // Повертаємо оновлену матрицю
}

int sum(int operand1, int operand2)
{
    // Якщо сума перевищує максимальне значення для 32-бітної
    // розрядної сітку, то повертаємо її максимальне значення
    if ((operand1 > 0) && (operand2 > 0) &&
            (MAX_DISTANCE - operand2 < operand1)) {
        return MAX_DISTANCE;
    }

    // Якщо сума перевищує максимальне значення для 32-бітної
    // розрядної сітку, то повертаємо її максимальне значення
    if ((operand1 < 0) && (operand2 < 0) &&
            (MIN_DISTANCE - operand2 > operand1)) {
        return MIN_DISTANCE;
    }

    // Якщо переповнень немає повертаємо сумму
    return operand1 + operand2;
}

int **copyOf(int **matrix, int size) {

    // Виділення памяті під нову матрицю
    int **newMatrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        newMatrix[i] = new int[size];

        // Заповнення нової матриці
        for (int j = 0; j < size; ++j) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    // Повернути копію матриці matrix
    return newMatrix;
}


int **prepareRenewMatrix(int **&renewMatrix, int size)
{
    // Инициализация матрицы
    renewMatrix = new int* [size];
    for (int i = 0; i < size; ++i) {
        renewMatrix[i] = new int [size];
        for (int j = 0; j < size; ++j) {
            renewMatrix[i][j] = i + 1;
        }
        renewMatrix[i][i] = 0;
    }
    return renewMatrix;
}
