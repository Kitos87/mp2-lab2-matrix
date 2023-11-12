// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц


#include <iostream>
#include <limits>
#include <cstdlib>
#include<ctime>
#include<vector>
#include <iomanip>
#include "../include/tmatrix.h"
using namespace std;

int main() {
    int choice;
    TDynamicVector<double> vector1, vector2, vectorResult;
    TDynamicMatrix<double> matrix1, matrix2, matrixResult;
    setlocale(LC_ALL, "Rus");
    while (true) {
        std::cout << "\n1. Создать вектор" << std::endl;
        std::cout << "2. Создать матрицу" << std::endl;
        std::cout << "3. Показать вектор" << std::endl;
        std::cout << "4. Показать матрицу" << std::endl;
        std::cout << "5. Операции над векторами" << std::endl;
        std::cout << "6. Операции над матрицами" << std::endl;
        std::cout << "7. Выход" << std::endl;
        std::cout << "Выберите опцию: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (choice) {
        case 1: {
            size_t size;
            std::cout << "Введите размер вектора: ";
            std::cin >> size;
            vector1 = TDynamicVector<double>(size);
            std::cout << "Введите элементы вектора: ";
            for (size_t i = 0; i < size; ++i) {
                std::cin >> vector1[i];
            }
            break;
        }
        case 2: {
            size_t size;
            std::cout << "Введите размер матрицы: ";
            std::cin >> size;
            matrix1 = TDynamicMatrix<double>(size);
            std::cout << "Введите элементы матрицы:" << std::endl;
            for (size_t i = 0; i < size; ++i) {
                for (size_t j = 0; j < size; ++j) {
                    std::cin >> matrix1[i][j];
                }
            }
            break;
        }
        case 3: {
            std::cout << "Вектор: " << vector1 << std::endl;
            break;
        }
        case 4: {
            std::cout << "Матрица:" << std::endl << matrix1 << std::endl;
            break;
        }
        case 5: {
            int vectorChoice;
            std::cout << "1. Сложение векторов" << std::endl;
            std::cout << "2. Вычитание векторов" << std::endl;
            std::cout << "3. Скалярное умножение векторов" << std::endl;
            std::cout << "Выберите операцию: ";
            std::cin >> vectorChoice;

            try {
                switch (vectorChoice) {
                case 1: {
                    vector2 = TDynamicVector<double>(vector1.size());
                    std::cout << "Введите элементы второго вектора: ";
                    for (size_t i = 0; i < vector1.size(); ++i) {
                        std::cin >> vector2[i];
                    }
                    vectorResult = vector1 + vector2;
                    std::cout << "Результат сложения: " << vectorResult << std::endl;
                    break;
                }
                default:
                    std::cout << "Неверный выбор операции." << std::endl;
                    break;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Произошла ошибка: " << e.what() << std::endl;
            }
            break;
        }
        case 6: {
            int matrixChoice;
            std::cout << "1. Сложение матриц" << std::endl;
            std::cout << "2. Вычитание матриц" << std::endl;
            std::cout << "3. Умножение матрицы на скаляр" << std::endl;
            std::cout << "4. Умножение матриц" << std::endl;
            std::cout << "Выберите операцию: ";
            std::cin >> matrixChoice;

            try {
                switch (matrixChoice) {
                case 1: {
                    matrix2 = TDynamicMatrix<double>(matrix1.size());
                    std::cout << "Введите элементы второй матрицы:" << std::endl;
                    for (size_t i = 0; i < matrix1.size(); ++i) {
                        for (size_t j = 0; j < matrix1.size(); ++j) {
                            std::cin >> matrix2[i][j];
                        }
                    }
                    matrixResult = matrix1 + matrix2;
                    std::cout << "Результат сложения матриц:" << std::endl << matrixResult << std::endl;
                    break;
                }
                case 2: {
                    matrix2 = TDynamicMatrix<double>(matrix1.size());
                    std::cout << "Введите элементы второй матрицы:" << std::endl;
                    for (size_t i = 0; i < matrix1.size(); ++i) {
                        for (size_t j = 0; j < matrix1.size(); ++j) {
                            std::cin >> matrix2[i][j];
                        }
                    }
                    matrixResult = matrix1 - matrix2;
                    std::cout << "Результат вычитания матриц:" << std::endl << matrixResult << std::endl;
                    break;
                }
                case 3: {
                    double scalar;
                    std::cout << "Введите скалярное значение: ";
                    std::cin >> scalar;
                    matrixResult = matrix1 * scalar;
                    std::cout << "Результат умножения матрицы на скаляр:" << std::endl << matrixResult << std::endl;
                    break;
                }
                case 4: {
                    matrix2 = TDynamicMatrix<double>(matrix1.size());
                    std::cout << "Введите элементы второй матрицы для умножения:" << std::endl;
                    for (size_t i = 0; i < matrix1.size(); ++i) {
                        for (size_t j = 0; j < matrix1.size(); ++j) {
                            std::cin >> matrix2[i][j];
                        }
                    }
                    matrixResult = matrix1 * matrix2;
                    std::cout << "Результат умножения матриц:" << std::endl << matrixResult << std::endl;
                    break;
                }
                default:
                    std::cout << "Неверный выбор операции." << std::endl;
                    break;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Произошла ошибка: " << e.what() << std::endl;
            }
            break;
        }
        case 7:
            return 0; 
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
        std::cout << "Нажмите Enter, чтобы продолжить...";
        std::cin.get();
    }

    return 0;
}




//int main() {
//    const int sizes[] = { 400, 700, 1000, 1500, 2000 };
//    const int tests = 10;
//    cout << left << setw(20) << "Size"
//        << setw(25) << "Average Time (sec) for *"
//        << "Operations" << endl;
//    cout << "-----------------------------------------------------" << endl;
//    for (int size : sizes) {
//        double totalTime = 0.0;
//        for (int t = 0; t < tests; ++t) {
//            {
//                TDynamicMatrix<double> m(size), n(size), result(size);
//                for (int i = 0; i < size; ++i) {
//                    for (int j = 0; j < size; ++j) {
//                        m[i][j] = rand() % 100;
//                        n[i][j] = rand() % 100;
//                    }
//                }
//                clock_t start = clock();
//                result = m * n; 
//                clock_t end = clock();
//                totalTime += double(end - start) / CLOCKS_PER_SEC;
//            }
//        }
//        double averageTime = totalTime / tests;
//        cout << setw(20) << size
//            << setw(25) << averageTime
//            << static_cast<long long>(size) * size * size << endl; 
//    }
//    cout << "Press Enter to exit..." << endl;
//    cin.get();
//    return 0;
//}