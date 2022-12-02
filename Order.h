#ifndef THIRDASSIGNMENT_ORDER_H
#define THIRDASSIGNMENT_ORDER_H


class Order{

public:
    double arrivalTime;
    double orderTime;
    double coffeeTime;
    double coffeePrice;
    double beforeBrew;

    Order(){}

    Order(double arrival, double orderSecond , double coffeTime, double coffePrice){
        arrivalTime = arrival;
        orderTime = orderSecond;
        coffeeTime = coffeTime;
        coffeePrice = coffePrice;
    }
};


#endif //THIRDASSIGNMENT_ORDER_H
