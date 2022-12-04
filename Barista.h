#ifndef THIRDASSIGNMENT_BARISTA_H
#define THIRDASSIGNMENT_BARISTA_H


#include "Order.h"
#include "Cashier.h"

class Barista {
public:
    Barista(int x);
    double lastTime = 0;
    int baristaNumber;
    double allTime ;
    Order* currentOrder;
    Cashier* cashier;

};


#endif //THIRDASSIGNMENT_BARISTA_H
