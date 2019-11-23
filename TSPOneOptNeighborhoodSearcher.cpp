//
// Created by timo on 11/23/19.
//

#include "TSPOneOptNeighborhoodSearcher.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>


bool TSPOneOptNeighborhoodSearcher::cont() {

    do {
        auto s1 = route.begin();
        std::advance(s1, rand() % route.size());

        auto s2 = route.begin();
        std::advance(s2, rand() % route.size());

        if(std::distance(s1, s2) <2 ) continue;
        it1= std::next(s1, 1);
        if(it1 ==route.end()) {
            continue;
        }
        it2 = std::next(s2, 1);
        if(it2 ==route.end()) {
            continue;
        }


        lengthChange =  -d[*s1][*it1] - d[*s2][*it2]    + d[*s1][*s2]  + d[*it1][*it2] ;

    } while(lengthChange == 0);

    return true;
}


bool TSPOneOptNeighborhoodSearcher::acceptChange() {
    if(lengthChange == 0) {
        return false;
    }


    //std::cout << "Accepted swaping city at positions " << std::distance(route.begin(), it1) << " with " <<  std::distance(route.begin(), it2) << " length change: " << lengthChange <<  std::endl;
    std::reverse(it1, it2);

    lengthChange = 0;

    return true;

}

void TSPOneOptNeighborhoodSearcher::ignoreChange() {
    //std::cout << "ignored swaping with length change " << lengthChange <<  std::endl;
    lengthChange = 0;
}



double TSPOneOptNeighborhoodSearcher::getCostChange() {
    return lengthChange;
}

std::vector<unsigned> TSPOneOptNeighborhoodSearcher::getBestSolution() {
    return bestsol;
}

bool TSPOneOptNeighborhoodSearcher::saveAsBestSolution() {
    bestsol = route;
    return true;
}


bool TSPOneOptNeighborhoodSearcher::restoreBestSolution() {
    route = bestsol;
    lengthChange = 0;
    return true;
}

void TSPOneOptNeighborhoodSearcher::setTSP(std::vector<unsigned> route, double **d) {
    this->route = route;
    this->d = d;
}

