#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

map<string, double> parm;
vector<string> printBill;

double round(double value, int places)
{
    if (places < 0)
        throw invalid_argument("places must be non-negative");

    double scale = pow(10.0, places);
    return round(value * scale) / scale;
}

string getKeyFromValue(map<string, double> &details, double value)
{
    for (auto &pair : details)
    {
        if (pair.second == value)
        {
            return pair.first;
        }
    }
    return "";
}

void findPath(map<string, double> &details)
{
    printBill.clear();
    double Max_Value = max_element(details.begin(), details.end(),
                                   [](const pair<string, double> &a, const pair<string, double> &b)
                                   {
                                       return a.second < b.second;
                                   })
                           ->second;
    double Min_Value = min_element(details.begin(), details.end(),
                                   [](const pair<string, double> &a, const pair<string, double> &b)
                                   {
                                       return a.second < b.second;
                                   })
                           ->second;

    if (Max_Value != Min_Value)
    {
        string Max_Key = getKeyFromValue(details, Max_Value);
        string Min_Key = getKeyFromValue(details, Min_Value);
        double result = Max_Value + Min_Value;
        result = round(result, 1);

        if (result >= 0.0)
        {
            cout << Min_Key << " needs to pay " << Max_Key << ": " << round(abs(Min_Value), 2) << endl;
            details.erase(Max_Key);
            details.erase(Min_Key);
            details[Max_Key] = result;
            details[Min_Key] = 0.0;
        }
        else
        {
            cout << Min_Key << " needs to pay " << Max_Key << ": " << round(abs(Max_Value), 2) << endl;
            details.erase(Max_Key);
            details.erase(Min_Key);
            details[Max_Key] = 0.0;
            details[Min_Key] = result;
        }

        findPath(details);
    }
}

int main()
{
    parm["A"] = -5.0;
    parm["B"] = 25.0;
    parm["C"] = -20.0;
    parm["D"] = 25.0;
    parm["E"] = -20.0;
    parm["F"] = -5.0;

    findPath(parm);

    return 0;
}
