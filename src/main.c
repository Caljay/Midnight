#include <stdlib.h>
#include <ncurses.h>
#include "game.h"



int option = 0;
const uint8_t n_start_menu = 2;
char *start_menu_options[] = {
    "Start",
    "Info",
    "Exit",
};
#define BLACK_ON_WHITE 1


void info_menu() {
    clear();
    move(0,0);
    printw("Use arrow keys to move and backspace to select");
    move(2,0);
    printw("Created by CJH. Uses Geometric Brownian Motion to simulate stock price movement");
    move(5,0);
    printw("Press any key to return to main menu...");
    refresh();
    getch();
    clear();


}
void start_game() {
    curs_set(0);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);


    int key;

    while (1) {

        for (int i = 0; start_menu_options[i] != NULL; i++) {
            if (option == i) {
                //highlight
                attron(COLOR_PAIR(BLACK_ON_WHITE));
                mvprintw(i,0, "%s",start_menu_options[i]);
                attroff(COLOR_PAIR(BLACK_ON_WHITE));
            }
            else {
                mvprintw(i,0, "%s",start_menu_options[i]);
            }



        }
        key = getch();

        if ((key == 'w' || key == KEY_UP) && option > 0) {
            option--;
        }
        if ((key == 's' || key == KEY_DOWN) && option < 2) {
            option++;
        }

        if (key == KEY_BACKSPACE) {
;
            if (option == 2) return;;
            if (option == 1) info_menu();
            if (option == 0) {
                //begin the game
                clear();
                //starting game
            init_game();
                clear();
            }
        }

    }
}
void init_window() {
    initscr();
    clear();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
}
void free_window() {
    endwin();
}
//TODO this entire program could be further optimized, cleaned and fixed
int main()
{
    init_window();
    start_game();
    free_window();
    return 0;



}
