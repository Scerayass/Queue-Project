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
    void execute(vector<vector<string>> vector,int cashierNumber,int customer);
    void insertCashier(Order* currOrder);
    void insertBarista(Cashier currCashier,Order* currOrder);
    void otherInsertBarista(Barista barista,Order* currOrder);
    void endCashiers();
    void endBaristas();
    void endBaristaQueue();
};


#endif //THIRDASSIGNMENT_MODEL2_H
