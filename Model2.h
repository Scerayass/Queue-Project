#ifndef THIRDASSIGNMENT_MODEL2_H
#define THIRDASSIGNMENT_MODEL2_H
#include <vector>
#include <string>
#include "Order.h"
using namespace std;
class Model2 {
    void execute(vector<vector<string>> vector,int cashierNumber,int customer);
    void insertCashier(Order* currOrder);
};


#endif //THIRDASSIGNMENT_MODEL2_H
