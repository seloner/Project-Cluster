#include "assignment.h"

void lloydAssignmentClusterCurves(unsigned int size, vector<cluster_curves> &curves_clusters)
{
    double distance;
    int min_index, min_distance;
    {
        // for (unsigned int i = 0; i < size; i++)
        // {
        //     dtw(curves[i], curves[i]);
        // }

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
                if (distance < min_distance)
                {
                    //cout << "VIMA 5"<<endl;
                    min_distance = distance;
                    min_index = k;
                }
            }
            //cout << "VIMA 6"<<endl;
        }

        clusters->at(min_index).cluster_vectors.push_back(&(vectors_array[i]));
    }
}

void test(vector<curve> curves)
{
}