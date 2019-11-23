#include <stdint.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "GoodyTwoOptNeighborhoodSearcher.h"
#include "DecisionMaker.h"
#include "Goody.h"


std::pair<unsigned,std::vector<Goody>> getn24dataset() {
    return std::pair<unsigned,std::vector<Goody>>(6404180,{
            {382745, 825594},
            {799601, 1677009},
            {909247, 1676628},
            {729069, 1523970},
            {467902, 943972},
            {44328,  97426},
            {34610,  69666},
            {698150, 1296457},
            {823460, 1679693},
            {903959, 1902996},
            {853665, 1844992},
            {551830, 1049289},
            {610856, 1252836},
            {670702, 1319836},
            {488960, 953277},
            {951111, 2067538},
            {323046, 675367},
            {446298, 853655},
            {931161, 1826027},
            {31385,  65731},
            {496951, 901489},
            {264724, 577243},
            {224916, 466257},
            {169684, 369261}});
}

unsigned getWeight(const std::vector<Goody>& goodies, unsigned maxWeight) {
    unsigned int weight=0;
    for(auto& g: goodies) {
        if(weight + g.weight <= maxWeight) {
            weight += g.weight;
        } else {
            break;
        }
    }
    return weight;
}

unsigned getValue(const std::vector<Goody>& goodies, unsigned maxWeight) {
    //return std::accumulate(goodies.begin(), goodies.end(), 0, [](unsigned sum, const Goody& g) {return sum+g.value;} );
    unsigned int weight=0;
    unsigned int value=0;
    for(auto& g: goodies) {
        if(weight + g.weight <= maxWeight) {
            weight += g.weight;
            value += g.value;
        } else {
            break;
        }
    }
    return value;
}


std::vector<Goody> greedy(std::vector<Goody>& goodies, std::function<std::vector<Goody>::const_iterator(const std::vector<Goody>& goodies)> goodiePicker)
{
    std::vector<Goody> sol;
    while(goodies.size()!=0) {
        auto goodyIt = goodiePicker(goodies);
        sol.push_back(*goodyIt);
        goodies.erase(goodyIt);
    }

    return sol;
}




int knap_main() {
    srand(time(NULL));

    auto pickMostValueable = [](const std::vector<Goody>& goodies) {
        return std::max_element(goodies.begin(), goodies.end(),
                [](const Goody& a, const Goody& b) { return a.value < b.value; });
    };

    auto pickBestRate = [](const std::vector<Goody>& goodies) {
        return std::max_element(goodies.begin(), goodies.end(),
                [](const Goody& a, const Goody& b) { return static_cast<double>(a.value)/a.weight < static_cast<double>(b.value)/b.weight; });
    };

    auto goodyDataset = getn24dataset();
    auto maxWeight = goodyDataset.first;
    auto remainingGoods = goodyDataset.second;

    //Weight 6172204/6404180 Value 12674883
    //auto sol = greedy(remainingGoods, pickMostValueable);

    //Weight 6289089/6404180 Value 13346220
    auto sol = greedy(remainingGoods, pickBestRate);
    //std::vector<Goody> sol = remainingGoods;
    unsigned weight = getWeight(sol, maxWeight);
    unsigned value = getValue(sol, maxWeight);
    std::cout << "Greedy Solution: Weight " << weight << "/" << maxWeight << " Value " << value << std::endl;


    GoodyTwoOptNeighborhoodSearcher ns;
    DecisionMaker dm(373868,60 * 100, 6, 0.5, 0.3, 0.9, 2 );


    ns.setMaxweight(maxWeight);
    ns.setGoodies(sol);
    ns.improveSolution(dm);
    auto improvedSolution= ns.getBestSolution();
    std::cout << "avg accepted improvement " << ns.avgImprovement() << std::endl;
    //avg improvement 79829 (positiv only)
    //avg improvement -715055 (positive + negative)

    //Cost improved 159658
    //Weight 6386705/6404180 Value 13505878

    weight = getWeight(improvedSolution, maxWeight);
    value = getValue(improvedSolution, maxWeight);
    std::cout << "Optimized Solution: Weight " << weight << "/" << maxWeight << " Value " << value << std::endl;

}



