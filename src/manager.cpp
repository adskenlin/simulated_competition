#include "manager.h"

//construction
Manager::Manager()
{
    this->initComp();

    this->createCompetitors();

    this->load();
}

void Manager::showMenu()
{
    cout << "*******************************" << endl;
    cout << "Welcome to Speech Competition! " << endl;
    cout << "1. Start the Competition       " << endl;
    cout << "2. Competition History         " << endl;
    cout << "3. Clear History               " << endl;
    cout << "0. Quit                        " << endl;
    cout << "*******************************" << endl;
    cout << endl;
}

void Manager::exitSystem()
{
    cout << "See You!" << endl;
    system("pause");
    exit(0);
}

void Manager::initComp()
{
    this->v1.clear();
    this->v2.clear();
    this->vwinners.clear();
    this->m_Competitors.clear();
    this->m_Round = 1;
    this->m_Record.clear();
}

void Manager::createCompetitors()
{
    string nameSeed = "ABCDEFGHIJKL";
    for (int i=0; i<nameSeed.size(); i++)
    {
        string name = "Competitor";
        name += nameSeed[i];
        Competitor cpr;
        cpr.m_Name = name;
        for (int i = 0; i < 2; i++)
        {
            cpr.m_Score[i] = 0;
        }

        this->v1.push_back(i+10001);
        this->m_Competitors.insert(make_pair(i+10001, cpr));
    }
}

void Manager::startComp()
{
    this-> CompDraw();
    this-> Comp();
    this->showScore();
    this->m_Round++;
    this-> CompDraw();
    this-> Comp();
    this->showScore();
    this->save();
    this->initComp();
    this->createCompetitors();
    this->load();
    cout << "Competition Ends!" << endl;
    system("pause");
    system("cls");
}

void Manager::CompDraw()
{
    cout << "the " << this->m_Round << " round: " << endl;
    cout << "-----------------------------------------" << endl;
    if (this->m_Round == 1)
    {
        random_shuffle(v1.begin(), v1.end());
        for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    else
    {
        random_shuffle(v2.begin(), v2.end());
        for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------------------" << endl;
    system("pause");
    cout << endl;
}

void Manager::Comp()
{
    cout << "The " << this->m_Round << " Round Competition Starts Now!" << endl;
    multimap<double, int, greater<double>> groupScore;

    int num = 0;
    vector<int> v_Scr;
    if (this->m_Round == 1)
    {
        v_Scr = v1;
    }
    else
    {
        v_Scr = v2;
    }

    for (vector<int>::iterator it = v_Scr.begin(); it != v_Scr.end(); it++)
    {
        num++;

        deque<double> d;
        for (int i = 0; i<10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;
            d.push_back(score);
        }
        sort(d.begin(), d.end(), greater<double>());
        d.pop_front();
        d.pop_back();

        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / (double)d.size();

        this->m_Competitors[*it].m_Score[this->m_Round - 1] = avg;

        groupScore.insert(make_pair(avg, *it));

        if (num % 6 == 0)
        {
            cout << "The " << num / 6 << " Group's Grade: " << endl;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                cout << "Competitor's Num: " << it ->second 
                     << "\tName: " << this->m_Competitors[it->second].m_Name
                     << "\tGrade: " << this->m_Competitors[it->second].m_Score[this->m_Round - 1]
                     << endl;
            }
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
            {
                if (this->m_Round == 1)
                {
                    v2.push_back((*it).second);
                }
                else
                {
                    vwinners.push_back((*it).second);
                }
            }
            groupScore.clear();
            cout << endl;
        }

    }
    cout << "The " << this->m_Round << " Round Competition Ends Now!" << endl;
    system("pause");
}

void Manager::showScore()
{
    cout << "Result of " << this->m_Round << " Round Competition: " << endl;
    vector<int> v;
    if (this->m_Round == 1)
    {
        v = v2;
    }
    else
    {
        v = vwinners;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "Competitor's Num: " << *it
             << "\tName: " << this->m_Competitors[*it].m_Name
             << "\tGrade: " << this->m_Competitors[*it].m_Score[this->m_Round - 1]
             << endl;
    }
    cout << endl;
    system("pause");
    system("cls");
    this->showMenu();
}

void Manager::save()
{
    ofstream ofs;
    ofs.open("SpeechCompetition.csv", ios::out | ios::app);

    for (vector<int>::iterator it = vwinners.begin(); it != vwinners.end(); it++)
    {
        ofs << *it << ","
            << m_Competitors[*it].m_Score[1] << ",";
    }
    ofs << endl;

    ofs.close();

    this->fileIsEmpty = false;

    cout << "Saved!" << endl;
}

void Manager::load()
{
    ifstream ifs("SpeechCompetition.csv", ios::in);
    if (!ifs.is_open())
    {
        this->fileIsEmpty = true;
        cout << "File not found!" << endl;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "Empty file!" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    this->fileIsEmpty = false;
    ifs.putback(ch);

    string data;
    int index = 0;
    while(ifs >> data)
    {
        vector<string> v;

        int pos = -1;
        int start = 0;
        while (true)
        {
            pos = data.find(",", start);
            if (pos == -1)
            {
                break;
            }
            string tmp = data.substr(start, pos-start);
            v.push_back(tmp);
            start = pos + 1;
        }

        this->m_Record.insert(make_pair(index, v));
        index++;
    }
    ifs.close();

    // for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
    // {
    //     cout << it->first << "\tWinner Nr.: " << it->second[0] << "\tGrade: " << it->second[1] << endl;
    // }

}

void Manager::showHistory()
{
    if (this->fileIsEmpty)
    {
        cout << "File not found or no record! " << endl;
    }else{
        for (int i=0; i < this->m_Record.size(); i++)
        {
            cout << "The Nr." << i+1 << " Competition's Winners: " << endl
             << "\tNr.1: " << this->m_Record[i][0] << "\t Grade: "
             << this->m_Record[i][1] << endl
             << "\tNr.2: " << this->m_Record[i][2] << "\t Grade: "
             << this->m_Record[i][3] << endl
             << "\tNr.3: " << this->m_Record[i][4] << "\t Grade: "
             << this->m_Record[i][5] << endl;
        }
    }
    
    system("pause");
    system("cls");
}

void Manager::clearHistory()
{
    cout << "Are your sure to clear all history?" << endl;
    cout << "1. YES " << endl;
    cout << "2. CANCEL" << endl;

    int select = 0;
    cin >> select;

    if (select == 1)
    {
        ofstream ofs("SpeechCompetition.csv", ios::trunc);
        ofs.close();
        this->initComp();
        this->createCompetitors();
        this->load();
        cout << "Clear!" << endl;
    }

    system("pause");
    system("cls");
}

//deconstruction
Manager::~Manager()
{}