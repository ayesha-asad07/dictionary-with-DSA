#include "Header.h"

using namespace std;

int main()
{
    ////////////////////////////////////////////////////////////////////////////
    //////////////////////   Just Designing Display ////////////////////////////
   ////////////////////////////////////////////////////////////////////////////



    system("color 0A");

    for (int i = 0; i < 4; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "\n\n\n\n\t\t\t-------------------------------------------------";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t|      Data Structure and Algorithem (DSA)       |";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t|                Final Project                   |";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t|        -> Dictionary Implementation <-         |";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t|      Fast National University CFD Campus       |";
        cout << "\n\t\t\t|                                                |";
        cout << "\n\t\t\t------------------------------------------------- \n\n";
    }
    _getch();

    system("cls");
    cout << "\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    cout << "\n\n\n\n\t\t\t\t\t     ====> Team Members <====    "; Sleep(800);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    cout << "\n\n\n\n\t\t\t\t\t          Muhammad Bilal         "; Sleep(800);
    cout << "\n\n\n\n\t\t\t\t\t          Tayyaba Imtiaz         "; Sleep(800);
    cout << "\n\n\n\n\t\t\t\t\t          Ayesha   Asad          "; Sleep(1500);
    _getch();

    system("cls");

    cout << "\n\t\t\t------------------------------------------------- ";
    cout << "\n\t\t\t|    Press Any Key to Open Dictionary___         |";
    cout << "\n\t\t\t------------------------------------------------- \n\n";
    _getch();
    cout << "\n\n\n\t\t\t\tLoading ";
    char a = 219;
    for (int i = 0; i < 27; i++)
    {
        Sleep(150);
        cout << a;
    }

    system("cls");
    system("color 07");

    UI uiObj;
    uiObj.process();

    return 0;
}
