#include <iostream>
#include "Model1.h"
#include "CashierQueue.h"
#include "Order.h"
#include "Cashier.h"
#include "Barista.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;
// cashier and barista numbers starts with 0;

::vector<Cashier> cashierOrder;
::vector<Barista> baristaBrew;
CashierQueue* cashierQueue;
CashierQueue* baristaQueue;
::vector<Order*> finishedOrder;
Order * lastOrder;
double lastOrderTime;
double finishTime;

void Model1::execute(vector<vector<string>> vector,int cashierNumber,int customer , string fileName) {
    ofstream outputFile(fileName , ios::trunc);

    cashierQueue = new CashierQueue(customer); // holding cashier's Queue
    baristaQueue = new CashierQueue(customer); // holding barista's Queue

    for(int i = 0; i < cashierNumber ; i++){ // adding them to vector cashier
        Cashier* tempCashier = new Cashier(i); // this will be used for if there is a cashier doesnt have any order it will get an order .
        tempCashier->currentOrder = NULL;
        tempCashier->allTime = 0;
        cashierOrder.push_back(*tempCashier);
    }

    for(int i = 0; i < (cashierNumber/3) ; i++){ // adding them to vector barista
        Barista tempBarista(i);
        tempBarista.currentOrder = NULL;
        tempBarista.allTime = 0;
        baristaBrew.push_back(tempBarista);
    }

    for(int i = 0; i < customer; i++){ // creating Orders
        ::vector<string> tempVector = vector.at(i);
        int index = 0;
        double arrivalTime;
        double orderTime;
        double brewOrder;
        double price;
        for(string j : tempVector){
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
        finishedOrder.push_back(tempOrder);
        insertCashier(tempOrder);
    }
    endCashiers();
    endBaristas();
    endBaristaQueue();


    // writing to output
    string output = to_string(finishTime) + "\n";
    outputFile << finishTime << "\n" << cashierQueue->max << "\n" << baristaQueue->max << "\n" ;

    output += to_string(cashierQueue->max) + "\n";
    for(int i = 0 ; i < cashierOrder.size(); i++){ // writing cashier's working unit to output
        int c = (int)( (cashierOrder.at(i).allTime / finishTime) *100 + .5 );
        double x = c /100.0;
        outputFile << x << "\n";
        output += to_string(x) + "\n";
    }
    for(int i = 0 ; i < baristaBrew.size() ; i++){// writing cashier's working unit to output
        baristaBrew.at(i).calculateFinish();
        int c = (int) ( (baristaBrew.at(i).allTime / finishTime) * 100 + .5);
        double x = c / 100.0;
        outputFile << x <<"\n";
        output += to_string(x) + "\n";
    }

    for(int i = 0 ; i < finishedOrder.size() ; i++){ // turnaround times
        double x = finishedOrder.at(i)->beforeBrew + finishedOrder.at(i)->coffeeTime - finishedOrder.at(i)->firstArrivalTime;
        output += to_string(x) + "\n";
        outputFile << x << "\n";
    }
    outputFile << "\n";


    // deleting all Orders , baristaQueue's and CashierQueue's pointers
    for(int i = 0 ; i < finishedOrder.size() ; i++ ){
        delete finishedOrder.at(i);
    }
    delete cashierQueue;
    delete baristaQueue;

    outputFile.close();


}
void Model1::insertCashier(Order* currOrder){
    int index = 0;

    for(int i = 0 ; i < cashierOrder.size() ; i++){ //  searching and if neccessary finishing orders at cashier
        if(cashierOrder.at(i).currentOrder != NULL  &&(currOrder->arrivalTime - cashierOrder.at(i).currentOrder->arrivalTime ) >= cashierOrder.at(i).currentOrder->orderTime ){
            Order* tempOrder = cashierOrder.at(i).currentOrder;
            cashierOrder.at(i).lastTime = (tempOrder->orderTime + tempOrder->arrivalTime);
            cashierOrder.at(i).currentOrder = NULL;
            tempOrder->beforeBrew = tempOrder->arrivalTime + tempOrder->orderTime;
            insertBarista(tempOrder);
        }
    }
    while( !cashierQueue->isEmpty() ){ // adding from Queue if queue is no empty
        double tempTime = 999999.0;
        for(int i = 0 ; i < cashierOrder.size() ; i++){
            if(cashierOrder.at(i).currentOrder == NULL && cashierOrder.at(i).lastTime < tempTime){
                tempTime = cashierOrder.at(i).lastTime;
            }
        }
        if(tempTime == 999999.0){break;}
        for(int i = 0 ; i < cashierOrder.size(); i++){

            if(cashierOrder.at(i).lastTime == tempTime){
                cashierOrder.at(i).lastTime = 0.0;
                cashierOrder.at(i).currentOrder = cashierQueue->dequeue();
                cashierOrder.at(i).allTime += cashierOrder.at(i).currentOrder->orderTime;
                cashierOrder.at(i).currentOrder->arrivalTime = tempTime;
                break;
            }
        }
    }
    for(int i = 0 ; i < cashierOrder.size() ; i++){ // adding order to cashier
        if (cashierOrder.at(i).currentOrder == NULL){
            cashierOrder.at(i).currentOrder = currOrder;
            cashierOrder.at(i).allTime += currOrder->orderTime;
            index = 1;
            break;
        }
    }
    if(index == 0){
        cashierQueue->enqueue(currOrder);// if any cashier is not empty order is added to queue
    }
}
void Model1::insertBarista(Order *currOrder) {
    int index = 0;
    int deleted = 0;

    for(int i = 0 ; i < baristaBrew.size() ; i++){//  searching and if neccessary finishing orders at barista
        if(baristaBrew.at(i).currentOrder != NULL && (currOrder->beforeBrew - baristaBrew.at(i).currentOrder->beforeBrew) >= baristaBrew.at(i).currentOrder->coffeeTime){
            Order* tempOrder = baristaBrew.at(i).currentOrder;
            baristaBrew.at(i).lastTime = tempOrder->beforeBrew + tempOrder->coffeeTime;
            baristaBrew.at(i).currentOrder = NULL;
            deleted++;
        }
    }
    while( !baristaQueue->isEmpty() && deleted > 0){ // adding from Queue if queue is no empty
        Order* maxPriceCoffe = baristaQueue->maxDequeue();
        double tempTime = 999999.0;
        for(int i = 0 ; i < baristaBrew.size() ; i++){

            if(baristaBrew.at(i).currentOrder == NULL && baristaBrew.at(i).lastTime < tempTime){
                tempTime = baristaBrew.at(i).lastTime;
            }
        }
        for(int i = 0 ; i < baristaBrew.size() ; i++){
            if ( baristaBrew.at(i).lastTime == tempTime ){
                baristaBrew.at(i).allOrders.insert(maxPriceCoffe);
                baristaBrew.at(i).currentOrder = maxPriceCoffe;
                baristaBrew.at(i).currentOrder->beforeBrew = tempTime;

            }
        }
        deleted--;
    }

    for(int i = 0 ; i < baristaBrew.size() ; i++){// adding order to barista
        if (baristaBrew.at(i).currentOrder == NULL){
            baristaBrew.at(i).currentOrder = currOrder;
            baristaBrew.at(i).allOrders.insert(currOrder);
            index = 1;
            break;
        }
    }
    if(index == 0){ // if all baristas are not empty , it adds to queue
        baristaQueue->enqueue(currOrder);
    }

}

void Model1::endCashiers() {  // finishing all orders at cashiers

    bool isFinished = false;
    while( !isFinished ){
        double time = 999999.0;
        for(int i = 0 ; i < cashierOrder.size(); i++){
            if(cashierOrder.at(i).currentOrder != NULL){
                Order * temp = cashierOrder.at(i).currentOrder;
                if((temp->arrivalTime + temp->orderTime) < time ){

                    time = temp->arrivalTime + temp->orderTime;
                }
            }
        }
        if(time == 999999.0){
            isFinished = true;
            break;
        }
        for(int i = 0 ; i < cashierOrder.size(); i++){
            if(cashierOrder.at(i).currentOrder != NULL &&  (cashierOrder.at(i).currentOrder->arrivalTime + cashierOrder.at(i).currentOrder->orderTime) == time){
                Order * temp = cashierOrder.at(i).currentOrder;
                cashierOrder.at(i).currentOrder = NULL;

                temp->beforeBrew = temp->arrivalTime + temp->orderTime ;
                lastOrder = temp;
                lastOrderTime = lastOrder->beforeBrew;
                insertBarista(temp);
            }
        }
    }
    for(int i = 0 ; i < baristaQueue->count; i++){
        Order * tempOrder = baristaQueue->peek(i);
        tempOrder->beforeBrew = lastOrderTime;
    }
}

void Model1::endBaristas() { // finishing all orders at baristas
    if(baristaQueue->count == 0){
        return;
    }
    vector<double> minNumber;
    for(int i = 0 ; i < baristaBrew.size() ; i++){
        Order * minOrder = baristaBrew.at(i).currentOrder;
        minNumber.push_back(( minOrder->beforeBrew + minOrder->coffeeTime) - lastOrderTime);
    }
    sort(minNumber.begin(),minNumber.end());

    for(int i = 0 ; i < baristaQueue->size() ; i++){
        baristaQueue->peek(i)->beforeBrew += minNumber.at(0);
    }

    for(int i = 0 ; i < baristaBrew.size() ; i++){
        Order * minOrder = baristaBrew.at(i).currentOrder;
        if( minNumber.at(0) == ( ( minOrder->beforeBrew + minOrder->coffeeTime) - lastOrderTime) ){
            lastOrderTime = minOrder->beforeBrew + minOrder->coffeeTime;
            baristaBrew.at(i).currentOrder = NULL;
            Order * tempOrder = baristaQueue->maxDequeue();
            baristaBrew.at(i).currentOrder = tempOrder;
            baristaBrew.at(i).allOrders.insert(tempOrder);
        }
    }
    endBaristas();
}

void Model1::endBaristaQueue() { // after EndBaristas() , if there is a order at barista Queues , it executes them
    double time = 0;
    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if(baristaBrew.at(i).currentOrder == NULL){
            continue;
        }else{
            Order * tempOrder = baristaBrew.at(i).currentOrder;

            baristaBrew.at(i).allOrders.insert(tempOrder);
            if( ( tempOrder->beforeBrew + tempOrder->coffeeTime) > time){
                time = tempOrder->beforeBrew + tempOrder->coffeeTime;
            }
        }
    }
    finishTime = time; // end of the program
}