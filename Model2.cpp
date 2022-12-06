#include <string>
#include "Model2.h"
#include "Cashier.h"
#include "Barista.h"
#include "CashierQueue.h"
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

::vector<Cashier> cashierOrder2;
::vector<Barista> baristaBrew2;
CashierQueue* cashierQueue2;
::vector<CashierQueue*> baristaQueues;
::vector<Order*> finishedOrder2;
Order * lastOrder2;
double lastOrderTime2;
double finishTime2;

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
        CashierQueue* tempBaristaQueue = new CashierQueue(customer);
        baristaQueues.push_back(tempBaristaQueue);

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

    endCashiers();
    cout << "bitti" << endl;
    endBaristas();
    endBaristaQueue();
    for(int i = 0 ; i < finishedOrder2.size();i++){
        cout << finishedOrder2.at(i)->coffeeTime + finishedOrder2.at(i)->beforeBrew - finishedOrder2.at(i)->firstArrivalTime << " - ";
        //cout <<  + finishedOrder.at(i)->beforeBrew << " - ";
    }
    cout << endl;
    for(int i = 0 ; i < cashierOrder2.size() ; i++){
        cout << (cashierOrder2.at(i).allTime / finishTime2) << " - ";
    }
    cout << endl;

    for(int i = 0 ; i < baristaBrew2.size() ; i++){
        baristaBrew2.at(i).calculateFinish();
    }

    for(int i = 0; i < baristaBrew2.size() ; i++ ){
        cout << baristaBrew2.at(i).allTime / finishTime2 << " - ";
    }
    cout<< endl;
    //cout << baristaQueue->max << " - "<< cashierQueue->max ;
    //cout << finishedOrder.size() << endl;
    cout << "\n-------------------------------MODEL2----------------------------------" << endl;
    //cout << lastOrderTime;
    /*
    for(int i = 0 ; i < finishedOrder2.size() ; i++){
        cout << finishedOrder2.at(i)->beforeBrew << endl;
    }*/

    /*
    cout << "end cashiers" << endl;
    for(int i = 0 ; i < baristaBrew2.size() ; i++){
        if(baristaBrew2.at(i).currentOrder != NULL){
            cout << baristaBrew2.at(i).currentOrder->arrivalTime << endl;
        }

    }*/


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
    cout << index << endl ;

}

void Model2::insertBarista(Cashier currCashier ,Order *currOrder) {
    int index = 0;


    //cout << "burda" << endl;
    //cout << currCashier.cashierNumber / 3 << endl;
    //Barista selectedBarista = baristaBrew2.at(currCashier.cashierNumber / 3);
    //cout << selectedBarista.baristaNumber;

    for(int i = 0 ; i < baristaBrew2.size() ; i++){
        if(baristaBrew2.at(i).currentOrder != NULL && (currOrder->beforeBrew - baristaBrew2.at(i).currentOrder->beforeBrew) >= baristaBrew2.at(i).currentOrder->coffeeTime){

            Order* tempOrder = baristaBrew2.at(i).currentOrder;
            baristaBrew2.at(i).lastTime = tempOrder->beforeBrew + tempOrder->coffeeTime;
            baristaBrew2.at(i).currentOrder = NULL;
        }/*
        else if (baristaBrew.at(i).currentOrder != NULL){
            Order* tempOrder = baristaBrew.at(i).currentOrder;
        }*/
    }
    for(int i = 0 ; i < baristaBrew2.size() ; i++){
        if( baristaBrew2.at(i).currentOrder == NULL && baristaQueues.at(i)->count != 0 ){

                Order* temp = baristaQueues.at(i)->maxDequeue();
                baristaBrew2.at(i).allOrders.insert(temp);
                baristaBrew2.at(i).currentOrder = temp;
                baristaBrew2.at(i).currentOrder->beforeBrew = baristaBrew2.at(i).lastTime;
        }
    }

    if(baristaBrew2.at(currCashier.cashierNumber / 3).currentOrder == NULL){

        baristaBrew2.at(currCashier.cashierNumber / 3).currentOrder = currOrder;
        baristaBrew2.at(currCashier.cashierNumber / 3).allOrders.insert(currOrder);
        index = 1;

    }

    if(index == 0){

        baristaQueues.at(currCashier.cashierNumber / 3)->enqueue(currOrder);
    }
    //cout << selectedBarista.currentOrder->coffeeTime << endl;

    cout << "------------------------------------";
    for( int i = 0 ; i < baristaBrew2.size() ; i++){

        if(baristaBrew2.at(i).currentOrder != NULL){

            cout << baristaBrew2.at(i).currentOrder->coffeeTime << " ";
        }

    }
    cout << "------------------------------------" << endl;



}

void Model2::otherInsertBarista(Barista barista, Order *currOrder) {}

void Model2::endCashiers() {
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

    /*
    for(int i = 0 ; i < baristaQueue->count; i++){
        Order * tempOrder = baristaQueue->peek(i);
        tempOrder->beforeBrew = lastOrderTime;
    }*/
}

void Model2::endBaristas() {

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
            cout << minNumber << "  what  ";
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

void Model2::endBaristaQueue() {
    double time = 0;
    for(int i = 0 ; i < baristaBrew2.size() ; i++){
        if(baristaBrew2.at(i).currentOrder == NULL){
            continue;
        }else{
            Order * tempOrder = baristaBrew2.at(i).currentOrder;
            //baristaBrew.at(i).allTime += tempOrder->coffeeTime;
            baristaBrew2.at(i).allOrders.insert(tempOrder);
            if( ( tempOrder->beforeBrew + tempOrder->coffeeTime) > time){
                time = tempOrder->beforeBrew + tempOrder->coffeeTime;
            }
        }
    }
    cout << "\n" << time  <<  endl;
    finishTime2 = time;
}

