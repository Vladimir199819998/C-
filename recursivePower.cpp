// Алгоритм рекурсивной степени
#include <iostream>
using namespace std;

static int counter = 0;
namespace mypow
{
template <typename Base>
Base fastPow(Base number, int power)
{
    if (power == 0)
    {
        return 1;
    }

    else if (power % 2 != 0)
    {
        return number * pow(number, power - 1);
        counter++;
    }
    else
    {
        counter++;
        return pow(number * number, power / 2);
    }
};
} // namespace mypow

int main()
{
    double base = 5.6;
    int power = 5;
    cout << base << " in power of " << power << " = " << mypow::fastPow(base, power) << endl;
    cout << "Iterations done: " << counter << endl;
    return 0;
}