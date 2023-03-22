#include <ncurses.h>  //-lcurses флаг для компиляции
#include <stdio.h>
#include <unistd.h>

void print_field(int size_horizon, int size_vertically, int Lrocet_posY, int Rrocet_posY, int Ball_posY,
                 int Ball_posX, int Point_left, int Point_right);

int main() {
    //Пермененные для подсчета очков
    int Point_left = 0;
    int Point_right = 0;
    //Переменные для нахождения позиции ракетки
    int Lrocet_posY = 13;
    int Lrocket_posX = 4;
    int Rrocet_posY = 13;
    int Rrocet_posX = 74;
    //Переменные для мяча
    int Ball_posX = 5;
    int Ball_posY = 12;
    int Collision_X = 1;
    int Collision_Y = 1;
    // cкороcть игры
    int speed = 1;
    //Для запуска риал-тайма
    initscr();
    //Отключение режима ожидания нажатия кнопки
    nodelay(stdscr, TRUE);
    int size_horizon = 80;
    int size_vertically = 25;
    while (1) {
        print_field(size_horizon, size_vertically, Lrocet_posY, Rrocet_posY, Ball_posY, Ball_posX, Point_left,
                    Point_right);
        char s = getch();
        //При нажатии активируем функцию идти вверх
        if (s == 'a' || s == 'A') {
            if (Lrocet_posY > 3) Lrocet_posY--;
            //При нажатии активируем функцию идти ввниз
        } else if (s == 'z' || s == 'Z') {
            if (Lrocet_posY < 23) Lrocet_posY++;
        } else if (s == 'k' || s == 'K') {
            if (Rrocet_posY > 3) Rrocet_posY--;

        } else if (s == 'm' || s == 'M') {
            if (Rrocet_posY < 23) Rrocet_posY++;
        }
        //обработка столкновений
        if (Collision_X == -1) {
            Ball_posX -= speed;
        }
        if (Collision_X == 1) {
            Ball_posX += speed;
        }
        if (Collision_Y == 1) {
            Ball_posY -= speed;
        }
        if (Collision_Y == -1) {
            Ball_posY += speed;
        }
        if (Ball_posY == 23) {
            Collision_Y = 1;
        }
        if (Ball_posY == 1) {
            Collision_Y = -1;
        }
        //Проверка на косание правой ракетки
        if (Ball_posX == Rrocet_posX &&
            (Ball_posY == Rrocet_posY || Ball_posY == Rrocet_posY - 1 || Ball_posY == Rrocet_posY - 2))
            Collision_X = -1;
        //Проверка на косание левой ракетки
        if (Ball_posX == Lrocket_posX &&
            (Ball_posY == Lrocet_posY || Ball_posY == Lrocet_posY - 1 || Ball_posY == Lrocet_posY - 2))
            Collision_X = 1;
        //При попадении засчитывать очки
        //Если забил левый игрок начинает правый
        if (Ball_posX == 79) {
            Collision_X = -Collision_X;
            //При попадении засчитывать очки
            Point_left++;
            Ball_posX = 74;
            Ball_posY = 12;
            Lrocet_posY = 13;
            Rrocet_posY = 13;
        }
        //Если забил правый игрок начинает левый
        if (Ball_posX == 0) {
            Collision_X = -Collision_X;
            //При попадении засчитывать очки
            Point_right++;
            Ball_posX = 5;
            Ball_posY = 12;
            Lrocet_posY = 13;
            Rrocet_posY = 13;
        }
        //Задает задержку чтобы мяч не летал как сумашедший
        usleep(50000);
        if (Point_left == 21 || Point_right == 21) {
            break;
        }
        //отчиста терминала
    }
    nodelay(stdscr, FALSE);
    if (Point_left > Point_right) {
        printw("________________________PLAYER LEFT WINNER!!!!!!!!!!___________________________\n\n");
    } else {
        printw("________________________PLAYER RIGHT WINNER!!!!!!!!!!__________________________\n\n");
    }
    refresh();
    //Ждем нажатия чтобы сразу не убирать надпись победителя
    getch();
    endwin();
}

void print_field(int size_horizon, int size_vertically, int Lrocet_posY, int Rrocet_posY, int Ball_posY,
                 int Ball_posX, int Point_left, int Point_right) {
    clear();
    printw("%39d : %d\n", Point_left, Point_right);
    // cтолбцы
    for (int i = 0; i < size_vertically; i++) {
        // cтроки
        for (int j = 0; j < size_horizon; j++) {
            //Печатаем верх и низ поля
            if ((i == 0 && j != 0 && j != size_horizon - 1) ||
                (i == size_vertically - 1 && j != 0 && j != size_horizon - 1)) {
                printw("-");
            }
            //Печатаем cтенки и центр поля
            else if (j == 0 || j == size_horizon - 1 || j == 40) {
                printw("|");
            }
            //Печатаем положение ракеток
            else if ((j == 4) && (i == Lrocet_posY || i == Lrocet_posY - 1 || i == Lrocet_posY - 2)) {
                printw("|");
            } else if ((j == size_horizon - 5) &&
                       (i == Rrocet_posY || i == Rrocet_posY - 1 || i == Rrocet_posY - 2)) {
                printw("|");
            }
            //Риcуем мяч
            else if ((i == Ball_posY) && (j == Ball_posX)) {
                printw("o");
            } else
                printw(" ");
        }
        printw("\n");
    }
}