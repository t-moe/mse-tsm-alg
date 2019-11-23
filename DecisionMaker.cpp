//
// Created by timo on 11/22/19.
//

#include "DecisionMaker.h"
#include <cmath>
#include <iostream>

bool DecisionMaker::cont() {
    if(cnt%(50*100) == 0) {
        temp = learningRate * temp;
        std::cout << "Decrease temp to " << temp << " after it " << cnt << std::endl;
        tempIncreaseWithoutImprovement++;
    }
    cnt++;
    //return cnt++ < 100000;
    return tempIncreaseWithoutImprovement < 30;
}

bool DecisionMaker::shouldTake(int cost_change) {

    double p = exp((double)cost_change/temp);
    double r = (double)rand() / RAND_MAX;

    //std::cout << "temp " << temp << " cost " << cost_change << " prob " << p << std::endl;


    //return cost_change > 0;
    return p> r;
}

DecisionMaker::DecisionMaker(double avgImprovement, double initialAcceptanceRate, double learningRate) {
    temp =  avgImprovement/log(initialAcceptanceRate);
    //std::cout << "initial temp " << temp << std::endl;
    this->learningRate = learningRate;

}

void DecisionMaker::recordNewBest() {
    std::cout << "New global maxima at it " << cnt << std::endl;
    tempIncreaseWithoutImprovement = 0;
}
