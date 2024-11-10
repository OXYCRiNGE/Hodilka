#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h> // Для kbhit() и getch()

using namespace std;

const int ROWS = 17; // Увеличили размер для границ
const int COLS = 17;

// Функция для вывода массива с цветами
void printArray(int arr[ROWS][COLS], HANDLE console, int score) {
    system("cls"); // Очистка экрана
    cout << "Счет: " << score << endl;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (arr[i][j] == 2) {
                SetConsoleTextAttribute(console, FOREGROUND_RED); // Стена
                cout << '#';
            }
            else if (arr[i][j] == 0) {
                cout << ' '; // Пустое пространство
            }
            else if (arr[i][j] == 3) {
                SetConsoleTextAttribute(console, FOREGROUND_GREEN); // Кристалл
                cout << '*';
            }
            else if (arr[i][j] == 4) {
                SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Граница
                cout << '/';
            }
            else {
                SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Игрок
                cout << '@';
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main() {
    setlocale(0, "");
    srand(static_cast<unsigned>(time(NULL)));

    int arr[ROWS][COLS];
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Инициализация массива случайными значениями 0, 2 и 3
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
                arr[i][j] = 4; // Граница карты
            }
            else {
                int number = rand() % 20;
                if (number < 2) arr[i][j] = 2; // Стена с вероятностью 10%
                else if (number == 3) arr[i][j] = 3; // Кристалл с вероятностью 5%
                else arr[i][j] = 0; // Пустое место
            }
        }
    }

    // Размещение игрока в случайной позиции внутри границ
    int playerX, playerY;
    do {
        playerX = rand() % (ROWS - 2) + 1;
        playerY = rand() % (COLS - 2) + 1;
    } while (arr[playerX][playerY] != 0);
    arr[playerX][playerY] = 1;

    int score = 0;
    bool running = true;

    // Первоначальный вывод массива
    printArray(arr, console, score);

    while (running) {
        // Проверка нажатия клавиши
        if (_kbhit()) {
            char key = _getch();
            int newX = playerX, newY = playerY;

            switch (key) {
            case 'w': case 'W': case 72: // Вверх (W или стрелка вверх)
                if (playerX > 1 && arr[playerX - 1][playerY] != 2 && arr[playerX - 1][playerY] != 4) newX--;
                break;
            case 's': case 'S': case 80: // Вниз (S или стрелка вниз)
                if (playerX < ROWS - 2 && arr[playerX + 1][playerY] != 2 && arr[playerX + 1][playerY] != 4) newX++;
                break;
            case 'a': case 'A': case 75: // Влево (A или стрелка влево)
                if (playerY > 1 && arr[playerX][playerY - 1] != 2 && arr[playerX][playerY - 1] != 4) newY--;
                break;
            case 'd': case 'D': case 77: // Вправо (D или стрелка вправо)
                if (playerY < COLS - 2 && arr[playerX][playerY + 1] != 2 && arr[playerX][playerY + 1] != 4) newY++;
                break;
            case 27: // ESC для выхода
                running = false;
                break;
            }

            // Проверка на сбор кристалла
            if (arr[newX][newY] == 3) {
                score++;
            }

            // Обновляем позицию игрока, если она изменилась
            if (newX != playerX || newY != playerY) {
                arr[playerX][playerY] = 0;
                playerX = newX;
                playerY = newY;
                arr[playerX][playerY] = 1;

                // Обновляем консоль только при изменении позиции
                printArray(arr, console, score);
            }
        }
    }

    system("cls");
    cout << "Игра завершена. Ваш финальный счет: " << score << endl;
    return 0;
}
