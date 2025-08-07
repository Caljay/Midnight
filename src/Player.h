//
//

#ifndef PLAYER_H
#define PLAYER_H
#include <time.h>
#include "Stocks.h"
#define STARTING_CASH 10000




#include "Stocks.h"

//creates the player, giving them starting cash
//also creates the list of stocks
void createPlayer(struct Player* player);

void calculateNetWorth(struct Player* player);



#endif //PLAYER_H
