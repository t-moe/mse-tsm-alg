//
// Created by timo on 11/22/19.
//

#include "DecisionMaker.h"

bool DecisionMaker::cont() {
    return cnt++ < 1000;
}

bool DecisionMaker::shouldTake(int cost_change) {
    return cost_change > 0;
}
