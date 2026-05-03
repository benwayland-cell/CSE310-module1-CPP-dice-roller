#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>
using namespace std;


class DieRoll {
    public:
        DieRoll(string input) {
            diceVector = {};

            int dieNumber = INT_MIN;
            int dieSize = INT_MIN;
            bool dieNumberChosen = false;

            // loop through every character
            for (int inputIndex = 0; inputIndex < input.size(); ++inputIndex) {
                char character = input[inputIndex];
                bool characterIsNum = isdigit(static_cast<unsigned char>(character));

                if (characterIsNum) {
                    if (!dieNumberChosen) {
                        // add the character to dieNumber
                        dieNumber *= 10;
                        dieNumber += character - '0';
                    }
                    else {
                        // add the character to dieSize
                        dieSize *= 10;
                        dieSize += character - '0';
                    }
                }

                // if we ended defining the die number
                else if (character == 'd') {
                    if (dieNumber == INT_MIN) dieNumber = 1;
                    dieNumberChosen = true;
                }

                // if we ended defining a die
                if ((!characterIsNum || inputIndex + 1 == input.size()) && dieSize > 0) {
                    for (int i = 0; i < dieNumber; ++i) {
                        diceVector.push_back([dieSize](){return (rand() % dieSize) + 1;});
                        addDieToProbabilityMap(dieSize);
                    }

                    dieNumber = INT_MIN;
                    dieSize = INT_MIN;
                    dieNumberChosen = false;
                }
            }

            // diceVector.push_back([](){return (rand() % 2) + 1;});
            // diceVector.push_back([](){return (rand() % 2) + 1;});

            // addDieToProbabilityMap(2);
            // addDieToProbabilityMap(2);
        }

        int roll() {
            int sum = 0;
            for (int index = 0; index < diceVector.size(); ++index) {
                sum += diceVector[index]();
            }
            return sum;
        }

        void printProbabilityMap() {
            
            vector<int> probMapKeys = getProbabilityMapKeys();
            
            // Get the number of possibilities
            int totalPossibilities = 0;
            for (int keyIndex = 0; keyIndex < probMapKeys.size(); ++keyIndex) {
                totalPossibilities += probabilityMap[probMapKeys[keyIndex]];
            }
            
            cout << "Current Probability Map" << "\n";
            for (int keyIndex = 0; keyIndex < probMapKeys.size(); ++keyIndex) {
                int probMapKey = probMapKeys[keyIndex];
                string roundPercent = getRoundPercent(probabilityMap[probMapKey], totalPossibilities);
                cout << probMapKey << (": " + roundPercent + "\n");
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

        string getRoundPercent(int numberGiven, int total) {
            float percentage = (float)numberGiven / total * 100.0; // Get the percentage
            int percentageRounded = (int)percentage; // Round it

            // Check if we need to round up
            float decimal = percentage - percentageRounded;
            if (decimal >= 0.5) {
                ++percentageRounded;
            }

            return (to_string(percentageRounded) + "%");
        }
};


int main() {
    srand(time(NULL));

    // cout << (rand() % 100);
    string input;
    cin >> input;
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