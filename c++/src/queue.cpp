#include "../headers/queue.h"

void InitQueue(Queue* queue) {
    queue->head = nullptr;
    queue->tail = nullptr;
}

void QPUSH(Queue* queue, int data) {
    QNode* new_node = new QNode{data, nullptr};
    if (queue->tail != nullptr) {
        queue->tail->next = new_node;
    }
    queue->tail = new_node;
    if (queue->head == nullptr) {
        queue->head = new_node;
    }
}

void QPOP(Queue* queue) {
    if (queue->head == nullptr) {
        return;
    }
    QNode* del_node = queue->head;
    queue->head = del_node->next;
    delete del_node;
    if (queue->head == nullptr) {
        queue->tail = nullptr;
    }
}

void PRINT(Queue* queue) {
    if (queue->head == nullptr) {
        return;
    }
    QNode* cur_node = queue->head;
    while (cur_node != nullptr) {
        cout << cur_node->data << " ";
        cur_node = cur_node->next;
    }
    cout << endl;
}

void CleanQueue(Queue* queue) {
    while (queue->head != nullptr) QPOP(queue);
}

void SaveQueue(Queue* queue, ostream& out) {
    int count = 0;
    for (QNode* c = queue->head; c; c = c->next) count++;
    out << count << "\n";
    for (QNode* c = queue->head; c; c = c->next) out << c->data << " ";
    out << "\n";
}

void LoadQueue(Queue* queue, istream& in) {
    CleanQueue(queue);
    int count; in >> count;
    for (int i = 0; i < count; i++) {
        int v; in >> v;
        QPUSH(queue, v);
    }
}