#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key;
    Node* next;
};

struct Flist {
    Node* head;
};

void InitFlist(Flist* flist);
void CleanFlist(Flist* flist);
void FPUSH(Flist* flist, const string& data);
void FPUSH_End(Flist* flist, const string& data);
void FPUSH_After(Flist* flist, Node* node, const string& data);
void FPUSH_Before(Flist* flist, Node* node, const string& data);
void FDEL(Flist* flist, const string& find_data);
void FDEL_Head(Flist* flist);
void FDEL_End(Flist* flist);
void FDEL_After(Flist* flist, Node* prev_node);
void FDEL_Before(Flist* flist, Node* next_node);
Node* FGET(Flist* flist, const string& find_data);
void PRINT(Flist* flist);
void SaveFlist(Flist* flist, ostream& out);
void LoadFlist(Flist* flist, istream& in);