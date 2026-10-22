#include "../headers/flist.h"

void InitFlist(Flist* flist) { flist->head = nullptr; }

void CleanFlist(Flist* flist) {
    Node* cur = flist->head;
    while (cur) { Node* n = cur->next; delete cur; cur = n; }
    flist->head = nullptr;
}

void FPUSH(Flist* flist, const string& data) {
    flist->head = new Node{data, flist->head};
}

void FPUSH_End(Flist* flist, const string& data) {
    Node* new_node = new Node{data, nullptr};
    if (!flist->head) { flist->head = new_node; return; }
    Node* cur = flist->head;
    while (cur->next) cur = cur->next;
    cur->next = new_node;
}

void FPUSH_After(Flist* flist, Node* node, const string& data) {
    if (!node) return;
    node->next = new Node{data, node->next};
}

void FPUSH_Before(Flist* flist, Node* node, const string& data) {
    if (!node || !flist->head) return;
    if (flist->head == node) { 
        flist->head = new Node{data, flist->head}; 
        return; 
    }
    Node* cur = flist->head;
    while (cur->next && cur->next != node) { cur = cur->next; }
    if (!cur->next) return;
    cur->next = new Node{data, cur->next};
}

void FDEL_After(Flist* flist, Node* prev_node) {
    if (!prev_node || !prev_node->next) return;
    Node* del = prev_node->next;
    prev_node->next = del->next;
    delete del;
}

void FDEL_Head(Flist* flist) {
    if (!flist->head) return;
    Node* del = flist->head;
    flist->head = del->next;
    delete del;
}

void FDEL_End(Flist* flist) {
    if (!flist->head) return;
    if (!flist->head->next) { delete flist->head; flist->head = nullptr; return; }
    Node* cur = flist->head;
    while (cur->next->next) cur = cur->next;
    delete cur->next;
    cur->next = nullptr;
}

void FDEL_Before(Flist* flist, Node* next_node) {
    if (!next_node || !flist->head || flist->head == next_node) return;
    if (flist->head->next == next_node) { FDEL_Head(flist); return; }
    Node* cur = flist->head;
    while (cur->next && cur->next->next != next_node) cur = cur->next;
    if (!cur->next) return;
    Node* del = cur->next;
    cur->next = del->next;
    delete del;
}

Node* FGET(Flist* flist, const string& find_data) {
    Node* cur = flist->head;
    while (cur) { 
        if (cur->key == find_data) return cur;
        cur = cur->next; 
    }
    return nullptr;
}

void FDEL(Flist* flist, const string& find_data) {
    if (!flist->head) return;
    if (flist->head->key == find_data) { FDEL_Head(flist); return; }
    Node* cur = flist->head;
    while (cur->next) {
        if (cur->next->key == find_data) { FDEL_After(flist, cur); return; }
        cur = cur->next;
    }
}

void PRINT(Flist* flist) {
    for (Node* c = flist->head; c; c = c->next) cout << c->key << " ";
    cout << endl;
}

void SaveFlist(Flist* flist, ostream& os) {
    int count = 0;
    for (Node* c = flist->head; c; c = c->next) count++;
    os << count << "\n";
    for (Node* c = flist->head; c; c = c->next) os << c->key << " ";
    os << "\n";
}

void LoadFlist(Flist* flist, istream& is) {
    CleanFlist(flist);
    int count; is >> count;
    for (int i = 0; i < count; ++i) { string v; is >> v; FPUSH_End(flist, v); }
}