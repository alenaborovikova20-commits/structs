#pragma once
#include <iostream>
using namespace std;

struct SNode {
    int field;
    SNode* ptr;
};

struct Stack {
    SNode* head;
};

void InitStack(Stack* stack);
void CleanStack(Stack* stack);
void SPUSH(int data, Stack* s);
void SPOP(Stack* s);
void PRINT(Stack* s);
void SaveStack(Stack* s, ostream& out);
void LoadStack(Stack* s, istream& in);