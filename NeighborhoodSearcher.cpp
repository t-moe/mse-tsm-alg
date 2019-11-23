//
// Created by timo on 11/22/19.
//

#include <cstdlib>
#include <iostream>
#include "NeighborhoodSearcher.h"

void NeighborhoodSearcher::setGoodies(std::vector<Goody> &goodyRef) {
    this->goodies = &goodyRef;
    totalWeight = 0;
    totalValue = 0;
    firstElementOutside = goodies->begin();
    elementsInside = 0;
    for(auto it= goodies->begin(); it!= goodies->end(); it++) {
        if(totalWeight + it->weight > maxWeight) {
            firstElementOutside = it;
            break;
        } else {
            elementsInside++;
            totalWeight += it->weight;
            totalValue += it->value;
        }
    }
}



bool NeighborhoodSearcher::cont() {

    do {
        it1 = goodies->begin();
        std::advance(it1, rand() % elementsInside);
        it2 = firstElementOutside;
        std::advance(it2, rand() % (goodies->size()-elementsInside));

        valueChange = it2->value - it1->value;
        weightChange = it2->weight - it1->weight;
    } while(totalWeight + weightChange > maxWeight);


    //if(valueChange > 0) {
        improvements++;
        costsum += valueChange;
   // }

    return true;
}

double NeighborhoodSearcher::getCostChange() {
    return valueChange;
}

bool NeighborhoodSearcher::acceptChange() {
    if(valueChange == 0 && weightChange==0) {
        return false;
    }
    //std::cout << "Accepted swaping el " << std::distance(goodies->begin(), it1) << " with " <<  std::distance(goodies->begin(), it2) << " value change: " << valueChange <<  std::endl;
    std::iter_swap(it1, it2);
    totalWeight += weightChange;
    totalValue += valueChange;

    weightChange = 0;
    valueChange = 0;

}

void NeighborhoodSearcher::ignoreChange() {
    //std::cout << "ignored swaping with value change " << valueChange <<  std::endl;

    weightChange = 0;
    valueChange = 0;
}

void NeighborhoodSearcher::setMaxweight(unsigned int m) {
    maxWeight = m;
}

double NeighborhoodSearcher::avgImprovement() {
    return (double) costsum / improvements;
}

