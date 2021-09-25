#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include<time.h>
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(2, 4);
    printf("<-O->");
}
void draw_star(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(2, 4);
    printf("*");
}
void erase_ship(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(0, 0);
    printf("     ");
}
void erase_R(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(0, 0);
    printf(" ");
}
void ammo(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(1, 4);
    printf("A");
}

char cursor(int x, int y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2]; COORD c = { x,y }; DWORD num_read;
    if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
    {
        return '\0';
    }
    else
    {
        return buf[0];
    }
}
void point(int x, int y, int points)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(1, 2);
    printf("point : %d", points);
}
int main()
{
    int i, sx = 0, sy = 0, points = 0;
    int ammoC = 0;//???????????
    int left = 5, right = 6, front = 7, space = 8, stop = 0;
    setcursor(0);
    char ch = ' ';
    int x = 38, y = 20;
    int c[5], d[5];
    int direction = 1000;
    int ammoINFO[5] = { 0,0,0,0,0 };
    int ammos = 0;
    int starC = 0;
    int starINFO[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int stars = 20;
    point(84, 4, points);
    draw_ship(x, 20);
    srand(time(NULL));
    for (i = 0; i < 20; i++)
    {
        sx = rand() % 60 + 10;
        sy = rand() % 3 + 2;
        draw_star(sx, sy);
        starC++;
    }
    do {
        while (1)
        {
            if (_kbhit())
            {
                ch = _getch();
                if (ch == 'a') { direction = left; }
                if (ch == 'd') { direction = right; }
                if (ch == ' ') { ammos = 1; }
            }
            if (direction == left && x > 1)
            {
                erase_ship(x, y);
                draw_ship(--x, y);
            }
            if (direction == right & x < 79)
            {
                erase_ship(x, y);
                draw_ship(++x, y);
            }
            if (ammos == 1 && ammoINFO[ammoC] != 1)
            {
                ammoINFO[ammoC] = 1;
                c[ammoC] = x + 2;
                d[ammoC] = y - 1;
                ammos = 0;
                ammoC++;
            }
            Sleep(100);

            if (ammoC > 4)
            {
                ammoC = 0;
            }
            fflush(stdin);
                if (starC < 20)
                {
                    sx = rand() % 60 + 10;
                    sy = rand() % 3 + 2;
                    draw_star(sx, sy);
                    starC++;
                }
            
            for (i = 0; i < 5; i++)
            {
                if (ammoINFO[i] == 1)
                {
                    erase_R(c[i], d[i]);
                    if (d[i] == 1)
                    {
                        ammoINFO[i] = 0;
                    }
                    else if(cursor(c[i], d[i] - 1) == '*')
                    {
                        points = points + 100;
                        starC--;
                        point(84, 4, points);
                        Beep(400, 100);
                        erase_R(c[i], --d[i]);
                        ammoINFO[i] = 0;
                    }
                    else
                    {
                        ammo(c[i], --d[i]);
                    }
                }
            }
        }
        Sleep(100);
    } while (ch != 'x');
    return 0;
}