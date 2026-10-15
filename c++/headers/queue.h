#pragma once
#include <iostream>
using namespace std;

struct QNode {
    int data;
    QNode* next;
};

struct Queue {
    QNode* head;
    QNode* tail;
};

void InitQueue(Queue* queue);
void CleanQueue(Queue* queue);
void QPUSH(Queue* queue, int data);
void QPOP(Queue* queue);
void PRINT(Queue* queue);
void SaveQueue(Queue* queue, ostream& out);
void LoadQueue(Queue* queue, istream& in);