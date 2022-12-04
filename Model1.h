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
    void execute(vector<vector<string>> vector,int cashierNumber,int customer);
    void insertCashier(Order* currOrder);
    void insertBarista(Order* currOrder);
    void endCashiers();
    void endBaristas();
    void endBaristaQueue();
};


#endif //THIRDASSIGNMENT_MODEL1_H
