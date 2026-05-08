#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>

#include "die-roll.h"
#include "die.h"

using namespace std;

int main() {
    srand(time(NULL));

    cout << "Roll: ";
    string input;
    getline(cin, input);
    DieRoll testDieRoll(input);

    cout << "Die Rolls" << "\n";
    map<int, int> dieRollMap = {};

    for (int i = 0; i < 100; ++i) {
        int currentRoll = testDieRoll.roll();
        ++dieRollMap[currentRoll];
    }

    // Vector to store the keys
    vector<int> dieRollKeys;
    // Extract keys using a loop
    for (auto it = dieRollMap.begin(); it != dieRollMap.end(); ++it)
    {
        // Add the key to the vector
        dieRollKeys.push_back(it->first);
    }

    for (int index = 0; index < dieRollKeys.size(); ++index) {
        cout << dieRollKeys[index] << ": " << dieRollMap[dieRollKeys[index]] << "\n";
    }

    testDieRoll.printProbabilityMap();

    return 0;
}