#include "../headers/dlist.h"

void InitDlist(Dlist* dlist) { dlist->head = nullptr; }

void CleanDlist(Dlist* dlist) {
    DNode* cur = dlist->head;
    while (cur) { DNode* n = cur->next; delete cur; cur = n; }
    dlist->head = nullptr;
}

void LPUSH(Dlist* dlist, const string& data) {
    DNode* n = new DNode{data, nullptr, dlist->head};
    if (dlist->head) dlist->head->prev = n;
    dlist->head = n;
}

void LPUSH_End(Dlist* dlist, const string& data) {
    DNode* n = new DNode{data, nullptr, nullptr};
    if (!dlist->head) { dlist->head = n; return; }
    DNode* cur = dlist->head;
    while (cur->next) cur = cur->next;
    cur->next = n;
    n->prev = cur;
}

void LPUSH_After(Dlist* dlist, DNode* node, const string& data) {
    if (!node) return;
    DNode* n = new DNode{data, node, node->next};
    if (node->next) node->next->prev = n;
    node->next = n;
}

void LPUSH_Before(Dlist* dlist, DNode* node, const string& data) {
    if (!node || !dlist->head) return;
    if (dlist->head == node) {
        LPUSH(dlist, data);
         return; }
    DNode* n = new DNode{data, node->prev, node};
    node->prev->next = n;
    node->prev = n;
}

void LDEL_Head(Dlist* dlist) {
    if (!dlist->head) return;
    DNode* del = dlist->head;
    dlist->head = del->next;
    if (dlist->head) dlist->head->prev = nullptr;
    delete del;
}

void LDEL_End(Dlist* dlist) {
    if (!dlist->head) return;
    if (!dlist->head->next) { delete dlist->head; dlist->head = nullptr; return; }
    DNode* cur = dlist->head;
    while (cur->next) cur = cur->next;
    cur->prev->next = nullptr;
    delete cur;
}

void LDEL_After(Dlist* dlist, DNode* prev_node) {
    if (!prev_node || !prev_node->next) return;
    DNode* del = prev_node->next;
    prev_node->next = del->next;
    if (del->next) del->next->prev = prev_node;
    delete del;
}

void LDEL_Before(Dlist* dlist, DNode* next_node) {
    if (!next_node || !dlist->head || dlist->head == next_node) return;
    if (dlist->head->next == next_node) {
        LDEL_Head(dlist); 
        return; }
    DNode* del = next_node->prev;
    del->prev->next = next_node;
    next_node->prev = del->prev;
    delete del;
}

DNode* LGET(Dlist* dlist, const string& find_data) {
    DNode* cur = dlist->head;
    while (cur) { if (cur->key == find_data) return cur; cur = cur->next; }
    return nullptr;
}

DNode* LGET_Reverse(Dlist* dlist, const string& find_data) {
    if (!dlist->head) return nullptr;
    DNode* cur = dlist->head;
    while (cur->next) cur = cur->next;
    while (cur) { if (cur->key == find_data) return cur; cur = cur->prev; }
    return nullptr;
}

void LDEL(Dlist* dlist, const string& find_data) {
    if (!dlist->head) return;
    if (dlist->head->key == find_data) { LDEL_Head(dlist); return; }
    DNode* cur = dlist->head;
    while (cur->next) {
        if (cur->next->key == find_data) { LDEL_After(dlist, cur); return; }
        cur = cur->next;
    }
}

void PRINT(Dlist* dlist) {
    for (DNode* c = dlist->head; c; c = c->next) cout << c->key << " ";
    cout << endl;
}

void PRINT_Reverse(Dlist* dlist) {
    if (!dlist->head) return;
    DNode* cur = dlist->head;
    while (cur->next) cur = cur->next;
    while (cur) { cout << cur->key << " "; cur = cur->prev; }
    cout << endl;
}

void SaveDlist(Dlist* dlist, ostream& out) {
    int count = 0;
    for (DNode* c = dlist->head; c; c = c->next) count++;
    out << count << "\n";
    for (DNode* c = dlist->head; c; c = c->next) out << c->key << " ";
    out << "\n";
}

void LoadDlist(Dlist* dlist, istream& in) {
    CleanDlist(dlist);
    int count; in >> count;
    for (int i = 0; i < count; ++i) { string v; in >> v; LPUSH_End(dlist, v); }
}