#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;
int main() {
	setlocale(0, "");
	srand(time(NULL));
	const int ROWS = 15; //  Количество строк
	const int COLS = 15; // Количество колонн 
	int arr[ROWS][COLS];
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int number = rand() % 3 + 1;
			if (number % 2 == 0) {
				arr[i][j] = 2;
			}
			else {
				arr[i][j] = 0;
			}
		}
	}
	arr[rand() % ROWS][rand() % COLS] = 1;
	int step = 0;
	while (step != 1) {
		for (int i = 0; i < ROWS; i++) {
			cout << endl;
			for (int j = 0; j < COLS; j++) {
				if (arr[i][j] == 2) {
					SetConsoleTextAttribute(console, FOREGROUND_RED); // красим цифру 2 красным
					cout << arr[i][j] << "\t";
				}
				else if (arr[i][j] == 0) {
					SetConsoleTextAttribute(console, FOREGROUND_GREEN); // красим цифру 0 зеленым
					cout << arr[i][j] << "\t";
				}
				else if (arr[i][j] == 7) {
					SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN); // красим цифру 7 оранжевым
					cout << arr[i][j] << "\t";
				}
				else {
					SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // красим цифру 1 синим 
					cout << arr[i][j] << "\t";
				}
			}
		}
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // красим следующие строки выбора белым
		cout <<"\n8 - вперед\n4 - налево\n6 - направо\n2 - вниз\n1 - выход" << endl << endl;
		cin >> step;
		switch (step)
		{
		case 8:
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					if ((arr[i][j] == 1) && (arr[i - 1][j] == 0)) {
						arr[i - 1][j] = 1;
						arr[i][j] = 0;
					}
					if ((arr[i][j] == 1) && (arr[i - 1][j] == 2)) {
						break;
					}
				}
			}
			break;
		case 4:
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					if ((arr[i][j] == 1) && (arr[i][j - 1] == 0)) {
						if (arr[i][COLS - COLS] == 1) {
							break;
						}
						else {
							arr[i][j - 1] = 1;
							arr[i][j] = 0;
						}
					}
					if ((arr[i][j] == 1) && (arr[i][j - 1] == 2)) {
						break;
					}
				}
			}
			break;
		case 6:
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					if ((arr[i][j] == 1) && (arr[i][j + 1] == 0)) {
						if (arr[i][COLS - 1] == 1) {
							break;
						}
						else {
							arr[i][j + 1] = 1;
							arr[i][j] = 0;
							break;
						}
					}
					if ((arr[i][j] == 1) && (arr[i][j + 1] == 2)) {
						break;
					}
				}
			}
			break;
		case 2:
			for (int j = 0; j < COLS; j++) {
				for (int i = 0; i < ROWS; i++) {
					if ((arr[i][j] == 1) && (arr[i + 1][j] == 0)) {
						arr[i + 1][j] = 1;
						arr[i][j] = 0;
						break;
					}
					if ((arr[i][j] == 1) && (arr[i + 1][j] == 2)) {
						break;
					}
				}
			}
			break;
		case 1:
			break;
		}
	}
	return 0;
}
