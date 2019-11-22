#include "tsp_utilities.h"
#include <stdint.h>

#include <vector>
#include <memory>

#include <algorithm>
#include <random>


void nearest_neighbor(unsigned start, std::vector<unsigned>& avail, double **d, std::vector<unsigned>& solution)
{
    unsigned n = avail.size() +1;
    solution.clear();
    solution.reserve(n);
    solution.push_back(start);
    unsigned current = start;

    for (int i = 1; i < n; i++)
    {

        double bestneibcost= infinite;
        std::vector<unsigned>::iterator bestneib = avail.end();

        for(auto it = avail.begin(); it!=avail.end(); it++) {
            if(d[current][*it] <  bestneibcost) {
                bestneibcost = d[current][*it];
                bestneib = it;
            }
        }
        current = *bestneib;
        avail.erase(bestneib);

        solution.push_back(current);
    }

    //might be wrong since it's not the complete path
    //return tsp_length(n, d, solution.data());
}

#ifdef __cplusplus
extern "C" {
#endif


/* Returns the length of the tour built                                       */
double tsp_nearest_neighbor(unsigned n,                   /* Number of cities */
                       double **d,                    /* Distance matrix */
                       unsigned *solution) /* -->Out Order of the cities */
{

    std::vector<unsigned> avail(n-1, 0);
    std::vector<unsigned> sol;

    unsigned start = 0;
    for (uint32_t i = 0; i < n-1; i++) { // all except start
        avail[i] = 1 + i;
    }

    nearest_neighbor(start, avail, d, sol);
    for (int i = 0; i < n; i++)
    {
        solution[i] = sol[i];
    }

    return tsp_length(n, d, solution);
}




#ifdef __cplusplus
};
#endif
