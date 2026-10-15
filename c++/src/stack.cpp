#include "../headers/stack.h"

void InitStack(Stack* stack) {
    stack->head = nullptr;
}

void SPUSH(int data, Stack* s) {
    if (s == nullptr) return;
    SNode* new_node = new SNode{data, nullptr};
    new_node->ptr = s->head;
    s->head = new_node;
}

void SPOP(Stack* s) {
    if (s == nullptr || s->head == nullptr) return;
    SNode* node_to_delete = s->head;
    s->head = s->head->ptr;
    delete node_to_delete;
}

void PRINT(Stack* s) {
    if (s == nullptr || s->head == nullptr) return;
    SNode* cur = s->head;
    while (cur != nullptr) {
        cout << cur->field << endl;
        cur = cur->ptr;
    }
}

void CleanStack(Stack* stack) {
    while (stack->head) {SPOP(stack);}
}

void SaveStack(Stack* s, ostream& out) {
    int count = 0;
    for (SNode* c = s->head; c; c = c->ptr) count++;
    out << count << "\n";
    for (SNode* c = s->head; c; c = c->ptr) out << c->field << " ";
    out << "\n";
}

void LoadStack(Stack* s, istream& in) {
    CleanStack(s);
    int count; in >> count;
    for (int i = 0; i < count; i++) {
        int v; in >> v;
        SPUSH(v, s);
    }
}