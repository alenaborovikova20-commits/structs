#pragma once
#include <iostream>
using namespace std;

struct Array {
    int* data;
    int size;
};


void InitArray(Array* arr);
void CleanArray(Array* arr);
void MPUSH(Array* arr, int value);
void MPUSH_Index(Array* arr, int index, int value);
int MGET(Array* arr, int index);
void MDEL(Array* arr, int index);
void MSET(Array* arr, int index, int value);
int MLEN(Array* arr);
void PRINT(Array* arr) ;
void SaveArray(Array* arr, ostream& out) ;
void LoadArray(Array* arr, istream& in);
