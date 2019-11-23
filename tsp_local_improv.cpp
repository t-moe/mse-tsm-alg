//
// Created by timo on 11/23/19.
//

#include <vector>
#include <cstdint>
#include <iostream>
#include "tsp_local_improv.h"
#include "tsp_utilities.h"
#include "DecisionMaker.h"
#include "TSPOneOptNeighborhoodSearcher.h"


extern "C" {

/* Returns the length of the tour built                                       */
double tsp_local_improv(unsigned n,                   /* Number of cities */
                            double **d,                    /* Distance matrix */
                            unsigned *solution) /* -->Out Order of the cities */
{
    std::vector<unsigned> sol(n, 0);
    for (uint32_t i = 0; i < n; i++) { // copy current solution
        sol[i] = solution[i];
    }

    TSPOneOptNeighborhoodSearcher ns;
    DecisionMaker dm(36,100 * n, 20, 0.9, 0.9, 0.99, 2 );

    ns.setTSP(sol, d);
    ns.improveSolution(dm);
    auto improvedSolution= ns.getBestSolution();
    std::cout << "avg accepted improvement " << ns.avgImprovement() << std::endl;


    for (uint32_t i = 0; i < n; i++) { // copy current solution
        solution[i] = improvedSolution[i];
    }

    return tsp_length(n, d, solution);
}



};
