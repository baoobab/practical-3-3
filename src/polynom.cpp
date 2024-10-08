#include "polynom.h"
#include <iostream>
#include <array.h>
#include <math.h>

using namespace std;


TPolynom::TPolynom(number canonicCoef) {
    this->canonicCoef = canonicCoef;
    this->printMode = EPrintMode::EPrintModeClassic;
    this->arrCoef = new TArray();
    this->arrRoot = new TArray();
}

TPolynom::~TPolynom() {
    this->flushMemory();
}


void TPolynom::addCoef(number coef) {
    this->arrCoef->appendElement(coef);
}

void TPolynom::addRoot(number root) {
    this->arrRoot->appendElement(root);
}


number TPolynom::value (number val) {
    number result = 0;
    for (int i= 0; i < this->arrCoef->getSize(); i++) {
        int rootPow = (this->arrCoef->getSize() - i - 1);
        result += this->arrCoef->get(i) * pow(val, rootPow);
    }

    return result;
}

ostream& operator<<(ostream& os, TPolynom& polynom) {
    cout << "P(x) = ";

    if (!polynom.arrCoef->getSize()) {
        cout << "0";
        return os;
    }

    if (polynom.printMode == EPrintMode::EPrintModeClassic) {
        for (int i = 0; i < polynom.arrCoef->getSize() - 1; i++) {
            int pow = (polynom.arrCoef->getSize() - i - 1);
            os << polynom.arrCoef->get(i);
            if (pow != 0) os << "x";
            if (pow > 1) os << "^" << pow;
            os << " + ";
        }
        cout << polynom.arrCoef->get(polynom.arrCoef->getSize() - 1);

    } else { // TODO: podumat'
        if (polynom.arrCoef->getSize() == 1) cout << polynom.arrCoef->get(0);
        else cout << "x";

        for (int i = 1; i < polynom.arrCoef->getSize(); i++) {
            os << " + ";
            int pow = (polynom.arrCoef->getSize() - i - 1);
            os << (polynom.arrCoef->get(i) / polynom.arrCoef->get(0));
            if (pow != 0) os << "x";
            if (pow > 1) os << "^" << pow;
        }
    }

    os << "\n";

    return os;
}

void TPolynom::flushMemory() {
    this->arrCoef->flushMemory();
    this->arrRoot->flushMemory();
}

void TPolynom::setPrintMode(EPrintMode mode) {
    this->printMode = mode;
}

void TPolynom::setCanonicCoef(number coef) {
    this->canonicCoef = coef;
}

void TPolynom::calcCoefFromRoots() {
    if (!arrRoot) return;

    // Начинаем с канонического коэффициента
    canonicCoef = 1;

    // Начальные коэффициенты многочлена (1 для x^0)
    TArray* coefficients = new TArray();
    coefficients->fillArray(arrRoot->getSize() + 1);
    coefficients->replaceElement(0, 1);

    // Умножаем на каждый линейный множитель
    for (int i = 0; i < arrRoot->getSize(); i++) {
        number currentRoot = -arrRoot->get(i); // (x - r) => x + (-r)
        for (int j = i + 1; j > 0; j--) { // Обновляем коэффициенты в обратном порядке
            (*coefficients)[j] += (*coefficients)[j - 1] * currentRoot;
        }
        (*coefficients)[0] = (*coefficients)[0] * currentRoot; // Умножаем на (-r)
    }

    // Очищаем предыдущие данные и добавляем новые коэффициенты в массив arrCoef
    arrCoef->flushMemory();
    for (int i = 0; i <= arrRoot->getSize(); i++) {
        addCoef(coefficients->get(i));
    }

    coefficients->flushMemory(); // Освобождаем память
}
