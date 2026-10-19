#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Array {
    string* data;
    int size;
};

void InitArray(Array* arr);
void CleanArray(Array* arr);
void MPUSH(Array* arr, const string& value);
void MPUSH_Index(Array* arr, int index, const string& value);
string MGET(Array* arr, int index);
void MDEL(Array* arr, int index);
void MSET(Array* arr, int index, const string& value);
int MLEN(Array* arr);
void PRINT(Array* arr);
void SaveArray(Array* arr, ostream& out);
void LoadArray(Array* arr, istream& in);