#ifndef THIRDASSIGNMENT_CASHIERQUEUE_H
#define THIRDASSIGNMENT_CASHIERQUEUE_H

#include "Order.h"
#include "Barista.h"
#include <vector>
#define SIZE 1000
using namespace std;

class CashierQueue {

public:
    CashierQueue();
    CashierQueue(int size = SIZE);
    ~CashierQueue();
    Order * dequeue();
    Order * maxDequeue();
    void enqueue(Order* x);
    Order* peek(int x);
    int size();
    bool isEmpty();
    bool isFull();
    int subtractor(double x);

    //Barista currBarista;
    int max = 0;
    int capacity;
    int front;
    int rear;
    int count;
    vector<Order*> arr;

};


#endif //THIRDASSIGNMENT_CASHIERQUEUE_H
