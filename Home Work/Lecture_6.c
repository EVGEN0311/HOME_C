#include <locale.h>
#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <time.h>

#define W 60
#define H 20
#define MAXLEN 400

#define OBJ_SNAKE1 1
#define OBJ_SNAKE2 2
#define OBJ_FOOD   3

typedef struct { int x, y; } Point;
typedef enum { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } Dir;

typedef struct {
    Point body[MAXLEN];
    int len;
    Dir dir;
    int alive;
} Snake;

typedef struct { int x, y; } Food;

static int mode_ignore_self_collision = 1;
static int speed_delay_ms = 90;

static int colorSnake1 = 1;
static int colorSnake2 = 2;
static int colorFood   = 3;

void setColor(int objectType) {
    for (int i = 1; i <= 6; i++) attroff(COLOR_PAIR(i));
    switch (objectType) {
        case OBJ_SNAKE1: attron(COLOR_PAIR(colorSnake1)); break;
        case OBJ_SNAKE2: attron(COLOR_PAIR(colorSnake2)); break;
        case OBJ_FOOD:   attron(COLOR_PAIR(colorFood));   break;
        default: break;
    }
}

static int inside(int x, int y) {
    return (x >= 1 && x <= W && y >= 1 && y <= H);
}

static int snake_hits_point(const Snake *s, Point p, int start_i) {
    for (int i = start_i; i < s->len; i++) {
        if (s->body[i].x == p.x && s->body[i].y == p.y) return 1;
    }
    return 0;
}

static void draw_border(void) {
    for (int x = 0; x <= W + 1; x++) {
        mvaddch(0, x, '#');
        mvaddch(H + 1, x, '#');
    }
    for (int y = 0; y <= H + 1; y++) {
        mvaddch(y, 0, '#');
        mvaddch(y, W + 1, '#');
    }
}

static void draw_food(const Food *f) {
    setColor(OBJ_FOOD);
    mvaddch(f->y, f->x, '@');
    setColor(0);
}

static void draw_snake(const Snake *s, int objType) {
    if (!s->alive) return;
    setColor(objType);
    mvaddch(s->body[0].y, s->body[0].x, 'O');
    for (int i = 1; i < s->len; i++) mvaddch(s->body[i].y, s->body[i].x, 'o');
    setColor(0);
}

static Point next_head(Point head, Dir d) {
    Point n = head;
    if (d == DIR_UP) n.y--;
    else if (d == DIR_DOWN) n.y++;
    else if (d == DIR_LEFT) n.x--;
    else if (d == DIR_RIGHT) n.x++;
    return n;
}

int isCrush(const Snake *self, const Snake *other, Point newHead) {
    if (!inside(newHead.x, newHead.y)) return 1;
    if (other && other->alive) {
        if (snake_hits_point(other, newHead, 0)) return 1;
    }
    if (!mode_ignore_self_collision) {
        if (snake_hits_point(self, newHead, 1)) return 1;
    }
    return 0;
}

static void spawn_food(Food *f, const Snake *s1, const Snake *s2) {
    while (1) {
        f->x = 1 + rand() % W;
        f->y = 1 + rand() % H;
        Point p = {f->x, f->y};
        if (s1 && s1->alive && snake_hits_point(s1, p, 0)) continue;
        if (s2 && s2->alive && snake_hits_point(s2, p, 0)) continue;
        break;
    }
}

static void snake_grow(Snake *s) {
    if (s->len < MAXLEN) {
        s->body[s->len] = s->body[s->len - 1];
        s->len++;
    }
}

static void snake_shift(Snake *s, Point newHead) {
    for (int i = s->len - 1; i >= 1; i--) s->body[i] = s->body[i - 1];
    s->body[0] = newHead;
}

static int menu_select_color(const char *title, int default_pair) {
    int choice = default_pair;
    while (1) {
        clear();
        mvprintw(2, 2, "%s", title);
        mvprintw(4, 2, "1) Красный");
        mvprintw(5, 2, "2) Синий");
        mvprintw(6, 2, "3) Зелёный");
        mvprintw(7, 2, "4) Жёлтый");
        mvprintw(9, 2, "Текущий выбор: %d", choice);
        mvprintw(11, 2, "1-4 выбрать, Enter подтвердить");
        refresh();

        int c = getch();
        if (c == '1') choice = 1;
        else if (c == '2') choice = 2;
        else if (c == '3') choice = 3;
        else if (c == '4') choice = 4;
        else if (c == '\n' || c == KEY_ENTER) return choice;
    }
}

void startMenu(void) {
    timeout(-1);
    while (1) {
        clear();
        mvprintw(2, 2, "SNAKE (C + ncursesw)");
        mvprintw(4, 2, "1) Стандартный режим (самопересечение НЕ убивает)");
        mvprintw(5, 2, "2) Хардкор (самопересечение УБИВАЕТ)");
        mvprintw(7, 2, "3) Цвета");
        mvprintw(8, 2, "4) Скорость");
        mvprintw(10, 2, "Enter - старт");
        mvprintw(12, 2, "Змейка 1: WASD");
        mvprintw(13, 2, "Змейка 2: стрелки");
        mvprintw(14, 2, "Выход: Q");
        refresh();

        int c = getch();
        if (c == 'q' || c == 'Q') break;
        if (c == '1') mode_ignore_self_collision = 1;
        else if (c == '2') mode_ignore_self_collision = 0;
        else if (c == '3') {
            colorSnake1 = menu_select_color("Цвет змейки 1", colorSnake1);
            colorSnake2 = menu_select_color("Цвет змейки 2", colorSnake2);
            colorFood   = menu_select_color("Цвет еды", colorFood);
        } else if (c == '4') {
            while (1) {
                clear();
                mvprintw(2, 2, "Delay (ms): %d", speed_delay_ms);
                mvprintw(4, 2, "+ быстрее");
                mvprintw(5, 2, "- медленнее");
                mvprintw(6, 2, "Enter назад");
                refresh();
                int k = getch();
                if (k == '+') { if (speed_delay_ms > 30) speed_delay_ms -= 10; }
                else if (k == '-') { if (speed_delay_ms < 300) speed_delay_ms += 10; }
                else if (k == '\n' || k == KEY_ENTER) break;
            }
        } else if (c == '\n' || c == KEY_ENTER) {
            break;
        }
    }
}

int main(void) {
    setlocale(LC_ALL, ".UTF-8");
    srand((unsigned)time(NULL));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    leaveok(stdscr, TRUE);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED,    COLOR_BLACK);
        init_pair(2, COLOR_BLUE,   COLOR_BLACK);
        init_pair(3, COLOR_GREEN,  COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_CYAN,   COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA,COLOR_BLACK);
    }

    startMenu();

    Snake s1 = {0}, s2 = {0};
    Food food = {0};

    s1.len = 5; s1.dir = DIR_RIGHT; s1.alive = 1;
    for (int i = 0; i < s1.len; i++) { s1.body[i].x = 10 - i; s1.body[i].y = 5; }

    s2.len = 5; s2.dir = DIR_LEFT; s2.alive = 1;
    for (int i = 0; i < s2.len; i++) { s2.body[i].x = 50 + i; s2.body[i].y = 15; }

    spawn_food(&food, &s1, &s2);

    int score1 = 0, score2 = 0;

    timeout(speed_delay_ms);

    while (1) {
        int c = getch();
        if (c == 'q' || c == 'Q') break;

        if (c == 'w' || c == 'W') { if (s1.dir != DIR_DOWN) s1.dir = DIR_UP; }
        else if (c == 's' || c == 'S') { if (s1.dir != DIR_UP) s1.dir = DIR_DOWN; }
        else if (c == 'a' || c == 'A') { if (s1.dir != DIR_RIGHT) s1.dir = DIR_LEFT; }
        else if (c == 'd' || c == 'D') { if (s1.dir != DIR_LEFT) s1.dir = DIR_RIGHT; }
        else if (c == KEY_UP) { if (s2.dir != DIR_DOWN) s2.dir = DIR_UP; }
        else if (c == KEY_DOWN) { if (s2.dir != DIR_UP) s2.dir = DIR_DOWN; }
        else if (c == KEY_LEFT) { if (s2.dir != DIR_RIGHT) s2.dir = DIR_LEFT; }
        else if (c == KEY_RIGHT) { if (s2.dir != DIR_LEFT) s2.dir = DIR_RIGHT; }

        if (s1.alive) {
            Point nh = next_head(s1.body[0], s1.dir);
            if (isCrush(&s1, &s2, nh)) s1.alive = 0;
            else {
                snake_shift(&s1, nh);
                if (nh.x == food.x && nh.y == food.y) {
                    snake_grow(&s1);
                    score1 += 10;
                    spawn_food(&food, &s1, &s2);
                }
            }
        }

        if (s2.alive) {
            Point nh = next_head(s2.body[0], s2.dir);
            if (isCrush(&s2, &s1, nh)) s2.alive = 0;
            else {
                snake_shift(&s2, nh);
                if (nh.x == food.x && nh.y == food.y) {
                    snake_grow(&s2);
                    score2 += 10;
                    spawn_food(&food, &s1, &s2);
                }
            }
        }

        erase();
        draw_border();
        mvprintw(H + 3, 2, "Score1=%d  Score2=%d  Mode=%s  (Q-exit)",
                 score1, score2, mode_ignore_self_collision ? "STANDARD" : "HARD");
        draw_food(&food);
        draw_snake(&s1, OBJ_SNAKE1);
        draw_snake(&s2, OBJ_SNAKE2);

        wnoutrefresh(stdscr);
        doupdate();

        if (!s1.alive && !s2.alive) {
            timeout(-1);
            mvprintw(H/2, (W/2)-10, "GAME OVER. Press any key.");
            refresh();
            getch();
            break;
        }
    }

    endwin();
    return 0;
}
