//
// Created by timo on 11/22/19.
//

#ifndef EXERCISES2_CODE_TSPONEOPTSEARCHER_H
#define EXERCISES2_CODE_TSPONEOPTSEARCHER_H


#include <vector>
#include "Goody.h"
#include "NeighborhoodSearcher.h"

class TSPOneOptNeighborhoodSearcher : public NeighborhoodSearcher {
    public:
    void setTSP(std::vector<unsigned> route, double **d);
    std::vector<unsigned> route;
    double **d;

    bool cont() override;
    double getCostChange() override;
    bool acceptChange() override;
    void ignoreChange() override;


    std::vector<unsigned>::iterator it1;
    std::vector<unsigned>::iterator it2;
    double lengthChange = 0;

    std::vector<unsigned> bestsol;
    std::vector<unsigned> getBestSolution();
    bool saveAsBestSolution() override;
    bool restoreBestSolution() override;

};



#endif //EXERCISES2_CODE_TSPONEOPTSEARCHER_H
