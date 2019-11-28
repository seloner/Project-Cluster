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
    vector<cluster_vectors> old_clusters;
    unsigned int THRESHOLD = 100, counter = 0;
    clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);
    //arxikopoihsh old cluster (thelei allagi mporei h random na epistrepsei ta idia kentra )
    old_clusters = random_selection_vector(vectors_array, clusterInfo.number_of_clusters, size);

    while (compare_vectors_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
    {
        old_clusters = copy_clusters_vector(&clusters);
        lloydAssignmentClusterVectors(vectors_array, &clusters, size);
        lloydAssignmentClusterVectorsUpdate(&clusters);
        counter++;
    }
    return clusters;
}

vector<cluster_vectors> copy_clusters_vector(vector<cluster_vectors> *clusters)
{
    vector<cluster_vectors> new_clusters;
    for (unsigned int i = 0; i < clusters->size(); i++)
    {
        new_clusters.push_back(clusters->at(i));
    }
    return new_clusters;
}

bool compare_vectors_clusters(vector<cluster_vectors> current, vector<cluster_vectors> old)
{
    bool flag = 0;
    for (unsigned int i = 0; i < current.size(); i++)
    {
        if (current[i].centerOfCluster != old[i].centerOfCluster)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

///k-means
vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size)
{
    vector<cluster_vectors> clusters;
    vector<cluster_vectors> old_clusters;
    unsigned int THRESHOLD = 100, counter = 0;
    clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);
    //arxikopoihsh old cluster (thelei allagi mporei h random na epistrepsei ta idia kentra )
    old_clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);

    while (compare_vectors_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
    {
        old_clusters = copy_clusters_vector(&clusters);
        for (unsigned int i = 0; i < old_clusters.size(); i++)
        {
            cout << "cluster old  " << i << "  centre     " << old_clusters[i].centerOfCluster->id << endl;
        }
        lloydAssignmentClusterVectors(vectors_array, &clusters, size);
        lloydAssignmentClusterVectorsUpdate(&clusters);
        counter++;
    }
    return clusters;
}

vector<cluster_vectors> kmeans_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size)
{
    vector<cluster_vectors> clusters;
    vector<vector<vector<int>>> siarrays;
    double w;
    int dimension = vectors_array[0].vectors.size();
    clusters = k_means_vector(vectors_array, clusterInfo.number_of_clusters, size);
    // // w = calculateW(size, vectors_array);
    w = 5376.42;
    for (unsigned i = 0; i < clusterInfo.number_of_vector_hash_tables; i++)
    {
        siarrays.push_back(generateSi(clusterInfo.number_of_vector_hash_functions, w, dimension));
    }
    // {
    //create a grid vectors array and match evey curve to the L grid

    //generate si arrays
    return clusters;
}
vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp)
{
    vector<cluster_curves> clusters;
    vector<cluster_curves> old_clusters;
    unsigned int THRESHOLD = 100, counter = 0;
    clusters = k_means_curve(&curves, clusterInfo.number_of_clusters, size);
    //arxikopoihsh old cluster (thelei allagi mporei h random na epistrepsei ta idia kentra )
    old_clusters = k_means_curve(&curves, clusterInfo.number_of_clusters, size);

    while (compare_curves_clusters(clusters, old_clusters) == true && counter < THRESHOLD)
    {
        old_clusters = copy_clusters_curves(&clusters);
        for (unsigned int i = 0; i < old_clusters.size(); i++)
        {
            cout << "cluster old  " << i << "  centre     " << old_clusters[i].centerOfCluster->id << endl;
        }
        lloydAssignmentClusterCurves(&curves, &clusters);
        lloydAssignmentClusterCurvesUpdate(&clusters);
        counter++;
    }
    return clusters;
}

vector<cluster_curves> copy_clusters_curves(vector<cluster_curves> *clusters)
{
    vector<cluster_curves> new_clusters;
    for (unsigned int i = 0; i < clusters->size(); i++)
    {
        new_clusters.push_back(clusters->at(i));
    }
    return new_clusters;
}

bool compare_curves_clusters(vector<cluster_curves> current, vector<cluster_curves> old)
{
    bool flag = 0;
    for (unsigned int i = 0; i < current.size(); i++)
    {
        if (current[i].centerOfCluster != old[i].centerOfCluster)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
