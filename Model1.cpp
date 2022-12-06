#include <iostream>
#include "Model1.h"
#include "CashierQueue.h"
#include "Order.h"
#include "Cashier.h"
#include "Barista.h"
#include <vector>
#include <bits/stdc++.h>
using namespace std;
// cashier an barista numbers starts with 0;
::vector<Cashier> cashierOrder;
::vector<Barista> baristaBrew;
CashierQueue* cashierQueue;
CashierQueue* baristaQueue;
::vector<Order*> finishedOrder;
Order * lastOrder;
double lastOrderTime;
double finishTime;

void Model1::execute(vector<vector<string>> vector,int cashierNumber,int customer) {
    cashierQueue = new CashierQueue(customer);
    baristaQueue = new CashierQueue(customer);

    for(int i = 0; i < cashierNumber ; i++){
        Cashier* tempCashier = new Cashier(i);
        tempCashier->currentOrder = NULL;
        tempCashier->allTime = 0;
        cashierOrder.push_back(*tempCashier);
    }

    for(int i = 0; i < (cashierNumber/3) ; i++){
        Barista tempBarista(i);
        tempBarista.currentOrder = NULL;
        tempBarista.allTime = 0;
        baristaBrew.push_back(tempBarista);
    }

    for(int i = 0; i < customer; i++){
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

    /*
    while(!baristaQueue->isEmpty()){
        cout << baristaQueue->dequeue()->coffeeTime << "-";
    }*/

    //cout << endl;
    /*
    for(int i = 0 ; i < cashierOrder.size() ; i++){
        cout << cashierOrder.at(i).allTime << " -";
    }*/

    //cout << baristaQueue->max << endl;

    for(int i = 0 ; i < finishedOrder.size();i++){
        cout << finishedOrder.at(i)->coffeeTime + finishedOrder.at(i)->beforeBrew - finishedOrder.at(i)->firstArrivalTime << " - ";
        //cout <<  + finishedOrder.at(i)->beforeBrew << " - ";
    }
    cout << endl;
    for(int i = 0 ; i < cashierOrder.size() ; i++){
        cout << (cashierOrder.at(i).allTime / finishTime) << " - ";
    }
    cout << endl;

    for(int i = 0 ; i < baristaBrew.size() ; i++){
        baristaBrew.at(i).calculateFinish();
    }

    for(int i = 0; i < baristaBrew.size() ; i++ ){
        cout << baristaBrew.at(i).allTime / finishTime << " - ";
    }
    cout<< endl;
    cout << baristaQueue->max << " - "<< cashierQueue->max ;
    //cout << finishedOrder.size() << endl;
    cout << "\n-------------------------------MODEL2----------------------------------" << endl;
    //cout << lastOrderTime;

}
void Model1::insertCashier(Order* currOrder){
    int index = 0;

    for(int i = 0 ; i < cashierOrder.size() ; i++){
        if(cashierOrder.at(i).currentOrder != NULL  &&(currOrder->arrivalTime - cashierOrder.at(i).currentOrder->arrivalTime ) >= cashierOrder.at(i).currentOrder->orderTime ){
            Order* tempOrder = cashierOrder.at(i).currentOrder;
            cashierOrder.at(i).lastTime = (tempOrder->orderTime + tempOrder->arrivalTime);
            cashierOrder.at(i).currentOrder = NULL;
            tempOrder->beforeBrew = tempOrder->arrivalTime + tempOrder->orderTime;
            insertBarista(tempOrder);
        }
    }
    while( !cashierQueue->isEmpty() ){

        double tempTime = 999999.0;
        for(int i = 0 ; i < cashierOrder.size() ; i++){
            //cout << cashierOrder.at(i).lastTime << " neden 2 ";
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
    for(int i = 0 ; i < cashierOrder.size() ; i++){ //  en baştan beri tarıyor boş yere koyuyor
        if (cashierOrder.at(i).currentOrder == NULL){
            cashierOrder.at(i).currentOrder = currOrder;
            cashierOrder.at(i).allTime += currOrder->orderTime;
            index = 1;
            break;
        }
    }
    if(index == 0){
        cashierQueue->enqueue(currOrder);
        /*
        while(!cashierQueue->isEmpty()){
            cout << cashierQueue->dequeue()->orderTime << endl;
        }*/
    }
    cout << endl;
    for( int i = 0 ; i < cashierOrder.size() ; i++){
        if(cashierOrder.at(i).currentOrder != NULL){
            cout << cashierOrder.at(i).currentOrder->orderTime << " ";
        }
    }
    cout << cashierOrder.size() << endl;

}
void Model1::insertBarista(Order *currOrder) {
    int index = 0;
    int deleted = 0;

    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if(baristaBrew.at(i).currentOrder != NULL && (currOrder->beforeBrew - baristaBrew.at(i).currentOrder->beforeBrew) >= baristaBrew.at(i).currentOrder->coffeeTime){
            Order* tempOrder = baristaBrew.at(i).currentOrder;
            baristaBrew.at(i).lastTime = tempOrder->beforeBrew + tempOrder->coffeeTime;
            baristaBrew.at(i).currentOrder = NULL;


            deleted++;
        }/*
        else if (baristaBrew.at(i).currentOrder != NULL){
            Order* tempOrder = baristaBrew.at(i).currentOrder;
        }*/
    }
    while( !baristaQueue->isEmpty() && deleted > 0){

        Order* maxPriceCoffe = baristaQueue->maxDequeue();
        double tempTime = 999999.0;
        for(int i = 0 ; i < baristaBrew.size() ; i++){
            //cout << cashierOrder.at(i).lastTime << " neden 2 ";
            if(baristaBrew.at(i).currentOrder == NULL && baristaBrew.at(i).lastTime < tempTime){
                tempTime = baristaBrew.at(i).lastTime;
            }
        }
        for(int i = 0 ; i < baristaBrew.size() ; i++){
            if ( baristaBrew.at(i).lastTime == tempTime ){
                //baristaBrew.at(i).allTime += maxPriceCoffe->coffeeTime;
                baristaBrew.at(i).allOrders.insert(maxPriceCoffe);
                baristaBrew.at(i).currentOrder = maxPriceCoffe;
                baristaBrew.at(i).currentOrder->beforeBrew = tempTime;

            }
        }
        deleted--;
    }

    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if (baristaBrew.at(i).currentOrder == NULL){
            baristaBrew.at(i).currentOrder = currOrder;
            //baristaBrew.at(i).allTime += currOrder->coffeeTime;
            baristaBrew.at(i).allOrders.insert(currOrder);
            index = 1;
            break;
        }
    }

    if(index == 0){
        baristaQueue->enqueue(currOrder);
        /*
        while(!baristaQueue->isEmpty()){
            cout << baristaQueue->dequeue()->orderTime << " bi bura "  <<endl;
        }*/
    }

    cout << "------------------------------------";
    for( int i = 0 ; i < baristaBrew.size() ; i++){
        if(baristaBrew.at(i).currentOrder != NULL){
            cout << baristaBrew.at(i).currentOrder->coffeeTime << " ";
        }

    }
    cout << "------------------------------------" << endl;


}

void Model1::endCashiers() {
    //  queueda varsa çalışmıyor
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

void Model1::endBaristas() {
    if(baristaQueue->count == 0){
        return;
    }

    vector<double> minNumber;
    for(int i = 0 ; i < baristaBrew.size() ; i++){
        Order * minOrder = baristaBrew.at(i).currentOrder;
        minNumber.push_back(( minOrder->beforeBrew + minOrder->coffeeTime) - lastOrderTime);
    }
    sort(minNumber.begin(),minNumber.end());
    cout << minNumber.at(0);


    for(int i = 0 ; i < baristaQueue->size() ; i++){
        baristaQueue->peek(i)->beforeBrew += minNumber.at(0);
    }

    for(int i = 0 ; i < baristaBrew.size() ; i++){
        Order * minOrder = baristaBrew.at(i).currentOrder;
        if( minNumber.at(0) == ( ( minOrder->beforeBrew + minOrder->coffeeTime) - lastOrderTime) ){
            cout << "-";
            lastOrderTime = minOrder->beforeBrew + minOrder->coffeeTime;
            baristaBrew.at(i).currentOrder = NULL;
            Order * tempOrder = baristaQueue->maxDequeue();
            baristaBrew.at(i).currentOrder = tempOrder;
            //baristaBrew.at(i).allTime += tempOrder->coffeeTime;
            baristaBrew.at(i).allOrders.insert(tempOrder);
        }
    }
    cout << lastOrderTime << " pusu ";
    endBaristas();

    /*
    int whileIndex = 0;

    while(!baristaQueue->isEmpty()){
        Order * tempOrder;
        double tempTime = 999999.0;
        for(int i = 0 ; i < baristaBrew.size() ; i++){
            Order* temp = baristaBrew.at(i).currentOrder;
            cout << (temp->beforeBrew + temp->coffeeTime) << " - ";
            cout << lastOrder->beforeBrew << " bunu ariyom ";
            if( temp != NULL && whileIndex == 0 && ((temp->beforeBrew + temp->coffeeTime) - lastOrder->beforeBrew < tempTime)){
                tempTime = (temp->beforeBrew + temp->coffeeTime) - lastOrder->beforeBrew ;
                tempOrder = temp;
            }else if{

            }
        }
    }

    int index = 0;
    for(int i = 0 ; i < baristaBrew.size(); i++){
        if(baristaBrew.at(i).currentOrder != NULL){
            index++;
        }
    }
    if(index == 0){return;}

    Order * tempOrder;
    double tempTime = 999999.0;

    for(int i = 0 ; i < baristaBrew.size() ; i++){
        Order* temp = baristaBrew.at(i).currentOrder;

        if( temp != NULL && ((temp->beforeBrew + temp->coffeeTime) - lastOrderTime < tempTime)){
            tempTime = (temp->beforeBrew + temp->coffeeTime) - lastOrder->beforeBrew ;
            cout << tempTime << " burasiiiiiii";
            tempOrder = temp;
        }
    }

    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if(baristaBrew.at(i).currentOrder != tempOrder){
            //baristaBrew.at(i).currentOrder->beforeBrew
        }
    }
    //lastOrderTime += tempTime;
    //cout << tempOrder->coffeeTime << endl;
    for(int i = 0 ; i < baristaQueue->count ; i++){
        Order* selectedOrder = baristaQueue->peek(i);
        cout << selectedOrder->coffeePrice << " - ";
        selectedOrder->beforeBrew += tempTime;
    }
    cout << endl;
    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if ( baristaBrew.at(i).currentOrder != NULL && baristaBrew.at(i).currentOrder == tempOrder){
            if(baristaQueue->count > 0){
                baristaBrew.at(i).currentOrder = baristaQueue->maxDequeue();
            }else{
                //lastOrderTime = baristaBrew.at(i).currentOrder.
                baristaBrew.at(i).currentOrder = NULL;
            }

        }
    }

    for(int i = 0 ; i < baristaQueue->count << i++){
        Order* newLastOrder
    }*/
    /*
    cout << "------------------------------------";
    for( int i = 0 ; i < baristaBrew.size() ; i++){
        if(baristaBrew.at(i).currentOrder != NULL){
            cout << baristaBrew.at(i).currentOrder->coffeeTime << " ";
        }

    }
    cout << "------------------------------------" << endl;

    if(baristaQueue->count == 0){return;}
    endBaristas();
     */

}

void Model1::endBaristaQueue() {
    double time = 0;
    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if(baristaBrew.at(i).currentOrder == NULL){
            continue;
        }else{
            Order * tempOrder = baristaBrew.at(i).currentOrder;
            //baristaBrew.at(i).allTime += tempOrder->coffeeTime;
            baristaBrew.at(i).allOrders.insert(tempOrder);
            if( ( tempOrder->beforeBrew + tempOrder->coffeeTime) > time){
                time = tempOrder->beforeBrew + tempOrder->coffeeTime;
            }
        }
    }
    cout << time  <<  " ---- \n";
    finishTime = time;
}