/* 
 * File:   Sales.cpp
 * Author: Daniel Banks
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "Sales.h"

SalesItem::SalesItem(StockItem* item, int date, int day, int month, int year, 
        int numSold) : item(item), date(date), day(day), month(month),
        year(year), numSold(numSold) {
}

void SalesItem::printSalesItem() {
    std::cout << this->date << ", ";
    std::cout << this->day<<"/"<<this->month<<"/"<<this->year<< ", ";
    std::cout << this->item->getStockCode() << ", ";
    std::cout << this->numSold << ", "<<std::endl;
}

Sales::Sales() : head(NULL), tail(NULL) {
}

Sales::~Sales() {
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
 * Initiate an Sales List node
 * @param item
 * @return Sales node*
 */
struct Sales::node* Sales::sale_initNode(SalesItem* item) {
    struct node *ptr = new node;

    if (ptr == NULL)
        return static_cast<struct node *> (NULL);
    else {
        ptr->item = item;
        return ptr;
    }
}

/**
 * Add a new node to a Sales List
 * @param newNode
 */
void Sales::sale_addNode(struct node *newNode) {
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    }

    tail->next = newNode;
    newNode->next = NULL;
    tail = newNode;
}

/**
 * Insert a node into a Sales List
 * @param newNode
 */
void Sales::sale_insertNode(struct node *newNode) {
    struct node *temp, *prev;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
        head->next = NULL;
        return;
    }

    temp = head;

    while (temp->item->getItem()->getType() < 
            newNode->item->getItem()->getType()) {
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
 * Find an item in a Sales List by its stockCode
 * @param ptr
 * @param stockCode
 * @return Sales node*
 */
struct Sales::node* Sales::sale_searchStockCode(struct Sales::node* ptr, 
        std::string stockCode) {
    while (stockCode != ptr->item->getItem()->getStockCode()) {
        ptr = ptr->next;
        if (ptr == NULL)
            break;
    }
    return ptr;
}

/**
 * Delete a specified node in a Sales List
 * @param ptr
 */
void Sales::sale_deleteNode(struct Sales::node *ptr) {
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
 * Clear an entire Sales List
 * @param ptr
 */
void Sales::sale_deleteList(struct node *ptr) {
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
 * Output an node in a Sales List
 * @param ptr
 */
void Sales::sale_displayNode(struct Sales::node *ptr) const {
    ptr->item->printSalesItem();
}

/**
 * Output an entire Sales List
 * @param ptr
 */
void Sales::sale_displayList(struct Sales::node *ptr) const {
    if (!ptr) std::cout << "Nothing to display" << std::endl;
    while (ptr) {
        sale_displayNode(ptr);
        ptr = ptr->next;
    }
}

/**
 * Sort a Sales List by Date, oldest to newest
 */
void Sales::sale_list_sort() {
    if (this->head != this->tail) {
        bool sorted = false;
        while (!sorted) {
            sorted = true;

            if (this->head->item->getDate() > 
                    this->head->next->item->getDate()) {
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
                if (node->next->item->getDate() > 
                        node->next->next->item->getDate()) {
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
 * Determine the date with the highest sales volume (Most money made in one day)
 * @return int array
 */
int * Sales::bestSalesDay() {
    static int maxDateArray[5];
    int count=0;
    int numSold=0;
    int maxNumSold=0;
    int currentDate=0;
    int lastDate=0;
    int max=0;
    int maxDate=0;

    Sales::node *node = this->head;
    lastDate = node->item->getDate();

    for (node; node != NULL; node = node->next) {
        currentDate = node->item->getDate();

        if (currentDate == lastDate) {
            count += node->item->getNumSold()*node->item->getItem()->getPrice();
            numSold += node->item->getNumSold();
        } else if (count > max) {
            max = count;
            maxDate = lastDate;
            maxNumSold = numSold;
            count = node->item->getNumSold()*node->item->getItem()->getPrice();
            numSold = node->item->getNumSold();
        } else {
            count = node->item->getNumSold()*node->item->getItem()->getPrice();
            numSold = node->item->getNumSold();
        }

        lastDate = currentDate;
    }

    Sales::node *secondNode = this->head;
    for (secondNode; secondNode != NULL; secondNode = secondNode->next) {
        if (secondNode->item->getDate() == maxDate) {
            maxDateArray[0] = secondNode->item->getDay();
            maxDateArray[1] = secondNode->item->getMonth();
            maxDateArray[2] = secondNode->item->getYear();
            maxDateArray[3] = max;
            maxDateArray[4] = maxNumSold;
            break;
        }
    }
    return maxDateArray;
}

//int main(int argc, char** argv) {
//    Resistor* resistor1 = new Resistor("resistor", "RES_1R0", 41, 12, "1R0");
//    Capacitor* capacior1 = new Capacitor("capacitor", "CAP_10pF", 648, 35, "10pF");
//    Diode* diode1 = new Diode("diode", "BY126", 118, 1);
//    Transistor* transistor1 = new Transistor("transistor", "AC125", 13, 11, "PNP");
//    IntegratedCircuit* ic1 = new IntegratedCircuit("IC", "NE555", 8, 1, "\"Timer\"");
//
//    SalesItem* salesItem1 = new SalesItem(resistor1, 15051995, 15, 5, 1995, 10);
//    SalesItem* salesItem2 = new SalesItem(capacior1, 16061996, 16, 6, 1996, 11);
//    SalesItem* salesItem3 = new SalesItem(diode1, 17071997, 17, 7, 1997, 12);
//    SalesItem* salesItem4 = new SalesItem(transistor1, 18081998, 18, 8, 1998, 13);
//    SalesItem* salesItem5 = new SalesItem(ic1, 19091999, 19, 9, 1999, 14);
//
//    Sales myList;
//    Sales::node* ptr;
//
//    ptr = myList.sale_initNode(salesItem4);
//    myList.sale_addNode(ptr);
//    ptr = myList.sale_initNode(salesItem3);
//    myList.sale_addNode(ptr);
//    ptr = myList.sale_initNode(salesItem2);
//    myList.sale_addNode(ptr);
//    ptr = myList.sale_initNode(salesItem1);
//    myList.sale_addNode(ptr);
//    ptr = myList.sale_initNode(salesItem5);
//    myList.sale_addNode(ptr);
//    myList.sale_displayList(myList.head);
//
//    std::string  stockCode = ic1->getStockCode();
//
//    //DELETE
//    ptr = myList.sale_searchStockCode(myList.head, stockCode);
//    if (ptr == NULL) {
//        std::cout << "\nName: " << stockCode << " not found" << std::endl;
//    } else {
//        std::cout << "\nDeleting node: ";
//        myList.sale_displayNode(ptr);
//        myList.sale_deleteNode(ptr);
//    }
//    myList.sale_displayList(myList.head);
//
//    //INSERT
//    ptr = myList.sale_initNode(salesItem5);
//    myList.sale_insertNode(ptr);
//    std::cout << "\nInserting node:  ";
//    myList.sale_displayNode(ptr);
//    myList.sale_displayList(myList.head);
//
//    //SORT
//    myList.sale_list_sort();
//    std::cout << "\nSorting list: \n";
//    myList.sale_displayList(myList.head);
//
//    std::cout << "FIN";
//}