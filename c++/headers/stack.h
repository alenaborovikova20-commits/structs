#pragma once
#include <iostream>
#include <string>
using namespace std;

struct SNode {
    string field;
    SNode* ptr;
};

struct Stack {
    SNode* head;
};

void InitStack(Stack* stack);
void CleanStack(Stack* stack);
void SPUSH(const string& data, Stack* s);
void SPOP(Stack* s);
void PRINT(Stack* s);
void SaveStack(Stack* s, ostream& out);
void LoadStack(Stack* s, istream& in);