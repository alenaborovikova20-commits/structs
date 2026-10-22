#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

#include "array.h"
#include "flist.h"
#include "dlist.h"
#include "queue.h"
#include "stack.h"
#include "avl.h"

enum class Command {
    Unknown = 0,
    
    MPUSH, MPUSH_INDEX, MGET, MSET, MDEL, MLEN, MPRINT,
    
    FPUSH, FPUSH_END, FPUSH_AFTER, FPUSH_BEFORE,
    FDEL, FDEL_HEAD, FDEL_END, FDEL_AFTER, FDEL_BEFORE,
    FGET, FPRINT,
    
    LPUSH, LPUSH_END, LPUSH_AFTER, LPUSH_BEFORE,
    LDEL, LDEL_HEAD, LDEL_END, LDEL_AFTER, LDEL_BEFORE,
    LGET, LGET_REVERSE, LPRINT, LPRINT_REVERSE,
    
    QPUSH, QPOP, QPRINT,
    
    SPUSH, SPOP, SPRINT,
    
    TINSERT, TDEL, TGET, ISMEMBER, TPRINT
};

enum class Kind {
    NONE = 0, ARR, FL, DL, QU, ST, TR
};

struct Entry {
    Kind   kind = Kind::NONE;
    Array  arr;
    Flist  fl;
    Dlist  dl;
    Queue  qu;
    Stack  st;
    ANode* tr = nullptr;
};

struct Database { map<string, Entry> db; };

void DB_exec(Database& db, const string& query);
bool DB_load(Database& db, const string& path);
bool DB_save(const Database& db, const string& path);
void DB_destroy(Database& db);