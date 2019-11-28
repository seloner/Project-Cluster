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
void pushLshResultsToClusterVectors(vector_struct *vectors_array,vector<int> results,cluster_vectors *cluster);
void pushLshResultsToClusterCurves( vector<curve> *curves,vector<int> results,cluster_curves *cluster);

vector<cluster_curves> copy_clusters_curves(vector<cluster_curves> *clusters);
bool compare_curves_clusters(vector<cluster_curves> current, vector<cluster_curves> old);
vector<cluster_curves> kmeans_lloyd_pam_curve(vector<curve> curves, cluster clusterInfo, unsigned int size, curve *temp);
vector<cluster_vectors> kmeans_lloyd_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size);
vector<cluster_vectors> kmeans_lsh_pam_vector(vector_struct *vectors_array, cluster clusterInfo, unsigned int size);
#endif