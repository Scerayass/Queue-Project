#ifndef THIRDASSIGNMENT_MODEL1_H
#define THIRDASSIGNMENT_MODEL1_H
#include <vector>
#include <string>
#include "Order.h"

using namespace std;


class Model1 {
public:
    vector<vector<string>> orders;
    double totalRunningTime;


    /**
     * main function for models
     * @param vector
     * @param cashierNumber
     * @param customer
     * @param fileName
     */
    void execute(vector<vector<string>> vector,int cashierNumber,int customer,string fileName);

    /**
     * insert order to cashier to necessary positions time 0 - time last arrivalTime
     * @param currOrder
     */
    void insertCashier(Order* currOrder);

    /**
     * insert orders to barista to necessary positions time 0 - time last order
     * @param currOrder
     */
    void insertBarista(Order* currOrder);

    /**
     * finishing all orders at cashiers
     */
    void endCashiers();

    /**
     * finishing all orders at baristas
     */
    void endBaristas();

    /**
     * after @endBaristas , if there is a order at barista Queues , it executes them
     */
    void endBaristaQueue();
};


#endif //THIRDASSIGNMENT_MODEL1_H
