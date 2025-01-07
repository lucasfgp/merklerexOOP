#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<string> strings;

    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");

    for(string s : strings)
    {
        cout << s << endl;
    }
}