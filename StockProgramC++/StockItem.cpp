/* 
 * File:   StockItem.cpp
 * Author: Daniel Banks
 */

#include <cstdlib>
#include <iostream>
#include "StockItem.h"

StockItem::~StockItem() {
}

StockItem::StockItem(std::string type, std::string stockCode, int stockLevel, 
        int price) : type(type), stockCode(stockCode), stockLevel(stockLevel), 
        price(price) {
}

Resistor::Resistor(std::string type, std::string stockCode, int stockLevel, 
        int price, std::string resistance) : StockItem(type, stockCode, 
        stockLevel, price), resistance(resistance) {
}

void Resistor::printItem() {
    std::cout << this->type << ", ";
    std::cout << this->stockCode << ", ";
    std::cout << this->stockLevel << ", ";
    std::cout << this->price << ", ";
    std::cout << this->resistance << std::endl;
}

Capacitor::Capacitor(std::string type, std::string stockCode, int stockLevel, 
        int price,std::string capacitance) : StockItem(type, stockCode, 
        stockLevel, price),capacitance(capacitance) {
}

void Capacitor::printItem() {
    std::cout << this->type << ", ";
    std::cout << this->stockCode << ", ";
    std::cout << this->stockLevel << ", ";
    std::cout << this->price << ", ";
    std::cout << this->capacitance << std::endl;
}

Diode::Diode(std::string type, std::string stockCode, int stockLevel,int price):
StockItem(type, stockCode, stockLevel, price) {
}

void Diode::printItem() {
    std::cout << this->type << ", ";
    std::cout << this->stockCode << ", ";
    std::cout << this->stockLevel << ", ";
    std::cout << this->price << std::endl;
}

Transistor::Transistor(std::string type, std::string stockCode, int stockLevel, 
        int price,std::string deviceType) : StockItem(type, stockCode, 
        stockLevel, price), deviceType(deviceType) {
}

void Transistor::printItem() {
    std::cout << this->type << ", ";
    std::cout << this->stockCode << ", ";
    std::cout << this->stockLevel << ", ";
    std::cout << this->price << ", ";
    std::cout << this->deviceType << std::endl;
}

IntegratedCircuit::IntegratedCircuit(std::string type, std::string stockCode, 
        int stockLevel, int price,std::string description) : StockItem(type, 
        stockCode, stockLevel, price), description(description) {
}

void IntegratedCircuit::printItem() {
    std::cout << this->type << ", ";
    std::cout << this->stockCode << ", ";
    std::cout << this->stockLevel << ", ";
    std::cout << this->price << ", ";
    std::cout << this->description << std::endl;
}

//int main(int argc, char** argv)
//{
//    
//    Resistor resistor1("resistor", "RES_1R0", 41, 1, "1R0");
//    resistor1.printItem();
//    
//    Capacitor capacior1("capacitor", "CAP_10pF", 648, 12, "10pF");
//    capacior1.printItem();
//    
//    Diode diode1("diode", "BY126", 118, 12);
//    diode1.printItem();
//    
//    Transistor transistor1("transistor", "AC125", 13, 35, "PNP");
//    transistor1.printItem();
//    
//    IntegratedCircuit ic1("IC", "NE555", 8, 17, "\"Timer\"");
//    ic1.printItem();
//    
//    std::cout << "FIN";
//    
//    return 0;
//}