/*** بسم الله الرحمن الرحيم  ***/
#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define Fast  std::ios_base::sync_with_stdio(0);cin.tie(NULL);	cout.tie(NULL);
using namespace std;
void file() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}
long long numOfRows = 0, numOfColumn = 0;
string C_ValueName = "";
//  colName      Data
map<string, vector<string>>dataSet;
//  ColName   Value
map<string, string>X_Value;
//  Yes/No       num   P(Ci)
map<string, pair<int, double>>P_CValues;
//       ValueX       ColName  YES/nO
map<pair<string, pair<string, string>>, double>P_XGivenCItems;
map < string, double>P_XGivenC;
vector<pair<double, string>>output;
void takeInput();
void takeX();
void P_CValueFun();
void P_XGivenCItemsFun();
void P_XGivenCFun();
void ouputFun();
int main()
{
    Fast  file();
    takeInput();
    takeX();
    P_CValueFun();
    P_XGivenCItemsFun();
    P_XGivenCFun();
    ouputFun();
}
void takeInput()
{
    cin >> numOfRows >> numOfColumn;
    for (int i = 0; i < numOfRows; i++)
    {
        //name of coulmn
        string name;
        cin >> name;
        for (int j = 0; j < numOfColumn; j++)
        {
            string value;
            cin >> value;
            dataSet[name].push_back(value);
        }
        if (i == numOfRows - 1)
            C_ValueName = name;
    }
} 

void takeX() 
{
    for (int i = 0; i < numOfRows - 1; i++)
    {
        string name, value;
        char eql;
        cin >> name >> eql >> value;
        X_Value[name] = value;
    }
    /*for (auto i : X_Value)
    {
        cout << i.first << " " << i.second << "\n";
    }*/
}

void P_CValueFun()
{
    for (auto i : dataSet[C_ValueName])
    {
        P_CValues[i].first++;
        P_CValues[i].second++;
    }
    cout << "P(Ci):\n";
    for (auto& i : P_CValues)
    {
        cout << "\tP(" << C_ValueName << " = \"" << i.first << "\") = " << i.second.second << "/" << numOfColumn;
        i.second.second /= numOfColumn;
        cout << " = " << i.second.second << "\n";
    }
    cout << "---------------------------------------------------\n\n";
}

void P_XGivenCItemsFun()
{
    cout << "Compute P(X|Ci) for each class\n";
    for (auto i : P_CValues)
    {
        for (auto j : X_Value)
        {
            P_XGivenCItems[{j.second, { j.first , i.first }}];
        }
    }
    for (auto i : X_Value)
    {
        int colSiz = dataSet[i.first].size();
        for (int col = 0; col < colSiz; col++)
        {
            if (dataSet[i.first][col] == i.second)
            {
                P_XGivenCItems[{i.second, { i.first, dataSet[C_ValueName][col] }}]++;
            }
        }
    }
    for (auto& i : P_XGivenCItems)
    {
        cout << "\tP(" << i.first.second.first << " = \"" << i.first.first << "\") | " <<
            C_ValueName << " = \"" << i.first.second.second << "\") = " << i.second << "/" << P_CValues[i.first.second.second].first;
        i.second /= P_CValues[i.first.second.second].first;
        cout << " = " << i.second << "\n";
        
    }
    cout << "---------------------------------------------------\n\n";
}

void P_XGivenCFun()
{
    bool ok = 0;
    cout << "P(X|Ci) : \n";
    for (auto i : P_CValues)
    {
        P_XGivenC[i.first] = 1;
        ok = 0;
        cout << "\tP(X|" << C_ValueName << " = \"" << i.first << "\") =";
        for (auto j : P_XGivenCItems)
        {
            if (j.first.second.second == i.first)
            {
                if (!ok)
                {
                    ok = 1;
                    cout << j.second;
                }
                else
                {
                    cout << " * " << j.second;
                }
                P_XGivenC[i.first] *= j.second;
            }
        }
        cout << " = "<< P_XGivenC[i.first]<<"\n";
    }
    cout << "---------------------------------------------------\n\n";
}

void ouputFun()
{
    cout << "P(X|Ci)*P(Ci) :\n";
    output.resize(P_XGivenC.size());
    auto it = P_XGivenC.begin();
    for (auto& i : output)
    {
        cout << "\tP(X|" << C_ValueName << " = \"" << it->first << "\") * P(" << C_ValueName << " =\"" << it->first << "\") = ";
        i.first = it->second * P_CValues[it->first].second;
        i.second = it->first;

        cout << i.first << "\n";
        it++;
    }
    cout << "---------------------------------------------------\n\n";
    sort(output.begin(), output.end());
    cout << "Therefore, X belongs to class (\"" << C_ValueName << " = ";
    cout << output[output.size() - 1].second << "\")\n";
}