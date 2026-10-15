#include "../headers/dlist.h"

void InitDlist(Dlist* dlist) {
    dlist->head = nullptr;
}

void CleanDlist(Dlist* dlist) {
    DNode* cur = dlist->head;
    while (cur != nullptr) {
        DNode* next = cur->next;
        delete cur;
        cur = next;
    }
    dlist->head = nullptr;
}

void LPUSH(Dlist* dlist, int data) {
    DNode* new_node = new DNode{data, nullptr, dlist->head};
    if (dlist->head != nullptr) {
        dlist->head->prev = new_node;
    }
    dlist->head = new_node;
}

void LPUSH_End(Dlist* dlist, int data) {
    DNode* new_node = new DNode{data, nullptr, nullptr};
    if (dlist->head == nullptr) {
        dlist->head = new_node;
        return;
    }
    DNode* cur = dlist->head;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = new_node;
    new_node->prev = cur;
}

void LPUSH_After(Dlist* dlist, DNode* node, int data) {
    if (node == nullptr) return;
    DNode* new_node = new DNode{data, node, node->next};
    if (node->next != nullptr) {
        node->next->prev = new_node;
    }
    node->next = new_node;
}

void LPUSH_Before(Dlist* dlist, DNode* node, int data) {
    if (node == nullptr || dlist->head == nullptr) return;
    if (dlist->head == node) {
        LPUSH(dlist, data);
        return;
    }
    DNode* new_node = new DNode{data, node->prev, node};
    node->prev->next = new_node;
    node->prev = new_node;
}

void LDEL_Head(Dlist* dlist) {
    if (dlist->head == nullptr) return;
    DNode* del_node = dlist->head;
    dlist->head = del_node->next;
    if (dlist->head != nullptr) {
        dlist->head->prev = nullptr;
    }
    delete del_node;
}

void LDEL_End(Dlist* dlist) {
    if (dlist->head == nullptr) return;
    if (dlist->head->next == nullptr) {
        delete dlist->head;
        dlist->head = nullptr;
        return;
    }
    DNode* cur = dlist->head;
    while (cur->next != nullptr) cur = cur->next;
    cur->prev->next = nullptr;
    delete cur;
}

void LDEL_After(Dlist* dlist, DNode* prev_node) {
    if (prev_node == nullptr || prev_node->next == nullptr) return;
    DNode* del_node = prev_node->next;
    prev_node->next = del_node->next;
    if (del_node->next != nullptr) {
        del_node->next->prev = prev_node;
    }
    delete del_node;
}

void LDEL_Before(Dlist* dlist, DNode* next_node) {
    if (next_node == nullptr || dlist->head == nullptr || dlist->head == next_node) return;
    if (dlist->head->next == next_node) {
        LDEL_Head(dlist);
        return;
    }
    DNode* del_node = next_node->prev;
    del_node->prev->next = next_node;
    next_node->prev = del_node->prev;
    delete del_node;
}

DNode* LGET(Dlist* dlist, int find_data) {
    DNode* cur = dlist->head;
    while (cur != nullptr) {
        if (cur->key == find_data) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

DNode* LGET_Reverse(Dlist* dlist, int find_data) {
    if (dlist->head == nullptr) {
        cout << "Список пуст!" << endl;
        return nullptr;
    }
    DNode* cur = dlist->head;
    while (cur->next != nullptr) cur = cur->next;
    while (cur != nullptr) {
        if (cur->key == find_data) {
            return cur;
        }
        cur = cur->prev;
    }
    return nullptr;
}

void LDEL(Dlist* dlist, int find_data) {
    if (dlist->head == nullptr) {
        return;
    }
    if (dlist->head->key == find_data) {
        LDEL_Head(dlist);
        return;
    }
    DNode* cur = dlist->head;
    while (cur->next != nullptr) {
        if (cur->next->key == find_data) {
            LDEL_After(dlist, cur);
            return;
        }
        cur = cur->next;
    }
    return;
}

void PRINT(Dlist* dlist) {
    DNode* cur = dlist->head;
    while (cur != nullptr) {
        cout << cur->key << " ";
        cur = cur->next;
    }
    cout << endl;
}

void PRINT_Reverse(Dlist* dlist) {
    if (dlist->head == nullptr) return;
    DNode* cur = dlist->head;
    while (cur->next != nullptr) cur = cur->next;
    while (cur != nullptr) {
        cout << cur->key << " ";
        cur = cur->prev;
    }
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
    for (int i = 0; i < count; i++) {
        int v; in >> v;
        LPUSH_End(dlist, v);
    }
}