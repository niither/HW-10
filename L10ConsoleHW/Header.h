using namespace std;

enum GameObject : short { HALL, WALL, COIN, ENEMY };
enum Color : short {
    BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
    PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN,
    CYAN, RED, PINK, YELLOW, WHITE
};
enum Key : short {
    LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80,
    ENTER = 13, SPACE = 32, ESCAPE = 27, BACKSPACE = 8
};

void initializeMap(int map[][65], int height, int width);
void renderMap(HANDLE h, int map[][65], int height, int width);
void initializeHero(HANDLE h, COORD& hero, int map[][65]);
void moveHero(HANDLE h, COORD& hero, int map[][65], int code, bool& has_been_moved, COORD& old_position);
void handleInteractions(HANDLE h, COORD hero, int map[][65], int& coins_collected, int width);

void initializeMap(int map[][65], int height, int width) {
    srand(time(0));
    rand();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x] = rand() % 4; // 0 1 2 3
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                map[y][x] = GameObject::WALL;
            if (x == 0 && y == 2 ||
                x == 1 && y == 2 ||
                x == 2 && y == 2 ||
                x == width - 1 && y == height - 3 ||
                x == width - 2 && y == height - 3 ||
                x == width - 3 && y == height - 3)
                map[y][x] = GameObject::HALL;
            if (map[y][x] == GameObject::ENEMY) {
                int r = rand() % 10;
                if (r != 0) {
                    map[y][x] = GameObject::HALL;
                }
            }
        }
    }
}

void renderMap(HANDLE h, int map[][65], int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (map[y][x]) {
            case GameObject::HALL:
                SetConsoleTextAttribute(h, Color::BLACK);
                cout << " ";
                break;
            case GameObject::WALL:
                SetConsoleTextAttribute(h, Color::DARKGREEN);
                cout << (char)178;
                break;
            case GameObject::COIN:
                SetConsoleTextAttribute(h, Color::YELLOW);
                cout << ".";
                break;
            case GameObject::ENEMY:
                SetConsoleTextAttribute(h, Color::RED);
                cout << "O";
                break;
            }
        }
        cout << "\n";
    }
}

void initializeHero(HANDLE h, COORD& hero, int map[][65]) {
    hero.X = 0;
    hero.Y = 2;
    SetConsoleCursorPosition(h, hero);
    SetConsoleTextAttribute(h, Color::BLUE);
    cout << "O";
}

void moveHero(HANDLE h, COORD& hero, int map[][65], int code, bool& has_been_moved, COORD& old_position) {
    old_position = hero;
    has_been_moved = false;
    switch (code) {
    case Key::LEFT:
        if (hero.X > 0 && map[hero.Y][hero.X - 1] != GameObject::WALL) {
            has_been_moved = true;
            hero.X--;
        }
        break;
    case Key::RIGHT:
        if (map[hero.Y][hero.X + 1] != GameObject::WALL) {
            has_been_moved = true;
            hero.X++;
        }
        break;
    case Key::UP:
        if (map[hero.Y - 1][hero.X] != GameObject::WALL) {
            has_been_moved = true;
            hero.Y--;
        }
        break;
    case Key::DOWN:
        if (map[hero.Y + 1][hero.X] != GameObject::WALL) {
            has_been_moved = true;
            hero.Y++;
        }
        break;
    }
    if (has_been_moved) {
        SetConsoleCursorPosition(h, old_position);
        SetConsoleTextAttribute(h, Color::BLACK);
        cout << " ";
        SetConsoleCursorPosition(h, hero);
        SetConsoleTextAttribute(h, Color::BLUE);
        cout << "O";
    }
}

void handleInteractions(HANDLE h, COORD hero, int map[][65], int& coins_collected, int width) {
    if (map[hero.Y][hero.X] == GameObject::COIN) {
        coins_collected++;
        map[hero.Y][hero.X] = GameObject::HALL;
        COORD coins_info;
        coins_info.X = width + 1;
        coins_info.Y = 0;
        SetConsoleCursorPosition(h, coins_info);
        SetConsoleTextAttribute(h, Color::DARKYELLOW);
        cout << "COINS: ";
        SetConsoleTextAttribute(h, Color::YELLOW);
        cout << coins_collected;
    }
    if (map[hero.Y][hero.X] == GameObject::ENEMY) {
        cout << "ENEMY";
    }
}