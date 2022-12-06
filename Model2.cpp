#include <string>
#include "Model2.h"
#include "Cashier.h"
#include "Barista.h"
#include "CashierQueue.h"
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// cashier and barista numbers starts with 0;

::vector<Cashier> cashierOrder2;
::vector<Barista> baristaBrew2;
CashierQueue* cashierQueue2;
::vector<CashierQueue*> baristaQueues;
::vector<Order*> finishedOrder2;
Order * lastOrder2;
double lastOrderTime2;
double finishTime2;

void Model2::execute(vector<vector<string>> vector,int cashierNumber,int customer , string outputFileName) {
    ofstream outputFile(outputFileName , ios::app);

    cashierQueue2 = new CashierQueue(customer);// holding cashier's Queue

    for(int i = 0; i < cashierNumber ; i++){// adding them to vector cashier
        Cashier* tempCashier = new Cashier(i);// this will be used for if there is a cashier doesnt have any order it will get an order .
        tempCashier->currentOrder = NULL;
        tempCashier->allTime = 0;
        cashierOrder2.push_back(*tempCashier);
    }

    for(int i = 0; i < (cashierNumber/3) ; i++){
        CashierQueue* tempBaristaQueue = new CashierQueue(customer); // creating barista queues
        baristaQueues.push_back(tempBaristaQueue);// adding them to vector barista

        Barista tempBarista(i);
        tempBarista.currentOrder = NULL;
        tempBarista.allTime = 0;
        tempBarista.baristaNumber = i;
        baristaBrew2.push_back(tempBarista);
    }

    for(int i = 0; i < customer; i++) { // creating Orders
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
    endCashiers();
    endBaristas();
    endBaristaQueue();

    // writing to output
    string output = to_string(finishTime2) + "\n";
    outputFile << finishTime2 << "\n" << cashierQueue2->max << "\n" ;
    for(int i = 0 ; i < baristaQueues.size() ; i++ ){ //  writing all barista's work units
        outputFile << baristaQueues.at(i)->max << "\n";
    }

    for(int i = 0 ; i < cashierOrder2.size(); i++){ // writing cashier's working unit to output
        int c = (int)( (cashierOrder2.at(i).allTime / finishTime2) *100 + .5 );
        double x = c /100.0;
        outputFile << x << "\n";
        output += to_string(x) + "\n";
    }
    for(int i = 0 ; i < baristaBrew2.size() ; i++){ // writing cashier's working unit to output
        baristaBrew2.at(i).calculateFinish();
        int c = (int) ( (baristaBrew2.at(i).allTime / finishTime2) * 100 + .5);
        double x = c / 100.0;
        outputFile << x <<"\n";
        output += to_string(x) + "\n";
    }

    for(int i = 0 ; i < finishedOrder2.size() ; i++){ // turnaround times
        double x = finishedOrder2.at(i)->beforeBrew + finishedOrder2.at(i)->coffeeTime - finishedOrder2.at(i)->firstArrivalTime;
        output += to_string(x) + "\n";
        outputFile << x << "\n";
    }
    // deleting all Orders , baristaQueue's and CashierQueue's pointers
    for(int i = 0 ; i < finishedOrder2.size() ; i++ ){
        delete finishedOrder2.at(i);
    }
    for(int i = 0 ; i < baristaQueues.size(); i++){
        delete baristaQueues.at(i);
    }
    delete cashierQueue2;
    outputFile.close();

}

void Model2::insertCashier(Order *currOrder) {
    int index = 0;

    for(int i = 0 ; i < cashierOrder2.size() ; i++){//  searching and if neccessary finishing orders at cashier
        if(cashierOrder2.at(i).currentOrder != NULL  &&(currOrder->arrivalTime - cashierOrder2.at(i).currentOrder->arrivalTime ) >= cashierOrder2.at(i).currentOrder->orderTime ){
            Order* tempOrder = cashierOrder2.at(i).currentOrder;
            cashierOrder2.at(i).lastTime = (tempOrder->orderTime + tempOrder->arrivalTime);

            cashierOrder2.at(i).currentOrder = NULL;
            tempOrder->beforeBrew = tempOrder->arrivalTime + tempOrder->orderTime;
            insertBarista(cashierOrder2.at(i),tempOrder);
        }
    }
    while( !cashierQueue2->isEmpty() ){ // adding from Queue if queue is no empty

        double tempTime = 999999.0;
        for(int i = 0 ; i < cashierOrder2.size() ; i++){
            if(cashierOrder2.at(i).currentOrder == NULL && cashierOrder2.at(i).lastTime < tempTime){
                tempTime = cashierOrder2.at(i).lastTime;
            }
        }
        if(tempTime == 999999.0){break;}
        for(int i = 0 ; i < cashierOrder2.size(); i++){
            if(cashierOrder2.at(i).lastTime == tempTime){

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
            cashierOrder2.at(i).currentOrder = currOrder;
            cashierOrder2.at(i).allTime += currOrder->orderTime;
            index = 1;
            break;
        }
    }

    if(index == 0){
        cashierQueue2->enqueue(currOrder);// if any cashier is not empty order is added to queue
    }
}

void Model2::insertBarista(Cashier currCashier ,Order *currOrder) {
    int index = 0;
    for(int i = 0 ; i < baristaBrew2.size() ; i++){ //  searching and if neccessary finishing orders at barista
        if(baristaBrew2.at(i).currentOrder != NULL && (currOrder->beforeBrew - baristaBrew2.at(i).currentOrder->beforeBrew) >= baristaBrew2.at(i).currentOrder->coffeeTime){

            Order* tempOrder = baristaBrew2.at(i).currentOrder;
            baristaBrew2.at(i).lastTime = tempOrder->beforeBrew + tempOrder->coffeeTime;
            baristaBrew2.at(i).currentOrder = NULL;
        }
    }
    for(int i = 0 ; i < baristaBrew2.size() ; i++){// adding from Queue if queue is no empty
        if( baristaBrew2.at(i).currentOrder == NULL && baristaQueues.at(i)->count != 0 ){

                Order* temp = baristaQueues.at(i)->maxDequeue();
                baristaBrew2.at(i).allOrders.insert(temp);
                baristaBrew2.at(i).currentOrder = temp;
                baristaBrew2.at(i).currentOrder->beforeBrew = baristaBrew2.at(i).lastTime;
        }
    }
    if(baristaBrew2.at(currCashier.cashierNumber / 3).currentOrder == NULL){// adding order to barista

        baristaBrew2.at(currCashier.cashierNumber / 3).currentOrder = currOrder;
        baristaBrew2.at(currCashier.cashierNumber / 3).allOrders.insert(currOrder);
        index = 1;

    }
    if(index == 0){  // if all baristas are not empty , it adds to queue

        baristaQueues.at(currCashier.cashierNumber / 3)->enqueue(currOrder);
    }
}
void Model2::endCashiers() { // finishing all orders at cashiers
    bool isFinished = false;
    while( !isFinished ){
        double time = 999999.0;
        for(int i = 0 ; i < cashierOrder2.size(); i++){
            if(cashierOrder2.at(i).currentOrder != NULL){
                Order * temp = cashierOrder2.at(i).currentOrder;
                if((temp->arrivalTime + temp->orderTime) < time ){

                    time = temp->arrivalTime + temp->orderTime;
                }
            }
        }
        if(time == 999999.0){
            isFinished = true;
            break;
        }
        for(int i = 0 ; i < cashierOrder2.size(); i++){
            if(cashierOrder2.at(i).currentOrder != NULL &&  (cashierOrder2.at(i).currentOrder->arrivalTime + cashierOrder2.at(i).currentOrder->orderTime) == time){

                Order * temp = cashierOrder2.at(i).currentOrder;
                cashierOrder2.at(i).currentOrder = NULL;

                temp->beforeBrew = temp->arrivalTime + temp->orderTime ;
                lastOrder2 = temp;
                lastOrderTime2 = lastOrder2->beforeBrew;

                insertBarista(cashierOrder2.at(i),temp);
            }
        }
    }
    for(int i = 0 ; i < baristaQueues.size() ; i++){
        baristaBrew2.at(i).lastCoffeTime = lastOrderTime2;
        CashierQueue* tempQueue = baristaQueues.at(i);
        for(int j = 0 ; j < tempQueue->count;j++){
            Order* tempOrder = tempQueue->peek(j);
            tempOrder->beforeBrew = lastOrderTime2;
        }

    }
}

void Model2::endBaristas() { // finishing all orders at baristas

    for(int i = 0 ; i < baristaBrew2.size() ; i++ ){
        bool finish = true;
        CashierQueue * tempQueue = baristaQueues.at(i);
        lastOrderTime2;
        while(finish){

            if (tempQueue->count == 0){
                finish = false;
                break;
            }

            Order * minOrder = baristaBrew2.at(i).currentOrder;
            double minNumber = ( minOrder->beforeBrew + minOrder->coffeeTime) - baristaBrew2.at(i).lastCoffeTime;

            baristaBrew2.at(i).lastCoffeTime += minNumber;
            for(int j = 0 ; j < tempQueue->count ; j++ ){
                tempQueue->peek(j)->beforeBrew += minNumber;

            }
            Order * maxOrder = tempQueue->maxDequeue();
            baristaBrew2.at(i).currentOrder = maxOrder;

            baristaBrew2.at(i).allOrders.insert(maxOrder);
        }
    }
    int finish = 0;

    for(int i = 0 ; i < baristaQueues.size(); i++){
        CashierQueue* tempBarista = baristaQueues.at(i);
        if(tempBarista->count != 0){
            finish++;
        }
    }
    if(finish == 0){
        return;
    }
    for(int i = 0 ; i < baristaBrew2.size(); i++){

    }

}

void Model2::endBaristaQueue() { // after EndBaristas() , if there is a order at barista Queues , it executes them
    double time = 0;
    for(int i = 0 ; i < baristaBrew2.size() ; i++){
        if(baristaBrew2.at(i).currentOrder == NULL){
            continue;
        }else{
            Order * tempOrder = baristaBrew2.at(i).currentOrder;

            baristaBrew2.at(i).allOrders.insert(tempOrder);
            if( ( tempOrder->beforeBrew + tempOrder->coffeeTime) > time){
                time = tempOrder->beforeBrew + tempOrder->coffeeTime;
            }
        }
    }

    finishTime2 = time;
}

