/* 
 * File:   Sales.h
 * Author: Daniel Banks
 */

#ifndef SALES_H
#define	SALES_H

#include "StockItem.h"
class SalesItem {    
private:
    StockItem* item;
    int date;
    int day;
    int month;
    int year;
    int numSold;
    
public:
    SalesItem(StockItem* item,int date,int day,int month,int year,int numSold);
    
    StockItem* getItem(){return item;}
    int getDate(){return date;}
    int getDay(){return day;}
    int getMonth(){return month;}
    int getYear(){return year;}
    int getNumSold(){return numSold;}
    void printSalesItem();
};

class Sales {
public:
    
    struct node {
        SalesItem* item;
        struct node *next;
    } *head, *tail, *ptr;

    Sales();
    ~Sales();
    
    struct Sales::node* sale_searchStockCode(struct Sales::node*, std::string);
    struct Sales::node* sale_initNode(SalesItem*);
    
    void sale_list_sort();
    void sale_addNode(struct Sales::node*);
    void sale_insertNode(struct Sales::node*);
    void sale_deleteNode(struct Sales::node*);
    void sale_deleteList(struct Sales::node*);
    void sale_displayList(struct Sales::node*)const;
    void sale_displayNode(struct Sales::node*) const;
    int * bestSalesDay();
};

#endif	/* SALES_H */

