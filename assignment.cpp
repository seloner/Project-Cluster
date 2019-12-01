#include "assignment.h"

void lloydAssignmentClusterCurves(vector<curve> *curves, vector<cluster_curves> *curves_clusters,  ofstream &outputFile)
{
    double distance;
    int min_index, min_distance;

    for (unsigned int i = 0; i < curves->size(); i++)
    {
        for (unsigned int k = 0; k < curves_clusters->size(); k++)
        {
            distance = dtw(curves->at(i), *(curves_clusters->at(k).centerOfCluster));
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
        curves_clusters->at(min_index).cluster_curves.push_back(&curves->at(i));
    }
     //Silhouette
    for(int loop=0; loop<curves_clusters->size(); loop++)
    {
        outputFile << "CLUSTER-"<<loop+1<<"{" <<"size: "<< curves_clusters->at(loop).cluster_curves.size()<<", centroid: "<< curves_clusters->at(loop).centerOfCluster->id << "}" << endl;
    }
    outputFile << endl;   
}

void lloydAssignmentClusterVectors(vector_struct *vectors_array, vector<cluster_vectors> *clusters, unsigned int size, ofstream &outputFile)
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
                    min_distance = distance;
                    min_index = k;
                }
            }
        }
        clusters->at(min_index).cluster_vectors.push_back(&(vectors_array[i]));
    }
    //Silhouette
    for(int loop=0; loop<clusters->size(); loop++)
    {
        outputFile << "CLUSTER-"<<loop+1<<"{" <<"size: "<< clusters->at(loop).cluster_vectors.size()<<", centroid: "<< clusters->at(loop).centerOfCluster->id << "}" << endl;
    }
    outputFile << endl;
}
