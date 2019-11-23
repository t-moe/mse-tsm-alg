//
// Created by timo on 11/23/19.
//

#include "TSPOneOptNeighborhoodSearcher.h"
#include <cstdlib>
#include <iostream>



bool TSPOneOptNeighborhoodSearcher::cont() {

    do {
        it1 = route.begin();
        std::advance(it1, rand() % route.size());

        it2 = std::next(it1, 1);
        if(it2== route.end()) {
            it2 = route.begin();
        }

        auto prev = std::prev(route.end(),1);
        if(it1!=route.begin()) {
            prev = std::prev(it1,1);
        }

        auto next = std::next(it2, 1);
        if(next ==route.end()) {
            next = route.begin();
        }


        lengthChange =  -d[*prev][*it1]  /*-d[*it1][*it2] */ - d[*it2][*next]    + d[*prev][*it2]  + /* d[*it2][*it1]*/ + d[*it1][*next] ;

    } while(lengthChange == 0);

    return true;
}


bool TSPOneOptNeighborhoodSearcher::acceptChange() {
    if(lengthChange == 0) {
        return false;
    }


    //std::cout << "Accepted swaping city at positions " << std::distance(route.begin(), it1) << " with " <<  std::distance(route.begin(), it2) << " length change: " << lengthChange <<  std::endl;
    std::iter_swap(it1, it2);

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

