/* 
 * File:   Inventory.c
 * Author: Daniel Banks
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Inventory.h"

InvList* inv_list_new() {
    InvList* list = (InvList*) malloc(sizeof (InvList));

    if (list == NULL) {
        fprintf(stderr, "Error: unable to allocate memory in list_new()/n");

        exit(EXIT_FAILURE);
    }

    list->first = NULL;
    list->last = NULL;

    return list;
}

void inv_list_add(InvList* list, stockItem* item) {
    InvNode* node = (InvNode*) malloc(sizeof (InvNode));
    if (node == NULL) {
        fprintf(stderr, "Error: unable to allocate node memory in list_add()/n");

        exit(EXIT_FAILURE);
    }

    node->item = (stockItem*) malloc(sizeof (stockItem));
    if (node->item == NULL) {
        fprintf(stderr, "Error: unable to allocate item memory in list_add()/n");

        exit(EXIT_FAILURE);
    }

    //    node->item = item;
    node->item->type = strdup(item->type);
    node->item->stockCode = strdup(item->stockCode);
    node->item->stockLevel = item->stockLevel;
    node->item->price = item->price;

    if (item->details != NULL) {
        node->item->details = strdup(item->details);
    } else
        node->item->details = NULL;

    node->next = NULL;

    if (list->last == NULL) {
        list->first = list->last = node;
    } else {
        list->last = list->last->next = node;
    }
}

void inv_list_insert(InvList* list, stockItem* item) {
    InvNode* node = (InvNode*) malloc(sizeof (InvNode));
    if (node == NULL) {
        fprintf(stderr, "Error: unable to allocate memory in list_insert()/n");

        exit(EXIT_FAILURE);
    }

    node->item = (stockItem*) malloc(sizeof (stockItem));
    if (node->item == NULL) {
        fprintf(stderr, "Error: unable to allocate item memory in list_add()/n");

        exit(EXIT_FAILURE);
    }
    
    node->item->type = strdup(item->type);
    node->item->stockCode = strdup(item->stockCode);
    node->item->stockLevel = item->stockLevel;
    node->item->price = item->price;

    if (item->details != NULL) {
        node->item->details = strdup(item->details);
    } else
        node->item->details = NULL;

    node->next = list->first;

    if (list->first == NULL) {
        list->first = list->last = node;
    } else {
        list->first = node;
    }
}

int inv_list_length(InvList* list) {
    int length = 0;
    InvNode* node = list->first;
    for (node; node != NULL; node = node->next) {
        length++;
    }
    return length;
}

stockItem* inv_list_head(InvList* list) {
    if (list->first == NULL) {
        fprintf(stderr, "Error: attempt to return the head of an empty list.");

        exit(EXIT_FAILURE);
    }

    stockItem* item = list->first->item;

    InvNode* node = list->first;

    if (list->first == list->last) {
        list->first = list->last = NULL;
    } else {
        list->first = list->first->next;
    }

    free(node);
    return item;
}

stockItem* inv_list_tail(InvList* list) {
    if (list->first == NULL) {
        fprintf(stderr, "Error: attempt to return the tail of an empty list.");

        exit(EXIT_FAILURE);
    }

    stockItem* item = list->last->item;

    InvNode* tail = list->last;

    if (list->first == list->last) {
        list->first = list->last = NULL;
    } else {
        InvNode* node;
        for (node = list->first; node->next != tail; node = node->next);

        list->last = node;
        list->last->next = NULL;
    }

    free(tail);
    return item;
}

void inv_list_sort(InvList* list) {
    if (list->first != list->last) {
        int sorted;
        do {
            sorted = 1;

            if (list->first->item->price > list->first->next->item->price) {
                InvNode* temp = list->first->next;
                list->first->next = temp->next;
                temp->next = list->first;
                list->first = temp;
                sorted = 0;

                if (list->last == temp) {
                    list->last = temp->next;
                }
            }
            InvNode* node = list->first;
            for (node; node->next->next != NULL; node = node->next) {
                if (node->next->item->price > node->next->next->item->price) {
                    InvNode* temp = node->next->next;
                    node->next->next = temp->next;
                    temp->next = node->next;
                    node->next = temp;
                    sorted = 0;

                    if (list->last == temp) {
                        list->last = temp->next;
                    }
                }
            }
        }        while (!sorted);
    }
}

void inv_list_clear(InvList* list) {
    while (list->first != NULL) {
        InvNode* node = list->first;
        list->first = node->next;
        free(node);
    }

    list->last = NULL;
}

void inv_list_fprint(InvList* list) {
    InvNode *node = list->first;
    for (node; node != NULL; node = node->next) {
        printItem(node->item);
    }
}
//------------------------------------------------------------------------------
//int main(int argc, char** argv) 
//{
//    InvList* list = inv_list_new();
//
//    int i = 0;
//    for (i; i < 10; i++)
//    {
//        stockItem test = {"Resistor", "ABC123", rand()%1000, rand()%100, NULL};
//        inv_list_insert(list, test);
//    }
//    stockItem test = {"Resistor", "ABC123", rand()%1000, rand()%100, "Made of Wood"};
//    inv_list_insert(list, test);
//        
//    printf("list = \n");
//    inv_list_fprint(list, stdout);
//    printf("\n\n");
//    printf("the list has %d items\n\n", inv_list_length(list));
//    
//    stockItem head = inv_list_head(list);
//    printf("Head: \n");
//    printItem(&head);
//    printf("\n");
//    
//    stockItem tail = inv_list_tail(list);
//    printf("Tail: \n");
//    printItem(&tail);
//    printf("\n");
//
//    printf("sorting the list...\n\n");
//
//    inv_list_sort(list);
//
//    printf("list = \n");
//    inv_list_fprint(list, stdout);
//    printf("\n\n");
//
//    printf("clearing the list...\n\n");
//
//    inv_list_clear(list);
//
//    printf("list = ");
//    inv_list_fprint(list, stdout);
//    printf("\n\n");
//
//    return (EXIT_SUCCESS);
//}
