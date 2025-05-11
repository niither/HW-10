#include <iostream>
#include <windows.h> // COORD HANDLE SetConsoleTextAttribute SetConsoleCursorPosition
#include <conio.h> // _getch
#include "Header.h"
using namespace std;

int main() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("title Bomberman");

    // Hide cursor
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 100;
    SetConsoleCursorInfo(h, &cursor);

    const int HEIGHT = 25;
    const int WIDTH = 65;
    int map[HEIGHT][WIDTH] = {};

    initializeMap(map, HEIGHT, WIDTH);
    renderMap(h, map, HEIGHT, WIDTH);

    COORD hero;
    initializeHero(h, hero, map);

    int coins_collected = 0;
    COORD coins_info;
    coins_info.X = WIDTH + 1;
    coins_info.Y = 0;
    SetConsoleCursorPosition(h, coins_info);
    SetConsoleTextAttribute(h, Color::DARKYELLOW);
    cout << "COINS: ";
    SetConsoleTextAttribute(h, Color::YELLOW);
    cout << coins_collected;

    while (true) {
        int code = _getch();
        if (code == 224) {
            code = _getch();
        }

        COORD old_position;
        bool has_been_moved = false;
        moveHero(h, hero, map, code, has_been_moved, old_position);
        if (has_been_moved) {
            handleInteractions(h, hero, map, coins_collected, WIDTH);
        }
    }

    Sleep(INFINITE);
}