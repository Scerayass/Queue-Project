#include "CashierQueue.h"
#include "Order.h"
#include <iostream>


CashierQueue::CashierQueue(int size) {

    capacity = size;
    front = 0;
    rear = -1;
    count = 0;

}

CashierQueue::CashierQueue() {

}
CashierQueue::~CashierQueue() {
    //delete[] arr;
}


Order * CashierQueue::dequeue() {
    if (isEmpty()){

    }
    Order *x = arr.front();
    arr.erase(arr.begin());

    count--;

    return x;
}

void CashierQueue::enqueue(Order* x) {
    if(isFull()){
        return;
    }

    arr.push_back(x);
    count++;

    if(count > max){
        max = count;
    }

}
Order* CashierQueue::peek(int x) {
    if(front + x > capacity-1){
        std::cout << "cannot peek" << std::endl;

    }
    return arr.at(x);
}

int CashierQueue::size() {
    return count;
}

bool CashierQueue::isEmpty() {
    return (size() == 0);
}
bool CashierQueue::isFull() {
    return (size() == capacity);
}

Order * CashierQueue::maxDequeue() {
    double maxCoffeePrice = 0.0;
    int index;
    for(int i = 0; i < arr.size() ; i++){
        if(arr.at(i)->coffeePrice > maxCoffeePrice){
            maxCoffeePrice = arr.at(i)->coffeePrice;
            index = i;
        }
    }
    Order* x = arr.at(index);
    arr.erase(arr.begin()+index);
    count--;

    return x;


}