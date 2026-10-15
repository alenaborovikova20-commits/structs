#pragma once
#include <iostream>
using namespace std;

struct DNode {
    int key;
    DNode* prev;
    DNode* next;
};

struct Dlist {
    DNode* head;
};

void InitDlist(Dlist* dlist);
void CleanDlist(Dlist* dlist);
void LPUSH(Dlist* dlist, int data);
void LPUSH_End(Dlist* dlist, int data);
void LPUSH_After(Dlist* dlist, DNode* node, int data);
void LPUSH_Before(Dlist* dlist, DNode* node, int data);
void LDEL(Dlist* dlist, int data);
void LDEL_Head(Dlist* dlist);
void LDEL_End(Dlist* dlist);
void LDEL_After(Dlist* dlist, DNode* prev_node);
void LDEL_Before(Dlist* dlist, DNode* next_node);
DNode* LGET(Dlist* dlist, int data);
DNode* LGET_Reverse(Dlist* dlist, int data);
void PRINT(Dlist* dlist);
void PRINT_Reverse(Dlist* dlist);
void SaveDlist(Dlist* dlist, ostream& out);
void LoadDlist(Dlist* dlist, istream& in);