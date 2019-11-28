#ifndef combinations_H_
#define combinations_H_
#include <iostream>
#include "assignment.h"
#include "initialization.h"
#include "update.h"
#include "lsh.h"
using namespace std;
vector<cluster_curves> random_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp);
vector<cluster_vectors> random_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size);
vector<cluster_vectors> copy_clusters_vector(vector<cluster_vectors> *clusters);
//returns 0 if same clusters ,1 if different  clusters
bool compare_vectors_clusters(vector<cluster_vectors> current, vector<cluster_vectors> old);
vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp);
vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size);
vector<cluster_vectors> kmeans_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size);
#endif