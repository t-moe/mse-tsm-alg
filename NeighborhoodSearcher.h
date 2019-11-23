//
// Created by timo on 11/23/19.
//

#ifndef EXERCISES2_CODE_NEIGHBORHOODSEARCHER_H
#define EXERCISES2_CODE_NEIGHBORHOODSEARCHER_H


#include <cstdlib>
#include <iostream>
#include <vector>
#include "DecisionMaker.h"
#include "Goody.h"

class NeighborhoodSearcher {
public:

    virtual bool cont() = 0;
    virtual bool acceptChange() = 0;
    virtual void ignoreChange() = 0;

    virtual double getCostChange() = 0;

    virtual bool restoreBestSolution() = 0;
    virtual bool saveAsBestSolution() = 0;
    virtual bool isBetterCost(double c1, double c2) = 0;


    void improveSolution( DecisionMaker& decisionMaker) {
        double bestcost = 0;
        improvements = 0;
        costsum = 0;
        while(cont() && decisionMaker.cont()) {
            double costChange = getCostChange();
            if(decisionMaker.shouldTake(costChange)) {
                improvements++;
                costsum += costChange;

                acceptChange();

                if(isBetterCost(costsum,bestcost)) {
                    decisionMaker.recordNewBest(costsum);
                    saveAsBestSolution();
                    bestcost = costsum;
                }
            } else {
                ignoreChange();
            }
            if(decisionMaker.shouldRestartWithBest()) {
                restoreBestSolution();
                costsum = bestcost;
                //This will invalidate avgImprovement!
            }
        }
        std::cout << "Cost improved by " << bestcost << std::endl;
    }

    double avgImprovement() {
        return (double) costsum / improvements;
    }

    unsigned int improvements = 0;
    long costsum =0;


};




#endif //EXERCISES2_CODE_NEIGHBORHOODSEARCHER_H
