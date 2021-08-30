#include <iostream>
using namespace std;
#include "manager.h"
#include <string>
#include <ctime>

int main()
{
    srand((unsigned int)time(NULL));
    Manager m;

    // for (map<int, Competitor>::iterator it = m.m_Competitors.begin(); it != m.m_Competitors.end(); it++)
    // {
    //     cout << "Competitor Num: " << it -> first
    //          << "\tName: " << it -> second.m_Name
    //          << "\tScore: " << it -> second.m_Score[0] << endl;
    // }

    int choice = 0;

    while(true)
    {
        m.showMenu();

        cout << "Please Enter Your Choice: " << endl;
        cin >> choice;

        switch(choice)
        {
        case 1: 
            m.startComp();
            break;
        case 2:
            m.showHistory();
            break;
        case 3:
            m.clearHistory();
            break;
        case 0:
            m.exitSystem();
            break;
        default:
            system("cls");
            break;
        }
    }
    


    system("pause");
    return 0;
}