#pragma once
#include <iostream>
#include <string>
using namespace std;

struct QNode {
    string data;
    QNode* next;
};

struct Queue {
    QNode* head;
    QNode* tail;
};

void InitQueue(Queue* queue);
void CleanQueue(Queue* queue);
void QPUSH(Queue* queue, const string& data);
void QPOP(Queue* queue);
void PRINT(Queue* queue);
void SaveQueue(Queue* queue, ostream& out);
void LoadQueue(Queue* queue, istream& in);