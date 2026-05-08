#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>

#include "die.h"
using namespace std;

class DieRoll 
{
    public:
        DieRoll(string input);
        int roll();
        void printProbabilityMap();
    
    private:
        vector<Die> diceVector = {};
        map<int, int> probabilityMap = {};

        vector<int> getProbabilityMapKeys();
        void addDieToProbabilityMap(int dieSize);
        string getRoundPercent(int numberGiven, int total);
        
};