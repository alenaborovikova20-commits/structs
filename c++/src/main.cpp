#include <iostream>
#include <string>
using namespace std;

#include "../headers/dbms.h"

int main(int argc, char** argv) {
    string file, query;
    bool hasFile = false, hasQuery = false;

    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if      (a == "--file"  && i + 1 < argc) { file = argv[++i]; hasFile = true; }
        else if (a == "--query" && i + 1 < argc) { query = argv[++i]; hasQuery = true; }
        else if (a == "-h" || a == "--help") {
            cout << "Usage: " << argv[0] << " --file <path> --query '<cmd>'\n";
            return 0;
        } else {
            cerr << "Unknown argument: " << a << "\n";
            return 2;
        }
    }
    if (!hasFile) { cerr << "Need --file\n"; return 2; }

    Database db;                      
    DB_load(db, file);                

    if (hasQuery) {
        DB_exec(db, query);
        DB_save(db, file);
    } else {
        string line;
        while (getline(cin, line)) {
            if (line.empty()) continue;
            DB_exec(db, line);
        }
        DB_save(db, file);
    }

    DB_destroy(db);
    return 0;
}