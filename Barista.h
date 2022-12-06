#ifndef THIRDASSIGNMENT_BARISTA_H
#define THIRDASSIGNMENT_BARISTA_H


#include "Order.h"
#include "Cashier.h"
#include "CashierQueue.h"
#include <set>

using namespace std;
class Barista {
public:
    Barista();
    Barista(int x);
    double lastTime = 0;
    int baristaNumber;
    double allTime ;
    Order* currentOrder;
    double lastCoffeTime;
    //Cashier* cashier;
    set<Order*> allOrders;
    void calculateFinish();
};


#endif //THIRDASSIGNMENT_BARISTA_H
