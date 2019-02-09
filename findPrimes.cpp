#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

bool isPrime(int number)
{
    for (int i = 2; i < number; i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int isPossibleToChange(int &number)
{
    int counter = 0;
    int splitNum[6];
    for (int i = 1000000, pos = 0; pos < 6; i /= 10, pos++)
    {
        splitNum[pos] = (number % i) / (i / 10);
    }

    for (int pos = 0; pos < 6; pos++)
    {

        string newStr = "";
        int newSplitNum[6];
        memcpy(newSplitNum, splitNum, sizeof(splitNum));
        newSplitNum[pos] = (newSplitNum[pos] - 1) % 10;
        for (int i = 0; i < 6; i++)
        {
            newStr += to_string(newSplitNum[i]);
        }

        int newNum = atoi(newStr.c_str());
        if (isPrime(newNum))
        {
            counter++;
            if (counter >= 2)
                return 2;
        }
    }
    if (counter == 1)
        return 1;

    return 0;
}

int main()
{

    string buffer;
    vector<int> primes;
    vector<int> output_primes;
    while (cin >> buffer)
    {
        primes.push_back(atoi(buffer.c_str()));
    }

    for (int &item : primes)
    {
        if (isPossibleToChange(item) == 1 || isPossibleToChange(item) == 0)
        {
            cout << item << endl;
        }
        else if (isPossibleToChange(item) == 2)
        {
            cout << item << "*" << endl;
        }
    }

    return 0;
}