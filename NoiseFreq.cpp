#include <iostream>
#include <vector>
using namespace std;

const int LIMIT = 100;
void pushToPairs(vector<pair<double, double>> &residuals, double &base, double &search, double &startBase);

int main()
{

    double base;
    double search;
    cout << "Enter the search interval: ";
    cin >> search;
    cout << "Enter the base interval: ";
    cin >> base;
    double startBase = base;

    vector<pair<double, double>> residuals;
    vector<pair<int, double>> table;

    while (residuals.size() < LIMIT)
    {
        pushToPairs(residuals, base, search, startBase);
    }

    for (int i = 0; i < residuals.size(); i++)
    {
        double probability = residuals[i].first * residuals[i].second;
        table.push_back(make_pair(i + 1, probability));
    }
    for (auto &item: table)
    {
        cout << item.first << '\t' << item.second << endl;
    }
    return 0;
}

void pushToPairs(vector<pair<double, double>> &residuals, double &base, double &search, double &startBase)
{
    while (base > search)
    {
        base -= search;
        residuals.push_back(make_pair(0, 0));
        if (residuals.size() == LIMIT)
            return;
    }
    double first_resid = base / startBase;
    double sec_resid = (search - base) / startBase;
    residuals.push_back(make_pair(first_resid, sec_resid));
    base = startBase - (search - base);
}