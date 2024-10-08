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
            polynom.setPrintMode(EPrintMode::EPrintModeClanonic);
            cout << polynom << "\n";
            break;
        }
        case 4: {
            polynom.calcCoefFromRoots();
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

            polynom.flushMemory();
            // cout << "Vibor tipa vvoda";

            cout << "Enter canonic coef: ";
            cin >> canonicCoef;
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


            // while (true) {
            //     if (!(cin >> item)) {
            //         cin.clear();
            //         string stopSeq;
            //         cin >> stopSeq;
            //         if (stopSeq.length() < 2 || stopSeq[0] != stopSeq[1]) {
            //             break;
            //         } else {
            //             cout << "Invalid input. Enter complex numbers or a non-numeric sequence to stop: ";
            //         }
            //     } else {
            //         polynom.addCoef(item);
            //     }
            // }
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
    cout << "5 - print (canonical)" << "\n";
    cout << "4 - print (classic)" << "\n";
    cout << "3 - roots" << "\n";
    cout << "2 - value" << "\n";
    cout << "1 - coef" << "\n";
    cout << "0 - exit" << "\n" << "> ";

    cin >> ch;
    if (!cin.good()) return -1;

    return ch;
}
