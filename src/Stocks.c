//
//
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "Stocks.h"



float rand_normal() {
    double u1 = rand() / (double) RAND_MAX;
    double u2 = rand() / (double) RAND_MAX;
    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}



struct Stock* createStocks(struct Stock* allStocks) {
    //6 current stocks
    memset(allStocks, 0, STOCK_COUNT*sizeof(struct Stock));

    for (int i = 0; i < STOCK_COUNT; i++) {

        strcpy((allStocks)[i].symbol, TICKETERS[i]);
        allStocks[i].volatility = VOLATILTY[i];
        allStocks[i].drift = DRIFT[i];
        allStocks[i].price = STARTING_PRICE[i];
        allStocks[i].lastPrice = STARTING_PRICE[i];


    }





}

void purchase_stocks(struct Player* player, uint8_t index) {

    float price = player->allStocks[index].price;
    if (player->cash < price) {
        return;
    }
    player->cash -= price;
    player->allStocks[index].amountOwnedByPlayer++;

}

void effect_stock(struct Player *player, int stockIndex, short time_of_effect, float price_change_as_percent,
    float drift_change_as_percent, float voltality_change_as_percent) {
    player->allStocks[stockIndex].timeOfAffect += time_of_effect;

    if (price_change_as_percent < 0.0) {
        price_change_as_percent *= -1;
        price_change_as_percent = 1 - price_change_as_percent;
        player->allStocks[stockIndex].price *= price_change_as_percent;

    }
    else {
        price_change_as_percent = 1 + price_change_as_percent;
        player->allStocks[stockIndex].price *= price_change_as_percent;
    }

    player->allStocks[stockIndex].driftOffset = drift_change_as_percent * player->allStocks[stockIndex].drift;
    player->allStocks[stockIndex].volatilityOffset = voltality_change_as_percent * player->allStocks[stockIndex].volatility;;
}

void effect_all_stocks(struct Player *player, short time_of_effect, float price_change_as_percent,
    float drift_change_as_percent, float voltality_change_as_percent) {

for (int i = 0; i < STOCK_COUNT; i++) {
    effect_stock(player, i, time_of_effect, price_change_as_percent, drift_change_as_percent, voltality_change_as_percent);
}





}

void sell_stocks(struct Player* player, uint8_t index) {
    if (player->allStocks[index].amountOwnedByPlayer > 0) {
        float price = player->allStocks[index].price;
        player->cash += price;
        player->allStocks[index].amountOwnedByPlayer--;
    }

}


void update_stocks(struct Stock* stock) {

    float dt = TIME_DELTA;



    //dW is the random "noise" and randomness
    for (int i = 0; i < STOCK_COUNT; i++) {
        stock->lastPrice = stock->price;
        float St = stock->price;
        float dW = rand_normal() * sqrt(dt);
        St *= exp(((stock->drift + stock->driftOffset) - 0.5 * (stock->volatility + stock->volatilityOffset) * (stock->volatility + stock->volatilityOffset)) * dt + stock->volatility * dW);

        stock->price = St;
        if (stock->timeOfAffect <= 0) {
            stock->timeOfAffect = 0;
            stock->driftOffset = 0;
            stock->volatilityOffset = 0;
        }
        stock++;

    }









}



