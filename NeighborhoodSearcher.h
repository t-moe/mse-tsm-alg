//
// Created by timo on 11/22/19.
//

#ifndef EXERCISES2_CODE_NEIGHBORHOODSEARCHER_H
#define EXERCISES2_CODE_NEIGHBORHOODSEARCHER_H


#include <vector>
#include "Goody.h"

class GoodyTwoOptNeighborhoodSearcher {
    public:
    void setGoodies(std::vector<Goody>& goodyRef);
    void setMaxweight(unsigned int m);
    bool cont();
    double getCostChange();
    bool acceptChange();
    void ignoreChange();


    std::vector<Goody>* goodies;
    //std::vector<Goody>::iterator firstElementOutside;
    unsigned int totalWeight;
    unsigned int totalValue;
    //unsigned int elementsInside;
    unsigned int maxWeight;




    std::vector<Goody>::iterator it1;
    std::vector<Goody>::iterator it2;
    int valueChange = 0;
    int weightChange = 0;

    unsigned int improvements = 0;
    long costsum =0;

    double avgImprovement();
};



#endif //EXERCISES2_CODE_NEIGHBORHOODSEARCHER_H
