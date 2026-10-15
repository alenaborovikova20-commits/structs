#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "../headers/array.h"
#include "../headers/flist.h"
#include "../headers/dlist.h"
#include "../headers/queue.h"
#include "../headers/stack.h"
#include "../headers/avl.h"

int main() {
    Array  marr;  InitArray(&marr);
    Flist  flist; InitFlist(&flist);
    Dlist  dlist; InitDlist(&dlist);
    Queue  queue; InitQueue(&queue);
    Stack  stack; InitStack(&stack);
    ANode* tree = nullptr;

    ifstream fin("input.txt");
    if (!fin.is_open()) { cout << "Cannot open input.txt" << endl; return 1; }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string cmd; iss >> cmd;

        if (cmd == "PRINT") {
            string type; iss >> type;
            if      (type == "M") PRINT(&marr);
            else if (type == "F") PRINT(&flist);
            else if (type == "L") PRINT(&dlist);
            else if (type == "Q") PRINT(&queue);
            else if (type == "S") PRINT(&stack);
            else if (type == "T") PRINT(tree);
            continue;
        }

        if (cmd == "MPUSH") {
            int a, b;
            string rest; getline(iss, rest);
            istringstream rs(rest);
            if (rs >> a >> b) MPUSH_Index(&marr, a, b);
            else               MPUSH(&marr, a);
        }
        else if (cmd == "MDEL")  { int i; iss >> i; MDEL(&marr, i); }
        else if (cmd == "MGET")  { int i; iss >> i; cout << MGET(&marr, i) << endl; }
        else if (cmd == "MSET")  { int i, v; iss >> i >> v; MSET(&marr, i, v); }
        else if (cmd == "MLEN")  { cout << MLEN(&marr) << endl; }

        else if (cmd == "FPUSH") { int v; iss >> v; FPUSH(&flist, v); }
        else if (cmd == "FDEL")  { int v; iss >> v; FDEL(&flist, v); }
        else if (cmd == "FGET")  { int v; iss >> v; FGET(&flist, v); }

        else if (cmd == "LPUSH") { int v; iss >> v; LPUSH(&dlist, v); }
        else if (cmd == "LDEL")  { int v; iss >> v; LDEL(&dlist, v); }
        else if (cmd == "LGET")  { int v; iss >> v; LGET(&dlist, v); }

        else if (cmd == "QPUSH") { int v; iss >> v; QPUSH(&queue, v); }
        else if (cmd == "QPOP")  { QPOP(&queue); }

        else if (cmd == "SPUSH") { int v; iss >> v; SPUSH(v, &stack); }
        else if (cmd == "SPOP")  { SPOP(&stack); }

        else if (cmd == "TINSERT") { int v; iss >> v; TINSERT(tree, v); }
        else if (cmd == "TDEL")    { int v; iss >> v; TDEL(tree, v); }
        else if (cmd == "TGET")    { int v; iss >> v; TGET(tree, v); }
    }
    fin.close();

    ofstream fout("output.txt");
    SaveArray(&marr, fout);
    SaveFlist(&flist, fout);
    SaveDlist(&dlist, fout);
    SaveQueue(&queue, fout);
    SaveStack(&stack, fout);
    SaveTree(tree, fout);
    fout.close();

    CleanArray(&marr);
    CleanFlist(&flist);
    CleanDlist(&dlist);
    CleanQueue(&queue);
    CleanStack(&stack);
    CleanTree(tree);

    return 0;
}