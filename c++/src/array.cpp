#include "../headers/array.h"

void InitArray(Array* arr) {
    arr->data = nullptr;
    arr->size = 0;
}

void CleanArray(Array* arr) {
    delete[] arr->data;
    arr->data = nullptr;
    arr->size = 0;
}

void MPUSH(Array* arr, const string& value) {
    string* new_data = new string[arr->size + 1];
    for (int i = 0; i < arr->size; ++i) new_data[i] = arr->data[i];
    new_data[arr->size] = value;
    delete[] arr->data;
    arr->data = new_data;
    arr->size++;
}

void MPUSH_Index(Array* arr, int index, const string& value) {
    if (index < 0 || index > arr->size) return;
    string* new_data = new string[arr->size + 1];
    for (int i = 0; i < index; ++i) new_data[i] = arr->data[i];
    new_data[index] = value;
    for (int i = index; i < arr->size; ++i) new_data[i + 1] = arr->data[i];
    delete[] arr->data;
    arr->data = new_data;
    arr->size++;
}

string MGET(Array* arr, int index) {
    if (index < 0 || index >= arr->size) return "";
    return arr->data[index];
}

void MDEL(Array* arr, int index) {
    if (index < 0 || index >= arr->size) return;
    string* new_data = new string[arr->size - 1];
    for (int i = 0; i < index; ++i) new_data[i] = arr->data[i];
    for (int i = index + 1; i < arr->size; ++i) new_data[i - 1] = arr->data[i];
    delete[] arr->data;
    arr->data = new_data;
    arr->size--;
}


void MSET(Array* arr, int index, const string& value) {
    if (index < 0 || index >= arr->size) return;
    arr->data[index] = value;
}

int MLEN(Array* arr) {
    return arr->size;
}

void PRINT(Array* arr) {
    for (int i = 0; i < arr->size; ++i) cout << arr->data[i] << " ";
    cout << endl;
}

void SaveArray(Array* arr, ostream& os) {
    os << arr->size << "\n";
    for (int i = 0; i < arr->size; ++i) os << arr->data[i] << " ";
    os << "\n";
}

void LoadArray(Array* arr, istream& is) {
    CleanArray(arr);
    int count; 
    is >> count;
    for (int i = 0; i < count; ++i) {
        string v; 
        is >> v;
        MPUSH(arr, v);
    }
}