#include "combinations.h"
vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp)
{
    vector<cluster_curves> clusters;
    int counter = 0;
    clusters = random_selection_curves(&curves, clusterInfo.number_of_clusters, size);
    while (counter < 5)
    {
        lloydAssignmentClusterCurves(&curves, &clusters);
        for (int i = 0; i < clusters.size(); i++)
        {
            cout << "Cluster: " << i << "  centre: " << clusters[i].centerOfCluster->id << endl;
        }
        lloydAssignmentClusterCurvesUpdate(&clusters);
        counter++;
    }

    // for (unsigned int i = 0; i < clusters[0].cluster_curves.size(); i++)
    // {
    //     cout << " id   " << clusters[0].cluster_curves[i]->id << endl;
    // }
    // for (unsigned int i = 0; i < clusters[1].cluster_curves.size(); i++)
    // {
    //     cout << " id   " << clusters[1].cluster_curves[i]->id << endl;
    // }

    return clusters;
}

vector<cluster_vectors> random_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size)
{
    vector<cluster_vectors> clusters;
    int counter = 0;
    clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);
    while (counter < 10)
    {

        lloydAssignmentClusterVectors(vectors_array, &clusters, size);
        lloydAssignmentClusterVectorsUpdate(&clusters);
        // for (unsigned int l = 0; l < clusters.size(); l++)
        // {
        //     cout << "cluster: " << l << "  centre  " << clusters[l].centerOfCluster->id << endl;
        // }
        // counter++;
    }
    return clusters;
}

///k-means
vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp)
{
    vector<cluster_curves> clusters;
    clusters = k_means_curve(&curves, clusterInfo.number_of_clusters, size);
    lloydAssignmentClusterCurves(&curves, &clusters);
    for (int i = 0; i < clusters.size(); i++)
    {
        cout << endl
             << "Cluster: " << i << " >>" << endl;
        for (int j = 0; j < clusters[i].cluster_curves.size(); j++)
        {
            cout << clusters[i].cluster_curves[j]->id << ", ";
        }
        cout << endl;
    }
    return clusters;
}

vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size)
{
    vector<cluster_vectors> clusters;

    clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);
    lloydAssignmentClusterVectors(vectors_array, &clusters, size);
    lloydAssignmentClusterVectorsUpdate(&clusters);

    return clusters;
}