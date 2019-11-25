#include "combinations.h"
vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size)
{
    vector<cluster_curves> clusters;

    clusters = random_selection_curves(curves, clusterInfo.number_of_clusters, size);
    // lloydAssignmentClusterCurves(&clusters, &curves);
    for (unsigned int l = 0; l < clusters.size(); l++)
    {
        cout << "cluster: " << l << "    " << clusters[l].centerOfCluster->id << endl;
    }

    return clusters;
}

vector<cluster_vectors> random_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size)
{
    vector<cluster_vectors> clusters;

    clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    for (unsigned int l = 0; l < clusters.size(); l++)
    {
        cout << "cluster: " << l << "  centre  " << clusters[l].centerOfCluster->id << endl;
        cout << "cluster: " << l << "  number of items  " << clusters[l].cluster_vectors.size() << endl;
    }
    return clusters;
}
