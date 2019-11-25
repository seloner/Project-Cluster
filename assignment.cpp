#include "assignment.h"

void lloydAssignmentClusterCurvesFunction(vector<curve> curves, vector<cluster_curves> *curves_clusters)
{
    //ta prwta kentra do8ikan ston lloyd
    double distance;
    int min_index, min_distance;
    for (unsigned int i = 0; i < curves.size(); i++)
    {
        for (unsigned int k = 0; k < (*curves_clusters).size(); k++)
        {
            distance = dtw(curves[i], (*(curves_clusters->at(k).centerOfCluster)));
            //set first as min
            if (k == 0)
            {
                min_distance = distance;
                min_index = k;
            }
            else
            {
                //update min if new distance is smaller
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = k;
                }
            }
        }
        //push curve to the closest cluster
        curves_clusters->at(min_index).cluster_curves.push_back(&curves[i]);
    }
}
