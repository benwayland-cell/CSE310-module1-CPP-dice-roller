#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Die {
    public:
        int dieNumber;
        int dieSize;
        Die(int dieNumber, int dieSize);
        int roll();
};