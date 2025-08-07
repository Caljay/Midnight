#include "game.h"

#include <math.h>
#include <ncurses.h>
#include <string.h>

#include "News.h"
#include "Player.h"
//TODO
//BUY/SELLING
//ADD THE NEWS
//ADD END OF GAME
#define PRINT_DELAY_MS 25
#define POSITIVE_RETURN 15
#define NEGATIVE_RETURN (-15)


short menu_option;
float calculate_percent_change(float last, float current) {

    if (last < 0) last *= -1;
    return last < 0 ? ((current - last) / (last*-1)) : ((current - last) / (last));

}

void preword() {
    int x,y;
    curs_set(0);

    const char preword1[] = "You just got fired from your job and with a new baby on the way your wife is asking if you can stay home and watch him. You ethusastically accept but realize that babies dont do much besides eat poop and sleep.";
    const char preword2[] = "Wanting to contribute to the growing bills you take some money that you have saved and open an account on this new website...";

    clear();
    for (int i = 0; i < strlen(preword1); i++) {
        addch(preword1[i]);
        delay_output(PRINT_DELAY_MS);
        refresh();

    }
    getyx(stdscr, y,x);
    y+=2;
    x = 0;
    move(y,0);
    for (int i = 0; i < strlen(preword2); i++) {
        addch(preword2[i]);
        delay_output(PRINT_DELAY_MS);
        refresh();

    }
    getyx(stdscr, y,x);
    y+=3;
    x = 0;
    move(y,x);
    addstr("Press any key to continue...");

    refresh();


    flushinp();
    getch();



}

//TODO add the end of the game
void end_game(struct Player* player) {
    calculateNetWorth(player);
    clear();
    int x,y;
    curs_set(0);

    static const char end_game_std[] = "Your child is going to be starting preschool soon and you are now prepared to show your wife what you have done the past 5 years.";
    static const char end_game_neutral[] = "You started with $%d and now have $%lf. Your wife is neither disappointed nor pleased with this activiety ";
    static const char end_game_negative[] = "You lost your family %lf dollars from the starting $%lf and your wife is saying you have a gambling addiction";
    static const char end_game_positive[] = "From the starting $%d you now have $%lf. Your family is overjoyed at this return. They think you might have a real talent for this.";
    char* placeholder = malloc(sizeof(char)*100);

    clear();
    for (int i = 0; i < strlen(end_game_std); i++) {
        addch(end_game_std[i]);
        delay_output(PRINT_DELAY_MS);
        refresh();

    }
    addstr("\n");
    float percent_change = calculate_percent_change(STARTING_CASH, player->totalNetWorth);


    if (percent_change >= POSITIVE_RETURN) {
        sprintf(placeholder, end_game_positive, STARTING_CASH, player->totalNetWorth);

        for(int i = 0; i < strlen(placeholder); i++) {
            addch(placeholder[i]);
            delay_output(PRINT_DELAY_MS);
            refresh();

        }
    }
    else if (percent_change <= NEGATIVE_RETURN) {
        sprintf(placeholder, end_game_neutral, STARTING_CASH, player->totalNetWorth);

        for(int i = 0; i < strlen(placeholder); i++) {

            addch(placeholder[i]);
            delay_output(PRINT_DELAY_MS);
            refresh();

        }
    }
    else {
        sprintf(placeholder, end_game_negative, player->totalNetWorth-STARTING_CASH, STARTING_CASH);

        for(int i = 0; i < strlen(placeholder); i++) {
            addch(placeholder[i]);
            delay_output(PRINT_DELAY_MS);
            refresh();

        }
    }
  addch('\n');
    mvprintw(5,0, "Press any key to return to main menu...");
    flushinp();
    getch();
    free(placeholder);



//should quit game
    return;



}

//inits all parts of the game
void init_game() {
    srand(time(NULL));

    clear();
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    curs_set(0);

    preword();

    //start the game
    game_loop();
}


void purchase_menu(struct Player* player) {

    int isPurchase = 1;
    clear();

    uint8_t selected = 0;
    int key;
    int x,y;

    clear();
    while (1) {
        clear();;
        for (int i = 0; i < STOCK_COUNT; i++) {
            attron(A_BOLD);
            mvprintw(i,0, "%s $%.3f", player->allStocks[i].symbol, player->allStocks[i].price);
            attroff(A_BOLD);
            if (selected == i) {

                if (!isPurchase) {

                    attron(COLOR_PAIR(2));
                    mvprintw(i, 20, " Sell 1 Share");
                    attroff(COLOR_PAIR(2));

                }
                else if (isPurchase) {
                    attron(COLOR_PAIR(2));
                    mvprintw(i, 20, " Purchase 1 Share");
                    attroff(COLOR_PAIR(2));
                }
            }

            else {
                if (!isPurchase) {
                    mvprintw(i, 20, " Sell 1 Share");

                }
                else if (isPurchase) {
                    mvprintw(i, 20, " Purchase 1 Share");

                }
            }
            mvprintw(i, 40, "Amount Owned: %d", player->allStocks[i].amountOwnedByPlayer);
            attron(A_DIM | A_ITALIC);
            mvprintw(i, 57, "$ Change: %.2f", player->allStocks[i].price - player->allStocks[i].lastPrice);
            mvprintw(i, 73, "%% Change: %.3f", 100*calculate_percent_change(player->allStocks[i].lastPrice, player->allStocks[i].price));
            mvprintw(i, 90, "Total %% Change: %lf ", 100*calculate_percent_change(STARTING_PRICE[i], player->allStocks[i].price));
attroff(A_DIM | A_ITALIC);
            refresh();


        }

        getyx(stdscr,y,x);

        if (selected == 10) {
            attron(COLOR_PAIR(2));
            mvprintw(y+1, 0, "Exit");
            attroff(COLOR_PAIR(2));
        }else {
            mvprintw(y+1, 0, "Exit");

        }
    if (isPurchase) {
        mvprintw(y+2, 0, "Press S To Sell");

    }else       mvprintw(y+2, 0, "Press S To Purchase");

        refresh();
        key = getch();
        switch (key) {
            case 's':
                isPurchase = !isPurchase;
            case KEY_UP:
                if (selected > 0) {
                    selected--;
                }
                break;
            case KEY_DOWN:
                if (selected <  10) {
                    selected++;
                }
                break;
            case KEY_BACKSPACE:
                if (selected == 0 && isPurchase) { purchase_stocks(player, 0); }
                else if (selected == 0 && !isPurchase) { sell_stocks(player, 0); }

                if (selected == 1 && isPurchase) { purchase_stocks(player, 1); }
                else if (selected == 1 && !isPurchase) { sell_stocks(player, 1); }

                if (selected == 2 && isPurchase) { purchase_stocks(player, 2); }
                else if (selected == 2 && !isPurchase) { sell_stocks(player, 2); }

                if (selected == 3 && isPurchase) { purchase_stocks(player, 3); }
                else if (selected == 3 && !isPurchase) { sell_stocks(player, 3); }

                if (selected == 4 && isPurchase) { purchase_stocks(player, 4); }
                else if (selected == 4 && !isPurchase) { sell_stocks(player, 4); }

                if (selected == 5 && isPurchase) { purchase_stocks(player, 5); }
                else if (selected == 5 && !isPurchase) { sell_stocks(player, 5); }

                if (selected == 6 && isPurchase) { purchase_stocks(player, 6); }
                else if (selected == 6 && !isPurchase) { sell_stocks(player, 6); }

                if (selected == 7 && isPurchase) { purchase_stocks(player, 7); }
                else if (selected == 7 && !isPurchase) { sell_stocks(player, 7); }

                if (selected == 8 && isPurchase) { purchase_stocks(player, 8); }
                else if (selected == 8 && !isPurchase) { sell_stocks(player, 8); }

                if (selected == 9 && isPurchase) { purchase_stocks(player, 9); }
                else if (selected == 9 && !isPurchase) { sell_stocks(player, 9); }

                if (selected == 10) { return; }
                if (selected == 11) {}

                break;

        }


    }



}


void show_news(struct Player* player) {
clear();
    if (!strlen(player->news[0].text)) {
        mvprintw(0,0, "There is currently no news.");
        getch();
        return;

    }
    for (int i = 0; i < 3; i++) {

        mvprintw(i, 0, "%s",player->news[i].text);
    }
    getch();





}


int next_turn(struct Player* player) {
    update_news(player);
    update_stocks(player->allStocks);
    calculateNetWorth(player);

    clear();



    player->turn++;
    if (player->turn > 60) {
        end_game(player);
        return 1;
    }
    return 0;
}


void game_loop() {

    struct Player player;
    createPlayer(&player);
    clear();

    int x,y;

    while (1) {

        clear();
        for (int i = 0; i < 4; i++) {
            if (menu_option == i) {
                attron(COLOR_PAIR(2));
                mvprintw(i, 0, "%s", menu[i]);
                attroff(COLOR_PAIR(2));

            }
            else {
                mvprintw(i, 0, "%s", menu[i]);

            }
            refresh();
        }
        //display the current month/turn
        getyx(stdscr, y, x);
        y++;
        x = 0;

        mvprintw(++y,x,"Month: %d", player.turn);
        mvprintw(++y,0,"Cash On Hand: %.4f", player.cash);
        mvprintw(++y,0,"Net Worth: %.4f", player.totalNetWorth);
        //possible display the change in networth
        //display news snippets




       int key = getch();
        switch (key) {
            case KEY_UP:
            case 'w':
                if (menu_option > 0) {
                    menu_option--;
                }

                break;

                case KEY_DOWN:
                case 's':
                if (menu_option < 3) {
                    menu_option++;
                }
                break;

            case KEY_BACKSPACE:

                if (menu_option == 3) {
                    clear();
                    printw("Exiting...");
                    return;
                }
                if (menu_option == 2) {
                    clear();
                    printw("Enter Pressed");
                    if (next_turn(&player)) return;
                }
                if (menu_option == 1) {
                    clear();
                    show_news(&player);

                }
                if (menu_option == 0) {
                    clear();
                    purchase_menu(&player);
                    clear();
                    refresh();
                }
        break;
                default:
                break;
        }






    }




    clear();
    refresh();
}
