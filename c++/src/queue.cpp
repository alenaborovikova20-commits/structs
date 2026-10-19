#include "../headers/queue.h"

void InitQueue(Queue* queue) {
    queue->head = queue->tail = nullptr;
}

void QPUSH(Queue* queue, const string& data) {
    QNode* n = new QNode{data, nullptr};
    if (queue->tail) queue->tail->next = n;
    queue->tail = n;
    if (!queue->head) queue->head = n;
}

void QPOP(Queue* queue) {
    if (!queue->head) return;
    QNode* del = queue->head;
    queue->head = del->next;
    delete del;
    if (!queue->head) queue->tail = nullptr;
}

void PRINT(Queue* queue) {
    for (QNode* c = queue->head; c; c = c->next) cout << c->data << " ";
    cout << endl;
}

void CleanQueue(Queue* queue) { while (queue->head) QPOP(queue); }

void SaveQueue(Queue* queue, ostream& os) {
    int count = 0;
    for (QNode* c = queue->head; c; c = c->next) count++;
    os << count << "\n";
    for (QNode* c = queue->head; c; c = c->next) os << c->data << " ";
    os << "\n";
}

void LoadQueue(Queue* queue, istream& is) {
    CleanQueue(queue);
    int count; is >> count;
    for (int i = 0; i < count; ++i) { 
        string v; 
        is >> v; 
        QPUSH(queue, v); }
}