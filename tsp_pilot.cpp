//
// Created by timo on 11/14/19.
//

#include <vector>
#include "tsp_pilot.h"
#include "tsp_nearest_neighbor.h"
#include "tsp_utilities.h"
#include <stdint.h>
#include <algorithm>



double pilot(unsigned start, std::vector<unsigned>& avail, double **d, std::vector<unsigned>& solution) {

    unsigned  n = avail.size() +1;
    std::vector<unsigned> tmp;
    tmp.reserve(n);

    solution[0] = start;


    unsigned current;

    for (int i = 1; i < n; i++)
    {

        double bestneibcost= infinite;
        std::vector<unsigned>::iterator bestneib = avail.end();

        for(auto it = avail.begin(); it!=avail.end(); it++) {
            auto availcpy = avail;
            availcpy.erase(std::find(availcpy.begin(), availcpy.end(), *it));
            nearest_neighbor(*it, availcpy, d, tmp);
            for(int j = 0; j<tmp.size(); j++) {
                solution[i+j] = tmp[j];
            }

            double cost = tsp_length(n, d, solution.data());
            if(cost <  bestneibcost) {
                bestneibcost = cost;
                bestneib = it;
            }
        }
        current = *bestneib;
        avail.erase(bestneib);

        solution[i] = current;
    }

    return tsp_length(n, d, solution.data());
}



#ifdef __cplusplus
extern "C" {
#endif

double tsp_pilot(unsigned n,                   /* Number of cities */
                 double **d,                    /* Distance matrix */
                 unsigned *solution) {/* -->Out Order of the cities */




    std::vector<unsigned> avail(n-1, 0);
    std::vector<unsigned> tmpsol(n, 0);

    std::vector<unsigned> bestsol(n, 0);
    double bestcost = infinite;

    for (int i = 0; i < n; i++)
    {

        for (uint32_t j = 0; j < n; j++) { // all except start
            if (j<i)
                avail[j] = j;
            else if (j>i) {
                avail[j-1] = j;
            }
        }

        auto availcpy = avail;
        double cost =  pilot(i, availcpy, d, tmpsol);
        if(cost < bestcost) {
            bestcost = cost;
            bestsol  = tmpsol;
        }
        //printf("cost: %f\n", cost);

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