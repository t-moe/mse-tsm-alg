//
// Created by timo on 11/14/19.
//

#ifndef EXERCISES2_CODE_TSP_PILOT_H
#define EXERCISES2_CODE_TSP_PILOT_H


#ifdef __cplusplus
extern "C" {
#endif

double tsp_pilot(unsigned n,                   /* Number of cities */
                            double **d,                    /* Distance matrix */
                            unsigned *solution);/* -->Out Order of the cities */

#ifdef __cplusplus
};
#endif


#endif //EXERCISES2_CODE_TSP_PILOT_H
