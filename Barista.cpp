#include "Barista.h"

Barista::Barista() {

}

Barista::Barista(int x) {
    baristaNumber = x;
}
/**
 * it calculates all time for barista's work.
 */
void Barista::calculateFinish() {
    for(Order* i : allOrders){
        allTime += i->coffeeTime;
    }
}