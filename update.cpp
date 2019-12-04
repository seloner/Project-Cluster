#include "update.h"
// void lloydAssignmentClusterCurvesUpdate(vector<curve> curves, vector<clusterarraycurves> &lloydAssignmentClusterArray, unsigned int threshold = 5);
void lloydAssignmentClusterCurvesUpdate(vector<cluster_curves> *lloydAssignmentClusterArray)
{

    double sum = 0, min_distance = 0;
    curve *new_centre;
    unsigned int counter = 0;
    for (unsigned j = 0; j < lloydAssignmentClusterArray->size(); j++)
    {
        for (unsigned int i = 0; i < lloydAssignmentClusterArray->at(j).cluster_curves.size(); i++)
        {
            for (unsigned int k = 0; k < lloydAssignmentClusterArray->at(j).cluster_curves.size(); k++)
            {
                sum += dtw(*(lloydAssignmentClusterArray->at(j).cluster_curves[i]), *(lloydAssignmentClusterArray->at(j).cluster_curves[k]));
            }
            if (i == 0)
            {
                min_distance = sum;
                new_centre = lloydAssignmentClusterArray->at(j).cluster_curves[i];
            }
            else
            {
                if (sum < min_distance)
                {
                    min_distance = sum;
                    new_centre = lloydAssignmentClusterArray->at(j).cluster_curves[i];
                }
            }
            sum = 0;
        }
        cout << "new centre: " << new_centre->id << endl;
        lloydAssignmentClusterArray->at(j).centerOfCluster = new_centre;
    }
}

void lloydAssignmentClusterVectorsUpdate(vector<cluster_vectors> *lloydAssignmentClusterArray)
{
    double sum = 0, min_distance = 0;
    vector_struct *new_centre;
    for (unsigned j = 0; j < lloydAssignmentClusterArray->size(); j++)
    {
        for (unsigned int i = 0; i < lloydAssignmentClusterArray->at(j).cluster_vectors.size(); i++)
        {
            for (unsigned int k = 0; k < lloydAssignmentClusterArray->at(j).cluster_vectors.size(); k++)
            {
                sum += manhattanDistance(lloydAssignmentClusterArray->at(j).cluster_vectors[i]->vectors, lloydAssignmentClusterArray->at(j).cluster_vectors[k]->vectors);
            }
            if (i == 0)
            {
                min_distance = sum;
                new_centre = lloydAssignmentClusterArray->at(j).cluster_vectors[i];
            }
            else
            {
                if (sum < min_distance)
                {
                    min_distance = sum;
                    new_centre = lloydAssignmentClusterArray->at(j).cluster_vectors[i];
                }
            }
            sum = 0;
        }
        cout << "new centre: " << new_centre->id << endl;
        lloydAssignmentClusterArray->at(j).centerOfCluster = new_centre;
    }
}
