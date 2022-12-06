#include <fstream>
#include <iostream>
#include "sstream"
#include "ReadAndWriteFile.h"
#include "Model1.h"
#include "Model2.h"
#include <vector>

using namespace std;

void ReadAndWriteFile::execute(string inputFileName,string outputFileName) {
    ifstream inputFile;
    inputFile.open(inputFileName,ios::in);
    string inputString;

    Model1 model1;
    Model2 model2;

    int cashiersNumber;
    int orderNumber;

    vector<vector<string>> allOrders; // holding all inputs

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
    }

    model1.orders = allOrders; // adding all orders to model1
    model1.execute(allOrders,cashiersNumber,orderNumber,outputFileName);
    model2.orders = allOrders; //  adding all orders to model2
    model2.execute(allOrders,cashiersNumber,orderNumber,outputFileName);

    inputFile.close();

}