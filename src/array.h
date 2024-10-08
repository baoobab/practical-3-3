
#ifndef ARRAY_H
#define ARRAY_H

#include "number.h"


class TArray {
private:
    unsigned size;
    number* arr;

    void quickSortHelper(int low, int high);
    void quickSortReverseHelper(int low, int high);
    bool checkIndex(unsigned int index);
public:
    TArray();
    ~TArray();
    unsigned getSize();
    void appendElement(number el);
    void print();
    void resizeArray(unsigned newSize);
    number mediumValue();
    number standardDeviation();
    void sort();
    void reverseSort();
    void flushMemory();
    void replaceElement(unsigned int index, number value);
    void removeElementByIndex(unsigned int index);
    void fillArray(unsigned newSize, number el = 0);


    // TODO: добавить
    // TODO: добавить
    // TODO: добавить    // TODO: добавить
    // TODO: добавить    // TODO: добавитьм
    // TODO: добавить    // TODO: добавить    // TODO: добавить
    // TODO: добавить
    number get(unsigned idx);
    number& operator[](unsigned index);
};

#endif // ARRAY_H
