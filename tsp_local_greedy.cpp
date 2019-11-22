//
// Created by timo on 11/20/19.
//

#include "tsp_local_greedy.h"
#include <vector>
#include <forward_list>
#include "tsp_utilities.h"
#include <stdint.h>
#include <algorithm>


/*
double local_greedy(unsigned start, std::vector<unsigned>& avail, double **d, std::vector<unsigned>& solution) {

    unsigned  n = avail.size() +1;
    std::vector<unsigned> tmp;
    tmp.reserve(n);

    solution[0] = start;


    unsigned current;

    for (int i = 1; i < n; i++)
    {

        double bestneibcost= infinite;
        std::vector<unsigned>::iterator bestneib = avail.end();

        for(auto it = avail.begin(); it!=avail.end(); it++) {
            auto availcpy = avail;
            availcpy.erase(std::find(availcpy.begin(), availcpy.end(), *it));
            nearest_neighbor(*it, availcpy, d, tmp);
            for(int j = 0; j<tmp.size(); j++) {
                solution[i+j] = tmp[j];
            }

            double cost = tsp_length(n, d, solution.data());
            if(cost <  bestneibcost) {
                bestneibcost = cost;
                bestneib = it;
            }
        }
        current = *bestneib;
        avail.erase(bestneib);

        solution[i] = current;
    }

    return tsp_length(n, d, solution.data());
}*/



#ifdef __cplusplus
extern "C" {
#endif

double tsp_local_greedy(unsigned n,                   /* Number of cities */
                 double **d,                    /* Distance matrix */
                 unsigned *solution) {/* -->Out Order of the cities */

    std::forward_list<unsigned> next;
    std::vector<unsigned> avail(n-2, 0);

    unsigned start1 = 0;
    unsigned start2 = 1;
    next.push_front(start2);
    next.push_front(start1);

    for (uint32_t i = 0; i < n-2; i++) { // for all except the two start cities
        avail[i] = 2 + i;
    }

    for (int i = 2; i < n; i++) // for the remaining "empty city places" in our route
    {

        double bestcost = infinite;
        std::vector<unsigned>::iterator bestcity = avail.end(); //best city to continue with
        std::forward_list<unsigned>::iterator bestplace = next.end(); //best place to insert the best city

        for (auto it = avail.begin(); it != avail.end(); it++) { //look at all cities that have not been placed

            //{auto it = avail.begin();   //Toggle comments in this line + line above to see non local greedy

            double dist_ins = infinite; //cost of inserting it into route
            std::forward_list<unsigned>::iterator bestplaceforit = next.end(); //best place to insert it

            //find best place to insert it
            for (auto j = next.begin(); j != next.end(); j++) { //for every point already in solution route (circle)
                unsigned jnext = next.front(); //the original next city of city j: the first city (if j = last city)
                if (std::next(j, 1) != next.end()) { //if j is no the last city...
                    jnext = *std::next(j, 1); //it's the next
                }
                double delta =  d[*j][*it] + d[*it][jnext] - d[*j][jnext]; //cost of inserting city it between j and jnext
                if (delta + epsilon < dist_ins) {
                    dist_ins = delta;
                    bestplaceforit = j;
                }
            }

            if (dist_ins < bestcost) {  // using this city would cost less than the best city we have looked at so far
                bestcost = dist_ins;
                bestcity = it;
                bestplace = bestplaceforit;
            }
        }

        next.insert_after(bestplace,
                          *bestcity); //insert the city bestcity after bestplace. city bestcity will therefore point to the next of bestplace
        avail.erase(bestcity);
    }






    /*
    for (unsigned i = 2; i < n; i++) { // for all except the two start cities
        double dist_ins = infinite;
        std::forward_list<unsigned>::iterator bestplace = next.end();

        for(auto j= next.begin(); j!= next.end(); j++) { //for every point already in solution route (circle)
            unsigned jnext= next.front(); //the original next city of city j: the first city (if j = last city)
            if(std::next(j,1)!=next.end()) { //if j is no the last city...
                jnext = *std::next(j,1); //it's the next
            }
            double delta = d[*j][i] + d[i][jnext] - d[*j][jnext]; //cost of inserting city i between j and jnext
            if (delta + epsilon < dist_ins)
            {
                dist_ins = delta;
                bestplace = j;
            }
        }

        next.insert_after(bestplace, i); //insert the city i after bestplace. city i will therefore point to the next of bestplace

    } */

    int i=0;
    for(auto j= next.begin(); j!= next.end(); j++) {
        solution[i++] = *j;
    }
    return tsp_length(n, d, solution);
}


#ifdef __cplusplus
};
#endif
