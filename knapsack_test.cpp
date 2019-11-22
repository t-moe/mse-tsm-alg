#include <stdint.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iostream>


struct Goody {
    unsigned weight;
    unsigned value;
    bool operator == ( const Goody& rhs) {
        return this->weight == rhs.weight && this->value == rhs.value;
    }
};

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

unsigned getWeight(const std::vector<Goody>& goodies) {
    return std::accumulate(goodies.begin(), goodies.end(), 0, [](unsigned sum, const Goody& g) {return sum+g.weight;} );
}

unsigned getValue(const std::vector<Goody>& goodies) {
    return std::accumulate(goodies.begin(), goodies.end(), 0, [](unsigned sum, const Goody& g) {return sum+g.value;} );
}


std::vector<Goody> greedy(std::vector<Goody> goodies, unsigned maxWeight, std::function<Goody(const std::vector<Goody>& goodies)> goodiePicker)
{
    std::vector<Goody> sol;
    while(goodies.size()!=0 && getWeight(sol) < maxWeight) {
        auto goody = goodiePicker(goodies);
        sol.push_back(goody);
        goodies.erase(std::find(goodies.begin(), goodies.end(), goody));
    }
    if (getWeight(sol) > maxWeight) {
        sol.erase(std::prev(sol.end(),1));
    }
    return sol;
}


int main() {

    auto pickMostValueable = [](const std::vector<Goody>& goodies) {
        return *std::max_element(goodies.begin(), goodies.end(),
                [](const Goody& a, const Goody& b) { return a.weight < b.weight; });
    };

    auto pickBestRate = [](const std::vector<Goody>& goodies) {
        return *std::max_element(goodies.begin(), goodies.end(),
                [](const Goody& a, const Goody& b) { return static_cast<double>(a.value)/a.weight < static_cast<double>(b.value)/b.weight; });
    };

    auto goodyDataset = getn24dataset();

    //Weight 6172204/6404180 Value 12674883
    //auto sol = greedy(goodyDataset.second, goodyDataset.first, pickMostValueable);

    //Weight 6289089/6404180 Value 13346220
    auto sol = greedy(goodyDataset.second, goodyDataset.first, pickBestRate);

    unsigned weight = getWeight(sol);
    unsigned value = getValue(sol);
    std::cout << "Weight " << weight << "/" << goodyDataset.first << " Value " << value << std::endl;
    std::cout << "Goodies in sack:" << std::endl;

    for(auto g: sol) {
        std::cout << "Value: " << g.value << " Weight:" << g.weight << " Value/weight: "<< static_cast<double>(g.value)/g.weight <<std::endl;
    }



}



