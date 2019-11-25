#include "assignment.h"

void lloydAssignmentClusterCurves(vector<cluster_curves> *clusters, vector<curve> *curves)
{
    double distance;
    int min_index, min_distance;
    {
        for (unsigned int i = 0; i < curves->size(); i++)
        {
            dtw(curves->at(clusters->at(0).centerOfCluster->id), curves->at(clusters->at(0).centerOfCluster->id));
            cout << "cluster centre " << clusters->at(0).centerOfCluster->id << endl;
        }
        // {
        //     for (unsigned int k = 0; k < 1; k++)
        //     {
        //         // distance = dtw(curves->at(i), curves->at(i));
        //         //set first as min
        //         //     if (k == 0)
        //         //     {
        //         //         min_distance = distance;
        //         //         min_index = k;
        //         //     }
        //         //     else
        //         //     {
        //         //         //update min if new distance is smaller
        //         //         if (distance < min_distance)
        //         //         {
        //         //             min_distance = distance;
        //         //             min_index = k;
        //         //         }
        //         //     }
        //         // }
        //         //push curve to the closest cluster
        //         // cout << "Min Index" << min_index << endl;
        //         // clusters->at(min_index).cluster_curves.push_back(&((*curves)[i]));
        //     }
        // }
    }
}

void lloydAssignmentClusterVectors(vector_struct *vectors_array, vector<cluster_vectors> *clusters, unsigned int size)
{
    double distance;
    int min_index, min_distance;
    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned int k = 0; k < clusters->size(); k++)
        {
            distance = manhattanDistance(clusters->at(k).centerOfCluster->vectors, vectors_array[i].vectors);
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
        clusters->at(min_index).cluster_vectors.push_back(&(vectors_array[i]));
    }
}
