#include "tsp_utilities.h"

/* Lowest cost difference considered for different solutions.                 */
/* To avoid considering 2 same solutions as different due to                  */
/* numerical imprecisions. Initial value: relative.                           */
double epsilon = 1.0e-14;

/******************************** Utilities ***********************************/
double seconds(clock_t cpu)
{ return (double)(clock() - cpu) / CLOCKS_PER_SEC;}

/* Random number ]0, 1] generator, proposed by Lecuyer, replace bad rand()    */
double rando(void)
{ static int x10 = 12345, x11 = 67890, x12 = 13579,          /* initial value */
             x20 = 24680, x21 = 98765, x22 = 43210;               /* of seeds */
  const int m = 2147483647; const int m2 = 2145483479;
  const int a12= 63308; const int q12=33921; const int r12=12979;
  const int a13=-183326; const int q13=11714; const int r13=2883;
  const int a21= 86098; const int q21=24919; const int r21= 7417;
  const int a23=-539608; const int q23= 3976; const int r23=2071;
  const double invm = 4.656612873077393e-10;
  int h, p12, p13, p21, p23;
  h = x10/q13; p13 = -a13*(x10-h*q13)-h*r13;
  h = x11/q12; p12 =  a12*(x11-h*q12)-h*r12;
  if (p13 < 0) p13 = p13 + m; if (p12 < 0) p12 = p12 + m;
  x10 = x11; x11 = x12; x12 = p12-p13; if (x12 < 0) x12 = x12 + m;
  h = x20/q23; p23 = -a23*(x20-h*q23)-h*r23;
  h = x22/q21; p21 =  a21*(x22-h*q21)-h*r21;
  if (p23 < 0) p23 = p23 + m2; if (p21 < 0) p21 = p21 + m2;
  x20 = x21; x21 = x22; x22 = p21-p23; if(x22 < 0) x22 = x22 + m2;
  if (x12 < x22) h = x12 - x22 + m; else h = x12 - x22;
  if (h == 0) return(1.0);
  else return(h*invm);
}

/********** Returns a random integer between low and high (included) **********/
int unif(int low, int high)
 {return low + (int)((double)(high - low + 1) * rando()) ;}

/**************************** Exchange two int  *******************************/
void swap(unsigned * a, unsigned * b)
{unsigned temp = *a; *a = *b; *b = temp;}

/***** Generate a random table of n unsigned with all elements of [0, n-1] ****/
void generate_random_permutation(unsigned n, unsigned* p)
{ unsigned i;
  for (i = 0; i < n; i = i+1) p[i] = i;
  for (i = 0; i <  n-1; i = i+1) swap(&p[i], &p[unif(i, n-1)]);
}

/********* Compute the Eulerian distance between (x1,y1) and (x2, y2) *********/
double dist(double x1, double y1, double x2, double y2)
{return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));}

/** Returns 0 if any elements appears exactly once in the permutation given  **/
int check_permutation(unsigned n, unsigned* p)
{ int * chosen;
  unsigned i;
  chosen = (int*) malloc(n * sizeof(int));

  for (i = 0; i < n; i++)
    chosen[i] = false;
  for (i = 0; i < n; i++)
    if (p[i] >= n)
    { printf("Element outside indices %d %d\n", i, p[i]); return 1;}
    else if (chosen[p[i]])
    { printf("Twice element %d %d\n", i, p[i]); return 1;}
    else
      chosen[p[i]] = true;

  free(chosen);
  return 0;
}

/************************ Compute the cost of a TSP tour **********************/
double  tsp_length(unsigned n,                             /* Number of cities */
                  double** d,                              /* Distance matrix */
                  unsigned* solution)                  /* Order of the cities */
{ unsigned i;
  double sum = 0.0;
  for (i = 0; i < n-1; i++)
    sum += d[solution[i]][solution[i+1]];
  return sum + d[solution[n-1]][solution[0]];
}

/** Initialization of a data structure for efficiently performing 2-opt moves */
/* Doubly connected edge list containing the successor of each city, either   */
/* performing the tour in one direction or in the other. Implemented with     */
/* a table of 2n elements. The neighbours of the ith city are the elements    */
/* of t[2i] and t[2i+1]. The cities adjacent to city i are t[2i]/2 and        */
/* So, if city i is between cities j and k, t[2i] will contain either 2j or   */
/* 2k or 2j+1 or 2k+1. The fast expression t[i]>>2 can be used to evaluate    */
/* t[i]/2 and the index of the twin of city i is i+1-2*(i%2), that can be     */
/*  fast evaluated with the expression i^1                                    */
void build_2opt_data_structure(unsigned n,
                               unsigned* solution,
                               unsigned* t)
{ unsigned i;
  /* Forward tour */
  for (i = 0; i < n-1; i = i + 1)
    t[2*solution[i]] = 2*solution[i+1];
  t[2*solution[n-1]] = 2*solution[0];

  /* Backward tour */
  for (i = 1; i < n; i = i + 1)
    t[2*solution[i]+1] = 2*solution[i-1]+1;
  t[2*solution[0]+1] = 2*solution[n-1]+1;
}


/**************** Generate a postscript file drawing a tour *******************/
void draw(unsigned n,                                     /* Number of cities */
          double* x, double* y,                  /* Coordinates of the cities */
          unsigned* sol,                                          /* Solution */
          char* file_name)      /* Name of the PostScript file (.ps expected) */
{ const unsigned xpsmin = 29;        /* Size of the drawing: A4, expressed in */
  const unsigned ypsmin = 29;                                /* 1/72th inches */
  const unsigned ypsmax = 813;
  const unsigned xpsmax = 567;
  unsigned i;
  double length = 0.0;

  FILE *postscript_file;
  double xmin, xmax, ymin, ymax;     /* Min and max coordinates of the cities */
  double scale;                      /* Scale between real and PS coordinates */

  for (i = 0; i < n; i++)
    length += dist(x[sol[i]], y[sol[i]], x[sol[(i+1)%n]], y[sol[(i+1)%n]]);

  xmin = xmax = x[0];
  ymin = ymax = y[0];
  for (i = 1; i < n; i++)
  { if (xmin > x[i]) xmin = x[i]; if (xmax < x[i]) xmax = x[i];
    if (ymin > y[i]) ymin = y[i]; if (ymax < y[i]) ymax = y[i];
  }
  if ((double)(xpsmax - xpsmin)/(xmax - xmin) <
      (double)(ypsmax - ypsmin)/(ymax - ymin) )
    scale = 0.95*(double)(xpsmax - xpsmin)/(xmax - xmin);
  else
    scale = 0.95*(double)(ypsmax - ypsmin)/(ymax - ymin);

  postscript_file = fopen(file_name,"w");
  fprintf(postscript_file, "%%!PS-Adobe-2.0\n");
  fprintf(postscript_file,
          "gsave\n %d %d translate\n%e %e scale \n %e %e translate\n",
          xpsmin, ypsmin, scale, scale, -xmin, -ymin);
  fprintf(postscript_file, "0.7 0.3 0.4 setrgbcolor\n");
  fprintf(postscript_file, "%f setlinewidth\n", (xmax - xmin)/(20.0*sqrt(n)));
  fprintf(postscript_file, "newpath %f %f moveto\n", x[sol[0]], y[sol[0]]);
  for (i = 1; i < n; i++)
    fprintf(postscript_file, "%f %f lineto\n", x[sol[i]], y[sol[i]]);
  fprintf(postscript_file, "closepath stroke\n");
  fprintf(postscript_file, "0.8 0.7 0.9 setrgbcolor\n");
  for (i = 0; i < n; i++)
    fprintf(postscript_file, "%f %f %f 0 360 arc fill\n",
            x[sol[i]], y[sol[i]], (xmax - xmin)/(15.0*sqrt(n)));
  fprintf(postscript_file, "0.0 0.0 0.0 setrgbcolor\n");
  fprintf(postscript_file, "%f setlinewidth\n", (xmax - xmin)/(400.0*sqrt(n)));
  for (i = 0; i < n; i++)
    fprintf(postscript_file, "%f %f %f 0 360 arc stroke\n",
            x[sol[i]], y[sol[i]], (xmax - xmin)/(15.0*sqrt(n)));
  fprintf(postscript_file, "/Times-Roman-iso findfont %f scalefont setfont\n",
          (xmax - xmin)/30.0);
  fprintf(postscript_file, "%f %f moveto (%f) show\n",
          xmin, ymin, length);
  fprintf(postscript_file, "grestore \n showpage\n");

  fprintf(postscript_file, "%%%%EOF");
  fclose(postscript_file);
}
