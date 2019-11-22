//
// Created by timo on 11/20/19.
//

#ifndef EXERCISES2_CODE_TSP_LOCAL_GREEDY_H
#define EXERCISES2_CODE_TSP_LOCAL_GREEDY_H

#ifdef __cplusplus
extern "C" {
#endif

double tsp_local_greedy(unsigned n,                   /* Number of cities */
                 double **d,                    /* Distance matrix */
                 unsigned *solution);/* -->Out Order of the cities */

#ifdef __cplusplus
};
#endif


#endif //EXERCISES2_CODE_TSP_LOCAL_GREEDY_H
