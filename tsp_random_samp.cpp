#include "tsp_utilities.h"
#include <stdint.h>

#include <vector>

#include <algorithm>
#include <random>


#ifdef __cplusplus
extern "C" {
#endif

/** Greedy insertion in arbitrary order at the best place in a partial tour  **/
/* Returns the length of the tour built                                       */
double tsp_random_samp(unsigned n,                   /* Number of cities */
                       double **d,                    /* Distance matrix */
                       unsigned *solution) /* -->Out Order of the cities */
{

    uint64_t tries = 50000000;
    std::vector<unsigned> sol(n, 0);
    std::vector<unsigned> bestsol(n, 0);
    double bestcost= infinite;

    for (uint32_t i = 0; i < n; i++) {
        sol[i] = i;
    }

    auto rng = std::default_random_engine {};

    for (uint64_t t = 0; t < tries; t++) {
        std::shuffle(std::begin(sol), std::end(sol), rng);
        double cost =  tsp_length(n, d, sol.data());
        if(cost < bestcost) {
            bestcost = cost;
            bestsol = sol;
        }
    }

    for (int i = 0; i < n; i++)
    {
        solution[i] = bestsol[i];
    }

    return bestcost;
}




#ifdef __cplusplus
};
#endif
