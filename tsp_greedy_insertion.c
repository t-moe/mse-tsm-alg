#include "tsp_utilities.h"
/** Greedy insertion in arbitrary order at the best place in a partial tour  **/
/* Returns the length of the tour built                                       */
double tsp_greedy_insertion(unsigned n,                   /* Number of cities */
                            double** d,                    /* Distance matrix */
                            unsigned* solution) /* -->Out Order of the cities */
{ unsigned* next;                                  /* Successors of each city */
  unsigned i, j, j_kept=-1;
  double delta, dist_ins;          /* Cost of inserting city j, cost retained */

  next = (unsigned*) malloc(n * sizeof(unsigned));
  next[0] = 1; next[1] = 0;               /* Initial partial tour 0 -> 1 -> 0 */
  for (i = 2; i < n; i = i + 1)
  { dist_ins = infinite;
    for(j = 0; j < i; j = j+1)
      {
        delta = d[j][i] + d[i][next[j]] - d[j][next[j]];
       if (delta + epsilon < dist_ins)
        {
           dist_ins = delta;
           j_kept = j;
        };
      };
    next[i] = next[j_kept];
    next[j_kept] = i;
  }

  /* Rebuild solution */
  j = 0;
  for (i = 0; i < n; i = i + 1)
   {solution[i] = j; j = next[j];}

  free(next);
  return tsp_length(n, d, solution);
 } /* tsp_greedy_insertion */
