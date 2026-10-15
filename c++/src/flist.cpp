#include "../headers/flist.h"

void InitFlist(Flist* flist) {
    flist->head = nullptr;
}

void CleanFlist(Flist* flist) {
    Node* cur = flist->head;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    flist->head = nullptr;
}

void FPUSH(Flist* flist, int data) {
    Node* new_node = new Node{data, flist->head};
    flist->head = new_node;
}

void FPUSH_End(Flist* flist, int data) {
    Node* new_node = new Node{data, nullptr};
    if (flist->head == nullptr) {
        flist->head = new_node;
    } else {
        Node* cur = flist->head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = new_node;
    }
}

void FPUSH_After(Flist* flist, Node* node, int data) {
    if (node == nullptr) return;
    Node* new_node = new Node{data, node->next};
    node->next = new_node;
}

void FPUSH_Before(Flist* flist, Node* node, int data) {
    if (node == nullptr || flist->head == nullptr) return;
    if (flist->head == node) {
        FPUSH(flist, data);
        return;
    }
    Node* cur = flist->head;
    while (cur->next != nullptr && cur->next != node) {cur = cur->next;}
    if (cur->next == nullptr) return;
    Node* new_node = new Node{data, cur->next};
    cur->next = new_node;
}

void FDEL_After(Flist* flist, Node* prev_node) {
    if (prev_node == nullptr || prev_node->next == nullptr) return;
    Node* del_node = prev_node->next;
    prev_node->next = del_node->next;
    delete del_node;
}

void FDEL_Head(Flist* flist) {
    if (flist->head == nullptr) return;
    Node* del_node = flist->head;
    flist->head = del_node->next;
    delete del_node;
}

void FDEL_End(Flist* flist) {
    if (flist->head == nullptr) return;
    if (flist->head->next == nullptr) {
        delete flist->head;
        flist->head = nullptr;
        return;
    }
    Node* cur = flist->head;
    while (cur->next->next != nullptr) {
        cur = cur->next;
    }
    Node* del_node = cur->next;
    cur->next = nullptr;
    delete del_node;
}

void FDEL_Before(Flist* flist, Node* next_node) {
    if (next_node == nullptr || flist->head == nullptr || flist->head == next_node) return;
    if (flist->head->next == next_node) {
        FDEL_Head(flist);
        return;
    }
    Node* cur = flist->head;
    while (cur->next != nullptr && cur->next->next != next_node) {
        cur = cur->next;
    }
    if (cur->next == nullptr) return;
    Node* del_node = cur->next;
    cur->next = del_node->next;
    delete del_node;
}

Node* FGET(Flist* flist, int find_data) {
    Node* cur = flist->head;
    while (cur != nullptr) {
        if (cur->key == find_data) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}


void FDEL(Flist* flist, int find_data) {
    if (flist->head == nullptr) {
        return;
    }
    if (flist->head->key == find_data) {
        FDEL_Head(flist);
        return;
    }
    Node* cur = flist->head;
    while (cur->next != nullptr) {
        if (cur->next->key == find_data) {
            FDEL_After(flist, cur);
            return;
        }
        cur = cur->next;
    }
    return;
}

void PRINT(Flist* flist) {
    Node* cur = flist->head;
    while (cur != nullptr) {
        cout << cur->key << " ";
        cur = cur->next;
    }
    cout << endl;
}

void SaveFlist(Flist* flist, ostream& out) {
    int count = 0;
    for (Node* c = flist->head; c; c = c->next) count++;
    out << count << "\n";
    for (Node* c = flist->head; c; c = c->next) out << c->key << " ";
    out << "\n";
}

void LoadFlist(Flist* flist, istream& in) {
    CleanFlist(flist);
    int count; in >> count;
    for (int i = 0; i < count; i++) {
        int v; in >> v;
        FPUSH_End(flist, v);
    }
}