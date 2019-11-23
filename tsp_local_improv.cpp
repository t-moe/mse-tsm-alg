//
// Created by timo on 11/23/19.
//

#include "tsp_local_improv.h"
#include "tsp_utilities.h"


extern "C" {

/* Returns the length of the tour built                                       */
double tsp_local_improv(unsigned n,                   /* Number of cities */
                            double **d,                    /* Distance matrix */
                            unsigned *solution) /* -->Out Order of the cities */
{

    /*std::vector<unsigned> avail(n-1, 0);
    std::vector<unsigned> sol;

    unsigned start = 0;
    for (uint32_t i = 0; i < n-1; i++) { // all except start
        avail[i] = 1 + i;
    }

    nearest_neighbor(start, avail, d, sol);
    for (int i = 0; i < n; i++)
    {
        solution[i] = sol[i];
    }*/

    return tsp_length(n, d, solution);
}



};
