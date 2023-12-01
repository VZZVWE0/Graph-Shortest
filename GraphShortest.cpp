//Programmer: Anna Felipe
//Programmer ID: 1500655

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>

using namespace std;

struct Node
{
    string name;

    bool cityPassed;
    list<pair<int, double> > neighbors;
    int prev;
    double cost;
};

pair<stack<int>, double> getShortestRoute(int iStart, int iEnd, vector<Node>& database)
{
    pair<stack<int>, double> result;
    
    for (int i = 0; i < database.size(); i++) {
        database[i].cost = 0;
        database[i].prev = -1;
        database[i].cityPassed = false;
    } 
    queue<int> toDo;
    database[iStart].cityPassed = true;
    toDo.push(iStart);

    while (!toDo.empty()) {
        int popIndex = toDo.front();
        toDo.pop();
        for (pair<int, double>& neb : database[popIndex].neighbors) {
            if (database[neb.first].cityPassed) {
                continue;
            }
            database[neb.first].cost = database[popIndex].cost + 1;
            database[neb.first].prev = popIndex;
            toDo.push(neb.first);
            database[neb.first].cityPassed = true;
            if (neb.first == iEnd) {
                while (!toDo.empty()) {
                    toDo.pop();
                }
                break;
            }
        }
    }
    result.second = database[iEnd].cost;
    int nextIndex = iEnd;
    while (nextIndex != iStart) {
        result.first.push(nextIndex);
        nextIndex = database[nextIndex].prev;
    }
    result.first.push(iStart);
    return result;
}

int main()
{
    cout << "Programmer: Anna Felipe" << endl;
    cout << "Programmer's ID: 1500655" << endl;
    cout << "File: " << __FILE__ << endl;

    ifstream fin;
    fin.open("cities.txt");
    if (!fin.good()) throw "I/O error";

    vector<Node> database;
    while (fin.good()) 
    {
        string startCity, endCity, cost;
        
        getline(fin, startCity);
        getline(fin, endCity);
        getline(fin, cost);
        fin.ignore(1000, 10); 
        
        int iToNode = -1, iFromNode = -1, i;
        for (i = 0; i < database.size(); i++)
            if (database[i].name == startCity)
                break;
        if (i == database.size()) 
        {
            
            Node fromNode = { startCity };
            database.push_back(fromNode);
        }
        iFromNode = i;

        for (i = 0; i < database.size(); i++) 
            if (database[i].name == endCity)
                break;

        if (i == database.size()) 
        {
           
            Node toNode = { endCity };
            database.push_back(toNode);
        }
        iToNode = i;

        
        double edgeCost = atof(cost.c_str());
        database[iFromNode].neighbors.push_back(pair<int, double>(iToNode, edgeCost));
        database[iToNode].neighbors.push_back(pair<int, double>(iFromNode, edgeCost));
    }
    fin.close();
   
    while (true)
    {
        string startCity, endCity;

        cout << endl;
        cout << "Enter the source city[blank to exit]: ";
        getline(cin, startCity);
        if (startCity.length() == 0)
            break;
          
        int start;
        for (start = 0; start < database.size(); start++)
            if (database[start].name == startCity)
                break;

        cout << "Enter the destination city [blank to exit]: ";
        getline(cin, endCity);
        if (endCity.length() == 0)
            break;
        
        int end;
        for (end = 0; end < database.size(); end++)
            if (database[end].name == endCity)
                break;

        pair<stack<int>, double> result = getShortestRoute(start, end, database);
        cout << "Total edges: " << result.second;
        
        for (; !result.first.empty(); result.first.pop())
           cout << "-" << database[result.first.top()].name;
        cout << endl;
       
    }

   system("PAUSE");
}