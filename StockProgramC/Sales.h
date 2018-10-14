/* 
 * File:   Sales.h
 * Author: Daniel Banks
 */

#ifndef SALES_H
#define	SALES_H

#include "StockItem.h"

typedef struct _SALESITEM
{
    stockItem* item;
    int date;
    int day;
    int month;
    int year;
    int numSold;
}SalesItem;

typedef struct _SALESNODE
{
    SalesItem* salesItem;
    struct _SALESNODE* next;
}
SalesNode;

typedef struct _SALESLIST
{
    SalesNode* first;
    SalesNode* last;
}
SalesList;

void printSalesItem(SalesItem* salesItem);

SalesList* sales_list_new();
void sales_list_add(SalesList* list, SalesItem* salesItem);
void sales_list_insert(SalesList* list, SalesItem* salesItem);
int sales_list_length(SalesList* list);
stockItem* sales_list_head(SalesList* list);
stockItem* sales_list_tail(SalesList* list);
void sales_list_sort(SalesList* list);
void sales_list_clear(SalesList* list);
void sales_list_fprint(SalesList* list);

#endif	/* SALES_H */

