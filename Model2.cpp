#include <string>
#include "Model2.h"
#include "Cashier.h"
#include "Barista.h"
#include "CashierQueue.h"
#include <vector>
#include <iostream>

using namespace std;

::vector<Cashier> cashierOrder2;
::vector<Barista> baristaBrew2;
CashierQueue* cashierQueue2;
::vector<CashierQueue*> baristaQueues;
::vector<Order*> finishedOrder2;


void Model2::execute(vector<vector<string>> vector,int cashierNumber,int customer) {
    cashierQueue2 = new CashierQueue(customer);
    //baristaQueue2 = new CashierQueue(customer);

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

        /*
        CashierQueue* temp = new CashierQueue(customer);
        temp->currBarista = tempBarista;
        baristaQueues.push_back(temp);
        tempBarista.currQueue = temp;
        for(int j = 0 ; j < (i*3 + 3); j++){
            cashierOrder2.at(j).currBarista = tempBarista;
        }*/
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
    int index = 0;

    for(int i = 0 ; i < cashierOrder2.size() ; i++){
        if(cashierOrder2.at(i).currentOrder != NULL  &&(currOrder->arrivalTime - cashierOrder2.at(i).currentOrder->arrivalTime ) >= cashierOrder2.at(i).currentOrder->orderTime ){

            Order* tempOrder = cashierOrder2.at(i).currentOrder;

            cashierOrder2.at(i).lastTime = (tempOrder->orderTime + tempOrder->arrivalTime);

            cashierOrder2.at(i).currentOrder = NULL;
            //cout <<  cashierOrder2.at(i).currentOrder->orderTime << " - ";
            tempOrder->beforeBrew = tempOrder->arrivalTime + tempOrder->orderTime;
            insertBarista(cashierOrder2.at(i),tempOrder);
        }
    }
    while( !cashierQueue2->isEmpty() ){

        double tempTime = 999999.0;
        for(int i = 0 ; i < cashierOrder2.size() ; i++){

            //cout << cashierOrder.at(i).lastTime << " neden 2 ";
            if(cashierOrder2.at(i).currentOrder == NULL && cashierOrder2.at(i).lastTime < tempTime){
                tempTime = cashierOrder2.at(i).lastTime;
            }
        }
        if(tempTime == 999999.0){break;}
        for(int i = 0 ; i < cashierOrder2.size(); i++){

            if(cashierOrder2.at(i).lastTime == tempTime){
                //cout << "3"<< endl;
                cashierOrder2.at(i).lastTime = 0.0;
                cashierOrder2.at(i).currentOrder = cashierQueue2->dequeue();
                cashierOrder2.at(i).allTime += cashierOrder2.at(i).currentOrder->orderTime;
                cashierOrder2.at(i).currentOrder->arrivalTime = tempTime;
                break;
            }
        }
    }
    for(int i = 0 ; i < cashierOrder2.size() ; i++){ //  en baştan beri tarıyor boş yere koyuyor
        if (cashierOrder2.at(i).currentOrder == NULL){
            //cout << "4"<< endl;
            cashierOrder2.at(i).currentOrder = currOrder;
            cashierOrder2.at(i).allTime += currOrder->orderTime;
            index = 1;
            break;
        }
    }

    if(index == 0){
        //cout << "x2";
        cashierQueue2->enqueue(currOrder);
        /*
        while(!cashierQueue->isEmpty()){
            cout << cashierQueue->dequeue()->orderTime << endl;
        }*/
    }

    for( int i = 0 ; i < cashierOrder2.size() ; i++){
        if(cashierOrder2.at(i).currentOrder != NULL){
            //cout << "5" << endl;
            cout << cashierOrder2.at(i).currentOrder->orderTime << " ";
        }
    }
    cout << index << endl;

}

void Model2::insertBarista(Cashier currCashier ,Order *currOrder) {

    int deleted = 0;

    cout << currCashier.cashierNumber / 3 << endl;
    Barista selectedBarista = baristaBrew2.at(currCashier.cashierNumber / 3);

    for(int i = 0 ; i < baristaBrew2.size() ; i++){
        if(baristaBrew2.at(i).currentOrder != NULL && (currOrder->beforeBrew - baristaBrew2.at(i).currentOrder->beforeBrew) >= baristaBrew2.at(i).currentOrder->coffeeTime){
            Order* tempOrder = baristaBrew2.at(i).currentOrder;
            baristaBrew2.at(i).lastTime = tempOrder->beforeBrew + tempOrder->coffeeTime;
            baristaBrew2.at(i).currentOrder = NULL;
            deleted++;
        }/*
        else if (baristaBrew.at(i).currentOrder != NULL){
            Order* tempOrder = baristaBrew.at(i).currentOrder;
        }*/
    }

    if(selectedBarista.currentOrder == NULL){
        selectedBarista.currentOrder = currOrder;
        selectedBarista.allOrders.insert(currOrder);

    }

}

void Model2::otherInsertBarista(Barista barista, Order *currOrder) {}

void Model2::endCashiers() {

}

void Model2::endBaristas() {

}

void Model2::endBaristaQueue() {

}

