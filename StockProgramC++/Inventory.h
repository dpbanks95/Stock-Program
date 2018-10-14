/* 
 * File:   Inventory.h
 * Author: Daniel Banks
 */

#ifndef INVENTORY_H
#define	INVENTORY_H

#include "StockItem.h"

class Inventory {
public:

    struct node {
        StockItem* item;
        struct node *next;
    } *head, *tail, *ptr;

    Inventory();
    ~Inventory();

    struct Inventory::node* searchStockCode(struct Inventory::node*,
    std::string);
    struct Inventory::node* initNode(StockItem*);

    void reverse();
    void inv_list_sort();
    void addNode(struct Inventory::node*);
    void insertNode(struct Inventory::node*);
    void deleteNode(struct Inventory::node*);
    void deleteList(struct Inventory::node*);
    void displayList(struct Inventory::node*) const;
    void displayNode(struct Inventory::node*) const;
    int countNPNTrans();
    double totalResistance();
};

#endif	/* INVENTORY_H */

