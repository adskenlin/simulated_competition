#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <numeric>
#include <fstream>
#include "competitor.h"
using namespace std;

// speech management class
class Manager
{
public:
    //construction
    Manager();

    //menu
    void showMenu();

    //quit
    void exitSystem();

    //init comp
    void initComp();

    //create competitors
    void createCompetitors();

    //start comp
    void startComp();

    void CompDraw();

    void Comp();

    void showScore();

    //save and load
    void save();

    void load();

    void showHistory();

    void clearHistory();

    //deconstruction
    ~Manager();

    // competiters in first round
    vector<int> v1;
    // 2. round
    vector<int> v2;
    // winners
    vector<int> vwinners;
    //container to store data
    map<int, Competitor> m_Competitors;

    int m_Round;

    bool fileIsEmpty;

    map<int, vector<string>> m_Record;

};