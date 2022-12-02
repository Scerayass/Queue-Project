#include <fstream>
#include <iostream>
#include "sstream"
#include "ReadAndWriteFile.h"
#include "Model1.h"
#include "Model2.h"
#include <vector>

using namespace std;

void ReadAndWriteFile::execute() {
    ifstream inputFile;
    inputFile.open("input.txt",ios::in);
    string inputString;

    Model1 model1;
    Model2 model2;
    int cashiersNumber;
    int orderNumber;

    vector<vector<string>> allOrders;

    //string* allOrders;
    int index = 0;
    int orderIndex = 0;
    while(getline(inputFile,inputString)){
        if (index == 0){
            cashiersNumber = stoi(inputString);
            index++;
        }else if(index == 1){
            orderNumber = stoi(inputString);
            index++;
        }else{
            istringstream orderStream(inputString);

            string orderString =  "";
            vector<string> tempVector;

            while(getline(orderStream,orderString,' ')){

                tempVector.push_back(orderString);


            }
            allOrders.push_back(tempVector);
            orderIndex++;

        }

    }/*
    for(vector<string> i : allOrders){

        for(string j: i){
            cout << j << " ";
        }
        cout << endl;
    }*/
    model1.orders = allOrders;
    model1.execute(allOrders,cashiersNumber,orderNumber);


    inputFile.close();

}