#include <stdint.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "NeighborhoodSearcher.h"
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


std::vector<Goody> greedy(std::vector<Goody>& goodies, unsigned maxWeight, std::function<std::vector<Goody>::const_iterator(const std::vector<Goody>& goodies)> goodiePicker)
{
    std::vector<Goody> sol;
    while(goodies.size()!=0 /*&& getWeight(sol) < maxWeight*/) {
        auto goodyIt = goodiePicker(goodies);
        sol.push_back(*goodyIt);
        goodies.erase(goodyIt);
    }
    //if (getWeight(sol) > maxWeight) {
     //   sol.erase(std::prev(sol.end(),1));
    //}
    return sol;
}


std::vector<Goody>  improveSolution(std::vector<Goody> solution, unsigned int maxWeight,  NeighborhoodSearcher& neighborhoodSearcher, DecisionMaker& decisionMaker) {
    neighborhoodSearcher.setMaxweight(maxWeight);
    neighborhoodSearcher.setGoodies(solution);

    double bestcost = 0;
    double cost = 0;
    std::vector<Goody> bestsol;
    while(neighborhoodSearcher.cont() && decisionMaker.cont()) {
        double costChange = neighborhoodSearcher.getCostChange();
        if(decisionMaker.shouldTake(costChange)) {
            neighborhoodSearcher.acceptChange();
            cost += costChange;
            if(cost > bestcost) {
                bestcost = cost;
                bestsol = solution;
            }
        } else {
            neighborhoodSearcher.ignoreChange();
        }
    }
    std::cout << "Cost improved " << bestcost<< std::endl;
    return bestsol;
}






int main() {

    auto pickMostValueable = [](const std::vector<Goody>& goodies) {
        return std::max_element(goodies.begin(), goodies.end(),
                [](const Goody& a, const Goody& b) { return a.weight < b.weight; });
    };

    auto pickBestRate = [](const std::vector<Goody>& goodies) {
        return std::max_element(goodies.begin(), goodies.end(),
                [](const Goody& a, const Goody& b) { return static_cast<double>(a.value)/a.weight < static_cast<double>(b.value)/b.weight; });
    };

    auto goodyDataset = getn24dataset();
    auto maxWeight = goodyDataset.first;
    auto remainingGoods = goodyDataset.second;

    //Weight 6172204/6404180 Value 12674883
    //auto sol = greedy(remainingGoods, maxWeight, pickMostValueable);

    //Weight 6289089/6404180 Value 13346220
    auto sol = greedy(remainingGoods, maxWeight, pickBestRate);

    unsigned weight = getWeight(sol, maxWeight);
    unsigned value = getValue(sol, maxWeight);
    std::cout << "Weight " << weight << "/" << maxWeight << " Value " << value << std::endl;
    std::cout << "Goodies in sack:" << std::endl;

    /*for(auto g: sol) {
        std::cout << "Value: " << g.value << " Weight:" << g.weight << " Value/weight: "<< static_cast<double>(g.value)/g.weight <<std::endl;
    }*/


    NeighborhoodSearcher ns;
    DecisionMaker dm;

    //sol.insert(sol.end(), remainingGoods.begin(), remainingGoods.end());
    auto improvedSolution= improveSolution(sol, maxWeight, ns, dm );

    weight = getWeight(improvedSolution, maxWeight);
    value = getValue(improvedSolution, maxWeight);
    std::cout << "Weight " << weight << "/" << maxWeight << " Value " << value << std::endl;
    //std::cout << "Goodies in sack:" << std::endl;

    /*for(auto g: sol) {
        std::cout << "Value: " << g.value << " Weight:" << g.weight << " Value/weight: "<< static_cast<double>(g.value)/g.weight <<std::endl;
    }*/





}



