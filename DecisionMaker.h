//
// Created by timo on 11/22/19.
//

#ifndef EXERCISES2_CODE_DECISIONMAKER_H
#define EXERCISES2_CODE_DECISIONMAKER_H


class DecisionMaker {

public:
     DecisionMaker(double avgImprovement,
             int tempDecreaseInterval = 60 * 100,
             int reheatInterval = 7,
             double reheatRate = 0.5,
             double initialAcceptanceRate = 0.4,
             double learningRate= 0.9);
     bool cont();
     bool shouldTake(int cost_change);
     void recordNewBest(unsigned best);

    int tempDecreaseInterval;
    double reheatRate;
    int reheatInterval;
    double learningRate;

private:
    int tempIncreaseWithoutImprovement = 0;
    int cnt=0;
    int reheatcnt=0;
    double temp;
    double lastReheatTemp;

};


#endif //EXERCISES2_CODE_DECISIONMAKER_H
