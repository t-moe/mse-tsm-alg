//
// Created by timo on 11/22/19.
//

#include "DecisionMaker.h"
#include <cmath>
#include <iostream>

bool DecisionMaker::cont() {
    //return cnt++ < 10000;
    shouldRestart = false;

    if(cnt % tempDecreaseInterval == 0) {
        temp = learningRate * temp;
        //std::cout << "Decrease temp to " << temp << " after it " << cnt << std::endl;
        tempIncreaseWithoutImprovement++;

        if(tempIncreaseWithoutImprovement > reheatInterval) {
            tempIncreaseWithoutImprovement=0;
            //temp = temp*2;
            temp = lastReheatTemp*reheatRate;
            lastReheatTemp= temp;
            reheatcnt++;
            std::cout << "Reheat temp to " << temp << " after it " << cnt << std::endl;
        }
    }
    cnt++;

    //return cnt++ < 1000;
    //return tempIncreaseWithoutImprovement < 10;
    //return temp > 1;
    if(temp > 1) {
        return true;
    } else if (restartsLeft>0) {
        restartsLeft--;
        std::cout << "Restarting!" << std::endl;
        temp = startTemp;
        lastReheatTemp = startTemp;
        tempIncreaseWithoutImprovement = 0;
        reheatcnt = 0;
        shouldRestart = true;
        return true;
    } else {
        return false;
    }
}

bool DecisionMaker::shouldTake(int cost_change) {

    double p = exp(-(double)cost_change/temp);
    double r = (double)rand() / RAND_MAX;

    //std::cout << "temp " << temp << " cost " << cost_change << " prob " << p << std::endl;

    //return cost_change < 0;
    //return true;
    return p > r;
    return cost_change > 0;
}

DecisionMaker::DecisionMaker(double avgImprovement, int tempDecreaseInterval,  int reheatInterval,
                             double reheatRate , double initialAcceptanceRate, double learningRate, int restartCnt ) {
    startTemp =  -avgImprovement/log(initialAcceptanceRate);
    temp = startTemp;
    lastReheatTemp = temp;
    std::cout << "initial temp " << temp << std::endl;
    this->learningRate = learningRate;
    this->reheatRate = reheatRate;
    this->reheatInterval = reheatInterval;
    this->tempDecreaseInterval = tempDecreaseInterval;
    this->restartsLeft = restartCnt;

}

void DecisionMaker::recordNewBest(double best) {
    std::cout << "New global best " << best << " at it " << cnt <<  " temp " << temp << std::endl;
    tempIncreaseWithoutImprovement = 0;
}

bool DecisionMaker::shouldRestartWithBest() {
    return shouldRestart;
}
