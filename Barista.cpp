#include "Barista.h"

Barista::Barista() {

}

Barista::Barista(int x) {
    baristaNumber = x;
}

void Barista::calculateFinish() {
    for(Order* i : allOrders){
        allTime += i->coffeeTime;
    }
}