/* 
 * File:   Inventory.h
 * Author: Daniel Banks
 */

#ifndef INVENTORY_H
#define	INVENTORY_H

#include "StockItem.h"

typedef struct _INVNODE
{
    stockItem* item;
    struct _INVNODE* next;
}
InvNode;

typedef struct _INVLIST
{
    InvNode* first;
    InvNode* last;
}
InvList;

InvList* inv_list_new();
void inv_list_add(InvList* list, stockItem* item);
void inv_list_insert(InvList* list, stockItem* item);
int inv_list_length(InvList* list);
stockItem* inv_list_head(InvList* list);
stockItem* inv_list_tail(InvList* list);
void inv_list_sort(InvList* list);
void inv_list_clear(InvList* list);
void inv_list_fprint(InvList* list);

#endif	/* INVENTORY_H */

