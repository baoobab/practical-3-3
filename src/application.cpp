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
        case 5: {
            polynom.calcCoefFromRoots();
            polynom.setPrintMode(EPrintMode::EPrintModeCanonical);
            cout << polynom << "\n";
            break;
        }
        case 4: {
            polynom.setPrintMode(EPrintMode::EPrintModeClassic);
            cout << polynom << "\n";
            break;
        }
        case 3: {
            break;
        }
        case 2: {
            cin >> item;
            cout << "P(" << item << "): " << polynom.value(item) << "\n";
            break;
        }
        case 1: {
            number canonicCoef = 1;

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
    cout << "5 - print polynom (canonical)" << "\n";
    cout << "4 - print polynom (classic)" << "\n";
    cout << "3 - roots" << "\n";
    cout << "2 - calculate value of polynom in point x" << "\n";
    cout << "1 - set polynom by a_n and x_n, x_(n-1), ... , x_0" << "\n";
    cout << "0 - exit" << "\n" << "> ";

    cin >> ch;
    if (!cin.good()) return -1;

    return ch;
}
