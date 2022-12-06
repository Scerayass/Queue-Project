#ifndef THIRDASSIGNMENT_MODEL2_H
#define THIRDASSIGNMENT_MODEL2_H
#include <vector>
#include <string>
#include "Order.h"
#include "Cashier.h"

using namespace std;
class Model2 {
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
    void execute(vector<vector<string>> vector,int cashierNumber,int customer,string outputFileName);
    /**
     * insert order to cashier to necessary positions time 0 - time last arrivalTime
     * @param currOrder
     */
    void insertCashier(Order* currOrder);
    /**
     * insert orders to barista to necessary positions time 0 - time last order
     * @param currOrder
     */
    void insertBarista(Cashier currCashier,Order* currOrder);
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


#endif //THIRDASSIGNMENT_MODEL2_H
