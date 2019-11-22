#ifndef TSP_UTILITIES

#define TSP_UTILITIES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* The length of any solution is supposed to be lower than this constant      */
#define infinite 2.2e222
#define true 1
#define false 0

/* Lowest cost difference considered for different solutions.                 */
/* To avoid considering 2 same solutions as different due to                  */
/* numerical imprecisions. Initial value: relative.                           */
/* Must be multiplied by longest distance before use (after data reading)     */
extern double epsilon;

/******************************** Utilities ***********************************/
double seconds(clock_t cpu);

/* Random number generator, proposed by Lecuyer                               */
double rando(void);

/********** Returns a random integer between low and high (included) **********/
int unif(int low, int high);

/************************* Exchange two unsigned  *****************************/
void swap(unsigned * a, unsigned * b);

/***** Generate a random table of n unsigned with all elements of [0, n-1] ****/
void generate_random_permutation(unsigned n, unsigned* p);

/********* Compute the Eulerian distance between (x1,y1) and (x2, y2) *********/
double dist(double x1, double y1, double x2, double y2);

/** Returns 0 if any elements appears exactly once in the permutation given  **/
int check_permutation(unsigned n, unsigned* p);

/************************ Compute the cost of a TSP tour **********************/
#ifdef __cplusplus
extern "C" {
#endif
    double tsp_length(unsigned n,                             /* Number of cities */
                  double** d,                              /* Distance matrix */
                  unsigned* solution);                 /* Order of the cities */

#ifdef __cplusplus
};
#endif

/** Initialization of a data structure for efficiently performing 2-opt moves */
void build_2opt_data_structure(unsigned n,
                               unsigned* solution,
                               unsigned* t);

/**************** Generate a postscript file drawing a tour *******************/
void draw(unsigned n,                                     /* Number of cities */
          double* x, double* y,                  /* Coordinates of the cities */
          unsigned* sol,                                          /* Solution */
          char* file_name);     /* Name of the PostScript file (.ps expected) */

#endif
