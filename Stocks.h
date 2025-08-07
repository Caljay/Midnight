//
//
#ifndef STOCKS_H
#define STOCKS_H

#include <stdlib.h>
#include <math.h>
#include  <stdint.h>



//this simulates the stock price using
// Geometric Brownian Motion
// follows the equation
// S(t)=S⋅e^(μ-0.5σ^2)t+σW(t)

#define TIME_DELTA1 0.025
#define TIME_DELTA 0.05
#define NEWS_COUNT 3

struct Stock {
    char symbol[7];
    float price;
    float lastPrice;
    int amountOwnedByPlayer;

    float drift;
    float volatility;
    float driftOffset;
    float volatilityOffset;
    uint8_t timeOfAffect;
};


static const char* TICKETERS[] = {

    "APPL",
    "MSFT",
    "GOOG",
    "PYLC",
    "INTC",
    "NFLX",
    "NVDA",
    "COCL",
    "AMEX",
    "JPMG"

};


static const float STARTING_PRICE[] = {
    100.f,
    350.f,
    50.f,
    25.0f,
    15.0f,
    375.0f,
    200.0f,
    50.0f,
    375.0f,
    450.0f



};
//affects the
static const float VOLATILTY[] = {
    0.2f,
    0.15f,
    0.25f,
    0.2f,
    0.35f,
    0.3f,
    0.25f,
    0.05f,
    0.15f,
    0.15f




};

//effects the average % return of he stock
static const float DRIFT[] = {
    0.15f,
    0.15f,
    0.05f,
    0.125f,
    0.0125f,
    0.175f,
    0.1f,
    0.075f,
    0.15f,
    0.165f




};
#define STOCK_COUNT (sizeof(TICKETERS)/sizeof(TICKETERS[0]))

//this could be removed but i might want to add more later
struct News {
    char* text;

};
struct Player {
    int turn;
    double cash;
    double totalNetWorth;
    struct Stock allStocks[STOCK_COUNT];
    struct News news[NEWS_COUNT];

};



struct Stock* createStocks(struct Stock* allStocks);


void purchase_stocks(struct Player* player, uint8_t index);

void effect_stock(struct Player* player, int stockIndex, short time_of_effect,  float price_change_as_percent, float drift_change_as_percent, float voltality_change_as_percent);
void effect_all_stocks(struct Player* player, short time_of_effect, float price_change_as_percent, float drift_change_as_percent, float voltality_change_as_percent);

void sell_stocks(struct Player* player, uint8_t index);


float rand_normal();


//uses Geometric Brownian Motion to model the stock prices
//imperfect but effective
//uses
void update_stocks(struct Stock* stock);



#endif //STOCKS_H

