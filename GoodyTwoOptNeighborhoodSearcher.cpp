//
// Created by timo on 11/22/19.
//

#include <cstdlib>
#include <iostream>
#include "GoodyTwoOptNeighborhoodSearcher.h"
#include "NeighborhoodSearcher.h"

void GoodyTwoOptNeighborhoodSearcher::setGoodies(std::vector<Goody> &goodyRef) {
    this->goodies = &goodyRef;
    calculateTotals();
}

void GoodyTwoOptNeighborhoodSearcher::calculateTotals() {
    totalWeight = 0;
    totalValue = 0;
    for(auto it= goodies->begin(); it != goodies->end(); it++) {
        if(totalWeight + it->weight > maxWeight) {
            break;
        } else {
            totalWeight += it->weight;
            totalValue += it->value;
        }
    }
}


bool GoodyTwoOptNeighborhoodSearcher::cont() {

    do {
        //pick an element thats from the whole list
        it1 = goodies->begin();
        std::advance(it1, rand() % goodies->size());

        //pick a second element from the whole list
        it2 = goodies->begin();
        std::advance(it2,  rand() % goodies->size());

        //calculate new items/weight/value inside
        unsigned  newTotalWeight = 0;
        unsigned  newTotalValue = 0;
        for(auto it= goodies->begin(); it!= goodies->end(); it++) {
            auto it2lookat = it;
            if(it==it1) {
                it2lookat = it2;
            } else if (it == it2) {
                it2lookat = it1;
            }

            if(newTotalWeight + it2lookat->weight > maxWeight) {
                break;
            } else {
                newTotalWeight += it2lookat->weight;
                newTotalValue += it2lookat->value;
            }
        }

        valueChange = newTotalValue - totalValue;
        weightChange = newTotalWeight - totalWeight;

    } while(valueChange==0 && weightChange==0);

    return true;
}


bool GoodyTwoOptNeighborhoodSearcher::acceptChange() {
    if(valueChange == 0 && weightChange==0) {
        return false;
    }
    //std::cout << "Accepted swaping el " << std::distance(goodies->begin(), it1) << " with " <<  std::distance(goodies->begin(), it2) << " value change: " << valueChange <<  std::endl;
    std::iter_swap(it1, it2);
    totalWeight += weightChange;
    totalValue += valueChange;

    weightChange = 0;
    valueChange = 0;

    return true;

}

void GoodyTwoOptNeighborhoodSearcher::ignoreChange() {
    //std::cout << "ignored swaping with value change " << valueChange <<  std::endl;

    weightChange = 0;
    valueChange = 0;
}

void GoodyTwoOptNeighborhoodSearcher::setMaxweight(unsigned int m) {
    maxWeight = m;
}


double GoodyTwoOptNeighborhoodSearcher::getCostChange() {
    return valueChange;
}

std::vector<Goody> GoodyTwoOptNeighborhoodSearcher::getBestSolution() {
    return bestsol;
}

bool GoodyTwoOptNeighborhoodSearcher::saveAsBestSolution() {
    bestsol = *goodies;
    return true;
}

bool GoodyTwoOptNeighborhoodSearcher::isBetterCost(double c1, double c2) {
    return c1 > c2;
}

bool GoodyTwoOptNeighborhoodSearcher::restoreBestSolution() {
    *goodies = bestsol;
    calculateTotals();
    valueChange = 0;
    weightChange = 0;
    return true;
}
