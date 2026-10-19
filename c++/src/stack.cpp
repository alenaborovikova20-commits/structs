#include "../headers/stack.h"

void InitStack(Stack* stack) {
    stack->head = nullptr;
}

void CleanStack(Stack* stack) {
    while (stack->head) SPOP(stack);
}

void SPUSH(const string& data, Stack* s) {
    if (!s) return;
    SNode* new_node = new SNode{data, s->head};
    s->head = new_node;
}

void SPOP(Stack* s) {
    if (!s || !s->head) return;
    SNode* del = s->head;
    s->head = del->ptr;
    delete del;
}

void PRINT(Stack* s) {
    if (!s) return;
    for (SNode* c = s->head; c; c = c->ptr) {
        cout << c->field << endl;
    }
}

void SaveStack(Stack* s, ostream& os) {
    int count = 0;
    for (SNode* c = s->head; c; c = c->ptr) count++;
    os << count << "\n";
    for (SNode* c = s->head; c; c = c->ptr) os << c->field << " ";
    os << "\n";
}

void LoadStack(Stack* s, istream& is) {
    CleanStack(s);
    int count;
    is >> count;
    for (int i = 0; i < count; ++i) {
        string v;
        is >> v;
        SPUSH(v, s);
    }
}