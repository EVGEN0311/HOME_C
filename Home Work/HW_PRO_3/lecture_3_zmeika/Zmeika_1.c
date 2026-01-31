/*
 * 1. Self collision (snake crashes into itself)
 * 2. Screen boundary exit (wrap OR death - selectable)
 * 3. Rewrite timeout using clock()
 *
 * hw-6 tasks integrated:
 * - self collision implemented, but in standard mode can be OFF
 * - colors for 2 snakes and food
 * - start menu implemented
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define NUM_SNAKES 2
#define MIN_Y  2  // minimum Y to avoid overwriting UI

enum { LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10) };
enum { MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10 };

// ======= GAME SETTINGS (menu can change) =======
static int snake_colors[NUM_SNAKES] = { 1, 6 }; // GREEN, CYAN default
static int game_running = 1;
static int can_eat_snakes = 1;
static int sound_enabled = 1;

// режимы из ДЗ:
static int self_collision_kills = 0; // стандартно НЕ умираем от самопересечения
static int wall_collision_kills = 0; // стандартно телепорт через границы

// game speed (tick) in ms via clock()
static int tick_ms = 120;

// ==============================================

// Structure for control keys
struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

// Standard control keys
struct control_buttons default_controls[NUM_SNAKES] = {
    { KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT },   // arrows for first snake
    { 's', 'w', 'a', 'd' }                       // WASD for second snake
};

// Structure for one tail segment
typedef struct tail_t {
    int x;
    int y;
} tail_t;

// Snake structure
typedef struct snake_t {
    int x;
    int y;
    int direction;
    size_t tsize;            // head + tail segments count
    struct tail_t *tail;     // tail array (MAX_TAIL_SIZE)
    struct control_buttons controls;
    int color_pair;
    int score;
    int is_alive;
} snake_t;

// Food structure
typedef struct food_t {
    int x;
    int y;
    char symbol;
} food_t;

// ============ SOUND ============
void playSound(int type) {
    if (!sound_enabled) return;

    switch(type) {
        case 1: // Food
            printf("\a"); fflush(stdout);
            break;
        case 2: // Snake eaten
            for(int i = 0; i < 3; i++) { printf("\a"); fflush(stdout); usleep(100000); }
            break;
        case 3: // Game over
            for(int i = 0; i < 5; i++) { printf("\a"); fflush(stdout); usleep(50000); }
            break;
        case 4: // Game start
            for(int i = 0; i < 2; i++) { printf("\a"); fflush(stdout); usleep(200000); }
            break;
    }
}

// ============ INIT ============
void initTail(tail_t t[], size_t size) {
    tail_t init_t = {0,0};
    for(size_t i=0; i<size; i++) t[i] = init_t;
}

void initHead(snake_t *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
    head->score = 0;
    head->is_alive = 1;
}

void initSnake(snake_t *head, size_t size, int x, int y, int color_pair) {
    tail_t *tail = (tail_t*) malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    if (!tail) {
        endwin();
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail;

    // tsize = head + tail_count
    head->tsize = size + 1;
    if (head->tsize > (size_t)(MAX_TAIL_SIZE + 1))
        head->tsize = (size_t)(MAX_TAIL_SIZE + 1);

    head->color_pair = color_pair;
}

void initAllSnakes(snake_t snakes[], size_t num_snakes, size_t start_size) {
    for (size_t i = 0; i < num_snakes; i++) {
        int start_x = 10 + (int)i * 20;
        int start_y = 10 + (int)i * 5;

        initSnake(&snakes[i], start_size, start_x, start_y, snake_colors[i]);
        snakes[i].controls = default_controls[i];
    }
}

// ============ FOOD ============
static int isCellBusyBySnake(const snake_t snakes[], size_t n, int x, int y) {
    for (size_t i = 0; i < n; i++) {
        if (!snakes[i].is_alive) continue;
        if (snakes[i].x == x && snakes[i].y == y) return 1;

        size_t tail_len = (snakes[i].tsize > 0) ? (snakes[i].tsize - 1) : 0;
        if (tail_len > MAX_TAIL_SIZE) tail_len = MAX_TAIL_SIZE;

        for (size_t k = 0; k < tail_len; k++) {
            if (snakes[i].tail[k].x == x && snakes[i].tail[k].y == y)
                return 1;
        }
    }
    return 0;
}

void spawnFood(food_t *food, const snake_t snakes[], size_t n, int max_x, int max_y) {
    food->symbol = '#';

    // подбираем позицию, чтобы не попасть в змей
    while (1) {
        food->x = rand() % max_x;
        food->y = (rand() % (max_y - MIN_Y)) + MIN_Y;

        if (!isCellBusyBySnake(snakes, n, food->x, food->y))
            break;
    }
}

void drawFood(food_t *food) {
    attron(COLOR_PAIR(8));
    mvprintw(food->y, food->x, "%c", food->symbol);
    attroff(COLOR_PAIR(8));
}

int checkFood(snake_t *snake, food_t *food) {
    if (snake->x == food->x && snake->y == food->y) {
        if (snake->tsize < (size_t)(MAX_TAIL_SIZE + 1)) {
            snake->tsize++;
        }
        snake->score += 10;
        playSound(1);
        return 1;
    }
    return 0;
}

int checkAllFood(snake_t snakes[], size_t num_snakes, food_t *food) {
    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;
        if (checkFood(&snakes[i], food)) return 1;
    }
    return 0;
}

// ============ MOVEMENT ============

// ВАЖНО: go() теперь НЕ стирает символы сам — мы рисуем кадр целиком через clear() в loop.
void go(snake_t *head) {
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    int nx = head->x;
    int ny = head->y;

    switch(head->direction){
        case LEFT:  nx--; break;
        case RIGHT: nx++; break;
        case UP:    ny--; break;
        case DOWN:  ny++; break;
    }

    if (!wall_collision_kills) {
        // wrap-режим: телепорт
        if (nx < 0) nx = max_x - 1;
        if (nx >= max_x) nx = 0;

        if (ny < MIN_Y) ny = max_y - 1;
        if (ny >= max_y) ny = MIN_Y;
    }

    head->x = nx;
    head->y = ny;
}

// goTail теперь принимает ПРЕДЫДУЩУЮ позицию головы — иначе хвост ломается
void goTail(snake_t *head, int prev_head_x, int prev_head_y) {
    if (!head->is_alive) return;
    if (head->tsize <= 1) return;

    size_t tail_len = head->tsize - 1;
    if (tail_len > MAX_TAIL_SIZE) tail_len = MAX_TAIL_SIZE;

    // shift
    for (size_t i = tail_len - 1; i > 0; i--) {
        head->tail[i] = head->tail[i - 1];
    }

    // first segment takes old head pos
    head->tail[0].x = prev_head_x;
    head->tail[0].y = prev_head_y;
}

// ======= INPUT / DIRECTIONS =======
static int isOpposite(int d1, int d2) {
    return (d1==LEFT && d2==RIGHT) || (d1==RIGHT && d2==LEFT) ||
           (d1==UP   && d2==DOWN)  || (d1==DOWN  && d2==UP);
}

void changeAllDirections(snake_t snakes[], size_t num_snakes, const int32_t key) {
    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;

        int new_dir = snakes[i].direction;

        if (i == 1) {
            // WASD + russian layout support
            switch(key) {
                case 'w': case 'W':
                case 1094: case 1062: // ц / Ц
                    new_dir = UP; break;

                case 's': case 'S':
                case 1099: case 1067: // ы / Ы
                    new_dir = DOWN; break;

                case 'a': case 'A':
                case 1092: case 1060: // ф / Ф
                    new_dir = LEFT; break;

                case 'd': case 'D':
                case 1074: case 1042: // в / В
                    new_dir = RIGHT; break;
            }
        } else {
            if (key == snakes[i].controls.down) new_dir = DOWN;
            else if (key == snakes[i].controls.up) new_dir = UP;
            else if (key == snakes[i].controls.right) new_dir = RIGHT;
            else if (key == snakes[i].controls.left) new_dir = LEFT;
        }

        // запрет на разворот на 180
        if (!isOpposite(snakes[i].direction, new_dir))
            snakes[i].direction = new_dir;
    }
}

// ============ DRAW ============
void drawAllSnakes(snake_t snakes[], size_t num_snakes) {
    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;

        attron(COLOR_PAIR(snakes[i].color_pair));

        // head
        mvprintw(snakes[i].y, snakes[i].x, "@");

        // tail
        size_t tail_len = (snakes[i].tsize > 0) ? (snakes[i].tsize - 1) : 0;
        if (tail_len > MAX_TAIL_SIZE) tail_len = MAX_TAIL_SIZE;

        for (size_t j = 0; j < tail_len; j++) {
            if (snakes[i].tail[j].x || snakes[i].tail[j].y) {
                mvprintw(snakes[i].tail[j].y, snakes[i].tail[j].x, "*");
            }
        }

        attroff(COLOR_PAIR(snakes[i].color_pair));
    }
}

// ============ COLLISIONS ============

// 1) Self collision (IMPLEMENTED)
int isCrush(snake_t *snake) {
    if (!self_collision_kills) return 0; // стандартный режим — не умираем

    if (snake->tsize <= 2) return 0; // хвост слишком мал
    size_t tail_len = snake->tsize - 1;
    if (tail_len > MAX_TAIL_SIZE) tail_len = MAX_TAIL_SIZE;

    for (size_t i = 0; i < tail_len; i++) {
        if (snake->tail[i].x == snake->x && snake->tail[i].y == snake->y) {
            return 1;
        }
    }
    return 0;
}

// 2) Wall collision (only if wall_collision_kills enabled)
int checkWallCollision(snake_t *snake, int max_x, int max_y) {
    if (!wall_collision_kills) return 0;

    if (snake->x < 0 || snake->x >= max_x || snake->y < MIN_Y || snake->y >= max_y)
        return 1;

    return 0;
}

// Check if snakes can eat each other
int checkSnakeEatSnake(snake_t snakes[], size_t num_snakes) {
    int snake_eaten = 0;

    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;

        for (size_t j = 0; j < num_snakes; j++) {
            if (i == j || !snakes[j].is_alive) continue;

            // head vs head
            if (snakes[i].x == snakes[j].x && snakes[i].y == snakes[j].y) {
                snakes[j].is_alive = 0;
                snakes[i].score += 50;
                snake_eaten = 1;
                playSound(2);

                mvprintw(3, 0, "Snake %lu ate snake %lu! +50 points!          ",
                         (unsigned long)(i + 1), (unsigned long)(j + 1));
            }

            // head vs tail
            size_t tail_len = (snakes[j].tsize > 0) ? (snakes[j].tsize - 1) : 0;
            if (tail_len > MAX_TAIL_SIZE) tail_len = MAX_TAIL_SIZE;

            for (size_t k = 0; k < tail_len; k++) {
                if (snakes[i].x == snakes[j].tail[k].x && snakes[i].y == snakes[j].tail[k].y) {
                    // shorten snake j
                    snakes[j].tsize = k + 1; // head + (k segments before this) -> but keep consistent
                    if (snakes[j].tsize < 1) snakes[j].tsize = 1;

                    snakes[i].score += 20;
                    snake_eaten = 1;
                    playSound(1);

                    mvprintw(4, 0, "Snake %lu bit tail of snake %lu! +20 points!  ",
                             (unsigned long)(i + 1), (unsigned long)(j + 1));
                    break;
                }
            }
        }
    }

    return snake_eaten;
}

int checkAllCollisions(snake_t snakes[], size_t num_snakes, int max_x, int max_y) {
    int alive_count = 0;

    for (size_t i = 0; i < num_snakes; i++) {
        if (!snakes[i].is_alive) continue;
        alive_count++;

        if (checkWallCollision(&snakes[i], max_x, max_y)) {
            snakes[i].is_alive = 0;
            playSound(3);
            mvprintw(2, 0, "Snake %lu crashed into wall!                 ", (unsigned long)(i + 1));
        }

        if (isCrush(&snakes[i])) {
            snakes[i].is_alive = 0;
            playSound(3);
            mvprintw(2, 0, "Snake %lu crashed into itself!               ", (unsigned long)(i + 1));
        }
    }

    if (can_eat_snakes) {
        checkSnakeEatSnake(snakes, num_snakes);
    }

    return (alive_count <= 1);
}

// ============ UI / MENU ============
void showWelcomeScreen() {
    clear();
    attron(A_BOLD);
    mvprintw(2, 15, "=== DOUBLE SNAKE GAME ===");
    attroff(A_BOLD);

    mvprintw(4, 5, "Welcome!");
    mvprintw(6, 5, "Snake 1: Arrows");
    mvprintw(7, 5, "Snake 2: WASD (any layout)");
    mvprintw(9, 5, "F10 - exit");
    mvprintw(11, 5, "Press any key...");
    refresh();
    getch();
}

// start menu returns: 1 start, 2 restart(menu again), 0 exit
int startMenu() {
    int selected_snake = 0;
    int selected_option = 0;

    int color_index[NUM_SNAKES] = {0, 4};

    int available_colors[] = { 1, 2, 4, 3, 5, 6, 7 };
    const char* color_names[] = { "Green","Red","Blue","Yellow","Magenta","Cyan","White" };
    int num_colors = 7;

    int key;
    while (1) {
        clear();

        attron(A_BOLD);
        mvprintw(2, 10, "=== DOUBLE SNAKE GAME ===");
        attroff(A_BOLD);

        mvprintw(3, 5, "Sound: %s (M)", sound_enabled ? "ON" : "OFF");
        mvprintw(4, 5, "Self collision kills: %s (C)", self_collision_kills ? "ON" : "OFF");
        mvprintw(5, 5, "Wall collision kills: %s (B)", wall_collision_kills ? "ON" : "OFF");
        mvprintw(6, 5, "Speed tick: %d ms ( - / + )", tick_ms);

        mvprintw(8, 5, "Select snake (TAB):");
        for (int i = 0; i < NUM_SNAKES; i++) {
            if (i == selected_snake) attron(A_REVERSE);
            mvprintw(9, 5 + i * 15, "Snake %d", i + 1);
            if (i == selected_snake) attroff(A_REVERSE);
        }

        mvprintw(11, 5, "Color for snake %d (LEFT/RIGHT):", selected_snake + 1);
        for (int i = 0; i < num_colors; i++) {
            attron(COLOR_PAIR(available_colors[i]));
            if (color_index[selected_snake] == i) attron(A_REVERSE);
            mvprintw(12, 5 + i * 11, "[%s]", color_names[i]);
            if (color_index[selected_snake] == i) attroff(A_REVERSE);
            attroff(COLOR_PAIR(available_colors[i]));
        }

        mvprintw(14, 5, "Options (UP/DOWN + ENTER):");
        const char* options[] = { "Start Game", "Restart", "Exit" };
        for (int i = 0; i < 3; i++) {
            if (i == selected_option) attron(A_REVERSE);
            mvprintw(15 + i, 8, "%s", options[i]);
            if (i == selected_option) attroff(A_REVERSE);
        }

        mvprintw(19, 5, "F10 or Q - exit menu");
        refresh();

        key = getch();
        switch(key) {
            case KEY_UP:   selected_option = (selected_option - 1 + 3) % 3; break;
            case KEY_DOWN: selected_option = (selected_option + 1) % 3; break;

            case KEY_LEFT:
                color_index[selected_snake] = (color_index[selected_snake] - 1 + num_colors) % num_colors;
                break;
            case KEY_RIGHT:
                color_index[selected_snake] = (color_index[selected_snake] + 1) % num_colors;
                break;

            case '\t':
                selected_snake = (selected_snake + 1) % NUM_SNAKES;
                break;

            case 'm': case 'M':
                sound_enabled = !sound_enabled;
                if (sound_enabled) playSound(4);
                break;

            case 'c': case 'C':
                self_collision_kills = !self_collision_kills;
                break;

            case 'b': case 'B':
                wall_collision_kills = !wall_collision_kills;
                break;

            case '-':
                tick_ms += 20;
                if (tick_ms > 300) tick_ms = 300;
                break;

            case '+': case '=':
                tick_ms -= 20;
                if (tick_ms < 40) tick_ms = 40;
                break;

            case '\n':
            case '\r':
                // save colors
                for (int i = 0; i < NUM_SNAKES; i++) {
                    snake_colors[i] = available_colors[color_index[i]];
                }

                if (selected_option == 0) { playSound(4); return 1; }
                if (selected_option == 1) return 2;
                if (selected_option == 2) return 0;
                break;

            case 'q': case 'Q':
            case STOP_GAME:
                return 0;
        }
    }
}

// ============ GAME LOOP (clock) ============
static int msFromClock(clock_t d) {
    // CLOCKS_PER_SEC ticks per second
    return (int)((d * 1000) / CLOCKS_PER_SEC);
}

void playGame() {
    snake_t snakes[NUM_SNAKES];
    initAllSnakes(snakes, NUM_SNAKES, START_TAIL_SIZE);

    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    food_t food;
    spawnFood(&food, snakes, NUM_SNAKES, max_x, max_y);

    int key_pressed = 0;
    int game_over = 0;

    // non-blocking input (replaces timeout)
    nodelay(stdscr, TRUE);

    clock_t last_tick = clock();

    while (game_running && !game_over && key_pressed != STOP_GAME) {
        int k = getch();
        if (k != ERR) key_pressed = k;

        if (key_pressed == 'm' || key_pressed == 'M') {
            sound_enabled = !sound_enabled;
            key_pressed = 0;
        }

        // tick via clock()
        clock_t now = clock();
        int elapsed = msFromClock(now - last_tick);
        if (elapsed < tick_ms) {
            // ничего не обновляем — просто ждём следующий тик
            continue;
        }
        last_tick = now;

        // direction update
        changeAllDirections(snakes, NUM_SNAKES, key_pressed);

        // move all snakes
        for (size_t i = 0; i < NUM_SNAKES; i++) {
            if (!snakes[i].is_alive) continue;

            int prev_x = snakes[i].x;
            int prev_y = snakes[i].y;

            go(&snakes[i]);
            goTail(&snakes[i], prev_x, prev_y);
        }

        // eat food
        if (checkAllFood(snakes, NUM_SNAKES, &food)) {
            spawnFood(&food, snakes, NUM_SNAKES, max_x, max_y);
        }

        // collisions
        if (checkAllCollisions(snakes, NUM_SNAKES, max_x, max_y)) {
            game_over = 1;
            playSound(3);
        }

        // draw
        clear();
        mvprintw(0, 0, "P1: %d | P2: %d | F10-exit | M-sound | C-self(%s) | B-wall(%s) | tick=%dms",
                 snakes[0].score, snakes[1].score,
                 self_collision_kills ? "ON":"OFF",
                 wall_collision_kills ? "ON":"OFF",
                 tick_ms);
        mvprintw(1, 0, "Controls: Arrows / WASD | Eat each other: %s",
                 can_eat_snakes ? "ON" : "OFF");

        drawAllSnakes(snakes, NUM_SNAKES);
        drawFood(&food);
        refresh();
    }

    // game over screen
    if (game_over) {
        clear();
        int winner = -1;
        int best = -999999;
        for (size_t i = 0; i < NUM_SNAKES; i++) {
            if (snakes[i].score > best) {
                best = snakes[i].score;
                winner = (int)i;
            }
        }

        mvprintw(max_y/2, (max_x-30)/2, "GAME OVER");
        mvprintw(max_y/2 + 1, (max_x-30)/2, "Winner: Snake %d  Score=%d", winner+1, snakes[winner].score);
        mvprintw(max_y/2 + 3, (max_x-40)/2, "Press any key to return to menu...");
        nodelay(stdscr, FALSE);
        refresh();
        getch();
    }

    // cleanup
    for (size_t i = 0; i < NUM_SNAKES; i++) {
        free(snakes[i].tail);
    }
}

// ============ MAIN ============
int main() {
    srand((unsigned)time(NULL));

    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);

    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support colors\n");
        return 1;
    }

    start_color();
    init_pair(1, COLOR_GREEN,   COLOR_BLACK);
    init_pair(2, COLOR_RED,     COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);
    init_pair(8, COLOR_RED,     COLOR_BLACK); // food

    showWelcomeScreen();

    while (game_running) {
        int menu_result = startMenu();
        if (menu_result == 1) {
            playGame();
        } else if (menu_result == 2) {
            continue;
        } else {
            game_running = 0;
        }
    }

    endwin();
    return 0;
}
