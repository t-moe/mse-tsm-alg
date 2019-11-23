/******************************************************************************/
/* Programme for testing various elementary metaheuristics for the symmetric  */
/* travelling salesman problem                                                */
/* All local searches are based on the 2-opt neighbourhood                    */
/* Purpose: Illustration of metaheuristics for students                       */
/* Writes PostScript files representing tours found                           */
/* File: tsp_test.c                                                           */
/* Language : c; compilers gcc and cl (visual studio) should work.
                                                                         */
/* Author and copyright : E. Taillard, HEIG-VD                                */
/* Date : 12. November 2014                                                   */

/******************************************************************************/

#include "tsp_utilities.h"
#include "tsp_greedy_insertion.h"


#include "tsp_random_samp.h"
#include "tsp_nearest_neighbor.h"
#include "tsp_pilot.h"
#include "tsp_local_greedy.h"
#include "tsp_local_improv.h"
#include <string.h>

/* For sorting a table of double by non-decreasing value */
int larger(const void *a, const void *b)
{
  if (*(double*)a > *(double*)b) return 1;
  else if (*(double*)a < *(double*)b) return -1;
  else return 0;
}

int main(void)
{ unsigned n;                                                 /* Problem size */
  unsigned* solution;   /* Permutation: order in which the cities are visited */
  double* x;                                     /* coordinates of the cities */
  double* y;
  double length;                                           /* Solution length */
  clock_t cpu;                                        /* For cpu time measure */
  double** d;                           /* Matrix of distances between cities */
  double dmax;                                         /* Most distant cities */

  /************************ data file reading *********************************/
  unsigned i, j,                                                   /* Indices */
      dummy_int;                        /* For skipping the reading of an int */
  FILE *data_file;              /* Data file, supposed in TSPLIB EUC2D format */
  char filename[80];                                     /* Name of data file */
  char trash[1000];             /* Skipping the reading up to 1000 characters */

  //printf("Data file name : \n");
  //dummy_int = scanf("%s",filename);
  // data_file = fopen(filename,"r");


    char* files [] = {
            "berlin52",
            "bier127",
            "tsp225",
            "pr1002",
            "pr2392",
            "rl5915"
    };

    for(int fn=0; fn < sizeof(files)/sizeof(char*); fn++) {
        char fname[100] = "../TSP_Instances/";
        strcpy(fname + strlen(fname), files[fn]);
        strcpy(fname + strlen(fname), ".tsp");
        printf("File: %s\n", files[fn]);


        char fname_picture[100] = "./";
        strcpy(fname_picture + strlen(fname_picture), files[fn]);
        strcpy(fname_picture + strlen(fname_picture), "_localimprov.ps");
        printf("Picture file name: %s\n", fname_picture);

        data_file = fopen(fname, "r");


        //data_file = fopen("/home/timo/study/tsmalg/Exercises2_CODE/TSP_Instances/bier127.tsp" , "r");
        //data_file = fopen("/home/timo/study/tsmalg/Exercises2_CODE/TSP_Instances/berlin52.tsp", "r");
        //data_file = fopen("/home/timo/study/tsmalg/Exercises2_CODE/TSP_Instances/pr2392.tsp", "r");
        //data_file = fopen("/home/timo/study/tsmalg/Exercises2_CODE/TSP_Instances/pr1002.tsp", "r");
        // data_file = fopen("/home/timo/study/tsmalg/Exercises2_CODE/TSP_Instances/tsp225.tsp", "r");

        /* Reading the data file. Hoping in right format!! ALMOST NO CHECKS!!       */
        dummy_int = fscanf(data_file, "%[^\n]\n", trash);
        dummy_int = fscanf(data_file, "%[^\n]\n", trash);
        dummy_int = fscanf(data_file, "%[^\n]\n", trash);
        if (fscanf(data_file, "DIMENSION : %u\n", &n))
            printf("%d\n", n);   /* Checking if the number of cities is correctly read */
        else
            return EXIT_FAILURE;
        dummy_int = fscanf(data_file, "%[^\n]\n", trash);
        dummy_int = fscanf(data_file, "%[^\n]\n", trash);

        /* Memory allocation */
        x = (double *) malloc(n * sizeof(double));
        y = (double *) malloc(n * sizeof(double));
        solution = (unsigned *) malloc(n * sizeof(unsigned));
        d = (double **) malloc(n * sizeof(double *));
        for (i = 0; i < n; i++) {
            d[i] = (double *) malloc(n * sizeof(double));
            if (!d[i]) {
                printf("Instance too large: Memory cannot be allocated!\n");
                getchar();
                getchar();
                return EXIT_FAILURE;
            }
        }

        /* Reading the cities coordinates */
        for (i = 0; i < n; i++)
            if (fscanf(data_file, "%u %lf %lf", &dummy_int, &x[i], &y[i]) != 3)
                return EXIT_FAILURE;
        fclose(data_file);
        /******************************** end reading ******************************/

        /* Compute distance matrix and absolute numerical precision */
        dmax = 0.0;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {
                d[i][j] = dist(x[i], y[i], x[j], y[j]);
                if (d[i][j] > dmax)
                    dmax = d[i][j];
            }
        epsilon *= dmax;



        //length = tsp_random_samp(n, d, solution);
        //length = tsp_nearest_neighbor(n, d, solution);
        //length = tsp_pilot(n, d, solution);
        // length = tsp_local_greedy(n, d, solution);

        cpu = clock();
        length = tsp_greedy_insertion(n, d, solution);
        printf("%d\t%e\t%e (number of cities, time, length) of greedy insertion. \n", n, seconds(cpu), length);
        draw(n, x, y, solution, "greedy.ps");

        /*cpu = clock();
        length = tsp_nearest_neighbor(n, d, solution);
        printf("%d\t%e\t%e (number of cities, time, length) of nearest neighbor. \n", n, seconds(cpu), length);
        draw(n, x, y, solution, "nneighbor.ps");

        cpu = clock();
        length = tsp_local_greedy(n, d, solution);
        printf("%d\t%e\t%e (number of cities, time, length) of local greedy insertion. \n", n, seconds(cpu), length);
        draw(n, x, y, solution, "localgreedy.ps");*/

        /*cpu = clock();
        length = tsp_pilot(n, d, solution);
        printf("%d\t%e\t%e (number of cities, time, length) of pilot. \n", n, seconds(cpu), length);
        draw(n, x, y, solution, "pilot.ps");*/

        cpu = clock();
        length = tsp_local_improv(n, d, solution);
        printf("%d\t%e\t%e (number of cities, time, length) of one local improvments. \n", n, seconds(cpu), length);
        draw(n, x, y, solution, fname_picture);


/*
  printf("2 opt first\n");
  cpu = clock();
  tsp_2opt_first(n, d, solution, &length);
  printf("%d\t%e\t%e Time and length 2opt first: \n", n, seconds(cpu), length);
  draw(n, x, y, solution, "tsp2opt.ps");
*/

/*
  printf("3 opt limited\n");
  cpu = clock();
  tsp_3opt_limited(n, d, 40, solution, &length);
  printf("%d\t%e\t%e Time and length 3-opt limited\n", n, seconds(cpu), length);
  draw(n, x, y, solution, "tsp3opt_limited.ps");
*/

/*
  printf("ejection chain\n");
  cpu = clock();
  tsp_ejection_chain(n, d, solution, &length);
  printf("%d\t%e\t%e Time and length ejection chain\n", n, seconds(cpu), length);
  draw(n, x, y, solution, "ejection_chain.ps");
*/

/* 
  printf("noising\n");  // Optimizing solution by SA
  cpu = clock();
  tsp_noising(n, d, solution, &length, 80*dmax/n, 800*dmax/(n*n), 0.99);
  tsp_daemon(n, d, solution, &length, 100*n, 1.2*dmax/sqrt(n));
  length = tsp_GRASP(n, d, solution, 1000, 0.4);
  tsp_3opt_first(n, d, solution, &length);
  printf("%d\t%e\t%e Time and length noising\n", n, seconds(cpu), length);
  draw(n, x, y, solution, "grasp.ps");
*/

    }
  printf("Press return to end ...");
  getchar(); getchar();
  return EXIT_SUCCESS;
}
