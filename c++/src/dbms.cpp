#include "../headers/dbms.h"
#include <vector>


static Command parseCommand(const string& s) {
    if (s == "MPUSH")       return Command::MPUSH;
    if (s == "MPUSH_INDEX") return Command::MPUSH_INDEX;
    if (s == "MGET")        return Command::MGET;
    if (s == "MSET")        return Command::MSET;
    if (s == "MDEL")        return Command::MDEL;
    if (s == "MLEN")        return Command::MLEN;
    if (s == "MPRINT")      return Command::MPRINT;

    if (s == "FPUSH")       return Command::FPUSH;
    if (s == "FDEL")        return Command::FDEL;
    if (s == "FGET")        return Command::FGET;
    if (s == "FPRINT")      return Command::FPRINT;

    if (s == "LPUSH")       return Command::LPUSH;
    if (s == "LDEL")        return Command::LDEL;
    if (s == "LGET")        return Command::LGET;
    if (s == "LPRINT")      return Command::LPRINT;

    if (s == "QPUSH")       return Command::QPUSH;
    if (s == "QPOP")        return Command::QPOP;
    if (s == "QPRINT")      return Command::QPRINT;

    if (s == "SPUSH")       return Command::SPUSH;
    if (s == "SPOP")        return Command::SPOP;
    if (s == "SPRINT")      return Command::SPRINT;

    if (s == "TINSERT")     return Command::TINSERT;
    if (s == "TDEL")        return Command::TDEL;
    if (s == "TGET")        return Command::TGET;
    if (s == "ISMEMBER")    return Command::ISMEMBER;
    if (s == "TPRINT")      return Command::TPRINT;

    return Command::Unknown;
}

static Kind parseKind(char c) {
    if (c == 'A') return Kind::ARR;
    if (c == 'F') return Kind::FL;
    if (c == 'L') return Kind::DL;
    if (c == 'Q') return Kind::QU;
    if (c == 'S') return Kind::ST;
    if (c == 'T') return Kind::TR;
    return Kind::NONE;
}

static char kindToChar(Kind k) {
    if (k == Kind::ARR) return 'A';
    if (k == Kind::FL)  return 'F';
    if (k == Kind::DL)  return 'L';
    if (k == Kind::QU)  return 'Q';
    if (k == Kind::ST)  return 'S';
    if (k == Kind::TR)  return 'T';
    return '?';
}


static void destroyEntry(Entry& e) {
    switch (e.kind) {
        case Kind::ARR: CleanArray(&e.arr); break;
        case Kind::FL:  CleanFlist(&e.fl);  break;
        case Kind::DL:  CleanDlist(&e.dl);  break;
        case Kind::QU:  CleanQueue(&e.qu);  break;
        case Kind::ST:  CleanStack(&e.st);  break;
        case Kind::TR:  CleanTree(e.tr);    break;
        default: break;
    }
    e.kind = Kind::NONE;
}

void DB_destroy(Database& db) {
    for (auto& kv : db.db) destroyEntry(kv.second);
    db.db.clear();
}


void DB_exec(Database& db, const string& query) {
    istringstream iss(query);
    string cmdStr;
    iss >> cmdStr;
    if (cmdStr.empty()) return;

    Command cmd = parseCommand(cmdStr);

    if (cmd == Command::MPUSH||cmd == Command::MPUSH_INDEX||cmd == Command::MGET|| cmd == Command::MSET||cmd == Command::MDEL|| cmd == Command::MLEN||cmd == Command::MPRINT)
    {
        string name;
        iss >> name;
        Entry& e = db.db[name];
        if (e.kind == Kind::NONE) {
            InitArray(&e.arr);
            e.kind = Kind::ARR;}
        if (e.kind != Kind::ARR) { cout << "ERR: not array\n"; return; }
        if (cmd == Command::MPUSH) {
            string v;
            iss >> v;
            MPUSH(&e.arr, v);}
        else if (cmd == Command::MPUSH_INDEX) {
            int i;
            string v;
            iss >> i >> v;
            MPUSH_Index(&e.arr, i, v);
        }
        else if (cmd == Command::MGET) {
            int i;
            iss >> i;
            cout << MGET(&e.arr, i) << "\n";
        }
        else if (cmd == Command::MSET) {
            int i;
            string v;
            iss >> i >> v;
            MSET(&e.arr, i, v);
        }
        else if (cmd == Command::MDEL) {
            int i;
            iss >> i;
            MDEL(&e.arr, i);
        }
        else if (cmd == Command::MLEN) {
            cout << MLEN(&e.arr) << "\n";
        }
        else if (cmd == Command::MPRINT) {
            PRINT(&e.arr);
        }
        return;
    }

    if (cmd == Command::FPUSH||cmd == Command::FDEL||cmd == Command::FGET||cmd == Command::FPRINT)
    {
        string name; iss >> name;
        Entry& e = db.db[name];
        if (e.kind == Kind::NONE) { InitFlist(&e.fl); e.kind = Kind::FL; }
        if (e.kind != Kind::FL) { cout << "ERR: not flist\n"; return; }
        if (cmd == Command::FPUSH) {
            string v; 
            iss >> v;
            FPUSH(&e.fl, v);
        }
        else if (cmd == Command::FDEL) {
            string v;
            iss >> v; 
            FDEL(&e.fl, v);
        }
        else if (cmd == Command::FGET) {
            string v; 
            iss >> v;
            cout << (FGET(&e.fl, v) ? "TRUE" : "FALSE") << "\n";
        }
        else if (cmd == Command::FPRINT) {
            PRINT(&e.fl);
        }
        return;
    }

    if (cmd == Command::LPUSH||cmd == Command::LDEL||cmd == Command::LGET||cmd == Command::LPRINT)
    {
        string name; iss >> name;
        Entry& e = db.db[name];
        if (e.kind == Kind::NONE) {
            InitDlist(&e.dl);
            e.kind = Kind::DL; }
        if (e.kind != Kind::DL) { cout << "ERR: not dlist\n"; return; }

        if (cmd == Command::LPUSH) {
            string v;
            iss >> v;
            LPUSH(&e.dl, v);
        }
        else if (cmd == Command::LDEL) {
            string v;
            iss >> v;
            LDEL(&e.dl, v);
        }
        else if (cmd == Command::LGET) {
            string v; iss >> v;
            cout << (LGET(&e.dl, v) ? "TRUE" : "FALSE") << "\n";
        }
        else if (cmd == Command::LPRINT) {
            PRINT(&e.dl);
        }
        return;
    }

    if (cmd == Command::QPUSH || cmd == Command::QPOP || cmd == Command::QPRINT) {
        string name; iss >> name;
        Entry& e = db.db[name];
        if (e.kind == Kind::NONE) { InitQueue(&e.qu);
            e.kind = Kind::QU; }
        if (e.kind != Kind::QU) { cout << "ERR: not queue\n"; return; }

        if (cmd == Command::QPUSH) {
            string v; 
            iss >> v; 
            QPUSH(&e.qu, v);
        }
        else if (cmd == Command::QPOP) {
            if (e.qu.head) { cout << e.qu.head->data << "\n"; QPOP(&e.qu); }
        }
        else if (cmd == Command::QPRINT) {
            PRINT(&e.qu);
        }
        return;
    }

    if (cmd == Command::SPUSH || cmd == Command::SPOP || cmd == Command::SPRINT) {
        string name; iss >> name;
        Entry& e = db.db[name];
        if (e.kind == Kind::NONE) { 
            InitStack(&e.st); 
            e.kind = Kind::ST; }
        if (e.kind != Kind::ST) { cout << "ERR: not stack\n"; return; }

        if (cmd == Command::SPUSH) {
            string v; 
            iss >> v;
            SPUSH(v, &e.st);
            cout << v << "\n";             
        }
        else if (cmd == Command::SPOP) {
            if (e.st.head) { cout << e.st.head->field << "\n"; SPOP(&e.st); }
        }
        else if (cmd == Command::SPRINT) {
            PRINT(&e.st);
        }
        return;
    }


    if (cmd == Command::TINSERT||cmd == Command::TDEL||cmd == Command::TGET||cmd == Command::ISMEMBER||cmd == Command::TPRINT)
    {
        string name; iss >> name;
        Entry& e = db.db[name];
        if (e.kind == Kind::NONE) e.kind = Kind::TR;
        if (e.kind != Kind::TR) { cout << "ERR: not tree\n"; return; }

        if (cmd == Command::TINSERT) {
            int v; 
            iss >> v; 
            TINSERT(e.tr, v);
        }
        else if (cmd == Command::TDEL) {
            int v; 
            iss >> v; 
            TDEL(e.tr, v);
        }
        else if (cmd == Command::TGET || cmd == Command::ISMEMBER) {
            int v; 
            iss >> v;
            cout << (TGET(e.tr, v) ? "TRUE" : "FALSE") << "\n";
        }
        else if (cmd == Command::TPRINT) {
            PRINT(e.tr);
        }
        return;
    }

    cout << "ERR: unknown command '" << cmdStr << "'\n";
}





static void saveEntry(ostream& out, const string& name, const Entry& e) {
    char t = kindToChar(e.kind);

    if (e.kind == Kind::ARR) {
        out << t << " " << name << " " << e.arr.size;
        for (int i = 0; i < e.arr.size; ++i) out << " " << e.arr.data[i];
        out << "\n";
        return;
    }
    if (e.kind == Kind::FL) {
        int n = 0; for (Node* c = e.fl.head; c; c = c->next) n++;
        out << t << " " << name << " " << n;
        for (Node* c = e.fl.head; c; c = c->next) out << " " << c->key;
        out << "\n";
        return;
    }
    if (e.kind == Kind::DL) {
        int n = 0; for (DNode* c = e.dl.head; c; c = c->next) n++;
        out << t << " " << name << " " << n;
        for (DNode* c = e.dl.head; c; c = c->next) out << " " << c->key;
        out << "\n";
        return;
    }
    if (e.kind == Kind::QU) {
        int n = 0; for (QNode* c = e.qu.head; c; c = c->next) n++;
        out << t << " " << name << " " << n;
        for (QNode* c = e.qu.head; c; c = c->next) out << " " << c->data;
        out << "\n";
        return;
    }
    if (e.kind == Kind::ST) {
        int n = 0; for (SNode* c = e.st.head; c; c = c->ptr) n++;
        out << t << " " << name << " " << n;
        for (SNode* c = e.st.head; c; c = c->ptr) out << " " << c->field;
        out << "\n";
        return;
    }
    if (e.kind == Kind::TR) {
    out << t << " " << name << " ";    
    SaveTree(e.tr, out);              
    return;
}
}

bool DB_save(const Database& db, const string& path) {
    ofstream out(path);
    if (!out) return false;
    for (auto& kv : db.db) saveEntry(out, kv.first, kv.second);
    return true;
}


static void LoadFlistReversed(istream& in, Flist* f, int n) {
    if (n == 0) return;
    string v; in >> v;
    LoadFlistReversed(in, f, n - 1);
    FPUSH(f, v);
}

static void LoadDlistReversed(istream& in, Dlist* d, int n) {
    if (n == 0) return;
    string v; in >> v;
    LoadDlistReversed(in, d, n - 1);
    LPUSH(d, v);
}

static void LoadStackReversed(istream& in, Stack* s, int n) {
    if (n == 0) return;
    string v; in >> v;
    LoadStackReversed(in, s, n - 1);
    SPUSH(v, s);
}

static bool loadEntryData(istream& in, Entry& e) {
    int n; in >> n;
    if (!in) return false;

    if (e.kind == Kind::ARR) {
        InitArray(&e.arr);
        for (int i = 0; i < n; ++i) { string v; in >> v; MPUSH(&e.arr, v); }
        return true;
    }
    if (e.kind == Kind::FL) {
        InitFlist(&e.fl);
        LoadFlistReversed(in, &e.fl, n);
        return true;
    }
    if (e.kind == Kind::DL) {
        InitDlist(&e.dl);
        LoadDlistReversed(in, &e.dl, n);
        return true;
    }
    if (e.kind == Kind::QU) {
        InitQueue(&e.qu);
        for (int i = 0; i < n; ++i) { string v; in >> v; QPUSH(&e.qu, v); }
        return true;
    }
    if (e.kind == Kind::ST) {
        InitStack(&e.st);
        LoadStackReversed(in, &e.st, n);
        return true;
    }
    if (e.kind == Kind::TR) {
        e.tr = nullptr;
        for (int i = 0; i < n; ++i) { int k; in >> k; TINSERT(e.tr, k); }
        return true;
    }
    return false;
}


bool DB_load(Database& db, const string& path) {
    ifstream in(path);
    if (!in) return false;

    DB_destroy(db);

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        char typeChar;
        iss >> typeChar;
        string name; 
        iss >> name;

        Entry& e = db.db[name];
        e.kind = parseKind(typeChar);
        if (e.kind == Kind::NONE) continue;

        if (!loadEntryData(iss, e)) {
            cout << "ERR: failed to load '" << name << "'\n";
        }
    }
    return true;
}