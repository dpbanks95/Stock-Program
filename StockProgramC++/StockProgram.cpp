/* 
 * File:   StockProgram.cpp
 * Author: Daniel Banks
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "Inventory.h"
#include "Sales.h"
#include "StockItem.h"

int main(int argc, char** argv) {

    //Read in inventory file
    std::ifstream invFile("inventory.txt");
    std::string line;
    std::string type;
    std::string stockCode;
    int stockLevel;
    int price;
    std::string details;
    Inventory::node* ptr;
    Inventory invList;
    StockItem* item;

    if (invFile.is_open()) {
        while (std::getline(invFile, line)) {
            std::istringstream iss(line);
            std::string token;

            int i = 0;
            while (std::getline(iss, token, ',')) {
                switch (i) {
                    case 0:
                        type = token;
                        break;
                    case 1:
                        stockCode = token;
                        break;
                    case 2:
                        stockLevel = atoi(token.c_str());
                        break;
                    case 3:
                        price = atoi(token.c_str());
                        break;
                    case 4:
                        token.erase(token.find_last_not_of("\n\r") + 1);
                        details = token;
                        break;
                    default:
                        fprintf(stderr, "Token out of bounds, too many "
                                "parameters for stock item. \n");
                }
                i++;
            }
            if (type == "resistor") {
                item = new Resistor(type,stockCode,stockLevel,price,details);
            } else if (type == "capacitor") {
                item = new Capacitor(type,stockCode,stockLevel,price,details);
            } else if (type == "diode") {
                item = new Diode(type,stockCode,stockLevel,price);
            } else if (type == "transistor") {
                item = new Transistor(type,stockCode,stockLevel,price,details);
            } else if (type == "IC") {
                item = new IntegratedCircuit(type,stockCode,stockLevel,price,
                        details);
            }
            ptr = invList.initNode(item);
            invList.addNode(ptr);
        }
    }
    
    //Read in sales file
    std::ifstream salesFile("sales.txt");
    Sales salesList;
    Sales::node* salesPtr;

    bool success;
    bool found;
    int day;
    int month;
    int year;
    int quantity;

    if (salesFile.is_open()) {
        while (std::getline(salesFile, line)) {
            success = false;
            found = false;
            std::istringstream iss(line);
            std::string token;

            int i = 0;
            while (std::getline(iss, token, ',')) {
                std::istringstream issDate(token);
                std::string tokenDate;
                int j = 0;
                switch (i) {
                    case 0:
                        while (std::getline(issDate, tokenDate, '/')) {
                            switch (j) {
                                case 0:
                                    day = atoi(tokenDate.c_str());
                                    break;
                                case 1:
                                    month = atoi(tokenDate.c_str());
                                    break;
                                case 2:
                                    year = atoi(tokenDate.c_str());
                                    break;
                            }
                            j++;
                        }
                        break;
                    case 1:
                        stockCode = token;
                        break;
                    case 2:
                        quantity = atoi(token.c_str());
                        break;
                    default:
                        printf("Token out of bounds, too many parameters for "
                                "sales item. \n");
                }
                i++;
            }

            Inventory::node* node = invList.head;
            for (node; node != NULL; node = node->next) {
                if (node->item->getStockCode().compare(stockCode) == 0) {
                    found = true;
                    if (node->item->getStockLevel() >= quantity) {
                        success = true;
                        node->item->setStockLevel(node->item->getStockLevel() 
                        - quantity);
                        item = node->item;
                    } else {
                        success = false;
                        std::cout << "Item " << node->item->getStockCode() 
                                << " stock level " <<node->item->getStockLevel()
                                << " is too low to apply sale of " <<quantity 
                                << " items." << std::endl;
                    }
                    break;
                }
            }

            if (!found) {
                std::cout << "Item " << stockCode << " not found in inventory." 
                        << std::endl;
            }
            if (success) {
                int date = 10000 * year + 100 * month + day;
                SalesItem* salesItem = new SalesItem(item, date, day, month, 
                        year, quantity);
                salesPtr = salesList.sale_initNode(salesItem);
                salesList.sale_addNode(salesPtr);
            }
        }
    }
    std::cout << std::endl;
    salesFile.close();
//    salesList.sale_displayList(salesList.head);
    
    printf("Sorted Inventory List ---------------------------------------- \n");
    invList.inv_list_sort();
    invList.displayList(invList.head);

    int *bestDay = salesList.bestSalesDay();
    printf("\n");
    printf("Best Day: %d/%d/%d", bestDay[0], bestDay[1], bestDay[2]);
    printf("\n");
    double amount = (double)bestDay[3]/100;
    printf("Amount Made: %f", amount);
    printf("\n");
    printf("Number of Items sold: %d", bestDay[4]);
    

    int npnStock = invList.countNPNTrans();
    printf("\n");
    printf("NPN Stock: %d", npnStock);

    double totalRes = invList.totalResistance();
    printf("\n");
    printf("Total Resistance: %f", totalRes);

    return 0;
}





