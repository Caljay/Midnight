#include "News.h"

#include <curses.h>
#include <string.h>
//TODO THIS ENTIRE THING STILL SEGFAULTS

//positive and negative news only
//1 - 3 sources?
//need to effect drift or voltality
//time of offset always just adds either 3 or 6 months
//take a range of a percent of the current drift or voltality

void clear_current_news(struct Player* player) {
    for (int i = 0; i < 3; i++) {

       // memset(player->news[i].text, 0, 1);
        strncpy(player->news[i].text, "\0", 1);


    }



}
//percent change from 0.0-1.0
//chance of being TRUE
int generateCoinFlip(float percentChange) {

        if (percentChange < 0.0 || percentChange > 1) {
            return -1;
        }
    int i = rand() % 100;
    return i < (percentChange*100) ? 1 : 0;



}

float generate_random_percent(float min, float max) {
    float out = (float)rand() / max;
    return out < min ? min : (out > max ? max : out);
}

int get_random_number(int max) {
    return rand() % max;
}

//flags should contain two halfs where the upper half is for if its global
//lower half is for if its singlular

//TODO MAKE THIS BETTER THIS SEGFAULTS FOR SOME REASON (i think it has been fixed 08/05/2025)
void get_news_message(struct Player* player, short index, uint8_t global, uint8_t positive, int stock_index) {
    uint8_t news = get_random_number(6);
    char* placeholder = malloc(sizeof(char)*150);

    if (positive) {


        if (global){
            snprintf(placeholder,strlen(pos_global_messages[news])+1,"%s", pos_global_messages[news]);



             }

        else {
            snprintf(placeholder,strlen(positive_messages[news])+4, positive_messages[news], player->allStocks[stock_index].symbol);

        }




    }
else {
    if (global) {
        snprintf(placeholder, strlen(neg_global_messages[news])+1,"%s", neg_global_messages[news]);

    }
    else {
        snprintf(placeholder,strlen(negative_messages[news])+4, negative_messages[news], player->allStocks[stock_index].symbol);


    }
}

strncpy(player->news[index].text, placeholder, strlen(placeholder)+1);
    free(placeholder);

}

void create_news(struct Player* player, short news_index) {
    int stock_index = get_random_number(STOCK_COUNT);
    //decide if it should be positive or negative
    short is_positive = generateCoinFlip(0.75);

    //then get it to be global or non global
    if (generateCoinFlip(0.35)) {
        get_news_message(player, news_index, 1, is_positive, -1);
        //global
       return
        is_positive ?
        effect_all_stocks(player, 3, generate_random_percent(0, 0.125f),generate_random_percent(0, 0.5f),  -generate_random_percent(0, 0.25f))
        :
        effect_all_stocks(player, 3, -generate_random_percent(0, 0.25f),-generate_random_percent(0, 0.75f),  generate_random_percent(0, 0.5f));


    }
    else {
    //get a random index;
        get_news_message(player, news_index, 0, is_positive, stock_index);

        return is_positive ?
        effect_stock(player, stock_index, generate_random_percent(0, 0.125f), generate_random_percent(0, 0.125f),generate_random_percent(0, 0.1f),  -generate_random_percent(0, 0.1f))
            :
        effect_stock(player, stock_index, -generate_random_percent(0, 0.125f), -generate_random_percent(0, 0.125f),-generate_random_percent(0, 0.1f),  generate_random_percent(0, 0.125f));

    }



}



void update_news(struct Player* player) {
    //first clear/delete all current news

    //create 3 pieces of news
    //effect the respective stock
    //put
    for (short i = 0; i < 3; i++) {

        create_news(player, i);
    }

}
