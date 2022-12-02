#include <iostream>
#include "Model1.h"
#include "CashierQueue.h"
#include "Order.h"
#include "Cashier.h"
#include "Barista.h"
#include <vector>
using namespace std;
// cashier an barista numbers starts with 0;
::vector<Cashier> cashierOrder;
::vector<Barista> baristaBrew;
CashierQueue* cashierQueue;
CashierQueue* baristaQueue;
::vector<Order*> finishedOrder;

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
        insertCashier(tempOrder);
        /*
        for(int i = 0 ; i < atOrder.size(); i++){
            if(atOrder.at(i).orderTime <= (arrivalTime - atOrder.at(i).arrivalTime)){

                if(atBrew().size() < (cashierNumber / 3)){
                    atBrew().push_back(atOrder.at(i));
                }else{
                    baristaQueue->enqueue(atOrder.at(i));
                }
                atOrder.erase(atOrder.begin() + i);
            }
        }
        if(!cashierQueue->isEmpty()){
            while(atOrder.size() < cashierNumber){
                cout << "burda3" << endl;
                Order tempOrder = cashierQueue->dequeue();

                if(tempOrder.orderTime != 0){
                    atOrder.push_back(tempOrder);
                }
            }
        }
        if(atOrder.size() < cashierNumber){

            atOrder.push_back(tempOrder);
        }else{

            cashierQueue->enqueue(tempOrder);

        }
        //cout << arrivalTime << " " << orderTime << " " << brewOrder << endl;
        for(Order i : atOrder){
            cout << i.orderTime << " ";
        }
        cout << endl;*/
    }

    while(!baristaQueue->isEmpty()){
        cout << baristaQueue->dequeue()->orderTime << "-";
    }
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

    for( int i = 0 ; i < cashierOrder.size() ; i++){
        if(cashierOrder.at(i).currentOrder != NULL){
            cout << cashierOrder.at(i).currentOrder->orderTime << " ";
        }

    }

    cout << index << endl;

}
void Model1::insertBarista(Order *currOrder) {
    int index = 0;


    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if(baristaBrew.at(i).currentOrder != NULL && (currOrder->beforeBrew - baristaBrew.at(i).currentOrder->beforeBrew) >= baristaBrew.at(i).currentOrder->coffeeTime){
            Order* tempOrder = baristaBrew.at(i).currentOrder;
            baristaBrew.at(i).currentOrder = NULL;
            finishedOrder.push_back(tempOrder);
        }
    }
    /*
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
                cashierOrder.at(i).currentOrder->arrivalTime = tempTime;
                break;
            }
        }
    }

    while(!baristaQueue->isEmpty()){
        double tempCoffeePrice = 0.0;
        for(int i = 0; i < baristaBrew.size() ; i++){
            if(baristaBrew.at(i).currentOrder == NULL && baristaBrew.at(i).currentOrder->coffeePrice > tempCoffeePrice ){
                tempCoffeePrice = baristaBrew.at(i).currentOrder->coffeePrice;
            }
        }
        if(tempCoffeePrice == 0.0){break;}

        for(int i = 0; i < baristaBrew.size() ; i++){
            if(baristaBrew.at(i).currentOrder.)
        }

    }
    */
    // en son maxDequeue yi yaptın buraya geri gelecektin
    for(int i = 0 ; i < baristaBrew.size() ; i++){
        if (baristaBrew.at(i).currentOrder == NULL){
            baristaBrew.at(i).currentOrder = currOrder;
            baristaBrew.at(i).allTime += currOrder->coffeeTime;
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