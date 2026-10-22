#pragma once
#include <iostream>
#include <string>
using namespace std;

struct DNode {
    string key;
    DNode* prev;
    DNode* next;
};

struct Dlist {
    DNode* head;
    DNode* tail;
};

void InitDlist(Dlist* dlist);
void CleanDlist(Dlist* dlist);
void LPUSH(Dlist* dlist, const string& data);
void LPUSH_End(Dlist* dlist, const string& data);
void LPUSH_After(Dlist* dlist, DNode* node, const string& data);
void LPUSH_Before(Dlist* dlist, DNode* node, const string& data);
void LDEL(Dlist* dlist, const string& data);
void LDEL_Head(Dlist* dlist);
void LDEL_End(Dlist* dlist);
void LDEL_After(Dlist* dlist, DNode* prev_node);
void LDEL_Before(Dlist* dlist, DNode* next_node);
DNode* LGET(Dlist* dlist, const string& data);
DNode* LGET_Reverse(Dlist* dlist, const string& data);
void PRINT(Dlist* dlist);
void PRINT_Reverse(Dlist* dlist);
void SaveDlist(Dlist* dlist, ostream& out);
void LoadDlist(Dlist* dlist, istream& in);