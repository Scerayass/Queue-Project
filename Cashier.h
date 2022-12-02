//
// Created by GameGaraj on 2.12.2022.
//

#ifndef THIRDASSIGNMENT_CASHIER_H
#define THIRDASSIGNMENT_CASHIER_H


#include "Order.h"

class Cashier {
public:
    Cashier(int x);
    double lastTime = 0;
    int cashierNumber = 0;
    double allTime = 0;
    Order* currentOrder;
};


#endif //THIRDASSIGNMENT_CASHIER_H
