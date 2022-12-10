//################################
// Seneca Library Application  ###
//################################

#include "Utils.h"
using namespace std;
namespace sdds
{
    int getInt()
    {
        int x;
        cin >> x;
        while (cin.fail() || cin.get() != '\n')
        {
            if (cin.fail())
                cout << "Invalid Selection, try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> x;
        }
        return x;
    }
    int getIntRange(int min, int max)
    {
        int x = getInt();
        while (x < min || x > max)
        {
            cout << "Invalid Selection, try again: ";
            x = getInt();
        }
        return x;
    }
}