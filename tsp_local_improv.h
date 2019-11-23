//
// Created by timo on 11/23/19.
//

#ifndef EXERCISES2_CODE_TSP_LOCAL_IMPROV_H
#define EXERCISES2_CODE_TSP_LOCAL_IMPROV_H


#ifdef __cplusplus
//double nearest_neighbor(unsigned start, std::vector<unsigned>& avail, double **d, std::vector<unsigned>& solution);
extern "C" {
#endif

double tsp_local_improv(unsigned n,                   /* Number of cities */
                            double **d,                    /* Distance matrix */
                            unsigned *solution);/* -->Out Order of the cities */

#ifdef __cplusplus
};
#endif


#endif //EXERCISES2_CODE_TSP_LOCAL_IMPROV_H
