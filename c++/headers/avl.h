#pragma once
#include <iostream>
using namespace std;

struct ANode {
    int key;
    ANode* left;
    ANode* right;
    int height;
};

void TINSERT(ANode*& node, int key);
void TDEL(ANode*& node, int key);
ANode* TGET(ANode* node, int key);
void PRINT(ANode* node);
void CleanTree(ANode*& node);
void SaveTree(ANode* node, ostream& out);
void LoadTree(ANode*& node, istream& in);