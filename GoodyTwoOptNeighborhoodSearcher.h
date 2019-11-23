//
// Created by timo on 11/22/19.
//

#ifndef EXERCISES2_CODE_GOODYTWOOPTNEIGHBORHOODSEARCHER_H
#define EXERCISES2_CODE_GOODYTWOOPTNEIGHBORHOODSEARCHER_H


#include <vector>
#include "Goody.h"
#include "NeighborhoodSearcher.h"

class GoodyTwoOptNeighborhoodSearcher : public NeighborhoodSearcher {
    public:
    void setGoodies(std::vector<Goody>& goodyRef);
    void setMaxweight(unsigned int m);
    bool cont() override;
    double getCostChange() override;
    bool acceptChange() override;
    void ignoreChange() override;


    bool isBetterCost(double c1, double c2) override;

    std::vector<Goody>* goodies;
    unsigned int totalWeight;
    unsigned int totalValue;
    unsigned int maxWeight;


    std::vector<Goody>::iterator it1;
    std::vector<Goody>::iterator it2;
    int valueChange = 0;
    int weightChange = 0;

    std::vector<Goody> bestsol;
    std::vector<Goody> getBestSolution();
    bool saveAsBestSolution() override;
    bool restoreBestSolution() override;


    void calculateTotals();
};



#endif //EXERCISES2_CODE_GOODYTWOOPTNEIGHBORHOODSEARCHER_H
