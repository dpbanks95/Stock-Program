/* 
 * File:   Inventory.cpp
 * Author: Daniel Banks
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "Inventory.h"

Inventory::Inventory() : head(NULL), tail(NULL) {
}

Inventory::~Inventory() {
    node *current, *temp;
    current = head;
    temp = head;
    while (current != NULL) {
        current = current->next;
        delete temp;
        temp = current;
    }
}

/**
 * Initiate an Inventory List node
 * @param item
 * @return Inventory node*
 */
struct Inventory::node* Inventory::initNode(StockItem* item) {
    struct node *ptr = new node;

    if (ptr == NULL)
        return static_cast<struct node *> (NULL);
    else {
        ptr->item = item;
        return ptr;
    }
}

/**
 * Add a new node to an Inventory List
 * @param newNode
 */
void Inventory::addNode(struct node *newNode) {
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    }

    tail->next = newNode;
    newNode->next = NULL;
    tail = newNode;
}

/**
 * Insert a node into an Inventory List
 * @param newNode
 */
void Inventory::insertNode(struct node *newNode) {
    struct node *temp, *prev;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
        head->next = NULL;
        return;
    }

    temp = head;

    while (temp->item->getType() < newNode->item->getType()) {
        temp = temp->next;
        if (temp == NULL) {
            break;
        }
    }

    if (temp == head) {
        newNode->next = head;
        head = newNode;
    } else {
        prev = head;
        while (prev->next != temp) {
            prev = prev->next;
        }
        prev->next = newNode;
        newNode->next = temp;
        if (tail == prev) {
            tail = newNode;
        }
    }
}

/**
 * Find an item in an Inventory List by its stockCode
 * @param ptr
 * @param stockCode
 * @return Inventory node*
 */
struct Inventory::node* Inventory::searchStockCode(struct Inventory::node* ptr, 
        std::string stockCode) {
    while (stockCode != ptr->item->getStockCode()) {
        ptr = ptr->next;
        if (ptr == NULL)
            break;
    }
    return ptr;
}

/**
 * Delete a specified node in an Inventory List
 * @param ptr
 */
void Inventory::deleteNode(struct Inventory::node *ptr) {
    struct node *temp, *prev;
    temp = ptr;
    prev = head;

    if (temp == prev) {
        head = head->next;
        if (tail == temp)
            tail = tail->next;
        delete temp;
    } else {
        while (prev->next != temp) {
            prev = prev->next;
        }
        prev->next = temp->next;
        if (tail == temp)
            tail = prev;
        delete temp;
    }
}

/**
 * Clear an entire Inventory List
 * @param ptr
 */
void Inventory::deleteList(struct node *ptr) {
    struct node *temp;

    if (head == NULL)
        return;

    if (ptr == head) {
        head = NULL;
        tail = NULL;
    } else {
        temp = head;
        while (temp->next != ptr) {
            temp = temp->next;
        }
        tail = temp;
    }

    while (ptr != NULL) {
        temp = ptr->next;
        delete ptr;
        ptr = temp;
    }
}

/**
 * Output an node in an Inventory List
 * @param ptr
 */
void Inventory::displayNode(struct Inventory::node *ptr) const {
    ptr->item->printItem();
}

/**
 * Output an entire Inventory List
 * @param ptr
 */
void Inventory::displayList(struct Inventory::node *ptr) const {
    if (!ptr) std::cout << "Nothing to display" << std::endl;
    while (ptr) {
        displayNode(ptr);
        ptr = ptr->next;
    }
}

/**
 * Sort an Inventory List by Price, lowest to highest
 */
void Inventory::inv_list_sort() {
    if (this->head != this->tail) {
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            if (this->head->item->getPrice() > this->tail->item->getPrice()) {
                struct node* temp = this->head->next;
                this->head->next = temp->next;
                temp->next = this->head;
                this->head = temp;
                sorted = false;

                if (this->tail == temp) {
                    this->tail = temp->next;
                }
            }

            struct node* node = this->head;
            for (node; node->next->next != NULL; node = node->next) {
                if (node->next->item->getPrice() > 
                        node->next->next->item->getPrice()) {
                    struct node* temp = node->next->next;
                    node->next->next = temp->next;
                    temp->next = node->next;
                    node->next = temp;
                    sorted = false;

                    if (this->tail == NULL) {
                        this->tail = temp->next;
                    }
                }
            }
        }
    }

}

/**
 * Determine many NPN transistors are in stock after processing all sales
 * @return int
 */
int Inventory::countNPNTrans() {
    int count = 0;

    Inventory::node *node = this->head;
    for (node; node != NULL; node = node->next) {
        if (node->item->getType() == "transistor") {
            if (node->item->getDetails() == " NPN") {
                count += node->item->getStockLevel();
            }
        }
    }

    return count;
}

/**
 * Calculate resistance of all resistors in stock
 * @return double
 */
double Inventory::totalResistance() {
    double count = 0;
    Inventory::node *node = this->head;
    
    for (node; node != NULL; node = node->next) {
        if (node->item->getType() == 
                "resistor" && node->item->getStockLevel() > 0) {
            char *str = new char[node->item->getDetails().length() + 1];
            strcpy(str, node->item->getDetails().c_str());
            char* ptr;
            double num1;

            num1 = std::strtol(str, &ptr, 10);

            char *num2Char = ptr + 1;
            double num2 = atoi(num2Char);
            double countEach;

            if (strstr(ptr, "R") != NULL) {
                if (num2 > 0) {
                    countEach = (num1 + (num2 / 10)) * node->item
                            ->getStockLevel();
                    count += (num1 + (num2 / 10)) * node->item
                            ->getStockLevel();
                } else {
                    countEach = num1 * node->item->getStockLevel();
                    count += num1 * node->item->getStockLevel();
                }
            } else if (strstr(ptr, "K") != NULL) {
                if (num2 > 0) {
                    countEach = ((num1 + (num2 / 10))*1000) * node->item
                            ->getStockLevel();
                    count += ((num1 + (num2 / 10))*1000) * node->item
                            ->getStockLevel();
                } else {
                    countEach = (num1 * 1000) * node->item->getStockLevel();
                    count += (num1 * 1000) * node->item->getStockLevel();
                }
            } else if (strstr(ptr, "M") != NULL) {
                if (num2 > 0) {
                    countEach = ((num1 + (num2 / 10))*1000000) * node->item
                            ->getStockLevel();
                    count += ((num1 + (num2 / 10))*1000000) * node->item
                            ->getStockLevel();
                } else {
                    countEach = (num1 * 1000000) * node->item->getStockLevel();
                    count += (num1 * 1000000) * node->item->getStockLevel();
                }
            }

//            printf("\n");
//            printf("Stock Level: %d\n", node->item->getStockLevel());
//            printf("Resistance: %s", str);
//            printf("ptr: %s", ptr);
//            printf("num1: %f\n", num1);
//            printf("num2Char: %s", num2Char);
//            printf("num2: %f\n", num2/10);
//            printf("CountEach: %f \n", countEach);
//            printf("Count: %f", count);
//            printf("\n");
        }
    }

    return count;
}

//int main(int argc, char** argv) {
//
//    Resistor* resistor1 = new Resistor("resistor", "RES_1R0", 41, 12, "1R0");
//    Capacitor* capacior1 = new Capacitor("capacitor", "CAP_10pF", 648, 35, "10pF");
//    Diode* diode1 = new Diode("diode", "BY126", 118, 1);
//    Transistor* transistor1 = new Transistor("transistor", "AC125", 13, 11, "PNP");
//    IntegratedCircuit* ic1 = new IntegratedCircuit("IC", "NE555", 8, 1, "\"Timer\"");
//    
//    Inventory myList;
//    Inventory::node* ptr;
//    std::string  stockCode = ic1->getStockCode();
//
//    //ADD
//    ptr = myList.initNode(resistor1);
//    myList.addNode(ptr);
//    ptr = myList.initNode(capacior1);
//    myList.addNode(ptr);
//    ptr = myList.initNode(diode1);
//    myList.addNode(ptr);
//    ptr = myList.initNode(transistor1);
//    myList.addNode(ptr);
//    ptr = myList.initNode(ic1);
//    myList.addNode(ptr);
//    myList.displayList(myList.head);
//
//    //DELETE
//    ptr = myList.searchStockCode(myList.head, stockCode);
//    if (ptr == NULL) {
//        std::cout << "\nName: " << stockCode << " not found" << std::endl;
//    } else {
//        std::cout << "\nDeleting node: ";
//        myList.displayNode(ptr);
//        myList.deleteNode(ptr);
//    }
//    myList.displayList(myList.head);
//    
//    //INSERT
//    ptr = myList.initNode(ic1);
//    myList.insertNode(ptr);
//    std::cout << "\nInserting node:  ";
//    myList.displayNode(ptr);
//    myList.displayList(myList.head);
//    
//    //SORT
//    myList.inv_list_sort();
//    std::cout << "\nSorting list: \n";
//    myList.displayList(myList.head);
//    
//    std::cout << "FIN";
//
//    return 0;
//}