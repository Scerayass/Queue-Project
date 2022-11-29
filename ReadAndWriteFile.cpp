#include <fstream>
#include <iostream>
#include "sstream"
#include "ReadAndWriteFile.h"
#include <vector>

using namespace std;

void ReadAndWriteFile::execute() {
    ifstream inputFile;
    inputFile.open("input.txt",ios::in);
    string inputString;

    int cashiersNumber;
    int orderNumber;

    vector<string*> allOrders;
    int index = 0;
    while(getline(inputFile,inputString)){
        if (index == 0){
            cashiersNumber = stoi(inputString);
            index++;
        }else if(index == 1){
            orderNumber = stoi(inputString);

            index++;
        }else{
            istringstream orderStream(inputString);

            string orderString;
            string* tempOrderArray = new string[4];
            int tempIndex;
            while(getline(orderStream,orderString,' ')){
                tempOrderArray[tempIndex] = orderString;
                tempIndex++;
            }
            allOrders.push_back(tempOrderArray);



        }


    }
    for(int i = 0; i < allOrders.size() ; i++){
        cout << allOrders[i];
    }





    inputFile.close();

}