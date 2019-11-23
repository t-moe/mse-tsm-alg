//
// Created by timo on 11/22/19.
//

#ifndef EXERCISES2_CODE_DECISIONMAKER_H
#define EXERCISES2_CODE_DECISIONMAKER_H


class DecisionMaker {

public:
     DecisionMaker(double avgImprovement, double initialAcceptanceRate = 0.3, double learningRate= 0.95);
     bool cont();
     bool shouldTake(int cost_change);
     void recordNewBest();

     int tempIncreaseWithoutImprovement = 0;
    int cnt=0;
    double temp;
    double learningRate;
};


#endif //EXERCISES2_CODE_DECISIONMAKER_H
