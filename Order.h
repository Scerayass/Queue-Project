#ifndef THIRDASSIGNMENT_ORDER_H
#define THIRDASSIGNMENT_ORDER_H


class Order{

public:
    double firstArrivalTime;
    double arrivalTime;
    double orderTime;
    double coffeeTime;
    double coffeePrice;
    double beforeBrew;
    double exitTime;
    int cashierNumber;
    int baristaNumber;
    double startBrew;

    Order(){}

    Order(double arrival, double orderSecond , double coffeTime, double coffePrice){
        arrivalTime = arrival;
        orderTime = orderSecond;
        coffeeTime = coffeTime;
        coffeePrice = coffePrice;
    }
};


#endif //THIRDASSIGNMENT_ORDER_H
