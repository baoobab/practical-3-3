#include "application.h"
#include "polynom.h"
#include "number.h"
#include <iostream>

using namespace std;


TApplication::TApplication() {

}

int TApplication::exec() {
    int ch;
    TPolynom polynom;

    while (true) {
        number item;

        cin.clear(); // Clearing the input stream from possible errors
        cin.sync();
        ch = menu();

        switch (ch) {
        case 6: {
//            polynom.calcCoefFromRoots(); // это делаем в case 1 чтобы все работало
            polynom.setPrintMode(EPrintMode::EPrintModeCanonical);
            cout << polynom << "\n";
            break;
        }
        case 5: {
            polynom.setPrintMode(EPrintMode::EPrintModeClassic);
            cout << polynom << "\n";
            break;
        }
        case 4: {
            unsigned size;

            cout << "Current roots: ";
            polynom.printRoots();

            cout << "\nEnter a new size of roots array: ";
            cin >> size;
            if (!cin.good()) {
                cout << "\nYou entered an incorrect value\n";
                break;
            }
            int addedCount = polynom.changeArrRootSize(size);

            if (addedCount > 0) {
                for (int i = size - addedCount; i < size; i++) {
                    cout << "Enter root[" << i << "]: ";
                    cin >> item;
                    polynom.changeRootByIndex(i, item);
                    cout << "\n";
                }
            }
            polynom.calcCoefFromRoots();

            cout << "Updated roots: ";
            polynom.printRoots();
            break;
        }
        case 3: {
            cout << "Current a_n = " << polynom.getCanonicCoef() << "\n";
            cout << "Enter new a_n: ";
            number newCanonicalCoef;
            cin >> newCanonicalCoef;
            if (!cin.good()) {
                cout << "\nYou entered an incorrect value\n";
                break;
            }
            polynom.setCanonicCoef(newCanonicalCoef);
            cout << "Current roots: ";
            polynom.printRoots();
            cout << "Enter index of root you want to change (or enter any char - to save ONLY new a_n): ";
            unsigned index;
            cin >> index;
            if (cin.good()) {
                cout << "Enter new root: ";
                cin >> item;
                polynom.changeRootByIndex(index, item);
            }
            polynom.calcCoefFromRoots();
            break;
        }
        case 2: {
            cout << "Enter point x to calculate P(x):\nx = ";
            cin >> item;
            cout << "P" << item << " = " << polynom.value(item) << "\n";
            break;
        }
        case 1: {
            number canonicCoef;

            cout << "Enter a_n (canonic coef): ";
            cin >> canonicCoef;
            polynom.flushMemory();
            polynom.setCanonicCoef(canonicCoef);
            cin.clear();
            cin.sync();

            cout << "\nEnter roots: ";
            while (true) {
                if (!(cin >> item)) {
                    cin.clear();
                    string stopSeq;
                    cin >> stopSeq;
                    if (stopSeq.length() < 2 || stopSeq[0] != stopSeq[1]) {
                        break;
                    } else {
                        cout << "Invalid input. Enter complex numbers or a non-numeric sequence to stop: ";
                    }
                } else {
                    polynom.addRoot(item);
                }
            }
            polynom.calcCoefFromRoots();
            break;
        }
        case 0: {
            return 0;
        }
        default: {
            cout << "\n" << "There is no case with this number" << "\n";
            break;
        }
        }
    }
    return 0;
}


int TApplication::menu() {
    int ch;

    cout << "\nOperations:" << "\n";
    cout << "6 - print polynom (canonical)" << "\n";
    cout << "5 - print polynom (classic)" << "\n";
    cout << "4 - change size of roots array" << "\n";
    cout << "3 - set new a_n and root" << "\n";
    cout << "2 - calculate value of polynom in point x" << "\n";
    cout << "1 - set polynom by a_n and x_n, x_(n-1), ... , x_1" << "\n";
    cout << "0 - exit" << "\n" << "> ";

    cin >> ch;
    if (!cin.good()) return -1;

    return ch;
}
