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

void MPUSH(Array* arr, int value) {
    if (arr == nullptr) return;
    int* newData = new int[arr->size + 1];
    for (int i = 0; i < arr->size; i++) {
        newData[i] = arr->data[i];
    }
    newData[arr->size] = value;
    delete[] arr->data;
    arr->data = newData;
    arr->size++;
}

void MPUSH_Index(Array* arr, int index, int value) {
    if (arr == nullptr) return;
    if (index < 0 || index > arr->size) return;
    int* newData = new int[arr->size + 1];
    for (int i = 0; i < index; i++) {
        newData[i] = arr->data[i];
    }
    newData[index] = value;
    for (int i = index; i < arr->size; i++) {
        newData[i + 1] = arr->data[i];
    }
    delete[] arr->data;
    arr->data = newData;
    arr->size++;
}

int MGET(Array* arr, int index) {
    if (arr == nullptr || index < 0 || index >= arr->size) return -1;
    return arr->data[index];
}

void MDEL(Array* arr, int index) {
    if (arr == nullptr) return;
    if (index < 0 || index >= arr->size) return;
    if (arr->size == 1) {
        CleanArray(arr);
        return;
    }
    int* newData = new int[arr->size - 1];
    for (int i = 0; i < index; i++) {
        newData[i] = arr->data[i];
    }
    for (int i = index + 1; i < arr->size; i++) {
        newData[i - 1] = arr->data[i];
    }
    delete[] arr->data;
    arr->data = newData;
    arr->size--;
}

void MSET(Array* arr, int index, int value) {
    if (arr == nullptr) return;
    if (index < 0 || index >= arr->size) return;
    arr->data[index] = value;
}

int MLEN(Array* arr) {
    if (arr == nullptr) return 0;
    return arr->size;
}

void PRINT(Array* arr) {
    if (arr == nullptr || arr->size == 0) {
        cout << "Array is empty" << endl;
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        cout << arr->data[i] << " ";
    }
    cout << endl;
}

void SaveArray(Array* arr, ostream& out) {
    out << arr->size << "\n";
    for (int i = 0; i < arr->size; i++) out << arr->data[i] << " ";
    out << "\n";
}

void LoadArray(Array* arr, istream& in) {
    CleanArray(arr);
    in >> arr->size;
    if (arr->size <= 0) { arr->size = 0; return; }
    arr->data = new int[arr->size];
    for (int i = 0; i < arr->size; i++) in >> arr->data[i];
}