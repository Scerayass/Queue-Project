#include <string>
#include "Model2.h"
#include "Cashier.h"
#include "Barista.h"
#include "CashierQueue.h"
#include <vector>
using namespace std;

::vector<Cashier> cashierOrder2;
::vector<Barista> baristaBrew2;
CashierQueue* cashierQueue2;
CashierQueue* baristaQueue2;
::vector<Order*> finishedOrder2;
void Model2::execute(vector<vector<string>> vector,int cashierNumber,int customer) {
    cashierQueue2 = new CashierQueue(customer);
    baristaQueue2 = new CashierQueue(customer);

    for(int i = 0; i < cashierNumber ; i++){
        Cashier* tempCashier = new Cashier(i);
        tempCashier->currentOrder = NULL;
        tempCashier->allTime = 0;
        cashierOrder2.push_back(*tempCashier);
    }

    for(int i = 0; i < (cashierNumber/3) ; i++){
        Barista tempBarista(i);
        tempBarista.currentOrder = NULL;
        tempBarista.allTime = 0;
        tempBarista.baristaNumber = i;
        baristaBrew2.push_back(tempBarista);
    }

    for(int i = 0; i < customer; i++) {
        ::vector<string> tempVector = vector.at(i);
        int index = 0;
        double arrivalTime;
        double orderTime;
        double brewOrder;
        double price;
        for (string j: tempVector) {
            switch (index) {
                case 0:
                    arrivalTime = stod(j);
                    break;
                case 1:
                    orderTime = stod(j);
                    break;
                case 2:
                    brewOrder = stod(j);
                    break;
                case 3:
                    price = stod(j);
                    break;
            }
            index++;
        }
        Order* tempOrder = new Order(arrivalTime, orderTime, brewOrder, price);
        tempOrder->firstArrivalTime = arrivalTime;
        finishedOrder2.push_back(tempOrder);
        insertCashier(tempOrder);
    }
}

void Model2::insertCashier(Order *currOrder) {

}