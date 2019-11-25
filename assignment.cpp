#include "assignment.h"

void lloydAssignmentClusterCurves(vector<cluster_curves> *clusters, vector<curve> *curves)
{
    double distance;
    int min_index, min_distance;
    for (unsigned int i = 0; i < curves->size(); i++)
    {
        for (unsigned int k = 0; k < 1; k++)
        {
            // distance = dtw(curves->at(i), curves->at(i));
            cout << "i" << i << "    " << fixed << distance << endl;
            //set first as min
            //     if (k == 0)
            //     {
            //         min_distance = distance;
            //         min_index = k;
            //     }
            //     else
            //     {
            //         //update min if new distance is smaller
            //         if (distance < min_distance)
            //         {
            //             min_distance = distance;
            //             min_index = k;
            //         }
            //     }
            // }
            //push curve to the closest cluster
            // cout << "Min Index" << min_index << endl;
            // clusters->at(min_index).cluster_curves.push_back(&((*curves)[i]));
        }
    }
}