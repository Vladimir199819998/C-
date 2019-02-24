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
    if (isPrime(number)) 
    {
        return 1;
    }
    vector<int> variants;
    for (int i = 0; i < 6; i++)
    {
        string strNumber = to_string(number);
        int digit = strNumber[i] - '0';
        digit += 1;
        digit %= 10;
        strNumber[i] = char(48 + digit);
        int digitNumber = stoi(strNumber);
        if (isPrime(digitNumber))
        {
            variants.push_back(digitNumber);
        }
    }
    if (variants.empty())
    {
        return 1;
    }
    else if (variants.size() == 1)
    {
        number = variants[0];
        return 1;
    }
    return 0;
    
}

int main()
{

    string buffer;
    vector<int> primes;
    while (cin >> buffer)
    {
        primes.push_back(atoi(buffer.c_str()));
    }

    // fstream input("input1.dat", ios_base::in | ios_base::binary);
    // if (!input.is_open())
    //     throw runtime_error("Cannot open this file!\n");
    // while (getline(input, buffer))
    // {
    //     primes.push_back(stoi(buffer.c_str()));
    // }
    // input.close();

    for (int &num : primes)
    {
        if (isPossibleToChange(num))
        {
            cout << num << "\n";
        }
        else if (!isPossibleToChange(num))
        {
            cout << num << "*"
                 << "\n";
        }
    }
    

    return 0;
}
