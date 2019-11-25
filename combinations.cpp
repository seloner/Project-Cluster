#include "combinations.h"
vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size)
{
    vector<cluster_curves> clusters;
    clusters = random_selection_curves(curves, clusterInfo.number_of_clusters, size);
    // lloydAssignmentClusterCurvesFunction(curves, clusters);

    lloydAssignmentClusterCurves(&clusters, &curves);
    for (unsigned int l = 0; l < clusters.size(); l++)
    {
        cout << "cluster: " << l << "    " << clusters[l].centerOfCluster->id << endl;
    }

    return clusters;
}
