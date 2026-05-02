#include <iostream>
#include <functional>
#include <vector>
#include <map>
using namespace std;


class DieRoll {
    public:
        DieRoll(string input) {
            diceVector = {};
            diceVector.push_back([](){return rand() % 2;});
            diceVector.push_back([](){return rand() % 2;});
            diceVector.push_back([](){return 1;});

            addDieToProbabilityMap(2);
            addDieToProbabilityMap(2);
        }

        int roll() {
            int sum = 0;
            for (int index = 0; index < diceVector.size(); ++index) {
                sum += diceVector[index]();
            }
            return sum;
        }

        void printProbabilityMap() {
            cout << "Current Probability Map" << "\n";

            vector<int> probMapKeys = getProbabilityMapKeys();
            for (int keyIndex = 0; keyIndex < probMapKeys.size(); ++keyIndex) {
                int probMapKey = probMapKeys[keyIndex];
                cout << probMapKey << ": " << probabilityMap[probMapKey] << "\n";
            }
        }

    private:
        vector<function<int()>> diceVector;
        map<int, int> probabilityMap = {};


        // Returns the keys of probabilityMap
        vector<int> getProbabilityMapKeys() {
            // Vector to store the keys
            vector<int> keys;
            // Extract keys using a loop
            for (auto it = probabilityMap.begin(); it != probabilityMap.end(); ++it)
            {
                // Add the key to the vector
                keys.push_back(it->first);
            }
            return keys;
        }

        void addDieToProbabilityMap(int dieSize) {
            map<int, int> newProbMap = {}; // we are going to set probabilityMap to this afterwards

            // Edge case: there is currently nothing in the probability map
            if (probabilityMap.size() == 0) {
                for (int currentNum = 1; currentNum <= dieSize; ++currentNum) {
                    probabilityMap[currentNum] = 1;
                }
                return;
            }

            vector<int> probMapKeys = getProbabilityMapKeys();

            for (int currentNum = 1; currentNum <= dieSize; ++currentNum) {
                for (int keyIndex = 0; keyIndex < probMapKeys.size(); ++keyIndex) {
                    int probMapKey = probMapKeys[keyIndex];
                    newProbMap[currentNum + probMapKey] += probabilityMap[probMapKey];
                }
            }

            probabilityMap = newProbMap;
        }
};


int main() {
    srand(time(NULL));

    // cout << (rand() % 100);
    DieRoll testDieRoll("input string");

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