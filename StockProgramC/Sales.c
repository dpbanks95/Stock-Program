/* 
 * File:   Sales.c
 * Author: Daniel Banks
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sales.h"

void printSalesItem(SalesItem* salesItem)
{
    printf("%d, %2d/%2d/%4d, %13s, %1d \n",salesItem->date, salesItem->day, salesItem->month, salesItem->year, salesItem->item->stockCode, salesItem->numSold);
    
}

SalesList* sales_list_new()
{
    SalesList* list = (SalesList*)malloc(sizeof(SalesList));
    if(list == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory in list_new()/n");
        
        exit(EXIT_FAILURE);
    }
    
    list->first=NULL;
    list->last=NULL;
    
    return list;
}

void sales_list_add(SalesList* list, SalesItem* salesItem)
{
    SalesNode* node = (SalesNode*)malloc(sizeof(SalesNode));
    if(node == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory in list_add()/n");
        
        exit(EXIT_FAILURE);
    }
    
    node->salesItem = (SalesItem*)malloc(sizeof(SalesItem));
    if(node->salesItem == NULL)
    {
        fprintf(stderr, "Error: unable to allocate item memory in list_add()/n");
        
        exit(EXIT_FAILURE);
    }
    node->salesItem->item = (stockItem*)malloc(sizeof(stockItem));
    if(node->salesItem->item == NULL)
    {
        fprintf(stderr, "Error: unable to allocate item memory in list_add()/n");
        
        exit(EXIT_FAILURE);
    }
    
    node->salesItem->item->type = strdup(salesItem->item->type);
    node->salesItem->item->stockCode = strdup(salesItem->item->stockCode);
    node->salesItem->item->stockLevel = salesItem->item->stockLevel;
    node->salesItem->item->price = salesItem->item->price;
    
    if(salesItem->item->details!=NULL){
        node->salesItem->item->details = strdup(salesItem->item->details);
    }else
        node->salesItem->item->details = NULL;
    
    node->salesItem->day = salesItem->day;
    node->salesItem->month = salesItem->month;
    node->salesItem->year = salesItem->year;
    node->salesItem->date = salesItem->date;
    node->salesItem->numSold = salesItem->numSold;
    node->next = NULL;
    
    if(list->last == NULL)
    {
        list->first = list->last = node;
    }
    else
    {
        list->last = list->last->next = node;
    }
}

void sales_list_insert(SalesList* list, SalesItem* salesItem)
{
    SalesNode* node = (SalesNode*)malloc(sizeof(SalesNode));
    if(node == NULL)
    {
        fprintf(stderr, "Error: unable to allocate memory in list_insert()/n");
        
        exit(EXIT_FAILURE);
    }
    
    node->salesItem = (SalesItem*)malloc(sizeof(SalesItem));
    if(node->salesItem == NULL)
    {
        fprintf(stderr, "Error: unable to allocate item memory in list_add()/n");
        
        exit(EXIT_FAILURE);
    }
    
//    node->item = item;
    node->salesItem->item->type = strdup(salesItem->item->type);
    node->salesItem->item->stockCode = strdup(salesItem->item->stockCode);
    node->salesItem->item->stockLevel = salesItem->item->stockLevel;
    node->salesItem->item->price = salesItem->item->price;
    
    if(salesItem->item->details!=NULL){
        node->salesItem->item->details = strdup(salesItem->item->details);
    }else
        node->salesItem->item->details = NULL;
    
    node->salesItem->day = salesItem->day;
    node->salesItem->month = salesItem->month;
    node->salesItem->year = salesItem->year;
    node->salesItem->date = salesItem->date;
    node->salesItem->numSold = salesItem->numSold;
    node->next = list->first;
    
    if(list->first == NULL)
    {
        list->first = list->last = node;
    }
    else
    {
        list->first = node;
    }
}

int sales_list_length(SalesList* list)
{
    int length = 0;
    SalesNode* node = list->first;
    for(node; node != NULL; node = node->next)
    {
        length++;
    }
    return length;
}

stockItem* sales_list_head(SalesList* list)
{
    if(list->first == NULL)
    {
        fprintf(stderr, "Error: attempt to return the head of an empty list.");

        exit(EXIT_FAILURE);
    }
    
    stockItem* item = list->first->salesItem;
    
    SalesNode* node = list->first;
    
    if(list->first == list->last)
    {
        list->first = list->last = NULL;
    }else
    {
        list->first = list->first->next;
    }
    
    free(node);
    return item;
}

stockItem* sales_list_tail(SalesList* list)
{
    if (list->first == NULL)
    {
        fprintf(stderr, "Error: attempt to return the tail of an empty list.");

        exit(EXIT_FAILURE);       
    }
    
    stockItem* item = list->last->salesItem;
    
    SalesNode* tail = list->last;
    
    if(list->first == list->last)
    {
        list->first = list->last = NULL;
    }else
    {
        SalesNode* node;
        for(node = list->first; node->next != tail; node = node->next);
        
        list->last = node;
        list->last->next = NULL;
    }
    
    free(tail);
    return item;
}

void sales_list_sort(SalesList* list)
{
    if(list->first != list->last)
    {
        int sorted;
        do
        {
            sorted = 1;
            
            if(list->first->salesItem->date > list->first->next->salesItem->date)
            {
                SalesNode* temp = list->first->next;
                list->first->next = temp->next;
                temp->next = list->first;
                list->first = temp;
                sorted = 0;
                
                if(list->last == temp)
                {
                    list->last = temp->next;
                }
            }
            SalesNode* node=list->first;
            for(node; node->next->next!=NULL; node=node->next)
            {
                if(node->next->salesItem->date > node->next->next->salesItem->date)
                {
                    SalesNode* temp = node->next->next;
                    node->next->next = temp->next;
                    temp->next = node->next;
                    node->next = temp;
                    sorted = 0;

                    if(list->last == temp)
                    {
                        list->last = temp->next;
                    }
                }
            }
        }
        while(!sorted);
    }
}

void sales_list_clear(SalesList* list)
{
    while(list->first != NULL)
    {
        SalesNode* node = list->first;
        list->first = node->next;
        free(node);
    }
    
    list->last = NULL;
}

void sales_list_fprint(SalesList* list)
{
    SalesNode *node = list->first;
    for(node; node!=NULL; node = node->next)
    {
        printSalesItem(node->salesItem);
    }
}
//------------------------------------------------------------------------------
//int main(int argc, char** argv) 
//{
//    SalesList* list = sales_list_new();
//
//    int i = 0;
//    for (i; i < 10; i++)
//    {
//        stockItem test = {"Resistor", "ABC123", rand()%1000, rand()%100, NULL};
//        sales_list_insert(list, test, i, i+10,i+100, i+6);
//    }
//    stockItem test = {"Resistor", "ABC123", rand()%1000, rand()%100, "Made of wood"};
//    sales_list_insert(list, test, i, i+10,i+100, i+6);
//    
//    printf("list = \n");
//    sales_list_fprint(list, stdout);
//    printf("\n\n");
//    printf("the list has %d items\n\n", sales_list_length(list));
//    
//    stockItem head = sales_list_head(list);
//    printf("Head: \n");
//    printItem(&head);
//    printf("\n");
//    
//    stockItem tail = sales_list_tail(list);
//    printf("Tail: \n");
//    printItem(&tail);
//    printf("\n");
//
//    printf("sorting the list...\n\n");
//
//    sales_list_sort(list);
//
//    printf("list = \n");
//    sales_list_fprint(list, stdout);
//    printf("\n\n");
//
//    printf("clearing the list...\n\n");
//
//    sales_list_clear(list);
//
//    printf("list = ");
//    sales_list_fprint(list, stdout);
//    printf("\n\n");
//
//    return (EXIT_SUCCESS);
//}
