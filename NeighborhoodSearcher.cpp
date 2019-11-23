//
// Created by timo on 11/22/19.
//

#include <cstdlib>
#include <iostream>
#include "NeighborhoodSearcher.h"

void GoodyTwoOptNeighborhoodSearcher::setGoodies(std::vector<Goody> &goodyRef) {
    this->goodies = &goodyRef;
    totalWeight = 0;
    totalValue = 0;
    //firstElementOutside = goodies->begin();
    //elementsInside = 0;
    for(auto it= goodies->begin(); it!= goodies->end(); it++) {
        if(totalWeight + it->weight > maxWeight) {
            //firstElementOutside = it;
            break;
        } else {
            //elementsInside++;
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


    } while((totalWeight + weightChange > maxWeight) || (valueChange==0 && weightChange==0));


    //if(valueChange > 0) {
        improvements++;
        costsum += valueChange;
   // }

    return true;
}

double GoodyTwoOptNeighborhoodSearcher::getCostChange() {
    return valueChange;
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

}

void GoodyTwoOptNeighborhoodSearcher::ignoreChange() {
    //std::cout << "ignored swaping with value change " << valueChange <<  std::endl;

    weightChange = 0;
    valueChange = 0;
}

void GoodyTwoOptNeighborhoodSearcher::setMaxweight(unsigned int m) {
    maxWeight = m;
}

double GoodyTwoOptNeighborhoodSearcher::avgImprovement() {
    return (double) costsum / improvements;
}

