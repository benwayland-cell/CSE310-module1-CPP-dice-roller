#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>

#include "die.h"
using namespace std;

Die::Die(int dieNumber, int dieSize) {
    this->dieNumber = dieNumber;
    this->dieSize = dieSize;
};

int Die::roll() {
    int sum = 0;
    for (int i = 0; i < dieNumber; ++i) {
        sum += (rand() % dieSize) + 1;
    }
    return sum;
}