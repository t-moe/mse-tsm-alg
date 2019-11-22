/** Greedy insertion in arbitrary order at the best place in a partial tour  **/
/* Returns the length of the tour built                                       */
double tsp_greedy_insertion(unsigned n,                   /* Number of cities */
                            double** d,                    /* Distance matrix */
                            unsigned* solution);/* -->Out Order of the cities */
