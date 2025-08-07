//
//

#ifndef NEWS_H
#define NEWS_H
#include "Stocks.h"


void clear_news(struct Player* player);

void update_news(struct Player* player);



void TEST_testPrint(char* in);





static const char* neg_global_messages[] = {

    "Recession all stocks have dropped",
    "High volatility due to market scare",
    "Consumer spending is at all time low.",
    "Market suffers losses due to foreign products",
    "Political and economic issues send the stock market downward",
    "Multi company fraud and abuse sends wider stock market down due to fear",
    "CJH Bank collapse sends ripples through the market"


};
static const char* pos_global_messages[] = {
    "General good returns from the market.",
    "Consumer spending is skyrocketing",
    "Investors claim a new golden era is upon us",
    "Consumers and investors rejoin with latest interest rate cut",
    "Market skyrockets after tax cut announcement",
    "Wide spread wage increases have stock market rising",
    "Investors and consumers show optimism in the future fueling higher records"



};
static const char* negative_messages[] = {
    "%s misses earnings - expected lower returns",
    "Injury at %s due to negligence",
    "%s tumbles after FTC opens an investigation",
    "Major losses from %s sends shares tumbling",
    "CEO at %s steps down after multiple project deadlines are missed",
    "Class action lawsuit harms %s shares this quarter",
    "Databreach at %s has both customers and shareholders spooked",




};


static const char* positive_messages[] = {
    "%s beats earnings - expected better returns",
    "%s releases a new product that catches investors eyes",
    "Massive gains from %s due to revolutionary new processes",
    "%s acquires competitor, share prices are expected to rise",
    "New product launcher from %s drives demand",
    "%s wins contracting award from the govt",
    "Brand new online platform by %s has shareholders applauding"
};



#endif //NEWS_H
