#include "Player.h"

#include "Stocks.h"
#include <stdlib.h>
void createPlayer(struct Player* player) {

    player->cash = STARTING_CASH;
    createStocks((player->allStocks));

    player->turn = 1;
    calculateNetWorth(player);
    //REMEMBER TO FREE THIS
    player->news[0].text = calloc(sizeof(char)*100, sizeof(char)*100);
    player->news[1].text = calloc(sizeof(char)*100, sizeof(char)*100);
    player->news[2].text = calloc(sizeof(char)*100, sizeof(char)*100);




}
void calculateNetWorth(struct Player* player) {
    float netWorth = 0;
    netWorth += player->cash;
    //add the value of all owned stocks

    for (int i = 0; i < STOCK_COUNT; i++) {
        netWorth += player->allStocks[i].price * player->allStocks[i].amountOwnedByPlayer;

    }
    player->totalNetWorth = netWorth;



}

