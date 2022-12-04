#ifndef THIRDASSIGNMENT_CASHIER_H
#define THIRDASSIGNMENT_CASHIER_H


#include "Order.h"
#include "Barista.h"

class Cashier {
public:
    Cashier(int x);
    double lastTime = 0;
    int cashierNumber = 0;
    double allTime = 0;
    Order* currentOrder;
    //Barista* currBarista;
};


#endif //THIRDASSIGNMENT_CASHIER_H
